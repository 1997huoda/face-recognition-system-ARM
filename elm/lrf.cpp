include"lrf.hpp"

int main() {
    Mat img = imread("../1.png", 0);
    cv::resize(img, img, cv::Size(500, 500));
    imshow("test", img);
    Mat kernel;
    Mat feature[10];
    for (int i = 0; i < 8; i++) {
        eigen2cv((MatrixXd)MatrixXd::Random(3, 3), kernel);
        cv::filter2D(img, feature[i], CV_8U, kernel);
        imshow("test", feature[i]);
        // if (cv::waitKey(0))
        // continue;
    }
    Mat pool[10];
    // pool[0].allocator
    int e = 3;
    for (int i = 0; i < 8; i++) {
        pool[i] = Mat(500, 500, CV_8UC3);
        for (int m = 0; m < 500; m++) {
            for (int n = 0; n < 500; n++) {
                int tmp = 0;
                for (int j = max(0, m - e); j < min(m + e, 500); j++) {
                    for (int k = max(0, n - e); k < min(n + e, 500); k++) {
                        tmp += pow(feature[i].at<uchar>(j, k), 2);
                    }
                }
                pool[i].at<uchar>(m, n) = tmp;
            }
        }
        imshow("test", feature[i]);
        if (cv::waitKey(0))
            continue;
    }

    // cv2eigen(img, mat);
    // eigen2cv(kernel, MatrixXd::Random(3, 3));

    return 0;
}
