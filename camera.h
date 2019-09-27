#ifndef CAMERA_H
#define CAMERA_H

#include <QLabel>
#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

class Camera : public QObject {
  Q_OBJECT

 private:
  VideoCapture cap;
  bool isWork;

 public:
  Camera(int id);

 public slots:
  void start();
  void stop();

 signals:
  void finished();
};

#endif // CAMERA_H
