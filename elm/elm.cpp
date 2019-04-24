#include "elm.hpp"
#include"lrf.hpp"


/******extract_feature: put one image into a vector(convert to gray image firstly)*****/
/*********************************************/
std::vector<float> extract_feature(Mat src) 
	{	
//         cout<<"      extract_feature     "<<endl;
		Mat dst;
// 		cvtColor(src,dst,COLOR_BGR2GRAY);
		std::vector<float> feature;
		for (int i=0;i<src.rows;i++)
			for (int j=0;j<src.cols;j++)
					feature.push_back(src.at<uchar>(i,j));
		return feature;
	}
	

void getFiles_train( string path, vector<string>& files )  
{
	int count_train=0;
	int person_id=0;
	struct dirent *ptr,*ptr1;    
	DIR *dir,*dir1;
	dir=opendir(path.c_str());//path如果是文件夹 返回NULL
	while((ptr=readdir(dir))!=NULL)//读取列表
	{
		if(ptr->d_name[0] == '.'||ptr->d_name=="Thumbs.db")		//去掉当前文件夹目录和 Thumbs.db这个windows下保存图片就会产生的文件
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
		if(ptr->d_name[0] == '.'||ptr->d_name=="Thumbs.db")
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
    // 	resize(SrcImage,SrcImage,cv::Size(50,50));
        Mat SrcImage1= Mat(get_feature(SrcImage),true);
        Mat SrcImage2=SrcImage1.t();		//
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
//         resize(SrcImage,SrcImage,cv::Size(50,50));
        Mat SrcImage1= Mat(get_feature(SrcImage),true);
        Mat SrcImage2=SrcImage1.t();
        trainingImages.push_back(SrcImage2);
        trainingLabels.push_back(test_labels_ori.at(i));//i/faces_per_person);

     }     
}


void init_stdio() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(NULL);
}



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
    
        Mat pic=imread(filename,0);flag=0;
		if(pic.empty())
		{
            flag=1;
            cout<<"pic  empty"<<endl;
			return cv::Mat::zeros(100,100,CV_8UC3);
		}
		 resize(pic,pic,cv::Size(50,50),0,0,INTER_LINEAR);
// equalizeHist(pic,pic);
            return pic;
        
}
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
// 			model_num=atoi(argv[k++]);
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
// 	cout<<"Hidden nodes="<<L<<','<<"People="<<m<<','<<"model_num="<<model_num<<endl;
	cout<<"training_face_num_per_person="<<training_face_num_per_person<<','<<"testing_face_num_per_person="<<testing_face_num_per_person<<endl;
	cout<<"trainfile_path="<<trainfile_path<<endl;
	cout<<"testfile_path="<<testfile_path<<endl;
	cout<<"*****************************"<<endl;	
}

MatrixXd ELM_in_ELM_face_training_matrix_from_files()
{

	cout<<"Loading train Data..."<<endl;
	//load training images
	getFaces_train(trainfile_path,trainingImages,trainingLabels,training_face_num_per_person);
	MatrixXd feature(trainingImages.rows, trainingImages.cols);		//创建新的矩阵
	VectorXd label(trainingLabels.size());							//创建新的向量
	cv2eigen(trainingImages,feature);								//转化
	cv2eigen(Mat(trainingLabels),label);							//转化
	cout<<"Number of training images:"<<trainingImages.rows<<endl;		//
	n = trainingImages.cols;//number of features						//
	return feature;
}
MatrixXd ELM_in_ELM_face_testing_matrix_from_files()
{
	// loading test images
	cout<<"Loading test Data..."<<endl;
	Mat testingImages;
// 	vector<int> testingLabels;
	getFaces_test(testfile_path,testingImages,testingLabels,testing_face_num_per_person);
	MatrixXd feature1(testingImages.rows, testingImages.cols);
	VectorXd label1(testingLabels.size());
	cv2eigen(testingImages,feature1);
	cv2eigen(Mat(testingLabels),label1);	
	N_test = testingImages.rows;
	cout<<"Number of testing images:"<<N_test<<endl;
	return feature1;
}

MatrixXd generate_training_labels()
{
	N = trainingImages.rows;
// 	MatrixXd F,output;
	MatrixXd temp_T;
// 	MatrixXd W[model_num],b[model_num], beta[model_num];
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



	//calculate accuracy

	void show_testing_results()
	{
		cout<<"testing results(ELM,real):\n";
		cout<<output.rows()<<','<<output.cols()<<",N_test(rows):"<<N_test<<endl;
//         cout<<output<<endl;
		int count=0;
        
        std::string fileName = "my.txt" ;
        std::ofstream outfile( fileName.c_str() ) ; // file name and the operation type. 
        outfile <<output<<endl;
        outfile.close() ;

		for (int i=0;i<N_test;i++)
		{
//             cout<<i<<endl;
			int ii,jj;
//             cout<<output.row(i).maxCoeff(&ii,&jj)<<endl;
			output.row(i).maxCoeff(&ii,&jj);
			cout<<jj<<','<<testingLabels.at(i)<<endl;
			if(jj==testingLabels.at(i))
				count++;
		}
		cout<<"accuracy:"<<(double)count/(double)N_test<<endl;
	}

int main(int argc, char** argv)
{
	init_stdio();//cin 提速
	int in=my_parse_args(argc,argv);
	if(argc<=1)
		cout<<"Using default settings!\n";
	cout_current_settings();
	if(in!=0)
		return 0;
	//time
// 	MatrixXd W[model_num],b[model_num], beta[model_num];
    
	MatrixXd feature,feature1;
	feature=ELM_in_ELM_face_training_matrix_from_files();
	feature1=ELM_in_ELM_face_testing_matrix_from_files();
	T=generate_training_labels();
    LRF_train();
    LRF_test();
// 	ELM_training(feature,W,b,beta);
// 	ELM_testing(feature1,W,b,beta);
	show_testing_results();
	return 0;
}
