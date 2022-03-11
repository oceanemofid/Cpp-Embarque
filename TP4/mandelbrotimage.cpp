#include "mandelbrotimage.h"


MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){
    for(int py=0; py<height;py++){
        for(int px=0; px<width;px++){
            auto[rx,ry] = convert(px,py);
                    auto[is_inside, rgb_color] = calc_in_out(rx,ry);
                    if(not is_inside){
                QColor rgb_color;
                setPixel(px, py, rgb_color);
        }
    }
}

std::pair<double,double> MandelbrotImage::convert(double px, double py){
    double cx = -0.5;
    double cy = 0.0;
    double d = 1.0;

    double px_min=0.0;
    double px_max=599.0;

    //linear interpolation with y

    //linea interpolation with x
    //px: 0        ---           599
    //rx: xc-1.5d      ---       c+1.5d
    //a , b
    double ax = (3.0*d/(px_max - px_min));
    double bx = cx - -1.5*d;
    double rx = ax*px+bx;
    return std::make_pair(rx,ry);

}

std::pair<bool, QColor> MandelbrotImage::calc_in_out(double rx, double ry)
{
    std::complex<double, double> c0( , );
    std::complex<double, double> z( , );
    for(;;){
        z = z*z+c0;
    }
        return std::make_pair(is_outside, color)


}
