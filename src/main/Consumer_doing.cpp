#include "Tracking.h"  
#include "Matching.h"
#include "Consumer_doing.h"

using namespace cv;

//.......... �ʿ��� ��ü�� ����
Tracking tracker = Tracking();  // ������ �Ǵ� �������� pointing 
Matching matcher = Matching();  // ������ �ش��ϴ� �����̸� ��ȯ

    

void* Consumer::consumer_doing(const Mat& frame) {


//############# ���� �̹����� �̿��Ͽ� ###################

    // .......1. ������ �����͸� ��ǥ�� ���Ѵ�.
    Point2i x, y = tracker.tracking_point(frame);

    // .......2. ���� ��ǥ�� Ư�� ���� ���� ��� �ֳ� Ȯ���Ѵ�.
    


    // .......3. ���� ����� �������� �ȳ��Ѵ�.



}