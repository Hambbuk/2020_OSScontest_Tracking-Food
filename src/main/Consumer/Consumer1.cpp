#include "Board.h"
#include "SocketClient.h"
#include "Consumer1.h"
#include <math.h>
#include <utility>
#include <opencv2/opencv.hpp>


using namespace cv;

//.......... �ʿ��� ��ü�� ����
Board board = Board();  
SocketClient client = SocketClient();
vector<pair<String, Rect>> matching_result;  // ������ �̸��� ��Ī�� �Լ� 


void* Consumer1::consumer_doing(const Mat& frame) {
    
    // .......1 ������ ������ ���Ѵ�.
    // �߽� check , ������ ��ġ�� �־����� 
    board_obj b_o= board.get_target_area(frame);  //�̹����� �߽��� ����ִ� ����ü ��ȯ
    board.crnt_point = b_o.board_center; // ������ �߽���ǥ update
    if (abs(board.pre_point.x - board.crnt_point.x) > 25 || abs(board.pre_point.y - board.crnt_point.y) > 25) {
        Mat board_img = b_o.board_img;
        
        // .......2 ���� ���� ���� ����
        frgm_obj f_o = board.frgm_board(board_img); // �̹����Ϳ������Ͱ� ����
        
        vector<Mat> frgm_imgs = f_o.crop_imgs;
        vector<Rect> frgm_Rects = f_o.crop_Rects;

         for (int i = 0; i < frgm_imgs.size(); i++) { // ������ ���� �̹����� �����Ѵ�.
            client.sendImage(frgm_imgs[i]);
        }

        // .......3 �������κ��� �亯�� ���� �޴´�.
         vector<string> result;
        while (1) {
            result = client.recv(); // ���� ������ ��ٸ���.
            if (result.size() != 0) break;
        }

        //matching_result�� �ʱ�ȭ ��Ű�� �����͸� ��´�.
        matching_result.clear();
        for (int i = 0; i < frgm_Rects.size(); i++) { // ������ ���� ���� ����� �̹����� �̸��� ��Ī.
            matching_result.push_back({result[i],frgm_Rects[i]});
        }

    
    }
    //########## ���� �̹����� �̿��Ͽ� #############
    pre_point = board_obj.board_center; // ������ ������ �߽���ǥ�� ���ŷ�update

   

    
    


}