
#include"new.hpp"

int n;
int L = 150;                          //隐层节点数
int N;
int m;// = 50;                           //训练集以及测试集人数		//后期会自动更新m为训练集文件夹的数量
int model_num = 6;                    //子ELM模型的数量

MatrixXd F, output, T;

template <typename _Matrix_Type_>
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
		result = svd.matrixV() * (svd.singularValues().array().abs() > tolerance)
.select(svd.singularValues().array().inverse(), 0).matrix()	.asDiagonal() *svd.matrixU().adjoint();
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
	MatrixXd tem[model_num];
	//#pragma omp  for
	//#pragma omp  parallel for
	for(int i = 0; i < model_num; i++){
		ELM_basic(feature, W[i], b[i], beta[i], tem[i]);
		//ELM_basic(feature, W[i], b[i], beta[i], temp_out);
		//Hg.block(0, m * i, N, m) = temp_out;
	}
	for(int i = 0; i < model_num; i++){
		Hg.block(0, m * i, N, m) = tem[i];
	}
	MatrixXd Hg1;
	pseudoInverse(Hg, Hg1);
	F = Hg1 * T;
}
