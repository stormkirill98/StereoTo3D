#include "camera.h"
#include "definition_camera_ids.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <QDebug>
#include <QThread>

using namespace std;

MainWindow::MainWindow(QWidget* parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow) {
  ui->setupUi(this);

  defineCameraIds();
}

MainWindow::~MainWindow() {
  delete ui;
}

void MainWindow::openCam(int id, QLabel* output) {
  Camera* cam = new Camera(id, output);

  QThread* thread = new QThread;
  cam->moveToThread(thread);

  connect(thread, SIGNAL(started()), cam, SLOT(start()));
  connect(cam, SIGNAL(finished()), thread, SLOT(quit()));
  connect(cam, SIGNAL(finished()), cam, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

  thread->start();
}

void MainWindow::defineCameraIds() {
  DefinitionCameraIds* defCamIds = new DefinitionCameraIds(&cameraId1, &cameraId2);

  QThread* thread = new QThread;
  defCamIds->moveToThread(thread);

  connect(thread, SIGNAL(started()), defCamIds, SLOT(defineCameraIds()));
  connect(defCamIds, SIGNAL(finished()), thread, SLOT(quit()));
  connect(defCamIds, SIGNAL(finished()), defCamIds, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

  thread->start();
}

void MainWindow::takePhoto() {
  VideoCapture cap;
  int i = 1, countOpenCam = 0;

  cap.set(CAP_PROP_FRAME_WIDTH, 320);
  cap.set(CAP_PROP_FRAME_HEIGHT, 240);

  while (i < 1024 && countOpenCam < 2) {
    if (!cap.open(i++))
      continue;
    countOpenCam++;

    qDebug() << i;
    Mat frame;

    cap >> frame;
    if(frame.empty()) {
      qDebug() << "Frame is empty";
      break; // end of video stream
    }

    QPixmap pixmap = QPixmap::fromImage(QImage((unsigned char*) frame.data, frame.cols, frame.rows, QImage::Format_RGB888));
    if (countOpenCam == 1) {
      ui->image1->setPixmap(pixmap);
    } else {
      ui->image2->setPixmap(pixmap);
    }
  }
}


QList<int> MainWindow::getCameraIds() {
  QList<int> ids;

  VideoCapture cap;
  int i = 0;

  while(i < 1024) {
    if (cap.open(++i)) {
      qDebug() << "Camera id = " << i;
      ids << i;
    }
  }

  return ids;
}

void MainWindow::on_pushButton_clicked() {
  takePhoto();
}
