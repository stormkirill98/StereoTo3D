#include "camera.h"
#include<QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <QCoreApplication>
#include <QTime>

Camera::Camera(int id) {
  isWork = cap.open(id);
}

void Camera::start() {
  while(isWork) {
    Mat frame;

    cap >> frame; // get a new frame from camera
    if(frame.empty()) {
      qDebug() << "Frame is empty";
      break; // end of video stream
    }

    imshow("Cam", frame);

    if (waitKey(1) == 27)
      break;

    QCoreApplication::processEvents(QEventLoop::AllEvents, 1);
  }

  qDebug() << "Camera output is finished";


  destroyAllWindows();
  cap.release();
  emit finished();
}

void Camera::stop() {
  qDebug() << "Stop camera";

  isWork = false;
}
