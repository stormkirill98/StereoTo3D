#ifndef DEFINITION_CAMERA_IDS_H
#define DEFINITION_CAMERA_IDS_H

#include <QObject>

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

#define NUMBER_SORTED_ID 1024

class DefinitionCameraIds : public QObject {
  Q_OBJECT

 private:
  int* id1, *id2;

 public:
  DefinitionCameraIds(int* id1, int* id2);

 private:
  bool checkCameraId(int id);
  int defineCameraId(int alreadyUsedId);

 public slots:
  void defineCameraIds();

 signals:
  void finished();
};

#endif // DEFINITION_CAMERA_IDS_H
