#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QMainWindow>
#include "camera.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 public slots:
  void enableMenuBar();
  void endedCameraOutput();

 private slots:
  void on_actionShowCamera_triggered();

  void on_actionTakePhotos_triggered();

 private:
  Ui::MainWindow* ui;
  int cameraId1 = -1, cameraId2 = -1;
  Camera* cam = nullptr;

 private:
  void showOutputCam(int id);
  void takePhoto(int cameraId, QLabel* label);
  void defineCameraIds();

 signals:
  void stopShowingCam();
};

#endif // MAINWINDOW_H
