#include "definition_camera_ids.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "image_converting.h"

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

void MainWindow::enableButtons() {
  qDebug() << "enableButtons";

  ui->takePhotos->setEnabled(true);
  ui->showCam->setEnabled(true);
}

void MainWindow::endedCameraOutput() {
  qDebug() << "endedCameraOutput()";

  cam = nullptr;
}

void MainWindow::showOutputCam(int id) {
  if (cam != nullptr) {
    qDebug() << "Camera is already opened";
    return;
  }
  cam = new Camera(id);

  QThread* thread = new QThread;
  cam->moveToThread(thread);

  connect(thread, SIGNAL(started()), cam, SLOT(start()));
  connect(cam, SIGNAL(finished()), thread, SLOT(quit()));
  connect(cam, SIGNAL(finished()), cam, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), this, SLOT(endedCameraOutput()));
  connect(this, SIGNAL(stopShowingCam()), cam, SLOT(stop()));

  thread->start();
}

void MainWindow::defineCameraIds() {
  DefinitionCameraIds* defCamIds = new DefinitionCameraIds(&cameraId1, &cameraId2);

  QThread* thread = new QThread;
  defCamIds->moveToThread(thread);

  connect(thread, SIGNAL(started()), defCamIds, SLOT(defineCameraIds()));
  connect(defCamIds, SIGNAL(finished()), thread, SLOT(quit()));
  connect(defCamIds, SIGNAL(finished()), this, SLOT(enableButtons()));
  connect(defCamIds, SIGNAL(finished()), defCamIds, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

  thread->start();
}

void MainWindow::takePhoto(int cameraId, QLabel* label) {
  qDebug() << "Take photo from " << cameraId;

  VideoCapture cap;

  if (cap.open(cameraId)) {
    Mat frame;

    cap >> frame;
    if (!frame.empty()) {
      QImage image = IMGCONV::cvMatToQImage(frame).scaled(320, 240, Qt::KeepAspectRatio);
      label->setPixmap(QPixmap::fromImage(image));
    } else {
      label->setText("Frame from camera is empty");
    }
  } else {
    label->setText("Camera is not opened");
  }

  cap.release();
}

void MainWindow::on_takePhotos_clicked() {
  qDebug() << "emit stopShowingCam";
  emit stopShowingCam();

  QThread::msleep(1000);

  takePhoto(cameraId1, ui->image1);
  takePhoto(cameraId2, ui->image2);
}

void MainWindow::on_showCam_clicked() {
  if (cameraId1 > 0) {
    showOutputCam(cameraId1);
  } else if (cameraId2 > 0) {
    showOutputCam(cameraId2);
  } else {
    qDebug() << "Not found camera's";
  }
}

void MainWindow::on_test_clicked() {
  VideoCapture cap1, cap2;
  int id = 700;

  if (cap1.open(id)) {
    for (int i = 0; i < 100; i++) {
      Mat frame;

      cap1 >> frame;
      imshow("Cap1", frame);
    }
  }

  cap1.release();

  if (cap2.open(id)) {
    for (int i = 0; i < 100; i++) {
      Mat frame;

      cap2 >> frame;
      imshow("Cap2", frame);
    }
  }
}
