#ifndef MANDELBROTIMAGE_H
#define MANDELBROTIMAGE_H

#include <QImage>
#include <QPainter>
#include <QtWidgets>
#include <vector>

class MandelbrotImage : public QImage
{  
public:
  MandelbrotImage(const int width, const int height);


private:
  //color points
  std::vector<double> xs_{ 0., 0.16, 0.42, 0.6425, 0.8575};
  std::vector<double> yr_{ 0., 32. , 237. , 215. , 0. };
  std::vector<double> yg_{ 7., 107. , 255. , 170. , 10. };
  std::vector<double> yb_{ 100., 183. , 235. , 40. , 15. };

  //vector of 2048 RGB colors
  std::vector<std::vector<QColor>> tab_colors;
  //methods
  std::pair<double,double> convert(double px, double py);
  std::pair<bool, QRgb> calc_in_out(double rx, double ry);
  double v_pixel2rect(double px, double cx, double d, double px_min, double px_max);
  double h_pixel2rect(double py, double cy, double d, double py_min, double py_max);
  //std::vector<QColor> get_value(const double x) const;
  void interpolColors(double x)
  void interpolColors();
  void create_tab_color();
  int is_valid(double color);
};

#endif // MANDELBROTIMAGE_H
