#pragma

struct board_obj {
    cv::Point board_center;
    cv::Mat board_img;
};

struct frgm_obj {
    std::vector<cv::Mat> crop_imgs; // �߸� �̹����� ��°�
    std::vector<cv::Rect> crop_Rects; // �߸� �̹����� ��ġ�� ��°� 
};


class Board {
private:
    int thresh = 10;
   

public:

    Board();


    Point pre_point = Point(0, 0);  // ������ ���� ��ġ 
    Point crnt_point; // ������ ���� ��ġ 

    cv::Mat img_preproces(cv::Mat src);
    board_obj get_target_area(cv::Mat src);
    frgm_obj frgm_board(cv::Mat src);
};