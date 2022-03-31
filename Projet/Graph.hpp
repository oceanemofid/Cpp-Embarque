#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <regex>
#include "Vertex.hpp"
#include "Edge.hpp"
#include <algorithm>


//auto result = std::find_if( set.begin(), set.end() , [] (const uint32_t index) {return v.getID() == index;});

class Graph {
    std::pair<std::map<uint32_t, Vertex>,std::multimap<uint32_t, Edge>> map_;

public:
    /*
    *Role: Create the Graph associates to the CSV file @file
    */
    Graph(char* file) {
        std::map<uint32_t,Vertex> vertices;
        std::multimap<uint32_t,Edge> edges;
        std::string file_name{file};
        std::ifstream fin(file_name, std::ios::in);
        std::string line, word;
        std::vector<std::string> row;
        
        while (std::getline(fin, line)) {
            std::istringstream stream(line);
            std::regex e ("^# .*");

            if (!(std::regex_match (line,e))){
                while(std::getline(stream, word, ',')){
                    row.push_back(word);
                }
            }
        }

        for (int i=0; i<6; i++ ){
            std::cout << row[i] << " " << std::endl;
        }

        auto it = row.begin();
        while(it!=row.end()){
            if(*it=="V"){
                /* create vertex
                vertex id = it+1
                longitude =it +2
                latitude = it+3
                */
                //get the Vextex attribute and s
                uint32_t vertexid = static_cast<uint32_t>(std::stof(*(it+1)));
                double longitude = std::stod(*(it+2));
                double latitude = std::stod(*(it+3));
                //create the corresponding vertex
                Vertex V = {longitude, latitude, vertexid};
                //creation of a vertices map 
                vertices.insert({vertexid, V});
                it=it+5;
            }
            else if(*it=="E"){
                /*create edge
                src = it+1
                dst = it+2
                length = it+3
                name = it+4 //faculatatif
                */
            //get the Edges attribute and insert all edges in the set
                uint32_t fromid = static_cast<uint32_t>(std::stof(*(it+1)));
                uint32_t toid = static_cast<uint32_t>(std::stof(*(it+2)));
                double length = std::stod(*(it+3));
                //create the corresponding vertex
                Edge E = {fromid, toid, length};
                //update the edges set
                edges.insert({fromid, E});
                it=it+6;
            }
              
        }
        
        std::ofstream myfile;
        myfile.open ("vertices.txt");
        for (auto i: vertices){
            myfile << i.second << std::endl;
        }
        myfile.close();

        std::ofstream myfile2;
        myfile2.open ("edges.txt");
        for (auto i: edges){
            myfile2 << i.second <<std::endl;
        }
        myfile2.close();

        //Creation of the adjacency list of each Vertex
        std::vector<uint32_t> adj_currentV;
        
        for(auto iterator=edges.begin(); iterator!=(edges.end()); iterator++){
            //adj_currentV.clear();
            //we keep the base FromID 
            uint32_t ref_ID = iterator->first;
    
            while(ref_ID == (iterator->first)){
                adj_currentV.push_back((iterator->second).getToID());
                iterator++;
            }
            auto pairKeyValue = vertices.find(63287);
            std::cout << pairKeyValue->first << std::endl;
            if(pairKeyValue!=vertices.end()){
                pairKeyValue->second.setAdjacencyList(adj_currentV);
                
            }  
            if(pairKeyValue==vertices.end()){
                std::cout<<"tu pues" << std::endl;
            }
            adj_currentV.clear();          
        }
        map_= make_pair(vertices,edges);
    }

    std::pair<std::map<uint32_t, Vertex>,std::multimap<uint32_t, Edge>> getMap(){
        return map_;
    }
    
/*
    bool checkIfVertexExistByID(int vid) {
      bool flag = false;
      for (int i = 0; i < map_.size(); i++) {
        if (map_.at(i).getID() == vid) {
          return true;
        }
      }
      return flag;
    }

    void addVertex(Vertex newVertex) {
        bool check = checkIfVertexExistByID(newVertex.getID());
        if (check == true) {
        cout << "Vertex with this ID already exist" << endl;
        } else {
        map_.push_back(newVertex);
        cout << "New Vertex Added Successfully" << endl;
        }
    }
    
    Vertex getVertexByID(int vid) {
        Vertex temp;
        for (int i = 0; i < vertices.size(); i++) {
        temp = vertices.at(i);
        if (temp.getID() == vid) {
            return temp;
        }
        }
        return temp;
    }
    
    bool checkIfEdgeExistByID(int fromVertex, int toVertex) {
        Vertex v = getVertexByID(fromVertex);
        list < Edge > e;
        e = v.getEdgeList();
        bool flag = false;
        for (auto it = e.begin(); it != e.end(); it++) {
        if (it -> getDestinationVertexID() == toVertex) {
            flag = true;
            return flag;
            break;
        }

        }
        return flag;
    }

    void updateVertex(int oldVID, string vname) {
        bool check = checkIfVertexExistByID(oldVID);
        if (check == true) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStateID() == oldVID) {
            vertices.at(i).setStateName(vname);
            break;
            }
        }
        cout << "Vertex(State) Updated Successfully " << endl;
        }
    }

    void addEdgeByID(int fromVertex, int toVertex, int weight) {
        bool check1 = checkIfVertexExistByID(fromVertex);
        bool check2 = checkIfVertexExistByID(toVertex);

        bool check3 = checkIfEdgeExistByID(fromVertex, toVertex);
        if ((check1 && check2 == true)) {

        if (check3 == true) {
            cout << "Edge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") Already Exist" << endl;
        } else {

            for (int i = 0; i < vertices.size(); i++) {

            if (vertices.at(i).getStateID() == fromVertex) {
                Edge e(toVertex, weight);
                //edgeList.push_back(e); 
                //vertices.at(i).addEdgeToEdgelist(toVertex,weight);
                vertices.at(i).edgeList.push_back(e);
            } else if (vertices.at(i).getStateID() == toVertex) {
                Edge e(toVertex, weight);
                //edgeList.push_back(e); 
                //vertices.at(i).addEdgeToEdgelist(fromVertex,weight);
                vertices.at(i).edgeList.push_back(e);
            }
            }

            cout << "Edge between " << fromVertex << " and " << toVertex << " added Successfully" << endl;
        }
        } else {
        cout << "Invalid Vertex ID entered.";
        }
    }

    void updateEdgeByID(int fromVertex, int toVertex, int newWeight) {
        bool check = checkIfEdgeExistByID(fromVertex, toVertex);
        if (check == true) {
        for (int i = 0; i < vertices.size(); i++) {

            if (vertices.at(i).getStateID() == fromVertex) {
            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                if (it -> getDestinationVertexID() == toVertex) {
                it -> setWeight(newWeight);
                break;
                }

            }

            } else if (vertices.at(i).getStateID() == toVertex) {
            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                if (it -> getDestinationVertexID() == fromVertex) {
                it -> setWeight(newWeight);
                break;
                }

            }
            }
        }
        cout << "Edge Weight Updated Successfully " << endl;
        } else {
        cout << "Edge between " << getVertexByID(fromVertex).getStateName() << "(" << fromVertex << ") and " << getVertexByID(toVertex).getStateName() << "(" << toVertex << ") DOES NOT Exist" << endl;
        }
    }

    void deleteEdgeByID(int fromVertex, int toVertex) {
        bool check = checkIfEdgeExistByID(fromVertex, toVertex);
        if (check == true) {
        for (int i = 0; i < vertices.size(); i++) {
            if (vertices.at(i).getStateID() == fromVertex) {
            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                if (it -> getDestinationVertexID() == toVertex) {
                vertices.at(i).edgeList.erase(it);
                //cout<<"First erase"<<endl;
                break;
                }
            }
            }

            if (vertices.at(i).getStateID() == toVertex) {

            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
                if (it -> getDestinationVertexID() == fromVertex) {
                vertices.at(i).edgeList.erase(it);
                //cout<<"second erase"<<endl;
                break;
                }
            }
            }
        }
        cout << "Edge Between " << fromVertex << " and " << toVertex << " Deleted Successfully." << endl;
        }
    }

    void deleteVertexByID(int vid) {
        int vIndex = 0;
        for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == vid) {
            vIndex = i;
        }
        }
        for (int i = 0; i < vertices.size(); i++) {
        for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            if (it -> getDestinationVertexID() == vid) {
            vertices.at(i).edgeList.erase(it);
            break;
            }
        }

        }
        vertices.erase(vertices.begin() + vIndex);
        cout << "Vertex Deleted Successfully" << endl;
    }

    void getAllNeigborsByID(int vid) {
        cout << getVertexByID(vid).getStateName() << " (" << getVertexByID(vid).getStateID() << ") --> ";
        for (int i = 0; i < vertices.size(); i++) {
        if (vertices.at(i).getStateID() == vid) {
            cout << "[";
            for (auto it = vertices.at(i).edgeList.begin(); it != vertices.at(i).edgeList.end(); it++) {
            cout << it -> getDestinationVertexID() << "(" << it -> getWeight() << ") --> ";
            }
            cout << "]";

        }
        }

    }

    void printGraph() {
        for (int i = 0; i < vertices.size(); i++) {
        Vertex temp;
        temp = vertices.at(i);
        cout << temp.getStateName() << " (" << temp.getStateID() << ") --> ";
        temp.printEdgeList();
        }
    }
    */
};
