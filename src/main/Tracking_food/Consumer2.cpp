#include "Tracking.h"  
#include "Matching.h"
#include "Consumer2.h"

using namespace cv;

//.......... �ʿ��� ��ü�� ����
Tracking tracker = Tracking();  // ������ �Ǵ� �������� pointing 
Matching matcher = Matching();  // ������ �ش��ϴ� �����̸� ��ȯ





void* Consumer2::consumer_doing(const Mat& frame, vector<pair<string, Rect> >& result) {


    //############# ���� �̹����� �̿��Ͽ� ###################

      // .......1. ������ �����͸� ��ǥ�� ���Ѵ�.
    Point center = tracker.tracking_point(frame);

    // .......2. ���� ��ǥ�� Ư�� ���� ���� ��� �ֳ� Ȯ���Ѵ�.
    string  answer = matcher.match_food(center, result);


    // .......3. ���� ����� �������� �ȳ��Ѵ�.



}