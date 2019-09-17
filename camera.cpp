#include "camera.h"
#include<QDebug>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

Camera::Camera(int id, QLabel* output) {
  this->output = output;

  isWork = cap.open(id);

  cap.set(CAP_PROP_FRAME_WIDTH, 320);
  cap.set(CAP_PROP_FRAME_HEIGHT, 240);
}

void Camera::start() {
  if (!cap.isOpened()) {
    isWork = false;
    qDebug() << "Camera is not opened";
  }

  while(isWork) {
    Mat frame;

    cap >> frame; // get a new frame from camera
    if(frame.empty()) {
      qDebug() << "Frame is empty";
      break; // end of video stream
    }

    //imshow("Cam", frame);
    QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888));

    output->setPixmap(pixmap);
    if (waitKey(10) == 27)
      break;
  }

  qDebug() << "Camera output is finished";

  emit finished();
}

void Camera::stop() {
  isWork = false;
  output = nullptr;
}


