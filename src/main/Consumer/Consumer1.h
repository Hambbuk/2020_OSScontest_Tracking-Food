#pragma once
#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#include "Board.h"
using namespace cv;


// image�� �޾Ƽ� Tracking�ϴ� -> matching Thread



class Consumer1 {

public:
	
	
	void* consumer_doing(const Mat& frame);
};
