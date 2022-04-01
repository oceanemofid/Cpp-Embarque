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
  std::vector<uint32_t> adjacencyList_;
  uint32_t previousID_;

public:
  Vertex(double longitude, double latitude, uint32_t id) : longitude_(longitude), latitude_(latitude), id_(id) {}

  //
  //getters
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

  std::vector<uint32_t> getAdjacencyList() const {
    return adjacencyList_;
  }
    
  //
  //setters
  //
  void setId(uint32_t id) {
    id_ = id;
  }
    
  void setLatitude(double latitude) {
    latitude_ = latitude;
  }
    
  void setLongitude(double longitude) {
    longitude_ = longitude;
  }
      
  void setAdjacencyList(std::vector<uint32_t> adjacencyList){
    for(const auto& e : adjacencyList) {
      adjacencyList_.push_back(e);
    }
  }
  void addAdjacent(uint32_t id) {
      adjacencyList_.push_back(id);
    }
    
  uint32_t getPreviousID(){
    return previousID_;
  }

  void setPreviousID(uint32_t ID){
    previousID_=ID;
  }

 

  std::string toString() {
    std::stringstream s;
    s << "V " << id_ << " " << longitude_ << " " << latitude_;
    return s.str();
  }

  friend std::ostream& operator<<(std::ostream &f, Vertex &v){
    return f << v.toString();
  }
};
    
