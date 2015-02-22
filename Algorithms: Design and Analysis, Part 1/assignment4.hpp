//
//  assignment4.cpp
//  Algorithms: Design and Analysis, Part 1
//
//  Programming Assignment 4
//
//  Created by Nenad Mancevic on 2/20/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem:
//
/***********************
    Download the text file here (http://bit.ly/1AUth4l)
    The file contains the edges of a directed graph. Vertices are labeled as 
    positive integers from 1 to 875714. Every row indicates an edge, the vertex 
    label in first column is the tail and the vertex label in second column is 
    the head (recall the graph is directed, and the edges are directed from the 
    first column vertex to the second column vertex). 
 
    So for example, the 11th row looks like: "2 47646". This just means that
    the vertex with label 2 has an outgoing edge to the vertex with label 47646.
 
    Your task is to code up the algorithm from the video lectures for computing 
    strongly connected components (SCCs), and to run this algorithm on the given graph.
 
    Output Format: You should output the sizes of the 5 largest SCCs in the given graph, 
    in decreasing order of sizes, separated by commas (avoid any spaces). 
    So if your algorithm computes the sizes of the five largest SCCs to be 
    500, 400, 300, 200 and 100, then your answer should be "500,400,300,200,100". 
    If your algorithm finds less than 5 SCCs, then write 0 for the remaining terms. 
    Thus, if your algorithm computes only 3 SCCs whose sizes are 400, 300, and 100, 
    then your answer should be "400,300,100,0,0".
 ************************/

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

namespace assignment4 {
    
    typedef std::map<int, std::vector<int>> Graph;
    typedef std::vector<int> seenList, timesList, leadersList;
    const int NUM_NODES = 875715; // 875714 + 1 (because we start from 0)
    
    // global vars
    timesList times;
    seenList seen;
    leadersList leaders;
    int time = 0;
    int s = -1;
    
    void DFS(Graph& g, int i)
    {
        if (g.count(i) == 0)
            return;
        
        seen[i] = 1;   // mark s as seen
        leaders[i] = s;
  //    std::cout << "Exploring " << i << endl;
        // for every edge (s, v)
        for (int v : g[i])
        {
            if (!seen[v])   // if v is not yet explored
            {
                DFS(g, v);
            }
        }
        time++;
        times[i] = time;
    }
    

    void DFSLoop(Graph& g)
    {
        time = 0;
        s = -1;
        seen = seenList(g.size(), 0);   // mark all nodes unexplored
        int n = g.size();
        
        for (int i = n; i > 0; i--)
        {
            if (!seen[i]) // if i is not yet explored
            {
                s = i;
                DFS(g, i);
            }
        }
    }
    
    void example1()
    {
        Graph g;
        g[1] = {4};
        g[2] = {8};
        g[3] = {6};
        g[4] = {7};
        g[5] = {2};
        g[6] = {9};
        g[7] = {1};
        g[8] = {5, 6};
        g[9] = {3, 7};
        
        Graph gRev;
        gRev[1] = {7};
        gRev[2] = {5};
        gRev[3] = {9};
        gRev[4] = {1};
        gRev[5] = {8};
        gRev[6] = {3, 8};
        gRev[7] = {4, 9};
        gRev[8] = {2};
        gRev[9] = {6};
        
        // initialize global var
        seen = seenList(g.size() + 1, 0); // initialize with zeros
        times = timesList(g.size() + 1, 0); // initialize with zeros
        leaders = leadersList(g.size() + 1, 0); // init with zeros
        
        // First step: Calculate finishing times on transpose Graph
        DFSLoop(gRev);
        
        // Second step: Construct a new graph (or update original)
        // with vertices updated according to their finishing times
        Graph newGraph;
        for (int i = 1; i <= times.size(); i++)
        {
            
            for (int neighbor : g[i])
            {
                // neighbors of i-th vertex of original graph are
                // vertices with new names taken from the finishing times list
                newGraph[times[i]].push_back(times[neighbor]);
            }

        }
        for (auto pair : newGraph)
        {
            std::cout << "Vertex " << pair.first << " has: ";
            for (int i : pair.second)
                std::cout << i << " ";
            std::cout << std::endl;
        }
        
        // Third step: DFS over the new graph (updated original) and compute leaders
        DFSLoop(newGraph);

        // Forth step: Sort leaders in order to compute number of nodes in each SCC
        sort(begin(leaders), end(leaders));
        int el = leaders[1];
        int elCnt = 1;
        for (int i = 2; i <= leaders.size(); i++)
        {
            if (leaders[i] == el)
                elCnt++;
            else
            {
                std::cout << "Leader " << el << " has " << elCnt << " nodes." << std::endl;
                el = leaders[i];
                elCnt = 1;
            }
        }
        
    }
    
    void example2()
    {
        Graph g;
        g[1] = {2};
        g[2] = {3, 5, 6};
        g[3] = {4, 7};
        g[4] = {3, 8};
        g[5] = {1, 6};
        g[6] = {7};
        g[7] = {6, 8};
        g[8] = {8};
        
        Graph gRev;
        gRev[1] = {5};
        gRev[2] = {1};
        gRev[3] = {2, 4};
        gRev[4] = {3};
        gRev[5] = {2};
        gRev[6] = {2, 5, 7};
        gRev[7] = {3, 6};
        gRev[8] = {4, 7, 8};
        
        // initialize global var
        seen = seenList(g.size() + 1, 0); // initialize with zeros
        times = timesList(g.size() + 1, 0); // initialize with zeros
        leaders = leadersList(g.size() + 1, 0); // init with zeros
        
        DFSLoop(gRev);
        Graph newGraph;
        for (int i = 1; i<= times.size(); i++)
        {
            
            for (int neighbor : g[i])
            {
                newGraph[times[i]].push_back(times[neighbor]);
            }
            
        }
        for (auto pair : newGraph)
        {
            //std::cout << "Vertex " << pair.first << " has: ";
            for (int i : pair.second)
                std::cout << i << " ";
            std::cout << std::endl;
        }
        
        DFSLoop(newGraph);
        
        sort(begin(leaders), end(leaders));
        int el = leaders[1];
        int elCnt = 1;
        for (int i = 2; i <= leaders.size(); i++)
        {
            if (leaders[i] == el)
                elCnt++;
            else
            {
                std::cout << "Leader " << el << " has " << elCnt << " nodes." << std::endl;
                el = leaders[i];
                elCnt = 1;
            }
        }

        
    }
    
    int SCC(const string& fileName)
    {
        // load from file
        Graph G, Grev;
        ifstream file(fileName, ios::in);
        for (int i = 1; i < NUM_NODES; i++)
        {
            G[i] = std::vector<int>();
            Grev[i] = std::vector<int>();
        }
        
        
        cout << "Reading file..." << endl;
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        if (file.is_open())
        {
            std::string rawInput;
            int tail, head;
            while (getline(file, rawInput))
            {
                std::istringstream is(rawInput);

                is >> tail;
                is >> head;
                
                G[tail].push_back(head);
                Grev[head].push_back(tail);
            }
            file.close();
        }
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Done. Time took to read the whole file and construct two graphs: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
        << "ms.\n";
        
        // initialize global var
        seen = seenList(875714 + 1, 0); // initialize with zeros
        times = timesList(875714 + 1, 0); // initialize with zeros
        leaders = leadersList(875714 + 1, 0); // init with zeros
 
        DFSLoop(Grev);
        
        Graph newGraph;
        for (int i = 1; i<= times.size(); i++)
        {
            // if the vertex doesn't have outgoing edges
            if (G[i].size() == 0)
            {
                newGraph[times[i]] = std::vector<int>();
                continue;
            }
            
            for (int neighbor : G[i])
            {
                newGraph[times[i]].push_back(times[neighbor]);
            }
            
        }
        
        DFSLoop(newGraph);
        
        sort(leaders.begin(), leaders.end());
        int el = leaders[1];
        int elCnt = 1;
        std::vector<int> totalNodes;
        ofstream f("out.txt");
        for (int i = 2; i <= leaders.size(); i++)
        {
            if (leaders[i] == el)
                elCnt++;
            else
            {
                totalNodes.push_back(elCnt);
           //     f << "Leader " << el << " has " << elCnt << endl;
               // std::cout << "Leader " << el << " has " << elCnt << " nodes." << std::endl;
                el = leaders[i];
                elCnt = 1;
            }
        }

        sort(totalNodes.begin(), totalNodes.end());
        
        for (int el : totalNodes)
            f << el << endl;

        f.close();
        return 0;
    }

   
  

} // namespace
