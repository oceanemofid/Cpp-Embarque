#pragma once

#include "Graph.hpp"

class BfsGraph : public Graph {
public:
    BfsGraph(std::string filename) : Graph(filename) {}
    
    std::deque<uint32_t> getPath(uint32_t vstart, uint32_t vend) override {
        std::deque<uint32_t> active_queue;
        std::set<uint32_t> closed_set;
        
        // ID of the start vertex
        active_queue.push_back(vstart);
        
        do {
            // from the current vertex in the front of the queue
            // compute all vertices reachable in 1 step
            uint32_t vcurrent = active_queue.front();
            active_queue.pop_front();
            
            
            if(vcurrent == vend)
                break;
            
            closed_set.insert(vcurrent);
            
            Vertex& currentVertex = getVertex(vcurrent);
            for(auto& vnext : currentVertex.getAdjacencyList()){
                if(closed_set.find(vnext) != closed_set.end()){
                    continue;
                }
                
                double w = currentVertex.getWeightUntilThisVertex() + getWeight_CurrentId_NextId(vcurrent, vnext);
                if(!isInDeque(active_queue, vnext)){
                    getVertex(vnext).setPreviousId(currentVertex.getId());
                    active_queue.push_back(vnext);
                    getVertex(vnext).setWeightUntilThisVertex(w);
                }
            }
        } while (active_queue.size() != 0);
        std::cout << "Total visited vertex = " << closed_set.size() << std::endl;
        
        std::deque<uint32_t> path = computePath(vstart, vend);
        printPath(path);
        
        return path;
    }
    
};
