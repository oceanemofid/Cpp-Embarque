#include <QtWidgets>

#include <iostream>
#include <string>
#include <chrono>

#include "mainwindow.h"
#include "Commify.h"
#include "fractalimage.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  //
  // construct image_widget

  image_widget_ = new QLabel;
  image_widget_->setBackgroundRole(QPalette::Base);
  image_widget_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
  image_widget_->setScaledContents(true);
  image_widget_->setMinimumSize(300, 300);

  create_actions();
  create_menus();

  setCentralWidget(image_widget_);
  resize(QGuiApplication::primaryScreen()->availableSize() * 2 / 5);
}


void MainWindow::create_actions() {
  //
  action_Mandelbrot_image_ = new QAction(tr("Mandelbrot Image"), this);
  connect(action_Mandelbrot_image_, SIGNAL(triggered()), this, SLOT(slot_load_fractal_image()));

  action_exit_ = new QAction(tr("E&xit"), this);
  action_exit_->setShortcut(tr("Ctrl+Q"));
  connect(action_exit_, SIGNAL(triggered()), this, SLOT(slot_exit()));

  action_about_ = new QAction(tr("&About"), this);
  connect(action_about_, SIGNAL(triggered()), this, SLOT(slot_about()));
}

void MainWindow::slot_exit() {
  close();
}

void MainWindow::slot_about() {
    QMessageBox::about(this, tr("About Image Viewer"),
            tr("<p>The user can select several images to be displayed on the screen</p>"));
}


void MainWindow::create_menus() {
  menu_open_ = new QMenu(tr("&Open"), this);

  menu_open_->addAction(action_Mandelbrot_image_);
  menu_open_->addAction(action_exit_);


  menu_help_ = new QMenu(tr("&Help"), this);
  menu_help_->addAction(action_about_);

  menuBar()->addMenu(menu_open_);
  menuBar()->addMenu(menu_help_);
}


//Mandelbrot
const int image_width = 600;
const int image_height = 400;

void MainWindow::slot_load_fractal_image() {
    // Create a QImage of required size
    // Draw a Mandelbrotimage
    auto start = std::chrono::high_resolution_clock::now();

    //create the Mandelbrotimage
    FractalImage* fractal_image;
    switch(imageType_) {
    case ImageType::Mandelbrot:
        fractal_image = new MandelbrotImage(image_width, image_height, xc_, yc_, d_);
        break;
    case ImageType::Julia:
        fractal_image = new JuliaImage(image_width, image_height, xc_, yc_, d_);
    default:
        break;
    }
    fractal_image->draw();

    auto end = std::chrono::high_resolution_clock::now();
    auto interval = end - start;
    int64_t t = std::chrono::duration_cast<std::chrono::microseconds>(interval).count();

    //prints the execution time
    Commify exe_time(t);
    std::cout << "INFO: image calculated in  " << exe_time << " us\n";

    image_widget_->setPixmap(QPixmap::fromImage(*fractal_image));
    image_widget_->setFixedSize(image_width, image_height);
    adjustSize();

    delete fractal_image;
 }

void MainWindow::keyPressEvent(QKeyEvent *event) {
  bool updateNeeded = false;

  switch (event->key()) {
  case Qt::Key_T:
      imageType_ = imageType_ == ImageType::Julia ? ImageType::Mandelbrot : ImageType::Julia;
      updateNeeded = true;
      break;

  case Qt::Key_Left:
      xc_ -= 0.1 * d_;
      updateNeeded = true;
      break;

  case Qt::Key_Right:
      xc_ += 0.1 * d_;
      updateNeeded = true;
      break;

  case Qt::Key_Up:
      yc_ += 0.1 * d_;
      updateNeeded = true;
      break;

  case Qt::Key_Down:
      yc_ -= 0.1 * d_;
      updateNeeded = true;
      break;

  case Qt::Key_Plus:
      d_ = d_ / 1.5;
      updateNeeded = true;
      break;

  case Qt::Key_Minus:
      d_ = d_ * 1.5;
      updateNeeded = true;
      break;

  default:
      QMainWindow::keyPressEvent(event);
  }

  //Update image only if needed
  if (updateNeeded) {
      slot_load_fractal_image();
  }
}

  //
  // You probably don't want to change these lines
  //
