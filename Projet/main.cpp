#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Graph.hpp"

void createGraph(std::vector<std::string> row){
    
    auto it = row.begin();
    while(it!=row.end()){
        if(*it=="V"){
            /* create vertex
            vertex id = it+1
            longitude =it +2
            latitude = it+3
            */
           uint32_t vertexid = static_cast<uint32_t>(std::stoul(*(it+1)));
           double longitude = std::stod(*(it+2));
           double latitude = std::stod(*(it+3));
           Vertex V = {longitude, latitude, vertexid};
           std::cout << V;
        }

        else if(*it=="E"){
            /*create edge
            src = it+1
            dst = it+2
            length = it+3
            name = it+4 //faculatatif
            */
            uint32_t fromid = static_cast<uint32_t>(std::stoul(*(it+1)));
            uint32_t toid = static_cast<uint32_t>(std::stoul(*(it+2)));
            double length = std::stod(*(it+3));
            Edge E = {fromid, toid, length};
            std::cout << E;
        }
        it=it+6;
    }
}

int main(int argc, char *argv[]){
    std::string file_name{argv[1]};
    std::ifstream fin(file_name, std::ios::in);
    std::string line, word;
    std::vector<std::string> row;
    


    while (std::getline(fin, line)) {
        std::istringstream stream(line);
        while(std::getline(stream, word, ',')){
            row.push_back(word);
        }
    }
    createGraph(row);
    return EXIT_SUCCESS;
}

