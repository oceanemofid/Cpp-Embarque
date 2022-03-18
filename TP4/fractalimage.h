#ifndef FRACTALIMAGE_H
#define FRACTALIMAGE_H

#include <QImage>
#include <QPainter>
#include <QtWidgets>
#include <vector>
#include "interpolator.h"
#include "pixel2rect.h"

class FractalImage : public QImage
{
public:
  FractalImage(const int width, const int height, double cx, double cy, double d);
  void draw();

private:
  //image parameters
  double cx_;
  double cy_;
  double d_;

  double px_min_ = 0.0;
  double px_max_ = 599.0;
  double py_min_ = 0.0;
  double py_max_ = 399.0;

  //color points
  std::vector<double> xs_{ 0., 0.16, 0.42, 0.6425, 0.8575};
  std::vector<double> yr_{ 0., 32. , 237. , 215. , 0. };
  std::vector<double> yg_{ 7., 107. , 255. , 170. , 10. };
  std::vector<double> yb_{ 100., 183. , 235. , 40. , 15. };

  //we create 3 interpolators objects (R, G, B)
  Interpolator interpolationR_{xs_,yr_};
  Interpolator interpolationG_{xs_,yg_};
  Interpolator interpolationB_{xs_,yb_};

  H_Pixel2Rect hPixel2Rect{cx_, d_, px_min_, px_max_};
  V_Pixel2Rect vPixel2Rect{cy_, d_, py_min_, py_max_};

  //methods
  double h_pixel2rect(double px);
  QRgb interpolColors(double x);
  void create_gradient_colors();
  void process_sub_image(int current_thread, int max_threads);

protected:
  virtual QRgb calc_in_out(double rx, double ry) = 0;

  std::vector<QRgb> tab_colors_; //vector of 2048 RGB colors
};

class MandelbrotImage : public FractalImage {
public:
    MandelbrotImage(const int width, const int height, double cx, double cy, double d) :
        FractalImage(width, height, cx, cy, d) {}
protected:
    QRgb calc_in_out(double rx, double ry) override;
};

class JuliaImage : public FractalImage {
public:
    JuliaImage(const int width, const int height, double cx, double cy, double d) :
        FractalImage(width, height, cx, cy, d) {}
protected:
    QRgb calc_in_out(double rx, double ry) override;
};

#endif // FRACTALIMAGE_H
