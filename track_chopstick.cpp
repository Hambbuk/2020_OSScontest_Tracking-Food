#include <opencv2/opencv.hpp>
#include <iostream>

using namespace cv;
using namespace std;

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
	Vec4i detect_chopstic(Mat img, int thr, int minLineLength, int maxLineGap)
	{
		lines.clear();
		HoughLinesP(img, lines, 1, CV_PI / 180, thr, minLineLength, maxLineGap);
		if (lines.empty())
		{
			return NULL;
		}

		return lines[0];
	}
	//������ ��ǥ ��ȯ�ϴ� �Լ�
	Vec3f detect_spoon(Mat img, int minDistance, int thr)
	{
		circles.clear();
		HoughCircles(img, circles, HOUGH_GRADIENT, 1, minDistance, thr, thr / 2, 10, 50);
		if (circles.empty())
		{
			return NULL;
		}

		return circles[0];
	}
	//��� ����� �Լ�
	Mat make_mask_image(Mat img)
	{
		cvtColor(img, img_YCrCb, COLOR_BGR2YCrCb);
		inRange(img_YCrCb, Scalar(0, 133, 77), Scalar(255, 173, 127), mask);
		bitwise_not(mask, mask);
		return mask;
	}
	//tracking point
	Point2i tracking_point(Mat frame)
	{
		if (frame.empty())
		{
			cout << "Could not open camera :(" << endl;
		}

		//frame ���� ��ó��(640x480, �¿����, 3x3 ����þ� ��)
		resize(frame, frame, Size(640, 480));
		flip(frame, frame, 1);
		GaussianBlur(frame, blur, Size(3, 3), 0);

		//�ʱ� ������ ����ũ Mat ����
		if (foreground_mask.empty())
		{
			foreground_mask.create(frame.size(), frame.type());
		}

		// 1.������ ����ũ ����� ������ ����(5x5 �̵�� ����)
		bg_model->apply(blur, foreground_mask);
		Mat kernel = getStructuringElement(MORPH_RECT, Size(5, 5), Point(-1, -1));
		morphologyEx(foreground_mask, foreground_mask, MORPH_CLOSE, kernel);
		medianBlur(foreground_mask, foreground_mask, 5);

		// 2.�����󿡼� ������� �� skin_mask�� ����
		copyTo(frame, skin_mask, foreground_mask);
		skin_mask = make_mask_image(frame);

		// 3.�ı⸸ ���� ���� ����ȭ
		bitwise_and(skin_mask, foreground_mask, foreground_mask);

		// 4.����ȭ ���� Canny ����
		Canny(foreground_mask, img_canny, 50, 150);
		//������
		imshow("canny_img", img_canny);

		// 5.�������� ã���� �ٷ� ��ȯ�ϰ�, �������� ������ ������ ��ǥ ��ȯ
		//������ ����Ʈ
		Vec3f s = NULL;
		s = detect_spoon(img_canny, 10, 30);
		if (s[0] > 0 && s[1] > 0 && s[2] > 0)
		{
			circle(frame, Point(s[0], s[1]), s[2], Scalar(0, 255, 0), 2);
			//circle(frame, Point(s[0], s[1]), 2, Scalar(255, 0, 0), -1);
			return Point(s[0], s[1]);
		}

		//������ ����Ʈ
		Vec4i c = NULL;
		c = detect_chopstic(img_canny, 70, 15, 100);
		if (c[0] > 0 && c[1] > 0 && c[2] > 0 && c[3] > 0)
		{
			line(frame, Point(c[0], c[1]), Point(c[2], c[3]), Scalar(0, 255, 0), 2, 10);
			//���󿡼� �� �����ִ� ����Ʈ ��ȯ
			return Point(c[1] > c[3] ? c[2] : c[0], c[1] > c[3] ? c[3] : c[1]);
			//circle(frame, Point(x, y), 5, Scalar(255, 0, 0), -1);
		}
	}
};

int main()
{
	Mat frame;
	Point2i x, y;
	VideoCapture cap;
	Tracking t = Tracking();
	cap.open(0);
	cap.set(CAP_PROP_AUTOFOCUS, 0);

	while (true)
	{
		cap.read(frame);
		flip(frame, frame, 1);
		x, y = t.tracking_point(frame);
		circle(frame, (x, y), 5, Scalar(255, 0, 0), -1);
		imshow("frame", frame);
		if (waitKey(5) >= 0)
			break;
	}
	return 0;
}