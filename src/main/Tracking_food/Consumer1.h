#pragma once
using namespace cv;


// image�� �޾Ƽ� Tracking�ϴ� -> matching Thread



class Consumer1 {

public:
	
	
	void* consumer_doing(const Mat& frame, vector<pair<string, Rect>>& v);
};
