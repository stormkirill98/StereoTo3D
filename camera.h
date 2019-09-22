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
  QLabel* output;
  bool isWork;

 public:
  Camera(int id, QLabel* output);

 public slots:
  void start();
  void stop();

 signals:
  void finished();
};

#endif // CAMERA_H
