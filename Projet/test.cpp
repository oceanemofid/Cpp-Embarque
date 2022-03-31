#include <iostream>
#include <set>
#include <algorithm>
 
template<typename T1, typename T2>
class Pair
{
public:
 
    T1 x;
    T2 y;
 
    // constructor
    Pair(T1 x, T2 y)
    {
        this->x = x;
        this->y = y;
    }
 
    // overload `<` operator to use a `Pair` object as a key in a `std::set`
    bool operator<(Pair const &p) const {
        return x < p.x || (x == p.x && y < p.y);
    }
};
 

struct find_by_first {
    find_by_first(const int & f) : color(f) {}

    bool operator()( Pair<int,int> &car) {
        return (car.x == color);
    }
private:
    std::string color;
};

int main()
{
    std::set<Pair<int, int>> set = {
        {521, 4}, {325, 4}, {62, 1}, {82, 0}, {62, 3}
    };
 
    for (auto const &p: set) {
        std::cout << "{" << p.x << ":" << p.y << "}\n";
    }
    
    std::set<Pair<int, int>>::iterator result = std::find_if(set.begin(), set.end(),find_by_first(325));

    for (auto const &p: set) {
        std::cout << "{" << p.x << ":" << p.y << "}\n";
    }*65437

    return 0;
}