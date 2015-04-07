//
//  assignment3.cpp
//  Algorithms: Design and Analysis, Part 1
//
//  Programming Assignment 3
//
//  Created by Nenad Mancevic on 2/10/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem:
//
/***********************
    Download the text file here (http://bit.ly/1CRWhtL)
    The file contains the adjacency list representation of a
    simple undirected graph. There are 200 vertices labeled 1 to 200.
     
    The first column in the file represents the vertex label,
    and the particular row (other entries except the first column)
    tells all the vertices that the vertex is adjacent to.
     
    So for example, the 6th row looks like : "6	155	56	52	120	...".
    This just means that the vertex with label 6 is adjacent to
    (i.e., shares an edge with) the vertices with labels
    155,56,52,120,......,etc
     
    Your task is to code up and run the randomized contraction algorithm
    for the min cut problem and use it on the above graph to compute the
    min cut (i.e., the minimum-possible number of crossing edges).
     
    (HINT: Note that you'll have to figure out an implementation of
    edge contractions. Initially, you might want to do this naively,
    creating a new graph from the old every time there's an edge contraction.
    But you should also think about more efficient implementations.)
     
    (WARNING: As per the video lectures, please make sure to run the
    algorithm many times with different random seeds, and remember the
    smallest cut that you ever find.)
 ************************/
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include <iterator>

namespace assignment3 {

    /* Our graph is represented as a std::map,
       where keys are the actual vertices and values
       are their adjacency lists represented as std::vector
    */
    class Graph
    {
    private:
        std::map<int, std::vector<int>> adjacencyList;
        size_t _minCut = 999999;
        
    public:
        Graph(std::string fileName)
        {
            ifstream file(fileName, ios::in);
            
            if (file.is_open())
            {
                std::string rawInput;
                while (getline(file, rawInput))
                {
                    std::istringstream is(rawInput);
                    int pos;
                    is >> pos;
                    adjacencyList.insert(std::pair<int, std::vector<int>>(pos, std::vector<int>( std::istream_iterator<int>(is), std::istream_iterator<int>() ) ));
                }
                file.close();
            }
        }
        
        void printGraph()
        {
            int i = 1;
            for (auto v : adjacencyList)
            {
                std::cout << v.first << ". [";
                for (auto e : v.second)
                    std::cout << e << " ";
                std::cout << "]" << std::endl << std::endl;
                i++;
            }
        }
        
        int mincut()
        {
            std::map<int, std::vector<int>> contractedList = adjacencyList; // make a copy of starting list
            size_t n = contractedList.size();
            
            // random generator
            std::random_device rd;
            std::mt19937 gen(rd());
            
            while (n > 2)
            {
                // random vertex from the list of vertices (we know that there are 200 of them,
                // but the correct way should be random vertex from min key to max key
                std::uniform_int_distribution<int> vertexDistribution(1, 200);
                int u = vertexDistribution(gen);

                // if randomly selected u has already been deleted from the list, let's skip it
                if (contractedList.count(u) == 0)
                    continue;
                
                // random edge selection for the given first vertex
                size_t uSize = contractedList[u].size();
                std::uniform_int_distribution<int > edgeDistribution(0, (int)(uSize - 1)); // [a,b]
                int e = edgeDistribution(gen);
                
                // find a node in adjacency list for given vertex represented by e
                int v = contractedList[u].at(e);
                // let's see if the node actually exists in the list
                if (contractedList.count(v) == 0 || u == v)
                    continue;
                
                // merge two nodes into one (we'll use u here and copy all the neighbors of v to u's its adjancency list)
                for (int node : contractedList[v])
                    contractedList[u].push_back(node);
                
                // point other vertices that were pointing to v to u
                for (const auto& map_el : contractedList)
                    for (int& neighbor : contractedList[map_el.first])  // we'll mutate neighbor here
                        if (neighbor == v)
                            neighbor = u;
                
         
                // erase the adjacency list of v and decrease number of nodes by one
                contractedList.erase(v);
                n--;
                
                // finally, let's clean all self loops in a merged node
                size_t i = 0;
                while (i < contractedList[u].size())
                    if (contractedList[u].at(i) == u)
                        contractedList[u].erase(begin(contractedList[u]) + i);
                    else i++;
            }
            
            // last two nodes and their sizes (corresponding to number of crossing edges)
            int u = -1, v = -1;
            size_t uSize = -1, vSize = -1;
            for (const auto& map_el : contractedList)
            {
                if (u == -1)
                {
                    u = map_el.first;
                    uSize = map_el.second.size();
                }
                else
                {
                    v = map_el.first;
                    vSize = map_el.second.size();
                }
            }
            
            // uSize must be the same as vSize
            assert(uSize == vSize);
            
            size_t currentMinCut = uSize;   // either uSize or vSize
            _minCut =  currentMinCut < _minCut ? currentMinCut : _minCut;
            
            return (int)_minCut;
        }
    };
} // namespace