#ifndef PIXEL2RECT_CONVERTER_H
#define PIXEL2RECT_CONVERTER_H

class Pixel2rect_Converter{
private:
    double pix_min, pix_max, real_min, real_max ;

public:
    Pixel2rect_Converter(double p_min, double p_max, double r_min, double r_max) : pix_min(p_min), pix_max(p_max), real_min(r_min), real_max(r_max) {}

    double operator()(double p){

        return (p-pix_min)/(pix_max-pix_min)*(real_max-real_min)+real_min;
    }

};

#endif // PIXEL2RECT_CONVERTER_H

