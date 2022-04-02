#pragma once

#include "Graph.hpp"

class DijkstraGraph : public Graph {
private:
    void setAllVerticesWeightToMaxValue() {
        for(auto& pairIdVertex : vertices_) {
            Vertex& v = pairIdVertex.second;
            v.setWeight(std::numeric_limits<double>::max());
        }
    }
    
public:
    DijkstraGraph(std::string filename) : Graph(filename) {}
    
    std::deque<uint32_t> getPath(uint32_t vstart, uint32_t vend) override {
        std::deque<uint32_t> active_queue;
        std::set<uint32_t> closed_set;
        
        setAllVerticesWeightToMaxValue();
        
        // ID of the start vertex
        active_queue.push_back(vstart);
        getVertex(vstart).setWeight(0);
        
        do {
            // from the current vertex in the front of the queue
            //  compute all vertices reachable in 1 step
            uint32_t vcurrent = active_queue.front();
            active_queue.pop_front();
            
            closed_set.insert(vcurrent);
            if(vcurrent == vend) break;
            
            Vertex& currentVertex = getVertex(vcurrent);
            for(auto& vnext : currentVertex.getAdjacencyList()){
                if(closed_set.find(vnext) != closed_set.end()){
                    continue;
                }
                
                double w = currentVertex.getWeight() + getWeight(vcurrent, vnext);
                Vertex& nextVertex = getVertex(vnext);
                if(!isInDeque(active_queue, vnext)){
                    nextVertex.setWeight(w);
                    active_queue.push_back(vnext);
                } else if(w < nextVertex.getWeight()){
                    nextVertex.setWeight(w);
                }
                nextVertex.setPreviousId(currentVertex.getId());
            }
            // the partial sort ensures that the vertex with the smallest weight
            //  is the first on the active_queue
            auto weightCompare = [&](uint32_t a, uint32_t b) {
                return getVertex(a).getWeight() < getVertex(b).getWeight();
            };
            std::sort(active_queue.begin(), active_queue.end(), weightCompare);
        } while (active_queue.size() != 0);
        std::cout << "Total visited vertex = " << closed_set.size() << std::endl;
        
        std::deque<uint32_t> path = computePath(vstart, vend);
        printPath(path);
        
        return path;
    }
};
