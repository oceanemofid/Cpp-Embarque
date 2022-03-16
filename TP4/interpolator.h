#ifndef INTERPOLATOR_H
#define INTERPOLATOR_H

#include <QImage>

class Interpolator : public QImage
{
private:
    std::vector<double> ai_;
    std::vector<double> bi_;
    std::vector<double> xs_;
    std::vector<double> ys_;

public:
    Interpolator(std::vector<double> y, std::vector<double> xs) : xs_(xs), ys_(y) {
        bi_=ys_;
        for(unsigned long long i=0; i<xs_.size()-1; i++) {
            ai_.push_back((ys_[i+1]-ys_[i])/(xs_[i+1]-xs_[i]));
           }
    }

    double get_value(const double x) const {
        for(unsigned long long i=0; i<xs_.size(); i++) {
          if(xs_[i]<= x and x <= xs_[i+1]){
              return (ai_[i]*(x-xs_[i])+bi_[i]);
          }
        }
        return 1;

;}
};

#endif // INTERPOLATOR_H
