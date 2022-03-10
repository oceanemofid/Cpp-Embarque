
#include "mainwindow.h"
#include <iostream>
#include <string>
#include <QtWidgets>



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
  action_triangle_image_ = new QAction(tr("Triangle Image"), this);
  connect(action_triangle_image_, SIGNAL(triggered()), this, SLOT(slot_load_triangle_image()));

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

  menu_open_->addAction(action_triangle_image_);
  menu_open_->addAction(action_exit_);


  menu_help_ = new QMenu(tr("&Help"), this);
  menu_help_->addAction(action_about_);

  menuBar()->addMenu(menu_open_);
  menuBar()->addMenu(menu_help_);
}



//
// Triangle
//
const int triangle_image_width = 600;
const int triangle_image_height = 600;

void MainWindow::slot_load_triangle_image() {

  // The ~10 lines of code below must be changed with your code 
  // Create a QImage of required size
  // Draw a simple black/white checker board

  QImage triangle_image(triangle_image_width, triangle_image_height, QImage::Format_RGB32);
  QPainter painter(&triangle_image);
  painter.fillRect(triangle_image.rect(), Qt::black);

  //border
  const QColor gridColor(51, 245, 102);
  QPen gridPen(gridColor);
  painter.setPen(gridPen);
  painter.drawLine(triangle_image.rect().topLeft(), triangle_image.rect().topRight());
  painter.drawLine(triangle_image.rect().topRight(), triangle_image.rect().bottomRight());
  painter.drawLine(triangle_image.rect().bottomRight(), triangle_image.rect().bottomLeft());
  painter.drawLine(triangle_image.rect().bottomLeft(), triangle_image.rect().topLeft());
  int m = 0;
  for (int y = 0; y < triangle_image_height; ++y) {
    for (int x = 0; x < triangle_image_width; ++x) {
        if(x%60==0||y%60==0){
                if(m%5==0){
                    triangle_image.setPixel(x, y, qRgb(51, 245, 102));
                }

        }
        m++;

    }
    m++;

 }



  //
  // You probably don't want to change these lines 
  //

  image_widget_->setPixmap(QPixmap::fromImage(triangle_image));
  image_widget_->setFixedSize(triangle_image_width, triangle_image_height);
  adjustSize();
}
