#pragma once

#include <string>
#include <list>
#include <iostream>
#include <cstdlib>
#include <vector>
#include <sstream>


class Vertex {
private:
    double longitude_;
    double latitude_;
    uint32_t id_;
    uint32_t previousId_{};
    std::vector<uint32_t> adjacencyList_;
    double weight_{};     //accumulated length
    
public:
    Vertex(double longitude, double latitude, uint32_t id) : longitude_(longitude), latitude_(latitude), id_(id) {}
    
    //
    //Setters
    //
    void addAdjacent(uint32_t id) {
        adjacencyList_.push_back(id);
    }
    
    void setPreviousId(uint32_t id){
        previousId_ = id;
    }

    void setWeight(double w) {
        weight_ = w;
    }
    
    //
    //Getters
    //
    double getLongitude() const {
        return longitude_;
    }
    
    double getLatitude() const {
        return latitude_;
    }
    
    uint32_t getId() const {
        return id_;
    }
    
    uint32_t getPreviousId() const {
        return previousId_;
    }
    
    std::vector<uint32_t> getAdjacencyList() const {
        return adjacencyList_;
    }
    
    double getWeight() const {
        return weight_;
    }
    
    std::string toString() const {
        std::stringstream s;
        s << "V " << id_ << " " << longitude_ << " " << latitude_;
        return s.str();
    }
    
    friend std::ostream& operator<<(std::ostream &f, Vertex &v){
        return f << v.toString();
    }
};

