#pragma
#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>


struct board_obj;  // board�� ���õ� ����ü 
struct frgm_obj;  // fragment�� ���õ� ����ü


class Board {
private:
    int thresh = 10;
    Point pre_point = Point(0, 0);  // ������ ���� ��ġ 
    Point crnt_point; // ������ ���� ��ġ 

public:
    Board();

    cv::Mat img_preproces(cv::Mat src);
    cv::Mat get_target_area(cv::Mat src); // ���� ����
    std::vector<cv::Mat> frgm_board(cv::Mat src); // ���ǳ��� ���е� ������ ����
};