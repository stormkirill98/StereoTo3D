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

void MainWindow::enableMenuBar() {
  qDebug() << "enableMenuBar";

  ui->menuBar->setEnabled(true);
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
  connect(defCamIds, SIGNAL(finished()), this, SLOT(enableMenuBar()));
  connect(defCamIds, SIGNAL(finished()), defCamIds, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

  thread->start();
}

void MainWindow::takePhoto(int cameraId, QLabel* label) {
  qDebug() << "Take photo from " << cameraId;
  ui->statusBar->showMessage(QString("Take photo from %1").arg(cameraId));

  VideoCapture cap;

  if (cap.open(cameraId)) {
    Mat frame;

    cap >> frame;
    if (!frame.empty()) {
      QImage image = IMGCONV::cvMatToQImage(frame);
      label->setFixedSize(image.width(), image.height());
      label->setPixmap(QPixmap::fromImage(image));
    } else {
      label->setText("Frame from camera is empty");
    }
  } else {
    label->setText("Camera is not opened");
  }

  cap.release();
}

void MainWindow::on_actionShowCamera_triggered() {
  if (cameraId1 > 0) {
    showOutputCam(cameraId1);
  } else if (cameraId2 > 0) {
    showOutputCam(cameraId2);
  } else {
    qDebug() << "Not found camera's";
  }
}

void MainWindow::on_actionTakePhotos_triggered() {
  qDebug() << "emit stopShowingCam";
  emit stopShowingCam();

  QThread::msleep(1000);

  takePhoto(cameraId1, ui->image1);
  takePhoto(cameraId2, ui->image2);
}
