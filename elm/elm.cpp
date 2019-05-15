#include "elm.hpp"
float getticks()
{
	struct timespec ts;
	if(clock_gettime(CLOCK_MONOTONIC, &ts) < 0)
		return -1.0f;
	return ts.tv_sec + 1e-9f*ts.tv_nsec;
}

vector<int> train_labels_ori;
int flag = 0;                         // 没有人脸?
int N_test;
PCA pca;
LDA lda;

//此路径后面不能加“/”       不能写成："/home/huoda/Desktop/100/"
string trainfile_path ; //路径

vector<int> trainingLabels;


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

/* MatrixXd ELM_in_ELM_face_training_matrix_from_files(){
	cout << "Loading train Data..." << endl;
	Mat trainingImages;
	getFaces_train(trainfile_path, trainingImages, trainingLabels);
	MatrixXd feature(trainingImages.rows, trainingImages.cols); //创建新的矩阵
	cout << "Number of training images:" << trainingImages.rows << endl; //
	// n = trainingImages.cols; // number of features //输出特征值
	N = trainingImages.rows;
	n=N;//在PCA中 输出特征的数量 我们取 PCA的位数 一般不大于2500 所以我们取PCA 维数为N
	// N 时训练人数 PCA的位数 就是这个个数，一般人脸照片数不会超过 2500

	pca(trainingImages, Mat(), CV_PCA_DATA_AS_ROW, N);
	// PCA pca2(trainingImages, Mat(), CV_PCA_DATA_AS_ROW, N);
	// pca=pca2;
	Mat dst = pca.project(trainingImages);//映射新空间
	// Mat eigenvectors = pca.eigenvectors.clone();//特征向量矩阵
	// cv2eigen(eigenvectors, feature);     //转化/
	cv2eigen(dst, feature);     //转化
	// cv2eigen(trainingImages, feature);     //转化
	return feature;
} */

MatrixXd ELM_in_ELM_face_training_matrix_from_files(){
	cout << "Loading train Data..." << endl;
	Mat trainingImages;
	getFaces_train(trainfile_path, trainingImages, trainingLabels);
	// MatrixXd feature(trainingImages.rows, trainingImages.cols); //创建新的矩阵
	// cv2eigen(trainingImages, feature);     //转化
	cout << "Number of training images:" << trainingImages.rows << endl; //
	// n = trainingImages.cols; // number of features //输入矩阵 单个样本 特征值 个数
	N = trainingImages.rows;
	n=N;//ELM
	pca(trainingImages, Mat(), CV_PCA_DATA_AS_ROW, N);
	Mat dst = pca.project(trainingImages);//映射新空间	
	MatrixXd feature(trainingImages.rows, N); 
	cv2eigen(dst, feature); 
	return feature;
}
MatrixXd ELM_in_ELM_face_testing_matrix_from_files(vector<Mat> mat_v){ //重载 有参数Mat

	Mat testingImages;
	getFaces_test(mat_v, testingImages);
	// MatrixXd feature1(testingImages.rows, testingImages.cols);
	// cv2eigen(testingImages, feature1);
	N_test = testingImages.rows;
	Mat dst = pca.project(testingImages);//映射新空间
	MatrixXd feature1(testingImages.rows, N);
	cv2eigen(dst, feature1); 
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
// clock_t start,end;
// start=clock();	
float t = getticks();
	ELM_in_ELM(feature, W, b, beta);
t = getticks() - t;
if(t!=0)    cout<<" elm	triaining    time     "<<t*1000<<"ms"<<endl;
// end=clock();
// double endtime=(double)(end-start)/CLOCKS_PER_SEC;
// cout<<"elm train time:	"<<endtime<<"s"<<endl;		//s为单位
}
// ELM testing
void ELM_testing(MatrixXd feature1, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	MatrixXd out_all;
	out_all = MatrixXd::Zero(N_test, m * model_num);
// clock_t start,end;
// start=clock();	
float t = getticks();
	MatrixXd tem[model_num];
    #pragma omp parallel for num_threads(2)
	for(int i = 0; i < model_num; i++){
		MatrixXd R,Tem,H;
		R = -feature1 * W[i] + MatrixXd::Ones(N_test, 1) * b[i];
		Tem = R.array().exp() + 1;
		H = Tem.array().inverse();
		tem[i]=H;
		//out_all.block(0, m * i, N_test, m) = H * beta[i];
	}
	for(int i = 0; i < model_num; i++){
		out_all.block(0, m * i, N_test, m) = tem[i] * beta[i];
	}
	output = out_all * F;
t = getticks() - t;
if(t!=0)    cout<<" elm	test    time     "<<t*1000<<"ms"<<endl;
// end=clock();
// double endtime=(double)(end-start)/CLOCKS_PER_SEC;
// cout<<"elm test time:	"<<endtime*1000<<"ms"<<endl;		//s为单位
}
