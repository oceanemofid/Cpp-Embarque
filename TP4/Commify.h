#ifndef COMMIFY_H
#define COMMIFY_H
#include <sstream>
#include <cstring>

class Commify {
 private:
    int64_t duration_;
 public:
    explicit Commify(int64_t value):duration_{value} {}

    friend std::ostream &operator << (std::ostream &os, const Commify &c){
        std::string s;
        s=std::to_string(c.duration_);
        int Comma_Pos = s.length() - 3;
        while (Comma_Pos > 0) {
            s.insert(Comma_Pos, ",");
            Comma_Pos -= 3;
        }
        os << s;
        return os;
    }
};

#endif // COMMIFY_H
