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


template<typename T>
void printList(std::vector<T> l){
  for(const auto& x : l)
    std::cout << x << " ";
  std::cout << std::endl;
}

int main(int argc, char *argv[]){
    Graph graph(argv[1]);
    
    Graph::VertexMap v = graph.getVertices();
    auto it = v.find(115099);
    Vertex vx = it->second;

    std::vector<uint32_t> l = vx.getAdjacencyList();
    printList(l);
    
    graph.bfs(86771, 110636);
    
    return EXIT_SUCCESS;
}
