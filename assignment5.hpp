//
//  assignment5.hpp
//  Algorithms: Design and Analysis, Part 1
//
//  Programming Assignment 5
//
//  Created by Nenad Mancevic on 2/24/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem:
//
/***********************
 In this programming problem you'll code up Dijkstra's shortest-path algorithm.
 Download the text file here (http://bit.ly/1LCXFBR)
 The file contains an adjacency list representation of an undirected
 weighted graph with 200 vertices labeled 1 to 200. Each row consists
 of the node tuples that are adjacent to that particular vertex along
 with the length of that edge. For example, the 6th row has 6 as the
 first entry indicating that this row corresponds to the vertex labeled 6.
 The next entry of this row "141,8200" indicates that there is an edge
 between vertex 6 and vertex 141 that has length 8200. The rest of the
 pairs of this row indicate the other vertices adjacent to vertex 6 and
 the lengths of the corresponding edges.
 
 Your task is to run Dijkstra's shortest-path algorithm on this graph,
 using 1 (the first vertex) as the source vertex, and to compute the
 shortest-path distances between 1 and every other vertex of the graph.
 If there is no path between a vertex v and vertex 1, we'll define
 the shortest-path distance between 1 and v to be 1000000.
 
 You should report the shortest-path distances to the following ten vertices,
 in order: 7,37,59,82,99,115,133,165,188,197. You should encode the distances
 as a comma-separated string of integers. So if you find that all ten of these
 vertices except 115 are at distance 1000 away from vertex 1 and 115 is 2000
 distance away, then your answer should be 1000,1000,1000,1000,1000,2000,1000,
 1000,1000,1000. Remember the order of reporting DOES MATTER, and the string
 should be in the same order in which the above ten vertices are given.
 
 
 IMPLEMENTATION NOTES: This graph is small enough that the straightforward O(mn)
 time implementation of Dijkstra's algorithm should work fine.
 OPTIONAL: For those of you seeking an additional challenge, try implementing
 the heap-based version. Note this requires a heap that supports deletions,
 and you'll probably need to maintain some kind of mapping between vertices
 and their positions in the heap.
 ************************/

#include <map>
#include <vector>
#include <fstream>
#include <sstream>

namespace assignment5 {
    
    // Define Graph as a map with keys as vertex numbers and values
    // as vector of vertices pairs: (connected_to_node, weight_of_edge)
    typedef std::map<int, std::vector<std::pair<int,int>>> Graph;

    Graph               _G;
    std::vector<int>    _shortest_paths;
    std::vector<int>    _processed_so_far;
    
    void loadGraphAndInit(const string& fileName)
    {
        // load from file
        ifstream file(fileName, ios::in);
        
        if (file.is_open())
        {
            std::string rawInput;
            int vertex;
            while (getline(file, rawInput))
            {
                std::istringstream is(rawInput);
                
                is >> vertex;
                // read the pairs of dest, weight
                int dest, weight;
                char comma;
                while (is >> dest >> comma >> weight)
                {
                    _G[vertex].push_back(make_pair(dest, weight));
                }
            }
            file.close();
        }
        
        // init shortest paths array
        _shortest_paths = std::vector<int>(_G.size() + 1,1000000); // we start with vertex 1
        _shortest_paths[1] = 0; // path to itself is 0
        
        // init processed_so_far array
        _processed_so_far.push_back(1); // first vertex is in X initially
        
    }
    
    void computeShortestPaths()
    {
        if (_G.size() == 0)
            return;
        
        while (_processed_so_far.size() != _G.size())
        {
            // for each edge (u, v) where u in X and v not in X
            std::pair<int,int> min_pair;
            int local_min = -1;
            for (int vertex : _processed_so_far)
            {
                for (auto edge : _G[vertex])
                {
                    // target vertex (v) is not in X
                    if (std::find(_processed_so_far.begin(), _processed_so_far.end(), edge.first) == _processed_so_far.end())
                    {
                        if (local_min == -1 || _shortest_paths[vertex] + edge.second < local_min)
                        {
                            min_pair = edge;
                            local_min = _shortest_paths[vertex] + edge.second;
                        }
                    }
                }
            }
            _processed_so_far.push_back(min_pair.first);
            _shortest_paths[min_pair.first] = local_min;
        }
        
        // reporting shortest paths for: 7,37,59,82,99,115,133,165,188,197
        cout << "Dijkstra's algorithm computed shortest paths to nodes 7,37,59,82,99,115,133,165,188,197: " << endl;
        cout << _shortest_paths[7] << ", ";
        cout << _shortest_paths[37] << ", ";
        cout << _shortest_paths[59] << ", ";
        cout << _shortest_paths[82] << ", ";
        cout << _shortest_paths[99] << ", ";
        cout << _shortest_paths[115] << ", ";
        cout << _shortest_paths[133] << ", ";
        cout << _shortest_paths[165] << ", ";
        cout << _shortest_paths[188] << ", ";
        cout << _shortest_paths[197] << ", respectively." << endl;
    }
    
}   // namespace