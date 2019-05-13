
#include <iostream>
#include <contrib\contrib.hpp>
#include <cxcore.hpp>
using namespace cv;
using namespace std;

/*  LDA(const Mat& src, vector<int> labels,int num_components = 0) :
第一个为数据集（行排列）
第二个为int类型的标签数组和第一个数据集相对应
第三个为默认降维的维度为c-1，c是类别的数量 */

int main(void)
{
	//sampledata
	double sampledata[6][2]={{0,1},{0,2},{2,4},{8,0},{8,2},{9,4}};
	Mat mat=Mat(6,2,CV_64FC1,sampledata);
	//labels
	vector<int>labels;
 
	for(int i=0;i<mat.rows;i++)
	{
		if(i<mat.rows/2)
		{
			labels.push_back(0);
		}
		else
		{
			labels.push_back(1);
		}
	}
 
	//do LDA
	//初始化并计算，构造函数中带有计算
	LDA lda=LDA(mat,labels,1);
	//get the eigenvector
	//获得特征向量
	Mat eivector=lda.eigenvectors().clone();
 
	cout<<"特征向量（double）类型:"<<endl;
	for(int i=0;i<eivector.rows;i++)
	{
		for(int j=0;j<eivector.cols;j++)
		{
			cout<<eivector.ptr<double>(i)[j]<<" ";
		}
		cout<<endl;
	}
 
 
	//------------------------------计算两个类心------------
	//针对两类分类问题，计算两个数据集的中心
	int classNum=2;
	vector<Mat> classmean(classNum);
	vector<int> setNum(classNum);
 
	for(int i=0;i<classNum;i++)
	{
		classmean[i]=Mat::zeros(1,mat.cols,mat.type());  //初始化类中均值为0
		setNum[i]=0;  //每一类中的条目数
	}
 
	Mat instance;
	for(int i=0;i<mat.rows;i++)
	{
		instance=mat.row(i);//获取第i行
		if(labels[i]==0)  //如果标签为0
		{	
			add(classmean[0], instance, classmean[0]);  //矩阵相加
			setNum[0]++;  //数量相加
		}
		else if(labels[i]==1)  //对于第1类的处理
		{
			add(classmean[1], instance, classmean[1]);
			setNum[1]++;
		}
		else
		{}
	}
	for(int i=0;i<classNum;i++)   //计算每一类的均值
	{
		classmean[i].convertTo(classmean[i],CV_64FC1,1.0/static_cast<double>(setNum[i]));
	}
	//----------------------------------END计算类心-------------------------
 
 
	vector<Mat> cluster(classNum);  //一共2类
 
	
	cout<<"特征向量："<<endl;
	cout<<eivector<<endl;   //此时的特征向量是一个列向量
	
	
	cout<<endl<<endl;
	cout<<"第一种方式(手动计算)："<<endl;
    //1.投影的第一种方式：Y=X*W
	//有的教程写成Y=W^T*X,（此时的X是列向量看待的所以需要将w转置）
	for(int i=0;i<classNum;i++)
	{
		cluster[i]=Mat::zeros(1,1,mat.type()); //初始化0
		//特征向量的转置同类均值相乘)
		cluster[i]=classmean[i]*eivector;
	}
 
	cout<<"The project cluster center is:"<<endl;  //计算均值的投影
	for(int i=0;i<classNum;i++) //输出两类中心的投影值
	{
		cout<<cluster[i].at<double>(0)<<endl;
	}
 
	//2.第二种方式使用内置函数计算
	//第一个中心
	cout<<endl<<"第二种方式:";
	cout<<endl<<"第一个类均值的投影:"<<endl;
	cout<<lda.project(classmean[0]).at<double>(0);
	cout<<endl<<"第二个类均值的投影"<<endl;
	cout<<lda.project(classmean[1]).at<double>(0);
 
 
	system("pause");
	return 0;
}
--------------------- 
作者：jiajiadejiali21 
来源：CSDN 
原文：https://blog.csdn.net/jialeheyeshu/article/details/52822010 
版权声明：本文为博主原创文章，转载请附上博文链接！