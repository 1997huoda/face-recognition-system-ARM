include"lrf.hpp"

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

void LRF_train(MatrixXd feature,MatrixXd T,MatrixXd beta){
//     N = feature.rows();
    MatrixXd Hg1;
    pseudoInverse(feature, Hg1);
    beta=Hg1*T;
}
void LRF_test(MatrixXd feature,MatrixXd beta,MatrixXd output){
//     N = feature.rows();
    output=feature*beta;
}

//该函数   读取一张图(灰度)   随机权重卷积 池化 拉直    返回vector
std::vector<float> get_feature(Mat img,int L,int e){
    
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
            for (int n = 0; n < cols; n++) {
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
    for(int i=0;i<L;i++){
        std::vector<float> feature;
        feature.clear();
        for (int i=0;i<pool[L].rows;i++)
            for (int j=0;j<pool[L].cols;j++)
                    feature.push_back(pool[L].at<uchar>(i,j));   //拉直单个特征图
        end.insert(end.end(), feature.begin(), feature.end());  //拉直所有特征图
    }
    
    return end;
}
