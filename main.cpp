#include <stdio.h>
#include <opencv2/opencv.hpp>
#include <iostream>
#define HAVE_STRUCT_TIMESPEC
#include <pthread.h>
#include <queue>
#include "Guess.h"

using namespace cv;
using namespace std;

// 0....��ķ �����ֱ�
VideoCapture vcap;
Mat frame;
// 1....Thread ����
pthread_mutex_t frameLocker;
pthread_t UpdThread;


// 2....Ŭ���� ��ü �����ϱ�
Guess guess;
// 3....�̹����� ���� ť����
deque<Mat> frameSeq;

// �̹����� �о QUEUE�� ��� ������ 
void* UpdateFrame(void* arg)
{
    for (;;)
    {
        Mat tempFrame;
        vcap >> tempFrame;

        frame = tempFrame;
        // queue�� �̹��� ���
        frameSeq.push_back(frame.clone());
        //if framneSeq    

    }

    pthread_exit((void*)0);
}


int main(int, char**)
{
    vcap.open(0);

    pthread_mutex_init(&frameLocker, NULL);
    pthread_create(&UpdThread, NULL, UpdateFrame, NULL);


    for (;;)
    {
        Mat currentFrame, grayImage;

        pthread_mutex_lock(&frameLocker);
        currentFrame = frame;
        pthread_mutex_unlock(&frameLocker);


        if (currentFrame.empty())
            continue;


        cvtColor(currentFrame, grayImage, COLOR_BGR2GRAY);
        imshow("Input Image", frameSeq.front());
        guess.showimage(currentFrame);

        //ESCŰ�� ������ �����带 ���� ������.. ���α׷� �����Ѵ�. 
        if (waitKey(20) == 27)
        {

            int ret = pthread_cancel(UpdThread);
            int status;

            if (ret == 0)
            {
                //�ڵ� ����    
                ret = pthread_join(UpdThread, (void**)&status);
                if (ret == 0)
                    //���� �����Ű�� status�� -1�� ���ϵȴ�. 
                    cout << "������ ���� ����" << status << endl;
                else
                    cout << "������ ���� ����" << ret << endl;

                break;
            }
        }

    }

    return 0;
}