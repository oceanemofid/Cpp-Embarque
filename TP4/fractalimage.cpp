#include "fractalimage.h"
#include <iostream>
#include <complex>
#include <cmath>

/*
 * Role : Constructs a MandelbrotImage of size width x height
 */
FractalImage::FractalImage(const int width, const int height, double cx, double cy, double d)
    : QImage (width, height, QImage::Format_RGB32), cx_(cx), cy_(cy), d_(d) {}

void FractalImage::draw() {
    //create the vector of 2048 colors
    create_gradient_colors();
    //allows the parallelism in multi-thread
    std::vector<std::thread> threads;
    const int max_threads = 16;

    for(int i = 0; i < max_threads; i++) {
        threads.emplace_back([=]() {
            process_sub_image(i, max_threads);
        });
     }
    for(auto &thread_elem :threads){
        thread_elem.join();
    }
}

/*
 * Role: create a gradient of colors
 */
void FractalImage::create_gradient_colors(){
    const double max_color = 2048;
    tab_colors_.reserve(max_color);
    //we iterate to calculate the 2048 RGB colors
    for(int i = 0; i < max_color; i++) {
        //we add to the vector the new color
        double color = static_cast<double>(i) /max_color;
        tab_colors_.emplace_back(interpolColors(color));
    }
}


/*
 * Role: create an QRgb object with the R G B values after interpolation
 */
QRgb FractalImage::interpolColors(double x) {
    //compute our R,G,B components
    int R = interpolationR_(x);
    int G = interpolationG_(x);
    int B = interpolationB_(x);
    return qRgb(R,G,B);
}

/*
 * Role: Draw a section of the image
 *
 *  @current_thread: index of subsection to process
 *  @max_threads: number of threads available on machine
 */
void FractalImage::process_sub_image(int current_thread, int max_threads){
    int sub_image_height = height() / max_threads;
    int yi = current_thread * sub_image_height;

    for (int py = yi; py < sub_image_height + yi; py++) {
        double ry = vPixel2Rect(py);
        for (int px = 0; px < width(); px++) {
            double rx = hPixel2Rect(px);
            QRgb rgb_color = calc_in_out(rx, ry);
            setPixel(px, py, rgb_color);
        }
    }
}


/*
 * Role : returns the QRgb color of the pixel of coordinates(rx,ry)
 *        depending on if it's inside the MandelbortImage.
 */
QRgb MandelbrotImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex<double> c0(rx, ry);
    std::complex z(0.0, 0.0);
    QRgb color= qRgb(0, 0, 0); //black

    bool is_inside = true;
    int i = 0;

    for(int n = 0; n < 512; n++){
        z = z * z + c0;
        double module = abs(z);
        if (module > 2) {
            is_inside = false;
         }
         if(!is_inside and module >= 256){
             double v = std::log2(std::log2(module * module));
             i = static_cast<int>(1024*sqrt(n + 5 -v)) % 2048;
             color = tab_colors_[i];
             return color;
         }
        }
       return color;
    }


QRgb JuliaImage::calc_in_out(double rx, double ry)
{
    //c0= x0 +iy0
    //z0 = 0
    std::complex<double> c0(-0.4, 0.6);
    std::complex z(rx, ry);
    QRgb color= qRgb(0, 0, 0); //black

    bool is_inside = true;
    int i = 0;

    for(int n = 0; n < 512; n++){
        z = z * z + c0;
        double module = abs(z);
        if (module > 2) {
            is_inside = false;
         }
         if(!is_inside and module >= 256){
             double v = std::log2(std::log2(module * module));
             i = static_cast<int>(1024*sqrt(n + 5 -v)) % 2048;
             color = tab_colors_[i];
             return color;
         }
        }
       return color;
    }

