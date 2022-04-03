#pragma once

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <regex>
#include <deque>
#include <cmath> //sqrt
#include <algorithm>

#include "Vertex.hpp"
#include "Edge.hpp"


class Graph {
protected:
    using VertexMap = std::map<uint32_t, Vertex>;
    using EdgesMap = std::multimap<uint32_t, Edge>;
    VertexMap vertices_;
    EdgesMap edges_;

    static constexpr long double R0 = 6378137; //Earth radius in meters
    double centerLongitude_; //for Mercator projection
    double centerLatitude_;  //
    struct CoordinatesMerc {
        double x;
        double y;
    };
    struct CoordinatesHeur {
        double x;
        double y;
        double z;
    };

    //
    //Functions
    //
    CoordinatesMerc getMercatorProjection(const Vertex& v) {
        double dlat = v.getLatitude() - centerLatitude_;
        
        double x = R0 * (v.getLongitude() - centerLongitude_);
        double y = R0 * std::log(std::tan(dlat / 2 + M_PI / 4));
        
        return {x, y};
    }
    CoordinatesHeur getHeuristicProjection(const Vertex& v) {
        
        double x = R0 * cos(v.getLatitude()) * cos(v.getLongitude());
        double y = R0 * cos(v.getLatitude()) * sin(v.getLongitude());
        double z = R0 * sin(v.getLatitude());
        return {x, y, z};
    }
    
    void computeCentralCoordinates() {
        double minLatitude = 90;
        double maxLatitude = -90;
        double minLongitude = 180;
        double maxLongitude = -180;
        
        for(const auto& pairIdVertex : vertices_) {
            const Vertex& v = pairIdVertex.second;
            double longitude = v.getLongitude();
            if(longitude > maxLongitude)
                maxLongitude = longitude;
            if(longitude < minLongitude)
                minLongitude = longitude;
            
            double latitude = v.getLatitude();
            if(latitude > maxLatitude)
                maxLatitude = latitude;
            if(latitude < minLatitude)
                minLatitude = latitude;
        }
        centerLongitude_ = (maxLongitude + minLongitude) / 2;
        centerLatitude_ = (maxLatitude + minLatitude) / 2;
    }

    
    Vertex& getVertex(uint32_t id) {
        auto it = vertices_.find(id);
        if(it == vertices_.end()) {
            std::cerr << "In Graph class: vertex " << id << " is not a valid vertex ID." << std::endl;
        }
        return it->second;
    }
    
    
    double computeWeight(uint32_t fromId, uint32_t toId) {
        Vertex& vfrom = getVertex(fromId);
        Vertex& vto = getVertex(toId);
        
        CoordinatesMerc cfrom = getMercatorProjection(vfrom);
        CoordinatesMerc cto = getMercatorProjection(vto);
        
        double dx = cfrom.x - cto.x;
        double dy = cfrom.y - cto.y;
        
        return std::sqrt(dx * dx + dy * dy);
    }
    

    double heuristic_distance_estimator(uint32_t fromId, uint32_t toId) {
        Vertex& vfrom = getVertex(fromId);
        Vertex& vto = getVertex(toId);


        CoordinatesHeur cfrom = getHeuristicProjection(vfrom);
        CoordinatesHeur cto = getHeuristicProjection(vto);
        
        double dx = (cfrom.x - cto.x);
        double dy = (cfrom.y - cto.y);
        double dz = (cfrom.z - cto.z);
        return std::sqrt(dx * dx + dy * dy + dz * dz);
    }


    std::vector<std::string> split(const std::string& line) {
        std::vector<std::string> elements;
        std::istringstream is(line);
        for(std::string elem; std::getline(is, elem, ','); ){
            elements.push_back(elem);
        }
        return elements;
    }
    
    void processLine(const std::string& line) {
        char firstChar = line[0];
        if(firstChar == 'V')
            processVertex(line);
        
        else if(firstChar == 'E')
            processEdge(line);
    }
    
    void processVertex(const std::string& line) {
        std::vector<std::string> elements = split(line);
        
        uint32_t vertexId = static_cast<uint32_t>(std::stol(elements[1]));
        double longitude = std::stod(elements[2]);
        double latitude = std::stod(elements[3]);
        
        Vertex v{longitude, latitude, vertexId};
        vertices_.emplace(vertexId, v);
    }
    
    void processEdge(const std::string& line) {
        std::vector<std::string> elements = split(line);
        
        uint32_t fromId = static_cast<uint32_t>(std::stol(elements[1]));
        uint32_t toId = static_cast<uint32_t>(std::stol(elements[2]));
        double weight;
        try {
            weight = std::stod(elements[3]);
        } catch (std::invalid_argument&){
            weight = computeWeight(fromId, toId);
        }
        
        Edge e{fromId, toId, weight};
        edges_.emplace(fromId, e);
        getVertex(fromId).addAdjacent(toId);
    }
    
    std::deque<uint32_t> computePath(uint32_t vstart, uint32_t vend) {
        std::deque<uint32_t> path = {vend};
        do {
            Vertex& vfront = getVertex(path.front());
            uint32_t previous = vfront.getPreviousId();
            path.push_front(previous);
        } while (path.front() != vstart);

        return path;
    }
    
    void printPath(std::deque<uint32_t>& path) {
        uint32_t nbVertex = path.size();
        std::cout << "Total vertex on path from start to end = " << nbVertex << std::endl;
        for (int i = 0; i < nbVertex; ++i){
            Vertex& v = getVertex(path[i]);
            std::cout << "Vertex [" << std::setw(4)  << i + 1 << "] = "
                                    << std::setw(7)  << v.getId()<< ", length = "
                                    << std::setw(10) << std::fixed << std::setprecision(2)
                                    << v.getWeightUntilThisVertex() << std::endl;
        }
    }

    void exportVertexFile() {
        std::ofstream f("vertices.txt");
        for (auto& idVertexPair: vertices_){
            f << idVertexPair.second << std::endl;
        }
    }
    
    void exportEdgesFile() {
        std::ofstream f("edges.txt");
        for (auto& fromIdEdgePair : edges_){
            f << fromIdEdgePair.second <<std::endl;
        }
    }

public:  
    //
    // Role: Creates the Graph associated to the CSV file @file
    //
    Graph(std::string file_name) {
        std::ifstream fin(file_name, std::ios::in);
        for(std::string line; std::getline(fin, line); ) {
            std::istringstream stream(line);
            std::regex e ("^# .*");
            if (!(std::regex_match (line, e))){
                processLine(line);
            }
        }
        computeCentralCoordinates();
#if DEBUG
        exportVertexFile();
        exportEdgesFile();
#endif
    }
    
    virtual ~Graph() = default;
    virtual std::deque<uint32_t> getPath(uint32_t vstart, uint32_t vend) = 0;
    
    VertexMap getVertices() const {
        return vertices_;
    }
    
    EdgesMap getEdges() const {
        return edges_;
    }
    
    template<typename T>
    bool isInDeque(std::deque<T> d, T i) {
        for(const auto& x : d) {
            if(x == i)
                return true;
        }
        return false;
    }
    
    double getWeight_CurrentId_NextId(uint32_t fromId, uint32_t toId) { 
        double w = std::numeric_limits<double>::max();
 
        auto pairStartEnd = edges_.equal_range(fromId);
        for(auto it = pairStartEnd.first; it != pairStartEnd.second; ++it) {
            Edge& e = it->second;
            if(e.getToId() == toId) {
                w = e.getWeight();
                break;
            }
        }
    
        return w;
    }
};
