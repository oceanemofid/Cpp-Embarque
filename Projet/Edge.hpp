#include <iostream>
#include <sstream> 
#pragma once

class Edge {
private :
    uint32_t fromId_;
    uint32_t toId_;
    double weight_;
    
public:
    Edge() = default;
    Edge(uint32_t fId, uint32_t toId, double w) : fromId_(fId), toId_(toId), weight_(w) {}

    void setEdgeValues(uint32_t fId, uint32_t destVId, double w) {
        fromId_ = fId;
        toId_ = destVId;
        weight_ = w;
    }

    void setWeight(double w) {
        weight_ = w;
    }

    uint32_t getToId() const {
        return toId_;
    }

    uint32_t getFromId() const {
        return fromId_;
    }
    
    double getWeight() const {
        return weight_;
    }

    std::string toString() {
        std::ostringstream s;
        s << "E " << fromId_ << " " << toId_ << " " << weight_ << std::endl;
        return s.str();
    }

    friend std::ostream &operator<<(std::ostream &f, Edge &V){
        return f << V.toString();
    }

};
