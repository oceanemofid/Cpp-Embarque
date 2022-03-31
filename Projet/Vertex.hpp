#pragma once
#include <string>
#include <list>
#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

class Vertex {
private:
    double longitude; //vertex longitude
    double latitude;  //vertex latitude
    uint32_t ID;      //ID of the vertex
    vector<uint32_t> adjacency_List_; //adjacency list of the vertex

public:
    Vertex(double L, double l, uint32_t i) : longitude(L), latitude(l), ID(i){}

    //getters
    double getLongitude() {
        return longitude;
    }
    double getLatitude() {
        return latitude;
    }
    uint32_t getID() {
        return ID;
    }

    vector<uint32_t> getAdjacency_List() {
        return adjacency_List_;
    }
    
    //setters
    void setID(uint32_t id) {
        ID = id;
    }
    void setLatitude(double l) {
        latitude = l;
    }
    void setLongitude(double L) {
        longitude = L;
    }
    void setAdjacencyList(vector<uint32_t> adjacency_List){
        for(int i;i<adjacency_List.size();i++){
            adjacency_List[i]=adjacency_List_[i];
        }
    }

   

    //  void addEdgeToEdgelist(int toVertexID, int weight)
    //  {
    //	  	Edge e(toVertexID,weight);
    //		edgeList.push_back(e); 
    //		cout<<"Edge between "<<state_id<<" and "<<toVertexID<<" added Successfully"<<endl; 	
    //  }
    /*
    void printEdgeList() {
        cout << "Total visited vertices : " << endl;
        cout << "Total vertex on path from start to end = " << endl;
        for (auto it = edgeList.begin(); it != edgeList.end(); it++) {
        cout << "Vertex[ "<< "indice ] = "<< it->getFromID() << "length =" << it -> getWeight() << endl;
        }
        cout << endl;
    }
    */

    std::string toString() {
        std::ostringstream s;
        s << "V " << ID << " " << longitude << " " << latitude << std::endl;
        return s.str();
    }

    friend std::ostream& operator<<(std::ostream &f, Vertex &E){
        return f << E.toString();
    }

};
    
