#include "make.hpp"
//研究思路 ::
//读取人脸识别参数  --<没有数据就训练-->训练参数写入txt
// 接受数据   
//case1：更改训练数据  change_train_set:--> human_name  picture_name    img
    //收到命令 再将命令字符串 返回发送到主机
        //查找有无  human_name 文件夹，没有则创建
        //将    picture_name.jpg    发送到  human_name
//case2：开始训练   start_traning :
    //收到命令 再将命令字符串 返回发送到主机
        //开始训练 训练结束后将参数写入txt

//case3：摄像头     send_picture:-->face_num    name    img
    //收到命令 再将命令字符串 返回发送到主机
        //摄像头
        //得到人脸对齐之后的图像
        //矩阵乘法 得到识别结果     -->需要数字标签与字符串对应关系获得预测结果
        //发送结果


int main(int argc, char* argv[])
{

	return 0;
}

