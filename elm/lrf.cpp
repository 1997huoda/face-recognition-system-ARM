#include"lrf.hpp"

cv::Size normal(100,100);

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
/*
MatrixXd get_beta(MatrixXd feature,MatrixXd T){
    MatrixXd temp,beta,beta1,temp2,temp3;
    if(feature.rows()>feature.cols()){ //列满秩
        //左逆    .transpose()转置  .inverse()逆
      temp=  feature.transpose()*feature;
      temp2=temp.inverse()*feature.transpose();
      beta1=temp2*T;
    }else if(feature.rows()<feature.cols()){    //行满秩
        //  T 的左逆
        temp=  T.transpose()*T;
        temp2=temp.inverse()*T.transpose();
        temp3=temp*feature;
        if(temp3.rows()>temp3.cols()){ //列满秩
            beta=temp3.transpose()*temp;
            beta1=beta.inverse()*temp3.transpose();
        }else if(temp3.rows()<temp3.cols()){    //行满秩
            //    temp * feature 的矩阵的右逆是 beta
            beta=temp3.transpose()*temp3;
            beta1=temp3.transpose()*beta.inverse();
        }else if(temp3.rows()==temp3.cols()){
            beta1=  temp3.inverse();
        }
    }else if(feature.rows()==feature.cols()){
        temp=  feature.inverse();
        beta1=temp*T;
    }
    return beta1;
}*/


MatrixXd LRF_train(MatrixXd feature,MatrixXd T){
    MatrixXd beta;
    cout<<"start train"<<endl;
    MatrixXd Hg1;
    pseudoInverse(feature, Hg1);
    cout<<"H->get!"<<Hg1.rows()<<","<<Hg1.cols()<<endl;
    beta=Hg1*T;
    
//     beta=get_beta(feature,T);
    cout<<"beta->get!"<<beta.rows()<<","<<beta.cols()<<endl;
    return beta;
}
MatrixXd LRF_test(MatrixXd feature,MatrixXd beta){
    MatrixXd output;
     cout<<"start test"<<endl;
     cout<<feature.rows()<<","<<feature.cols()<<"::"<<beta.rows()<<","<<beta.cols()<<endl;
    output=feature*beta;
    cout<<"out->get!"<<endl;
    return output;
}

//该函数   读取一张图(灰度)   随机权重卷积 池化 拉直    返回vector
Mat get_feature(Mat img,int L,int e){
    
//     int L=8;    //L 为隐含层数量 为特征图数量
    Mat kernel;
    Mat feature[L];
    for (int i = 0; i < L; i++) {
        //随机权重  3*3扫描   kernel窗口大小
        eigen2cv((MatrixXd)MatrixXd::Random(3, 3), kernel);
        //卷积    feature为卷积之后的图
        cv::filter2D(img, feature[i], CV_8U, kernel);
    }
    Mat pool[L];    
    // pool[0].allocator
    //池化 e的大小   ：   e 表示池化中心到边的距离
//     int e = 3;
    for (int i = 0; i < L; i++) {
        pool[i] = Mat(img.size(), CV_8UC1);   //CV_8UC-->uchar
        for (int m = 0; m < img.rows; m++) {
            for (int n = 0; n < img.cols; n++) {
                int tmp = 0;
                for (int j = max(0, m - e); j < min(m + e, img.rows); j++) {
                    for (int k = max(0, n - e); k < min(n + e, img.cols); k++) {
                        //  tmp 为方均根
                        tmp += pow(feature[i].at<uchar>(j, k), 2);  //j行k列
                    }
                }
                pool[i].at<uchar>(m, n) = tmp;  //m行n列
            }
        }
    }
    std::vector<float> end;
    std::vector<float> fea;
    for(int i=0;i<L;i++){
        
        fea.clear();
        for (int i=0;i<pool[L].rows;i++)
            for (int j=0;j<pool[L].cols;j++)
                    fea.push_back(pool[L].at<uchar>(i,j));   //拉直单个特征图
        end.insert(end.end(), fea.begin(), fea.end());  //拉直所有特征图
    }
    vector<float>().swap(fea);
    Mat SrcImage1= Mat(end,true);
    Mat SrcImage2=SrcImage1.t();
    vector<float>().swap(end);
    
    return SrcImage2;
}
