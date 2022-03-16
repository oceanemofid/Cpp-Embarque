#include "mandelbrotimage.h"
#include "interpolator.h"
#include "Commify.h"
#include <iostream>
#include <complex>
#include <cmath>
#include <chrono>

MandelbrotImage::MandelbrotImage(const int width, const int height): QImage (width, height, QImage::Format_RGB32){
    auto start = std::chrono::high_resolution_clock::now();
    create_tab_color();
    double cx = -0.5;
    double cy = 0.0;
    double d = 1.0;

    double px_min=0.0;
    double px_max=599.0;
    double py_min=0.0;
    double py_max=399.0;

    for(int py=0; py<height;py++){
        double ry = v_pixel2rect(py,cy,d,py_min,py_max);
        for(int px=0; px<width;px++){
            double rx = h_pixel2rect(px,cx,d,px_min,px_max);
            //auto[rx,ry] = convert(px,py);
            QRgb rgb_color =calc_in_out(rx,ry);
            setPixel(px, py, rgb_color);
        }
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto interval = end-start;
    int64_t t = std::chrono::duration_cast<std::chrono::microseconds>(interval).count();
    Commify exe_time(t);
    std::cout << "INFO: image calculated in  " << exe_time << "us\n";
}


double MandelbrotImage::h_pixel2rect(double px, double cx, double d, double px_min, double px_max){
    //linea interpolation with x
    //px: 0        ---           599
    //rx: xc-1.5d      ---       xc+1.5d
    //a , b
    double ax = (3.0*d/(px_max - px_min));
    double bx = cx -1.5*d;
    double rx = ax*px+bx;
    return rx;
}

double MandelbrotImage::v_pixel2rect(double py, double cy, double d, double py_min, double py_max){
    //linea interpolation with y
    //py: 0        ---           399
    //ry: yc+d      ---          yc-d
    //a , b
    double ay = (2.0*d/(py_max - py_min));
    double by = cy + d;
    double ry = -ay*py+by;
    return ry;
}

QRgb MandelbrotImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex c0(rx,ry);
    std::complex z(0.0,0.0);
    QRgb color= qRgb(0, 0, 0);//we initialise with black
    bool is_inside =true;
    int i = 0.0;
    int cpt = 0.0;
    double mod = 0.0;


    for(int n=0; n<512; n++){
        z = z*z+c0;
        double module= sqrt(z.real()*z.real()+z.imag()*z.imag());
        if(module>2){
            is_inside=false;
            mod = module;
         }
         if(!is_inside and module>=256){
                 cpt = n;
                 double v = log2(log2(mod*mod));
                 i = static_cast<int>(1024*sqrt(cpt+5-v))%2048;
                 color = tab_colors[i];
                 return color;
         }
        }
       return color;
    }


/*
 * Role:Create the vector of nb_color colors
 */
void MandelbrotImage::create_tab_color(){
    //nb of colors we want
    double nb_color= 2048.0;

    //we iterate to calculate the 2048 RGB colors
    for(double i=0.0; i<nb_color; i++){
        //we add to the vector the new color
        tab_colors.push_back(interpolColors(i/nb_color));
    }
}


/*
 * Role: create an QRgb object with the R G B values after interpolation
 */
QRgb MandelbrotImage::interpolColors(double x){
    int R, G, B;
    //we create 3 interpolators objects (R, G, B)
    Interpolator interpolation_R(xs_,yr_);
    Interpolator interpolation_G(xs_,yg_);
    Interpolator interpolation_B(xs_,yb_);
    //we compute our R,G,B components
    R=is_valid(interpolation_R.get_value(x));
    G=is_valid(interpolation_G.get_value(x));
    B=is_valid(interpolation_B.get_value(x));
    QRgb color = qRgb(R,G,B);
    //std::cout << R << " " << G << " " << B << std::endl;
    return color;
}

/*
 * return  notre donnée double en castée int
 */
int MandelbrotImage::is_valid(double color){
    int c= static_cast<int>(color);
    if(c<0 || c>255){
        if(c<0){
            return 0;
        }
        return 255;
    }
    return c;
}

