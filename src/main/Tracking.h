#pragma once
#include <opencv2/opencv.hpp>
#include <vector>
using namespace cv;




class Tracking {
private:
	Mat blur, skin_mask, foreground_mask, img_canny;
	//������ background ����(history = -1, threshold = 400, shadow = false) 
	Ptr<BackgroundSubtractor> bg_model = createBackgroundSubtractorMOG2(-1, 400, false);
	vector<Vec4i> lines;
	vector<Vec3f> circles;
	Mat img_YCrCb;
	Mat mask;
public:


	//������ ��ǥ ��ȯ�ϴ� �Լ�
	Vec4i detect_chopstic(Mat img, int thr, int minLineLength, int maxLineGap);

	//������ ��ǥ ��ȯ�ϴ� �Լ�
	Vec3f detect_spoon(Mat img, int minDistance, int thr);

	//��� ����� �Լ�
	Mat make_mask_image(Mat img);

	//tracking point �������� ��ǥ ��ȯ _______ �̰͸� ���!!
	Point2i tracking_point(Mat frame);
};
