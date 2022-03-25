#include <iostream>
#include <sstream> 

class Edge {
private :
    uint32_t FromID_;
    uint32_t ToID_;
    double Weight_;
    
public:
    Edge() {}
    Edge(uint32_t fID, uint32_t toID, double w ) : FromID_(fID), ToID_(toID), Weight_(w) {}

    void setEdgeValues(uint32_t fID, uint32_t destVID, double w) {
        FromID_=fID;
        ToID_ = destVID;
        Weight_ = w;
    }

    void setWeight(double w) {
        Weight_ = w;
    }

    uint32_t getToID() {
        return ToID_;
    }

    uint32_t getFromID() {
        return FromID_;
    }
    
    double getWeight() const{
        return Weight_;
    }

    std::string toString() {
        std::ostringstream s;
        s << "E " << FromID_ << " " << ToID_ << " " << Weight_ << std::endl;
        return s.str();
    }

    friend std::ostream &operator<<(std::ostream &f, Vertex &V){
        return f << V.toString();
    }

};
