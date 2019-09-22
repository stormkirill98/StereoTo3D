#include "definition_camera_ids.h"

#include <QDebug>

DefinitionCameraIds::DefinitionCameraIds(int* id1, int* id2) {
  this->id1 = id1;
  this->id2 = id2;
}

bool DefinitionCameraIds::checkCameraId(int id) {
  if (id < 1) {
    return false;
  }

  VideoCapture cap;
  return cap.open(id);
}

int DefinitionCameraIds::defineCameraId(int alreadyUsedId) {
  VideoCapture cap;
  int i = 0;

  while (i++ < NUMBER_SORTED_ID) {
    if (i != alreadyUsedId) {
      if (cap.open(i))
        return i;
    }
  }

  return -1;
}

void DefinitionCameraIds::defineCameraIds() {
  qDebug() << "Start camera ids definition";
  if (!checkCameraId(*id1)) {
    *id1 = defineCameraId(*id2);
    qDebug() << "Define first camera id = " << *id1;
  }

  if (!checkCameraId(*id2)) {
    *id2 = defineCameraId(*id1);
    qDebug() << "Define second camera id = " << *id2;
  }

  qDebug() << "End camera ids definition";
  emit finished();
}
