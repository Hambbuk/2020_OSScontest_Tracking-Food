#pragma once
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;


// image�� �޾Ƽ� Tracking�ϴ� -> matching Thread


class Consumer {

public:
	void* consumer_doing(const Mat& frame);
};
