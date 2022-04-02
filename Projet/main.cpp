#include <cstdlib>
#include <iostream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <memory>

#include "Vertex.hpp"
#include "Edge.hpp"
#include "Graph.hpp"
#include "BfsGraph.hpp"
#include "DijkstraGraph.hpp"

int main(int argc, char *argv[]){
    uint32_t vstart;
    uint32_t vend;
    std::string filename;
    std::string searchType;

    for(unsigned int i = 1; i < argc; i += 2){
        if(strcmp(argv[i], "--start") == 0)
            vstart = std::stol(argv[i + 1]);
        else if(strcmp(argv[i], "--end") == 0)
            vend = std::stol(argv[i + 1]);
        else if(strcmp(argv[i], "--algorithm") == 0)
            searchType = argv[i + 1];
        if(strcmp(argv[i], "--file") == 0)
            filename = argv[i + 1];
    }

    std::unique_ptr<Graph> graph;
    if(searchType == "bfs")
        graph = std::make_unique<BfsGraph>(filename);
    else if(searchType == "dij")
        graph = std::make_unique<DijkstraGraph>(filename);

    graph->getPath(vstart, vend);
    
    return EXIT_SUCCESS;
}
