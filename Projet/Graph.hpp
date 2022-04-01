#include <vector>
#include <set>
#include <map>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <regex>
#include <algorithm>
#include <deque>

#include "Vertex.hpp"
#include "Edge.hpp"


class Graph {
public:
  using VertexMap = std::map<uint32_t, Vertex>;
  using EdgesMap = std::multimap<uint32_t, Edge>;

private:
  VertexMap vertices_;
  EdgesMap edges_;

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

	Vertex v = {longitude, latitude, vertexId};
	vertices_.insert({vertexId, v});
  }

  void processEdge(const std::string& line) {
	std::vector<std::string> elements = split(line);
	
	uint32_t fromId = static_cast<uint32_t>(std::stof(elements[1]));
	uint32_t toId = static_cast<uint32_t>(std::stof(elements[2]));
	double length = std::stod(elements[3]);

	Edge e = {fromId, toId, length};
	edges_.insert({fromId, e});

	auto itFromId = vertices_.find(fromId);
	if(itFromId != vertices_.end())
	  itFromId->second.addAdjacent(toId);
	else
	  std::cerr << "Edge created before associated vertex with id: " << fromId << std::endl;
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
  Graph(const char* file) {
	std::string file_name{file};
	std::ifstream fin(file_name, std::ios::in);
	
	for(std::string line; std::getline(fin, line); ) {
	  std::istringstream stream(line);
	  std::regex e ("^# .*");
	  if (!(std::regex_match (line, e))){
	processLine(line);
	  }
	}
#if DEBUG
	exportVertexFile();
	exportEdgesFile();
#endif
  }

  VertexMap getVertices() {
	return vertices_;
  }

  EdgesMap getEdges() {
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
  
  void bfs(uint32_t vstart, uint32_t vend) {
	std::deque<uint32_t> active_queue;
	std::set<uint32_t> closed_set;
	
	// ID of the start vertex
	active_queue.push_back(vstart);

	uint32_t totalVisitedVertex = 0;
	do {
	  // from the current vertex in the front of the queue
	  // compute all vertices reachable in 1 step
	  uint32_t vcurrent = active_queue.front();
	  active_queue.pop_front();
	  ++totalVisitedVertex;
	  
	  if(vcurrent == vend)
	break;

	  closed_set.insert(vcurrent);
	  
	  auto itVcurrent = vertices_.find(vcurrent);
	  if(itVcurrent == vertices_.end())
	continue;
	  
	  for(auto& vnext : itVcurrent->second.getAdjacencyList()){
	if(closed_set.find(vnext) != closed_set.end())
	  continue;

	if(!isInDeque(active_queue, vnext))
	  active_queue.push_back(vnext);
	  }
	} while (active_queue.size() != 0);
	std::cout << "Total visited vertex = " << totalVisitedVertex << std::endl;
  }
};
