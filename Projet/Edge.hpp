#pragma once

#include <iostream>
#include <sstream> 


class Edge {
    private :
    uint32_t fromId_;
    uint32_t toId_;
    double weight_; //length
    
public:
    Edge(uint32_t fId, uint32_t toId, double w) : fromId_(fId), toId_(toId), weight_(w) {}
    
    uint32_t getToId() const {
        return toId_;
    }
    
    double getWeight() const {
        return weight_;
    }
    
    std::string toString() const {
        std::ostringstream s;
        s << "E " << fromId_ << " " << toId_ << " " << weight_ << std::endl;
        return s.str();
    }
    
    friend std::ostream &operator<<(std::ostream &f, Edge &V){
        return f << V.toString();
    }
    
};
