#include "ELM-test.h"
PCA pca;

/******************LBP***********************/
void LBP81(const Mat& src, Mat& dst) {
    dst = Mat::zeros(src.rows-2, src.cols-2, CV_8UC1);
    for(int i=1;i<src.rows-1;i++) 
	{
        for(int j=1;j<src.cols-1;j++) 
		{
			uchar center = src.at<uchar>(i,j);
			unsigned char code=0,U2 = 0;
			unsigned char a[8];
			a[7]=(src.at<uchar>(i-1,j-1) > center);a[6]=(src.at<uchar>(i-1,j) > center);
			a[5]=(src.at<uchar>(i-1,j+1) > center);a[4]=(src.at<uchar>(i,j+1) > center);
			a[3]=(src.at<uchar>(i+1,j+1) > center);a[2]=(src.at<uchar>(i+1,j) > center);
			a[1]=(src.at<uchar>(i+1,j-1) > center);a[0]=(src.at<uchar>(i,j-1) > center);
			code |= a[7]<< 7;
			code |= a[6]<< 6;
			code |= a[5]<< 5;
			code |= a[4]<< 4;
			code |= a[3]<< 3;
			code |= a[2]<< 2;
			code |= a[1]<< 1;
			code |= a[0]<< 0;
	    //Uniform LBP
            U2=abs(a[7]-a[0]);
		for(int p=1;p<8;p++)
			U2+=abs(a[p]-a[p-1]);
		if(U2>2)
			code=9;
	    dst.at<unsigned char>(i-1,j-1) = code;
		}
	}
}
/*********************************************/
std::vector<float> extract_feature_LBP(Mat src, int src_rows, int src_cols) 
	{	
		Mat dst,dst1;
		int lbp_81[243]={0};
		cvtColor(src,dst1,COLOR_BGR2GRAY);
		std::vector<float> feature;
		LBP81(dst1,dst);
		//imshow("DDD",dst);
		//waitKey();
		for(int ii=0;ii<dst.rows;ii++)
			for(int jj=0;jj<dst.cols;jj++)
				lbp_81[table[dst.at<uchar>(ii,jj)]]++;
		
		for(int kk=0;kk<59;kk++)
		{
			feature.push_back((float)lbp_81[kk]/(src_rows*src_cols));
		}				
		/*for (int i=0;i<src.rows;i++)
			for (int j=0;j<src.cols;j++)
					feature.push_back(dst.at<uchar>(i,j));*/
		return feature;
	}
/******extract_feature: put one image into a vector(convert to gray image firstly)*****/
/*********************************************/
std::vector<float> extract_feature(Mat src) 
	{	
		Mat dst;
		cvtColor(src,dst,COLOR_BGR2GRAY);
		std::vector<float> feature;
		for (int i=0;i<src.rows;i++)
			for (int j=0;j<src.cols;j++)
					feature.push_back(dst.at<uchar>(i,j));
		return feature;
	}
	
/**time**/
	double difftimeval(const struct timeval *start, const struct timeval *end) 
	{ 
		double d; 
		time_t s; 
		suseconds_t u; 
		s = start->tv_sec - end->tv_sec; 
		u = start->tv_usec - end->tv_usec; 
		d = s; 
		d *= 1000000.0;
		d += u; 
		return d; 
	}

/**********************************************/
/**getFiles: put the filename in all subfolders in the path**/ //(just two cascades)
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
void getFiles_train( string path, vector<string>& files )  
{
	int count_train=0;
	int person_id=0;
	struct dirent *ptr,*ptr1;    
	DIR *dir,*dir1;
	dir=opendir(path.c_str());//path如果是文件夹 返回NULL
	while((ptr=readdir(dir))!=NULL)//读取列表
	{
		if(ptr->d_name[0] == '.'||ptr->d_name=="Thumbs.db"||ptr->d_name=="..")		//去掉当前文件夹目录和 Thumbs.db这个windows下保存图片就会产生的文件
			continue;
		string ss=path+'/'+ptr->d_name+'/';//二级文件夹目录   //这TM有问题 path后面少了一个'/'
		dir1=opendir(ss.c_str());
		while((ptr1=readdir(dir1))!=NULL)
		{
			if(ptr1->d_name[0] == '.'||ptr1->d_name=="Thumbs.db")
				continue;
			string sss=ss+ptr1->d_name;		//
			files.push_back(sss);			//返回图片路径
			count_train++;					//训练数量++
			train_labels_ori.push_back(person_id);		//vector<int> train_labels_ori;添加标签
			if(count_train==training_face_num_per_person)	//训练数量结束
			{
				count_train=0;
				break;
			}
		}
		closedir(dir1);
		person_id++;			//下一个文件夹 下一个人的标签++
    }
    closedir(dir);
} 

void getFiles_test( string path, vector<string>& files )  
{
	int count_test=0;
	int person_id=0;
	struct dirent *ptr,*ptr1;    
	DIR *dir,*dir1;
	dir=opendir(path.c_str());
	while((ptr=readdir(dir))!=NULL)		//一级目录
	{
		if(ptr->d_name[0] == '.'||ptr->d_name=="Thumbs.db"||ptr->d_name=="..")
			continue;
		string ss=path+'/'+ptr->d_name+'/';
		dir1=opendir(ss.c_str());
		while((ptr1=readdir(dir1))!=NULL)		//二级目录
		{	
			if(ptr1->d_name[0] == '.'||ptr1->d_name=="Thumbs.db"||count_test<training_face_num_per_person)
			{
				if(count_test>=training_face_num_per_person)
					cout<<"***"<<ss+ptr1->d_name<<endl;
				count_test++;
				continue;
			}
			
			string sss=ss+ptr1->d_name;
			files.push_back(sss);
			count_test++;
			test_labels_ori.push_back(person_id);
			if(count_test>=(training_face_num_per_person+testing_face_num_per_person))
			{
				count_test=0;
				break;
			}	
		}
		closedir(dir1);
		person_id++;	
	}
	//cout<<test_labels_ori<<endl;
    closedir(dir);
} 

/**********************************************/
/**getTrainfile: put all the faces in filepath into Mat trainingImages and gengrate labels into trainingLabels automatically**/
/**********************************************/
/*void getFaces(string filePath, Mat& trainingImages, vector<int>& trainingLabels, int faces_per_person)
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
void getFaces_train(string filePath, Mat& trainingImages, vector<int>& trainingLabels, int faces_per_person)
{
     vector<string> files;  
     getFiles_train(filePath, files);  
     int number = files.size();  
     for (int i = 0;i <number;i++)  
     {  
        Mat  SrcImage=face_align(files[i].c_str());		//读取图片
	if(flag)
	{
		flag=0;
		cout<<"No face in this file:"<<files[i].c_str()<<endl;
		continue;
	}
	resize(SrcImage,SrcImage,cv::Size(50,50));
        Mat SrcImage1= Mat(extract_feature(SrcImage),true);
        //Mat SrcImage1= Mat(extract_feature_LBP(SrcImage,50,50),true);
	Mat SrcImage2=SrcImage1.t();		//矩阵逆		extract_feature特征值的逆
        trainingImages.push_back(SrcImage2);			//
        trainingLabels.push_back(train_labels_ori.at(i));//(i/faces_per_person);//i 将标签 push进
     }
}

void getFaces_test(string filePath, Mat& trainingImages, vector<int>& trainingLabels, int faces_per_person)
{
     vector<string> files;  
     getFiles_test(filePath, files );  
     int number = files.size();  
     cout<<test_labels_ori.size()<<','<<number<<endl;
     for (int i = 0;i <number;i++)  
     {  
        Mat  SrcImage=face_align(files[i].c_str());
	if(flag)
	{
		flag=0;
		cout<<"No face in this file:"<<files[i].c_str()<<endl;
		continue;
	}
	resize(SrcImage,SrcImage,cv::Size(50,50));
        Mat SrcImage1= Mat(extract_feature(SrcImage),true);
        //Mat SrcImage1= Mat(extract_feature_LBP(SrcImage,50,50),true);
	Mat SrcImage2=SrcImage1.t();
        trainingImages.push_back(SrcImage2);
	//cout<<test_labels_ori.at(i)<<':'<<files[i].c_str()<<endl;
        trainingLabels.push_back(test_labels_ori.at(i));//i/faces_per_person);
	//cout<<i<<':'<<test_labels_ori.at(i)<<endl;
     }     
}

template<typename _Matrix_Type_>
bool pseudoInverse(const _Matrix_Type_ &a, _Matrix_Type_ &result, double epsilon = std::numeric_limits<typename _Matrix_Type_::Scalar>::epsilon()) {
	Eigen::JacobiSVD< _Matrix_Type_ > svd = a.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV);
	if (a.rows() < a.cols()) {
		typename _Matrix_Type_::Scalar tolerance = epsilon * std::max(a.cols(), a.rows()) * svd.singularValues().array().abs()(0);
		result = svd.matrixV() * (svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0).matrix().asDiagonal() * svd.matrixU().adjoint();
	}
       //return false;
	else {
		typename _Matrix_Type_::Scalar tolerance = epsilon * std::max(a.cols(), a.rows()) * svd.singularValues().array().abs().maxCoeff();
		//  Eigen::JacobiSVD< _Matrix_Type_ > svd = a.jacobiSvd(Eigen::ComputeThinU | Eigen::ComputeThinV);
		//  typename _Matrix_Type_::Scalar tolerance = epsilon * std::max(a.cols(), a.rows()) * svd.singularValues().array().abs().maxCoeff();
		result = svd.matrixV() * ((svd.singularValues().array().abs() > tolerance).select(svd.singularValues().array().inverse(), 0)).matrix().asDiagonal() * svd.matrixU().adjoint();
	}
	return true;
}

void init_stdio() {
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

void extract_data(vector<vector<double>> &traindata, MatrixXd &feature, VectorXd &label) {
	for (unsigned long i = 0; i < traindata.size(); i++) {
		for (unsigned long j = 0; j < traindata[0].size(); j++) {
			if (j < traindata[0].size()-1)
				feature(i, j) = traindata[i][j];
			else
				label(i) = traindata[i][j];
		}
	}
}	
*/

#if 1
void ELM_basic(MatrixXd &feature,/* VectorXd &label,*/ MatrixXd &W, MatrixXd &b_1, MatrixXd &beta, MatrixXd &output, int L, int m, int n, int N) {
	MatrixXd b, R, Tem, H;
	W = MatrixXd::Random(n, L);
	b_1 = MatrixXd::Random(1, L);// + MatrixXd::Ones(1, L)) / 2;
	b = MatrixXd::Ones(N, 1)*b_1;
	R = -feature*W+b;
	Tem = R.array().exp() + 1;
	H = Tem.array().inverse();
/*	MatrixXd temp_T, T;
	temp_T = MatrixXd::Zero(N, m);
	for (int i = 0; i < N; i++) {
		if (label(i)==1) {
			temp_T(i, 0) = 1;
			temp_T(i, 1) = 0;
		} else {
			temp_T(i, 0) = 0;
			temp_T(i, 1) = 1;
		}
	}
	T = temp_T * 2 - MatrixXd::Ones(N, m);*/
	MatrixXd result(L, N);
	pseudoInverse(H, result);
	beta = result*T;
	output = H*beta;
}
void ELM_in_ELM(MatrixXd &feature, /*VectorXd &label,*/ MatrixXd* W, MatrixXd* b, MatrixXd* beta, MatrixXd & F, MatrixXd &output, int L, int m, int n, int N, int model_num){
	MatrixXd Hg,temp_out;
	Hg=MatrixXd::Zero(N,m*model_num);
	for(int i=0;i<model_num;i++){
		ELM_basic(feature, W[i], b[i], beta[i], temp_out,L, m, n, N) ;
		Hg.block(0,m*i,N,m)=temp_out;
	}
	MatrixXd Hg1;
	pseudoInverse(Hg, Hg1);
	F=Hg1*T;
	output=Hg*F;
}
#endif

void pr(string msg, MatrixXd &T) {
	cout<<msg<<endl<<T<<endl;
}
void pr(string msg, VectorXd &T) {
	cout<<msg<<endl<<T<<endl;
}

void print_matrix(MatrixXd &T) {
	for (int i = 0; i < T.cols(); i++)
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

cv::Mat face_align(const char* filename)
{
	Mat pic = imread(filename);/*彩色图检测人脸*/	Mat dst;	flag = 0;
	// cout<<pic.channels()<<endl;
	// cout<<pic<<endl;
	if((pic.empty()))	{		flag = 1;		cout << "pic  empty" << endl;		return cv::Mat::zeros(50, 50, CV_8UC1);	}
	Mat for_end;
	cvtColor(pic, for_end, COLOR_BGR2GRAY);
	// pic.convertTo(for_end,CV_8UC1);
	equalizeHist(for_end,for_end);
	return pic;
/* 	Mat image_roi=imread(filename,0);
		if((image_roi.empty()))	{		flag = 1;		cout << "pic  empty" << endl;		return cv::Mat::zeros(50, 50, CV_8UC1);	}
	equalizeHist(image_roi, image_roi); */

/* 	dlib::cv_image<dlib::bgr_pixel> img(image_roi);   
	// dlib::cv_image<dlib::bgr_pixel> img(image_roi);   
	std::vector<dlib::full_object_detection> shapes;//shape的向量
	dlib::array<dlib::array2d<dlib::bgr_pixel> > face_chips;//图像的向量	用来存储对齐之后的人脸
	dlib::rectangle dlibRect(0, 0, image_roi.cols, image_roi.rows);
	dlib::full_object_detection shape = sp(img, dlibRect);
	shapes.push_back(shape);
	dlib::extract_image_chips(img, dlib::get_face_chip_details(shapes), face_chips);
	dlib::array2d<dlib::bgr_pixel> equ;//图像格式
	dlib::equalize_histogram(face_chips[0], equ);
	// dlib::equalize_histogram(img, equ);
	Mat eve = dlib::toMat(equ);
	return eve; */
	// return image_roi;

}

/* 		dlib::array2d<dlib::rgb_pixel> img;//常规图片格式
		//dlib::array2d<unsigned char> img_gray;//img_rgb转灰度图片
		//dlib::assign_image(img_gray, img_rgb);
		dlib::load_image(img, filename);//加载图片
		//gettimeofday(&start2, NULL);
		dlib::pyramid_up(img);//使可以扫描更小像素的人脸
		std::vector<dlib::rectangle> dets = detector(img);  //返回矩阵【（x1，y1）（x2，y2）】
		std::vector<dlib::full_object_detection> shapes;//shape的向量
		dlib::array<dlib::array2d<dlib::rgb_pixel> > face_chips;//图像的向量	用来存储对齐之后的人脸	
		if(dets.size()<=0)
		{
			flag=1;
			return cv::Mat::zeros(100,100,CV_8UC3);
		}
			for (unsigned long j = 0; j < dets.size(); ++j)
			{
				dlib::full_object_detection shape = sp(img, dets[j]);	
/*				//cout << "pixel position of first part:  " << shape.part(0) << endl;//获得第一个点的坐标,注意第一个点是从0开始的
				//cout << "pixel position of second part: " << shape.part(1) << endl;//获得第二个点的坐标
				//自己改写，打印出全部68个点
				for (int i = 1; i < 69; i++)
				{
					cout << "第 " << i<< " 个点的坐标： " << shape.part(i-1) << endl;
				}
*/				
			/*	shapes.push_back(shape);
			}
			dlib::extract_image_chips(img, dlib::get_face_chip_details(shapes), face_chips);
			dlib::array2d<dlib::rgb_pixel> equ;//图像格式
			dlib::equalize_histogram(face_chips[0],equ);
			//gettimeofday(&end2, NULL);
			//cout<<"Preprocessing time:"<<(difftimeval(&end2, &start2)/1000000)<<'s'<<endl;
			return dlib::toMat(equ); */
			
// }
/**********************************************************************************/
int my_parse_args(int argc, char* argv[]) {
  if(argc>1) 
	while(argv[k] && argv[k][0]=='-') {
		char *p=argv[k];
		p++;k++;
		if(*p=='o') {
			cout<<"Setting number of hidden nodes ..."<<endl;
			L=atoi(argv[k++]);
		} else if(*p=='p') {
			cout<<"Setting number of training people ..."<<endl;
			m=atoi(argv[k++]);
		} else if(*p=='n') {
			cout<<"Setting number of models ..."<<endl;
			model_num=atoi(argv[k++]);
		} else if(*p=='t') {
			cout<<"Setting number of faces per training person ..."<<endl;
			training_face_num_per_person=atoi(argv[k++]);
		} else if(*p=='s') {
			cout<<"Setting number of faces per testing person ..."<<endl;
			testing_face_num_per_person=atoi(argv[k++]);
		} else if(*p=='r') {
			cout<<"Setting training path ..."<<endl;
			trainfile_path=argv[k++];
		} else if(*p=='e') {
			cout<<"Setting testing path ..."<<endl;
			testfile_path=argv[k++];
		}else {
			cout<<"-o: Setting number of hidden nodes\n";
			cout<<"-p: Setting number of training people\n";
			cout<<"-n: Setting number of models\n";
			cout<<"-t: Setting number of faces per training person\n";
			cout<<"-s: Setting number of faces per testing person\n";
			cout<<"-r: Setting training path\n";
			cout<<"-e: Setting testing path\n";
			cout<<"other: Help\n";
			return 1;
		}
	}
	return 0;
}

void cout_current_settings()
{
	cout<<"*****************************"<<endl;
	cout<<"Current settings:\n";
	cout<<"Hidden nodes="<<L<<','<<"People="<<m<<','<<"model_num="<<model_num<<endl;
	cout<<"training_face_num_per_person="<<training_face_num_per_person<<','<<"testing_face_num_per_person="<<testing_face_num_per_person<<endl;
	cout<<"trainfile_path="<<trainfile_path<<endl;
	cout<<"testfile_path="<<testfile_path<<endl;
	cout<<"*****************************"<<endl;	
}

void init_face_detector_dlib(string face_landmark)
{
	detector = dlib::get_frontal_face_detector();
	dlib::deserialize(face_landmark) >> sp;
}

MatrixXd ELM_in_ELM_face_training_matrix_from_files()
{

	cout<<"Loading train Data..."<<endl;
	//load training images
	getFaces_train(trainfile_path,trainingImages,trainingLabels,training_face_num_per_person);
	N = trainingImages.rows;
	MatrixXd feature(trainingImages.rows,trainingImages.cols);		//创建新的矩阵		//PCA 需要修改这个初始化
	VectorXd label(trainingLabels.size());							//创建新的向量
	cv2eigen(trainingImages,feature);								//转化
	cv2eigen(Mat(trainingLabels),label);							//转化
	cout<<"Number of training images:"<<trainingImages.rows<<endl;		//
	n = trainingImages.cols;//number of features						//
/* 	n=N;
	pca(trainingImages, Mat(), PCA::DATA_AS_ROW,N);
	Mat dst = pca.project(trainingImages);//映射新空间
	cv2eigen(dst,feature); */
	// cout<<feature<<endl;
	return feature;
}
MatrixXd ELM_in_ELM_face_testing_matrix_from_files()
{
	// loading test images
	cout<<"Loading test Data..."<<endl;
	Mat testingImages;
	// vector<int> testingLabels;
	getFaces_test(testfile_path,testingImages,testingLabels,testing_face_num_per_person);
	MatrixXd feature1(testingImages.rows, testingImages.cols);
	VectorXd label1(testingLabels.size());
	cv2eigen(testingImages,feature1);
	N_test = testingImages.rows;
/* 	cv2eigen(Mat(testingLabels),label1);	
	N_test = testingImages.rows;
	cout<<"Number of testing images:"<<N_test<<endl;
	Mat dst = pca.project(testingImages);//映射新空间
	// cout<<dst<<endl;
	cv2eigen(dst,feature1);
	// cout<<feature1<<endl; */
	return feature1;
}

MatrixXd generate_training_labels()
{
	
	MatrixXd F,output;
	MatrixXd temp_T;
	// MatrixXd W[model_num],b[model_num], beta[model_num];
	//generate testing labels
	temp_T = MatrixXd::Zero(N, m);
	for (int i = 0; i < N; i++) {
		for (int jj=0;jj<m;jj++)
		{
			if (trainingLabels.at(i)==jj)
				temp_T(i, jj) = 1;
			else
				temp_T(i, jj) = 0;
		}
	
	}
	T = temp_T ;
	return T;
}


	//ELM training
	void ELM_training(MatrixXd feature,MatrixXd* W,MatrixXd* b,MatrixXd* beta)
	{
		//MatrixXd W[model_num],b[model_num], beta[model_num];
		struct timeval start,end;
		gettimeofday(&start, NULL);
		ELM_in_ELM(feature,W,b,beta,F,output,L,m,n,N,model_num);
		gettimeofday(&end, NULL);
		cout<<"Training time:"<<(difftimeval(&end, &start)/1000000)<<'s'<<endl;
	}
	//ELM testing
	void ELM_testing(MatrixXd feature1,MatrixXd* W,MatrixXd* b,MatrixXd* beta)
	{
// 		Mat ac;
// eigen2cv(feature,ac);
// Mat pro=pca.project(ac);//映射新空间
// MatrixXd feature1;
// cv2eigen(pro, feature1);     //转化
		struct timeval start1,end1;
		MatrixXd out_all,R,Tem,H;
		out_all=MatrixXd::Zero(N_test,m*model_num);
		gettimeofday(&start1, NULL);
		for(int i=0;i<model_num;i++){
			R = -feature1*W[i]+MatrixXd::Ones(N_test, 1)*b[i];
			Tem = R.array().exp() + 1;
			H = Tem.array().inverse();
			out_all.block(0,m*i,N_test,m)=H*beta[i];
		}
		output=out_all*F;
		gettimeofday(&end1, NULL);
		cout<<"Testing time:"<<(difftimeval(&end1, &start1)/1000000)<<'s'<<endl;
	}
	//calculate accuracy

	void show_testing_results()
	{
		cout<<"testing results(ELM,real):\n";
		cout<<output.rows()<<','<<output.cols()<<endl;
		int count=0;
		for (int i=0;i<N_test;i++)
		{
			int ii,jj;
			output.row(i).maxCoeff(&jj);
			cout<<jj<<','<<testingLabels.at(i)<<endl;
			if(jj==testingLabels.at(i))
				count++;
		}
		cout<<"accuracy:"<<(double)count/(double)N_test<<endl;
	}

int main(int argc, char** argv)
{
	init_stdio();
	int in=my_parse_args(argc,argv);
	if(argc<=1)
		cout<<"Using default settings!\n";
	cout_current_settings();
	if(in!=0)
		return 0;
	init_face_detector_dlib();
	//time
	MatrixXd W[model_num],b[model_num], beta[model_num];
	MatrixXd feature,feature1;
	feature=ELM_in_ELM_face_training_matrix_from_files();
	feature1=ELM_in_ELM_face_testing_matrix_from_files();
	T=generate_training_labels();
	ELM_training(feature,W,b,beta);
	ELM_testing(feature1,W,b,beta);
	show_testing_results();
	return 0;
}