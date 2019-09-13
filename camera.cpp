#include "camera.h"
#include<QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Camera::Camera(int id)
{
    cap.open(id);
    isWork = true;
}

void Camera::start()
{
//    if (!cap.isOpened())
//        return;
    int i = 3;
    while (!cap.open(i++)) {
    }
    qDebug() << i;

    Mat frame;
    while(isWork) {
        cap >> frame; // get a new frame from camera
        if( frame.empty())
            break; // end of video stream

        imshow("Cam", frame);
        if (waitKey(10) == 27)
            break;
    }

    emit finished();
}

void Camera::stop()
{
    isWork = false;
}


