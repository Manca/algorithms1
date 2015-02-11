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
#include <vector>
#include <list>
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

namespace assignment3 {

    class Graph
    {
    private:
        std::vector<std::list<int>> adjacencyList;
        
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
                    adjacencyList.push_back(std::list<int>( std::istream_iterator<int>(is), std::istream_iterator<int>() ));
                }
                file.close();
            }
        }
        
        void printGraph()
        {
            int i = 1;
            for (auto v : adjacencyList)
            {
                std::cout << i << ". [";
                for (auto e : v)
                    std::cout << e << " ";
                std::cout << "]" << std::endl << std::endl;
                i++;
            }
        }
    };
    
}