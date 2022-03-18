
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>

QT_BEGIN_NAMESPACE
class QAction;
class QLabel;
class QMenu;
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() override = default;

  QLabel *image_widget_;

private slots:
  void slot_exit();
  void slot_about();
  void slot_load_fractal_image();

private:
  void create_menus();
  void create_actions();
  void keyPressEvent(QKeyEvent *event) override;

  QAction *action_Mandelbrot_image_;
  QAction *action_about_;
  QAction *action_exit_;

  QMenu *menu_open_;
  QMenu *menu_help_;

  enum class ImageType {
      Mandelbrot, Julia
  };

  ImageType imageType_ = ImageType::Mandelbrot;
  double xc_ = -0.5;
  double yc_ = 0.0;
  double d_ = 1.0;
};


#endif  // MAINWINDOW_H
