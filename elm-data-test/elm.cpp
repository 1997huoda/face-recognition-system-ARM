#include "elm.hpp"
vector<int> train_labels_ori;
vector<int> test_labels_ori;

int k = 1;
int flag = 0;                         // 没有人脸?
// MatrixXd T;                           //存放训练集标签
int L = 600;                          //隐层节点数
int m = 50;                           //训练集以及测试集人数		//后期会自动更新m为训练集文件夹的数量
int model_num = 5;                    //子ELM模型的数量

int training_face_num_per_person = 11; //训练集中每个人的人脸数
int testing_face_num_per_person = 10;  // 测试集中每个人的人脸数
//此路径后面不能加“/”       不能写成："/home/huoda/Desktop/100/"
string trainfile_path = "/home/huoda/Desktop/YALE"; //路径
string testfile_path = "/home/huoda/Desktop/test";

Mat trainingImages;
Mat testingImages;
vector<int> trainingLabels;
vector<int> testingLabels;
double gamma_value=0.2f;
double accuracy[200];
int mode = 0;
int pca_num=2000;
int N;
int n;
int N_test;
int all_num =0;
MatrixXd F, output, T, temp_T;
// MatrixXd W[model_num], b[model_num], beta[model_num];


/******extract_feature: put one image into a vector(convert to gray image
 * firstly)*****/
/*********************************************/
template<typename _Tp>
vector<_Tp> convertMat2Vector(const Mat &mat)
{
	return (vector<_Tp>)(mat.reshape(1, 1));//通道数不变，按行转为一行
}

std::vector<float> extract_feature(Mat src){
	Mat dst;
	if(src.channels()==3){
	cvtColor(src, dst, COLOR_BGR2GRAY);
	}	else {
		dst=src;
	}
	std::vector<float> feature;
	for(int i = 0; i < src.rows; i++)
		for(int j = 0; j < src.cols; j++)
			feature.push_back(dst.at<uchar>(i, j));
	return feature;
	//不知道为什么 YALE 数据库 PCA 炸了
	// Mat SrcImage1 = Mat(feature, true);
	// TickMeter tm;
	// tm.start();
	// PCA pca(SrcImage1,Mat(),CV_PCA_DATA_AS_COL,pca_num);//按照圆的面积参数应该是0.785 
	// Mat get_back = pca.project(SrcImage1);//映射新空间
	// tm.stop();
	// std::cout << "PCA time:    " << tm.getTimeSec() *1000<< "  ms" << endl;
	// std::vector<float> back = convertMat2Vector<float>(get_back);
	// return back;
}

/**time**/
// double difftimeval(const struct timeval *start, const struct timeval *end) {
//     double d;
//     time_t s;
//     suseconds_t u;
//     s = start->tv_sec - end->tv_sec;
//     u = start->tv_usec - end->tv_usec;
//     d = s;
//     d *= 1000000.0;
//     d += u;
//     return d;
// }

/**********************************************/
/**getFiles: put the filename in all subfolders in the path**/ //(just two
                                                               // cascades)
/**********************************************/
/*void getFiles( string path, vector<string>& files )
   {
     struct dirent *ptr,*ptr1;
     DIR *dir,*dir1;
    dir=opendir(path.c_str());
    while((ptr=readdir(dir))!=NULL)
    {
        if(ptr->d_name[0] == '.'||ptr->d_name=="Thumbs.db")
            continue;
        string ss=path+'/'+ptr->d_name+'/';
        dir1=opendir(ss.c_str());
        while((ptr1=readdir(dir1))!=NULL)
        {
        if(ptr1->d_name[0] == '.'||ptr1->d_name[0]=='T')
            continue;
        string sss=ss+ptr1->d_name;
        files.push_back(sss);
        }
        closedir(dir1);
    }
    closedir(dir);
   } */
void getFiles_train(string path, vector<string> & files){
	m=0;
	int person_id = 0;
	struct dirent * ptr, * ptr1;
	DIR * dir, * dir1;
	dir = opendir(path.c_str());         // path如果是文件夹 返回NULL
	while((ptr = readdir(dir)) != NULL)  //读取列表
	{
		if(ptr->d_name[0] == '.' ||  ptr->d_name ==   "Thumbs.db")      //去掉当前文件夹目录和
			                 // Thumbs.db这个windows下保存图片就会产生的文件
			continue;
		if(ptr->d_type == DT_DIR){ 
			m++;
			string ss = path + '/' + ptr->d_name +	'/'; //二级文件夹目录   //这TM有问题 path后面少了一个'/'
			dir1 = opendir(ss.c_str());
			while((ptr1 = readdir(dir1)) != NULL){
				if(ptr1->d_name[0] == '.' || ptr1->d_name == "Thumbs.db")
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

void getFiles_test(string path, vector<string> & files){
	int count_test = 0;
	int person_id = 0;
	struct dirent * ptr, * ptr1;
	DIR * dir, * dir1;
	dir = opendir(path.c_str());
	while((ptr = readdir(dir)) != NULL)  //一级目录
	{
		if(ptr->d_name[0] == '.' || ptr->d_name == "Thumbs.db")
			continue;
		string ss = path + '/' + ptr->d_name + '/';
		dir1 = opendir(ss.c_str());
		while((ptr1 = readdir(dir1)) != NULL)  //二级目录
		{
			//          if(ptr1->d_name[0] ==
			// '.'||ptr1->d_name=="Thumbs.db"||count_test<training_face_num_per_person)
			//          {
			//              if(count_test>=training_face_num_per_person)
			//                  cout<<"***"<<ss+ptr1->d_name<<endl;
			//              count_test++;
			//              continue;
			//          }

			if(ptr1->d_name[0] == '.' || ptr1->d_name == "Thumbs.db"){
				cout << "***" << ss + ptr1->d_name << endl;
				continue;
			}

			string sss = ss + ptr1->d_name;
			files.push_back(sss);
			count_test++;
			test_labels_ori.push_back(person_id);
			if(count_test >=   (testing_face_num_per_person))  //(training_face_num_per_person+testing_face_num_per_person))
			{
				count_test = 0;
				break;
			}
		}
		closedir(dir1);
		person_id++;
	}
	// cout<<test_labels_ori<<endl;
	closedir(dir);
}

/**********************************************/
/**getTrainfile: put all the faces in filepath into Mat trainingImages and
 * gengrate labels into trainingLabels automatically**/
/**********************************************/
/*void getFaces(string filePath, Mat& trainingImages, vector<int>&
   trainingLabels, int faces_per_person)
   {
     vector<string> files;
     getFiles(filePath, files );
     int number = files.size();
     for (int i = 0;i <number;i++)
     {
        Mat  SrcImage=face_align(files[i].c_str());
        if(flag)
        {
                flag=0;
                cout<<"No face in this file:"<<files[i].c_str()<<endl;
                continue;
        }
        resize(SrcImage,SrcImage,cv::Size(100,100));
        Mat SrcImage1= Mat(extract_feature(SrcImage),true);
        Mat SrcImage2=SrcImage1.t();
        trainingImages.push_back(SrcImage2);
        trainingLabels.push_back(i/faces_per_person);
     }
   }*/
void getFaces_train(string filePath, Mat & trainingImages,
					vector<int> & trainingLabels){
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
		// Mat SrcImage1= Mat(extract_feature_LBP(SrcImage,50,50),true);
		Mat SrcImage2 = SrcImage1.t();
		// PCA pca(SrcImage2 ,Mat(),CV_PCA_DATA_AS_ROW,pca_num);//按照圆的面积参数应该是0.785 
		// Mat get_back = pca.project(SrcImage2);//映射新空间
		// trainingImages.push_back(get_back);
		trainingImages.push_back(SrcImage2);
		trainingLabels.push_back(train_labels_ori.at(i));
	}
}

void getFaces_test(string filePath, Mat & trainingImages,	   vector<int> & trainingLabels){
	vector<string> files;
	getFiles_test(filePath, files);
	int number = files.size();
	cout << "TEST start num: " << number << endl;
	cout << test_labels_ori.size() << ',' << number << endl;
	for(int i = 0; i < number; i++){
		Mat SrcImage = face_align(files[i].c_str());
		if(flag){
			flag = 0;
			cout << "No face in this file:" << files[i].c_str() << endl;
			continue;
		}
		resize(SrcImage, SrcImage, cv::Size(50, 50));
		Mat SrcImage1 = Mat(extract_feature(SrcImage), true);
		// Mat SrcImage1= Mat(extract_feature_LBP(SrcImage,50,50),true);
		Mat SrcImage2 = SrcImage1.t();
		// PCA pca(SrcImage2 ,Mat(),CV_PCA_DATA_AS_ROW,pca_num);//按照圆的面积参数应该是0.785 
		// Mat get_back = pca.project(SrcImage2);//映射新空间
		// trainingImages.push_back(get_back);
		trainingImages.push_back(SrcImage2);
		trainingLabels.push_back(test_labels_ori.at(i));
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
		result = svd.matrixV() *(svd.singularValues().array().abs() > tolerance) .select(svd.singularValues().array().inverse(), 0).matrix() .asDiagonal() * svd.matrixU().adjoint();
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

void init_stdio(){
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
}
/*
   void load_data(vector<vector<double>> &traindata, string filename) {
        ifstream trainfile;
        trainfile.open(filename);
        //cout<<"Loading traindata..."<<endl;
        vector<double> rowdata;
        double temp[10000];
        while (!trainfile.eof()) {
                for (int i = 0; i < 10001; i++) {
                        trainfile >> temp[i];
                        cout<<temp[i]<<"\t";
                        rowdata.push_back(temp[i]);
                }
                cout<<endl;
                traindata.push_back(rowdata);
                rowdata.erase(rowdata.begin(), rowdata.end());
        }
        trainfile.close();
        //cout<<"traindata.size="<<traindata.size()<<"*"<<2<<endl;
   }

   void extract_data(vector<vector<double>> &traindata, MatrixXd &feature, VectorXd
   &label) { for (unsigned long i = 0; i < traindata.size(); i++) { for (unsigned
   long j = 0; j < traindata[0].size(); j++) { if (j < traindata[0].size()-1)
                                feature(i, j) = traindata[i][j];
                        else
                                label(i) = traindata[i][j];
                }
        }
   }
 */

#if 1
void ELM_basic(MatrixXd & feature, MatrixXd & W, MatrixXd & b_1, MatrixXd & beta, MatrixXd & output, int L, int m, int n, int N){
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
	output = H * beta;
}
void ELM_in_ELM(MatrixXd & feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta,
				MatrixXd & F, MatrixXd & output, int L, int m, int n, int N,
				int model_num){
	MatrixXd Hg, temp_out;
	Hg = MatrixXd::Zero(N, m * model_num);
	for(int i = 0; i < model_num; i++){
		ELM_basic(feature, W[i], b[i], beta[i], temp_out, L, m, n, N);
		Hg.block(0, m * i, N, m) = temp_out;
	}
	MatrixXd Hg1;
	pseudoInverse(Hg, Hg1);
	F = Hg1 * T;
	output = Hg * F;
}
#endif

void pr(string msg, MatrixXd & T){
	cout << msg << endl << T << endl;
}
void pr(string msg, VectorXd & T){
	cout << msg << endl << T << endl;
}

void print_matrix(MatrixXd & T){
	for(int i = 0; i < T.cols(); i++)
		cout << T(i, 0) << " ";
	cout << endl;
	//~ for (int i = 0; i < N; i++)
	//~ cout << output(i, 0) << " ";
	//~ cout<<endl;
}

/*void load_MatrixXd(MatrixXd &T,string filename) {
        char *text=get_file_text(filename.c_str());
        vector<double> vec;
	}*/

void MyGammaCorrection(Mat& src, Mat& dst, float fGamma)
{
	CV_Assert(src.data);
	// accept only char type matrices
	CV_Assert(src.depth() != sizeof(uchar));
	// build look up table
	unsigned char lut[256];
	for( int i = 0; i < 256; i++ )
	{
		lut[i] = saturate_cast<uchar>(pow((float)(i/255.0), fGamma) * 255.0f);
	}
	dst = src.clone();
	const int channels = dst.channels();
	switch(channels)
	{
		case 1:
			{
				MatIterator_<uchar> it, end;
				for( it = dst.begin<uchar>(), end = dst.end<uchar>(); it != end; it++ )
					//*it = pow((float)(((*it))/255.0), fGamma) * 255.0;
					*it = lut[(*it)];
				break;
			}
		case 3: 
			{
				MatIterator_<Vec3b> it, end;
				for( it = dst.begin<Vec3b>(), end = dst.end<Vec3b>(); it != end; it++ )
				{
					//(*it)[0] = pow((float)(((*it)[0])/255.0), fGamma) * 255.0;
					//(*it)[1] = pow((float)(((*it)[1])/255.0), fGamma) * 255.0;
					//(*it)[2] = pow((float)(((*it)[2])/255.0), fGamma) * 255.0;
					(*it)[0] = lut[((*it)[0])];
					(*it)[1] = lut[((*it)[1])];
					(*it)[2] = lut[((*it)[2])];
				}
				break;
			}
	}
}

cv::Mat logTransform3(Mat srcImage, float c)  
{  
    // 输入图像判断
    if(srcImage.empty())
        std::cout<< "No data!" <<std::endl;
    cv::Mat resultImage = 
      cv::Mat::zeros(srcImage.size(), srcImage.type());  
    srcImage.convertTo(resultImage,CV_32F);
    resultImage = resultImage + 1;
    cv::log(resultImage,resultImage);
    resultImage = c * resultImage;
    cv::normalize(resultImage,resultImage,0,255,cv::NORM_MINMAX);
    cv::convertScaleAbs(resultImage,resultImage);
    return resultImage; 
}

cv::Mat face_align(const char * filename){

	Mat pic = imread(filename,0);

	Mat dst;
	flag = 0;
	if((pic.empty()))
	{
		flag = 1;
		cout << "pic  empty" << endl;
		return cv::Mat::zeros(50, 50, CV_8UC1);
	}
if(mode==0){
	return pic;
}else if(mode==1)
{
	equalizeHist(pic, dst);
	return dst;
}else if(mode ==2){
	MyGammaCorrection(pic,dst,0.4f);
	return dst;
}else if(mode ==3){
	MyGammaCorrection(pic,dst,1.2f);
	return dst;
}else if(mode ==4){
	MyGammaCorrection(pic,dst,gamma_value);
	return dst;
}else if(mode ==5){
	MyGammaCorrection(pic,dst,0.4f);
	equalizeHist(dst, dst);
	return dst;
}else if(mode ==6){
	dst=logTransform3(pic,0.2f);
	return dst;
}else if(mode ==7){
	dst=logTransform3(pic,20.0f);
	return dst;
}else if(mode ==8){	
	dst=logTransform3(pic,1.0f);
	return dst;
}else if(mode ==9){	
	dst=logTransform3(pic,1.2f);
	return dst;
}else if(mode ==10){	
	dst=logTransform3(pic,5.0f);
	return dst;
}else if(mode==11)
{
	return pic;
}
}
/**********************************************************************************/
int my_parse_args(int argc, char * argv[]){
	if(argc > 1)
		while(argv[k] && argv[k][0] == '-'){
			char * p = argv[k];
			p++;
			k++;
			if(*p == 'o'){
				cout << "Setting number of hidden nodes ..." << endl;
				L = atoi(argv[k++]);
			} else if(*p == 'p'){
				cout << "Setting number of training people ..." << endl;
				m = atoi(argv[k++]);
			} else if(*p == 'n'){
				cout << "Setting number of models ..." << endl;
				model_num = atoi(argv[k++]);
			} else if(*p == 't'){
				cout << "Setting number of faces per training person ..."	 << endl;
				training_face_num_per_person = atoi(argv[k++]);
			} else if(*p == 's'){
				cout << "Setting number of faces per testing person ..."	 << endl;
				testing_face_num_per_person = atoi(argv[k++]);
			} else if(*p == 'g'){
				cout << "Setting gamma value ..."	 << endl;
				gamma_value = atoi(argv[k++]);
			} else if(*p == 'r'){
				cout << "Setting training path ..." << endl;
				trainfile_path = argv[k++];
			} else if(*p == 'e'){
				cout << "Setting testing path ..." << endl;
				testfile_path = argv[k++];
			} else if(*p == 'a'){
				cout << "Setting pca ..." << endl;
				pca_num = atoi(argv[k++]);
			} else if(*p == 'z'){
				cout << "Setting all_num ..." << endl;
				all_num = atoi(argv[k++]);
			} else {
				cout << "-o: Setting number of hidden nodes\n";
				cout << "-p: Setting number of training people\n";
				cout << "-n: Setting number of models\n";
				cout << "-t: Setting number of faces per training person\n";
				cout << "-s: Setting number of faces per testing person\n";
				cout << "-r: Setting training path\n";
				cout << "-e: Setting testing path\n";
				cout << "other: Help\n";
				return 1;
			}
		}
	return 0;
}

void cout_current_settings(){
	cout << "*****************************" << endl;
	cout << "Current settings:\n";
	cout << "Hidden nodes=" << L << ',' << "People=" << m << ','
		 << "model_num=" << model_num << endl;
	cout << "training_face_num_per_person=" << training_face_num_per_person
		 << ',' << "testing_face_num_per_person=" << testing_face_num_per_person
		 << endl;
	cout << "trainfile_path=" << trainfile_path << endl;
	cout << "testfile_path=" << testfile_path << endl;
	cout << "*****************************" << endl;
}

// void init_face_detector_dlib(string face_landmark) {
//     detector = dlib::get_frontal_face_detector();
//     dlib::deserialize(face_landmark) >> sp;
// }

MatrixXd ELM_in_ELM_face_training_matrix_from_files(){

	cout << "Loading train Data..." << endl;
	// load training images
	getFaces_train(trainfile_path, trainingImages, trainingLabels);
	MatrixXd feature(trainingImages.rows, trainingImages.cols); //创建新的矩阵
	// VectorXd label(trainingLabels.size()); //创建新的向量
	cv2eigen(trainingImages, feature);     //转化
	// cv2eigen(Mat(trainingLabels), label);  //转化
	cout << "Number of training images:" << trainingImages.rows << endl; //
	n = trainingImages.cols; // number of features //输出特征值
	return feature;
}

MatrixXd ELM_in_ELM_face_testing_matrix_from_files(){
	// loading test images
	cout << "Loading test Data..." << endl;
	Mat testingImages;
	getFaces_test(testfile_path, testingImages, testingLabels);
	MatrixXd feature1(testingImages.rows, testingImages.cols);
	// VectorXd label1(testingLabels.size());
	cv2eigen(testingImages, feature1);
	// cv2eigen(Mat(testingLabels), label1);
	N_test = testingImages.rows;
	cout << "Number of testing images:" << N_test << endl;
	return feature1;
}

MatrixXd generate_training_labels(){
	N = trainingImages.rows;
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
	T = temp_T;
	return T;
}

// ELM training
void ELM_training(MatrixXd feature, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	struct timeval start, end;
	TickMeter tm;
	tm.start();
	ELM_in_ELM(feature, W, b, beta, F, output, L, m, n, N, model_num);
	tm.stop();
	std::cout << "Training time:    " << tm.getTimeSec() << "  s" << endl;

	// for(int i = 0; i < model_num; i++){
	// 	string write_w = "W"+to_string(i)+".txt";
	// 	write_parameter(write_w,W[i]);
	// 	string write_b = "b"+to_string(i)+".txt";
	// 	write_parameter(write_b,b[i]);
	// 	string write_beta = "beta"+to_string(i)+".txt";
	// 	write_parameter(write_beta,beta[i]);
	// }
}
// ELM testing
void ELM_testing(MatrixXd feature1, MatrixXd * W, MatrixXd * b, MatrixXd * beta){
	struct timeval start1, end1;
	MatrixXd out_all, R, Tem, H;
	out_all = MatrixXd::Zero(N_test, m * model_num);
	TickMeter tm;
	tm.start();
	for(int i = 0; i < model_num; i++){
		R = -feature1 * W[i] + MatrixXd::Ones(N_test, 1) * b[i];
		Tem = R.array().exp() + 1;
		H = Tem.array().inverse();
		out_all.block(0, m * i, N_test, m) = H * beta[i];
	}
	output = out_all * F;
	tm.stop();
	std::cout << "Testing time:    " << tm.getTimeSec() *1000<< "  ms" << endl;
}
// calculate accuracy
void show_testing_results(){
	cout << "testing results(ELM,real):" << endl;
	cout << output.rows() << ',' << output.cols() << ",N_test(rows):" << N_test << endl;
	int count = 0;

	for(int i = 0; i < N_test; i++){
		//             cout<<i<<endl;
		int ii, jj;
		//             cout<<output.row(i).maxCoeff(&ii,&jj)<<endl;
		double truth = output.row(i).maxCoeff(&ii, &jj);
		// cout << truth << endl;
		// cout << jj << ',' << testingLabels.at(i) << endl;
		if(jj == testingLabels.at(i))
			count++;
	}
	cout << "accuracy:" << (double)count / (double)N_test << endl;
	accuracy[mode]= (double)count / (double)N_test;
}

int main(int argc, char * * argv){
	init_stdio();
	int in = my_parse_args(argc, argv);
	if(argc <= 1)
		cout << "Using default settings!\n";
	cout_current_settings();
	if(in != 0)
		return 0;
	// init_face_detector_dlib();
	// time
	// for(int all_num=0;all_num<10,all_num++){
		// system("echo 'h'");

		for(mode=0;mode <=11;mode++){
			// system("echo 'h'");
			MatrixXd W[model_num], b[model_num], beta[model_num];
			MatrixXd feature, feature1;
			feature = ELM_in_ELM_face_training_matrix_from_files();
			feature1 = ELM_in_ELM_face_testing_matrix_from_files();
			T = generate_training_labels();
			ELM_training(feature, W, b, beta);
			ELM_testing(feature1, W, b, beta);
			show_testing_results();
		}
		std::string fileName = to_string(1)+".txt";
		std::ofstream outfile(	fileName.c_str()); // file name and the operation type. 
		for(mode=0;mode <=11;mode++){
			// outfile << "mode : " <<mode<< "	accuracy:	"<<accuracy[mode]<< endl;
				outfile << accuracy[mode]<< endl;
		}
		outfile.close();
	// }
	return 0;
}
