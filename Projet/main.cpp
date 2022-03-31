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


void printadj(std::vector<uint32_t> adjlist){
    for(auto e : adjlist){
        std::cout << "ok" << std::endl;
        std::cout << e << std::endl;
        
    }
}

int main(int argc, char *argv[]){
    Graph graph(argv[1]);
    std::map<uint32_t, Vertex> v = std::get<0>(graph.getMap());
    auto it = v.find(11408);
    Vertex v11408 = it->second;
    std::vector<uint32_t> fjksndjkfj = v11408.getAdjacency_List();
    printadj(fjksndjkfj);
    return EXIT_SUCCESS;
}
  




