#ifndef PIXEL2RECT_H
#define PIXEL2RECT_H

class H_Pixel2Rect{
private:
    double a_;
    double b_;
public:
    H_Pixel2Rect(double cx, double d, double px_min, double px_max){
        //linear interpolation with x
        //px: 0        ---           599
        //rx: xc - 1.5d      ---       xc + 1.5d
        //a , b
        a_ = (3.0 * d / (px_max - px_min));
        b_ = cx - 1.5 * d;
    }
    double operator()(double px) {
        return a_ * px + b_;
    }
};

class V_Pixel2Rect{
private:
    double a_;
    double b_;
public:
    V_Pixel2Rect(double cy, double d, double py_min, double py_max){
        //linea interpolation with y
        //py: 0           ---           399
        //ry: yc + d      ---          yc - d
        //a , b
        a_ = (2.0 * d / (py_max - py_min));
        b_ = cy + d;
    }
    double operator()(double py) {
        return -a_ * py + b_;
    }
};

#endif // PIXEL2RECT_H
