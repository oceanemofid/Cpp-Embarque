#ifndef MANDELBROTIMAGE_H
#define MANDELBROTIMAGE_H

#include <QImage>
#include <QPainter>
#include <QtWidgets>
#include <vector>
#include "interpolator.h"

class MandelbrotImage : public QImage
{
public:
  MandelbrotImage(const int width, const int height, const double xc, const double yc, const double d);

private:

  double px_min = 0.0;
  double px_max = 599.0;
  double py_min = 0.0;
  double py_max = 399.0;

  //color points
  std::vector<double> xs_{ 0., 0.16, 0.42, 0.6425, 0.8575};
  std::vector<double> yr_{ 0., 32. , 237. , 215. , 0. };
  std::vector<double> yg_{ 7., 107. , 255. , 170. , 10. };
  std::vector<double> yb_{ 100., 183. , 235. , 40. , 15. };
  std::vector<QRgb> tab_colors; //vector of 2048 RGB colors

  //we create 3 interpolators objects (R, G, B)
  Interpolator interpolation_R{xs_,yr_};
  Interpolator interpolation_G{xs_,yg_};
  Interpolator interpolation_B{xs_,yb_};

  //methods
  double h_pixel2rect(double px, double cx, double d, double px_min, double px_max);
  double v_pixel2rect(double py, double cy, double d, double py_min, double py_max);
  QRgb interpolColors(double x);
  QRgb calc_in_out(double rx, double ry);
  QRgb calc_Julia(double rx, double ry);
  void create_gradient_colors();
  void process_sub_image(int current_thread, int max_threads, double xc, double yc, double d);
};

#endif // MANDELBROTIMAGE_H
