#include "elm.hpp"
vector<int> train_labels_ori;


int flag = 0;                         // 没有人脸?
int L = 600;                          //隐层节点数
int m = 50;                           //训练集以及测试集人数		//后期会自动更新m为训练集文件夹的数量
int model_num = 5;                    //子ELM模型的数量

//此路径后面不能加“/”       不能写成："/home/huoda/Desktop/100/"
string trainfile_path ; //路径

vector<int> trainingLabels;

int N;
int n;
int N_test;
MatrixXd F, output, T;

template<typename _Tp>
vector<_Tp> convertMat2Vector(const Mat &mat)
{
	return (vector<_Tp>)(mat.reshape(1, 1));//通道数不变，按行转为一行
}

std::vector<float> extract_feature(Mat src){

	Mat dst;
	cvtColor(src, dst, COLOR_BGR2GRAY);
	std::vector<float> feature;
	for(int i = 0; i < src.rows; i++)
		for(int j = 0; j < src.cols; j++)
			feature.push_back(dst.at<uchar>(i, j));
	return feature;

}

void getFiles_train(string path, vector<string> & files){
	m=0;
	int person_id = 0;
	struct dirent * ptr, * ptr1;
	DIR * dir, * dir1;
	dir = opendir(path.c_str());         // path如果是文件夹 返回NULL
	while((ptr = readdir(dir)) != NULL)  //读取列表
	{
		// if(ptr->d_name[0] == '.' || ptr->d_name ==  "Thumbs.db")      //去掉当前文件夹目录和
			                 // Thumbs.db这个windows下保存图片就会产生的文件
		if(strncmp(ptr->d_name, ".", 1) == 0)
			continue;
		if(ptr->d_type == DT_DIR){ 
			m++;
			string ss = path + '/' + ptr->d_name +	'/'; //二级文件夹目录   //这TM有问题 path后面少了一个'/'
			dir1 = opendir(ss.c_str());
			while((ptr1 = readdir(dir1)) != NULL){
					// if(ptr1->d_name[0] == '.' || ptr1->d_name == "Thumbs.db")
					if(strncmp(ptr1->d_name, ".", 1) == 0)
					continue;
				
				string sss = ss + ptr1->d_name; //
				files.push_back(sss);           //返回图片路径
				train_labels_ori.push_back(person_id); // vector<int> train_labels_ori;添加标签
			}
			closedir(dir1);
			person_id++; //下一个文件夹 下一个人的标签++			
		}
	}
	closedir(dir);
}

cv::Mat face_align(const char * filename){

	Mat pic = imread(filename);
	flag = 0;
	if(pic.empty())
	{
		flag = 1;
		cout << "pic  empty" << endl;
		return cv::Mat::zeros(50, 50, CV_8UC3);
	}
	resize(pic, pic, cv::Size(50, 50), 0, 0, INTER_LINEAR);
	return pic;
}
void getFaces_train(string filePath, Mat & trainingImages,vector<int> & trainingLabels){
	vector<string> files;
	getFiles_train(filePath, files);
	int number = files.size();
	for(int i = 0; i < number; i++){
		Mat SrcImage = face_align(files[i].c_str()); //读取图片
		if(flag){
			flag = 0;
			cout << "No face in this file:" << files[i].c_str() << endl;
			continue;
		}
		resize(SrcImage, SrcImage, cv::Size(50, 50));
		Mat SrcImage1 = Mat(extract_feature(SrcImage), true);

		Mat SrcImage2 = SrcImage1.t();
		trainingImages.push_back(SrcImage2);
		trainingLabels.push_back(train_labels_ori.at(i));
	}
}

void getFaces_test(vector<Mat> mat_v, Mat & trainingImages){
	for(vector<Mat>::iterator iter = mat_v.begin(); iter != mat_v.end(); iter++){
		// imwrite("alignment"+to_string(iter-mat_v.begin())+".jpg",(*iter));
		Mat SrcImage;
		resize((*iter), SrcImage, cv::Size(50, 50));
		Mat SrcImage1 = Mat(extract_feature(SrcImage), true);

		Mat SrcImage2 = SrcImage1.t();
		trainingImages.push_back(SrcImage2);
	}
}
template<typename _Matrix_Type_>
bool pseudoInverse(
	const _Matrix_Type_ & a, _Matrix_Type_ & result,
	double epsilon =
		std::numeric_limits<typename _Matrix_Type_::Scalar>::epsilon()){
	Eigen::JacobiSVD<_Matrix_Type_> svd =
		a.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV);
	if(a.rows() < a.cols()){
		typename _Matrix_Type_::Scalar tolerance =
			epsilon * std::max(a.cols(), a.rows()) *
			svd.singularValues().array().abs()(0);
		result = svd.matrixV() *
				 (svd.singularValues().array().abs() > tolerance)
				 .select(svd.singularValues().array().inverse(), 0)
				 .matrix()
				 .asDiagonal() *
				 svd.matrixU().adjoint();
	}
	// return false;
	else {
		typename _Matrix_Type_::Scalar tolerance =
			epsilon * std::max(a.cols(), a.rows()) *
			svd.singularValues().array().abs().maxCoeff();
		//  Eigen::JacobiSVD< _Matrix_Type_ > svd =
		//  a.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV); typename
		//  _Matrix_Type_::Scalar tolerance = epsilon * std::max(a.cols(),
		//  a.rows()) * svd.singularValues().array().abs().maxCoeff();
		result = svd.matrixV() *
				 ((svd.singularValues().array().abs() > tolerance)
				  .select(svd.singularValues().array().inverse(), 0))
				 .matrix()
				 .asDiagonal() *
				 svd.matrixU().adjoint();
	}
	return true;
}

void ELM_basic(MatrixXd & feature, MatrixXd & W, MatrixXd & b_1, MatrixXd & beta, MatrixXd & output_basic){
	MatrixXd b, R, Tem, H;
	W = MatrixXd::Random(n, L);
	b_1 = MatrixXd::Random(1, L);
	b = MatrixXd::Ones(N, 1) * b_1;
	R = -feature * W + b;
	Tem = R.array().exp() + 1;
	H = Tem.array().inverse();

	MatrixXd result(L, N);
	pseudoInverse(H, result);
	beta = result * T;
	output_basic = H * beta;
}
void ELM_in_ELM(MatrixXd & feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	MatrixXd Hg, temp_out;
	Hg = MatrixXd::Zero(N, m * model_num);
	for(int i = 0; i < model_num; i++){
		ELM_basic(feature, W[i], b[i], beta[i], temp_out);
		Hg.block(0, m * i, N, m) = temp_out;
	}
	MatrixXd Hg1;
	pseudoInverse(Hg, Hg1);
	F = Hg1 * T;
}

MatrixXd ELM_in_ELM_face_training_matrix_from_files(){

	cout << "Loading train Data..." << endl;

	Mat trainingImages;
	getFaces_train(trainfile_path, trainingImages, trainingLabels);
	MatrixXd feature(trainingImages.rows, trainingImages.cols); //创建新的矩阵
	cv2eigen(trainingImages, feature);     //转化
	cout << "Number of training images:" << trainingImages.rows << endl; //
	n = trainingImages.cols; // number of features //输出特征值
	N = trainingImages.rows;
	return feature;
}
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(vector<Mat> mat_v){ //重载 有参数Mat

	Mat testingImages;
	getFaces_test(mat_v, testingImages);
	MatrixXd feature1(testingImages.rows, testingImages.cols);
	cv2eigen(testingImages, feature1);
	N_test = testingImages.rows;
	return feature1;
}

MatrixXd generate_training_labels(){
	MatrixXd temp_T;
	// generate testing labels
	temp_T = MatrixXd::Zero(N, m);
	for(int i = 0; i < N; i++){
		for(int jj = 0; jj < m; jj++){
			if(trainingLabels.at(i) == jj)
				temp_T(i, jj) = 1;
			else
				temp_T(i, jj) = 0;
		}
	}
	return temp_T;
}

// ELM training
void ELM_training(MatrixXd feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	// TickMeter tm;
	// tm.start();
	ELM_in_ELM(feature, W, b, beta);
	// tm.stop();
	// std::cout << "Training time:    " << tm.getTimeSec() << "  s" << endl;
}
// ELM testing
void ELM_testing(MatrixXd feature1, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	MatrixXd out_all, R, Tem, H;
	out_all = MatrixXd::Zero(N_test, m * model_num);
	// TickMeter tm;
	// tm.start();
	for(int i = 0; i < model_num; i++){
		R = -feature1 * W[i] + MatrixXd::Ones(N_test, 1) * b[i];
		Tem = R.array().exp() + 1;
		H = Tem.array().inverse();
		out_all.block(0, m * i, N_test, m) = H * beta[i];
	}
	output = out_all * F;
	// tm.stop();
	// std::cout << "Testing time:    " << tm.getTimeSec() *1000<< "  ms" << endl;
}
