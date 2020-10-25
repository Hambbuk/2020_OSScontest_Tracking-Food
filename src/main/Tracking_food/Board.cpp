#include "opencv2/opencv.hpp"
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include <iostream>
#include <string>
#include "Board.h"

using namespace cv;
using namespace std;


Board::Board() {}


Mat Board::img_preproces(Mat src)
{
    //�̹��� ��ó�� ����
    //�̹��� ������� ��ȯ�� ������ ���Ҹ� ���� ��ó��
    Mat src_gray;
    cvtColor(src, src_gray, COLOR_BGR2GRAY);
    blur(src_gray, src_gray, Size(3, 3));

    //canny�Լ��� �̿��Ͽ� �̹����� ��������
    Mat canny_output;
    Canny(src_gray, canny_output, thresh, thresh * 2);

    return canny_output;
}

board_obj Board::get_target_area(Mat src)
{

    board_obj my_board_obj;
    //�̹������� ������ �������� ����
    Mat img_pre = img_preproces(src);

    //������ �������� �ձ� ���� canny edge���� ���� point���� Ȯ��
    Mat mask = getStructuringElement(MORPH_RECT, Size(2, 2), Point(1, 1));
    Mat dilate_edge;
    dilate(img_pre, dilate_edge, mask, Point(-1, -1), 1);

    //edge�� Ȯ���� �̹������� contour�� ã��
    vector<vector<Point>> contours;
    findContours(dilate_edge, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    vector<vector<Point>> contours_poly(contours.size());
    Rect boundRect;

    vector<Point> biggest_area = contours[0];

    //�̹������� ���� ū �������� ã��
    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], contours_poly[i], 20, true);

        if (contourArea(contours_poly[i]) > contourArea(biggest_area))
        {
            biggest_area = contours_poly[i];
        }
    }

    //������ ã�� ����ū �������� �簢������ ��ȯ
    boundRect = boundingRect(biggest_area);
    rectangle(src, boundRect.tl(), boundRect.br(), (0, 0, 255), 2);

    // ������ �߽��� ���Ѵ�.
    my_board_obj.board_center = Point((boundRect.x + boundRect.width) / 2, (boundRect.y + boundRect.height) / 2);


    //�簢���� ���ɿ������� �ϰ� �̹����� crop
    my_board_obj.board_img = src(boundRect);
    imshow("Contours", my_board_obj.board_img);
    waitKey();

    return my_board_obj;
}

frgm_obj Board::frgm_board(Mat src)
{

    frgm_obj my_frgm_obj;
    //�̹��� ��ó��
    Mat img_pre = img_preproces(src);
    //�̹��� �ȿ��� contours�� ã��
    vector<vector<Point>> contours;
    findContours(img_pre, contours, RETR_TREE, CHAIN_APPROX_SIMPLE);

    imshow("Contours", img_pre);
    waitKey();

    vector<vector<Point>> contours_poly(contours.size());
    vector<Rect> boundRect;

    //���� ũ�� ������ contour�� ������
    for (size_t i = 0; i < contours.size(); i++)
    {
        approxPolyDP(contours[i], contours_poly[i], 20, true);

        if (contourArea(contours_poly[i]) < 600 || contourArea(contours_poly[i]) > 2000)
        {
            continue;
        }
        cout << contourArea(contours_poly[i]) << endl;
        //���͸��� contours�� �簢������ ��ȯ��
        boundRect.push_back(boundingRect(contours_poly[i]));
    }

    Mat drawing = Mat::zeros(img_pre.size(), CV_8UC3);



    //������ ���� �簢�� ������ ������ �������� �ν��ϰ�
    //������ ������ŭ �̹����� crop�Ͽ� ����
    for (size_t i = 0; i < boundRect.size(); i++)
    {
        drawContours(drawing, contours_poly, (int)i, (0, 0, 255));
        rectangle(src, boundRect[i].tl(), boundRect[i].br(), (0, 0, 255), 2);
        cout << boundRect[i].x << " " << boundRect[i].y << " " << boundRect[i].width << " " << boundRect[i].height << endl;
        my_frgm_obj.crop_imgs.push_back(src(boundRect[i]));
        my_frgm_obj.crop_Rects.push_back(boundRect[i]);
    }
    imshow("Contours", src);
    waitKey();

    return my_frgm_obj;
}