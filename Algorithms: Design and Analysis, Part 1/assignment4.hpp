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
//
// Note:
//
// Compile the program with stack size set to at least 16MB.
// Correct way to set it if using clang compiler:
//
// clang++ --std=c++11 -O3 -g -Wl,-stack_size -Wl,0x1000000 -o main ../main.cpp
//
///////////////////////////

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

namespace assignment4 {
    
    // Let's define some necessary structs and values
    typedef std::map<int, std::vector<int>> Graph;
    typedef std::vector<int> seenList, timesList, leadersList;
    typedef struct
    {
        int leader;
        int numNodes;
    } SCC;
    const int NUM_NODES = 875715; // 875714 + 1 - total number of nodes in G
    
    // global vars
    timesList   _times;
    seenList    _seen;
    leadersList _leaders;
    int _time = 0;
    int _s = -1; // potential leader
    
    void DFS(Graph& g, int i)
    {
        assert(g.count(i) > 0); // every node MUST be in a graph
        
        _seen[i] = 1;           // mark s as seen
        _leaders[i] = _s;

        // for every edge (s, v)
        for (int v : g[i])
        {
            if (!_seen[v])   // if v is not yet explored
            {
                DFS(g, v);
            }
        }
        _time++;
        _times[i] = _time;
    }
    
    void DFSLoop(Graph& g)
    {
        // initally time and leader set to 0 and -1, respectively
        // seen list i reset too
        _time = 0;
        _s = -1;
        _seen = seenList(g.size()+1, 0);   // mark all nodes unexplored
        
        int n = g.size();   // we assume the vertex labeling 1..n here
        
        for (int i = n; i > 0; i--)
        {
            if (!_seen[i]) // if i is not yet explored
            {
                _s = i;
                DFS(g, i);
            }
        }
    }
    
    Graph constructNewGraph(Graph& originalGraph, const timesList& fTimes)
    {
        Graph newGraph;
        
        // First fTimes should have exactly n+1 elements of the originalGraph
        // assuming vertex labels start from 1 to n.
        assert(fTimes.size() == originalGraph.size()+1);
        
        for (int i = 1; i < fTimes.size(); i++)
        {
            // if the vertex in original graph doesn't have outgoing edges
            if (originalGraph[i].size() == 0)
            {
                // just construct it with updated key in a new graph
                newGraph[fTimes[i]] = std::vector<int>();
                continue;
            }
            
            for (int neighbor : originalGraph[i])
            {
                
                // neighbors of i-th vertex of original graph are
                // vertices with new names taken from the finishing times list
                newGraph[fTimes[i]].push_back(fTimes[neighbor]);
            }
        }
        
        return newGraph;
    }
    
    // utility comparator function
    bool compareByNumSCCs(const SCC &a, const SCC &b)
    {
        return a.numNodes > b.numNodes;
    }
    
    void testCase1()
    {
        cout << "***** ASSIGNMENT4 TEST CASE 1 *****" << endl;
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
        _seen       = seenList(g.size() + 1, 0);        // initialize with zeros
        _times      = timesList(g.size() + 1, 0);       // initialize with zeros
        _leaders    = leadersList(g.size() + 1, 0);     // initialize with zeros
        
        // First step: Calculate finishing times on transpose Graph gRev
        DFSLoop(gRev);
        
        // Second step: Construct a new graph (or update original)
        // with vertices updated according to their finishing times
        Graph newGraph = constructNewGraph(g, _times);
        
        // Third step: DFS over the new graph (updated original) and compute leaders
        DFSLoop(newGraph);

        // Forth step: Sort leaders in order to compute number of nodes in each SCC
        sort(begin(_leaders), end(_leaders));
        std::vector<SCC> SCCs;
        
        int el = _leaders[1];
        int elCnt = 1;
        for (int i = 2; i < _leaders.size(); i++)
        {
            if (_leaders[i] == el)
                elCnt++;
            else
            {
                SCC scc;
                scc.leader = el;
                scc.numNodes = elCnt;
                SCCs.push_back(scc);

                el = _leaders[i];
                elCnt = 1;
            }
        }
        // last SCC
        SCC scc;
        scc.leader = el;
        scc.numNodes = elCnt;
        SCCs.push_back(scc);
        
        // there are 3 SCCs in the given graph
        assert(SCCs.size() == 3);
        for (SCC scc : SCCs)
        {
            cout << "SCC with leader " << scc.leader << " has " << scc.numNodes << " nodes." << endl;
        }
        
    }
    
    void testCase2()
    {
        cout << "***** ASSIGNMENT4 TEST CASE 2 *****" << endl;
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
        _seen       = seenList(g.size() + 1, 0);
        _times      = timesList(g.size() + 1, 0);
        _leaders    = leadersList(g.size() + 1, 0);
        
        DFSLoop(gRev);
        Graph newGraph = constructNewGraph(g, _times);
        DFSLoop(newGraph);
        
        sort(begin(_leaders), end(_leaders));
        std::vector<SCC> SCCs;
        int el = _leaders[1];
        int elCnt = 1;
        for (int i = 2; i < _leaders.size(); i++)
        {
            if (_leaders[i] == el)
                elCnt++;
            else
            {
                SCC scc;
                scc.leader = el;
                scc.numNodes = elCnt;
                SCCs.push_back(scc);
                
                el = _leaders[i];
                elCnt = 1;
            }
        }
        // last SCC
        SCC scc;
        scc.leader = el;
        scc.numNodes = elCnt;
        SCCs.push_back(scc);
        
        // there are 4 SCCs in the given graph
        assert(SCCs.size() == 4);
        for (SCC scc : SCCs)
        {
            cout << "SCC with leader " << scc.leader << " has " << scc.numNodes << " nodes." << endl;
        }
    }
    
    void computeSCC(const string& fileName)
    {
        cout << "***** ASSIGNMENT4 MAIN TEST CASE *****" << endl;
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
        
        // initialize global vars
        _seen       = seenList(G.size() + 1, 0);
        _times      = timesList(G.size() + 1, 0);
        _leaders    = leadersList(G.size() + 1, 0);
 
        DFSLoop(Grev);
        
        Graph newGraph = constructNewGraph(G, _times);
        DFSLoop(newGraph);
        
        sort(_leaders.begin(), _leaders.end());
        std::vector<SCC> SCCs;
        int el = _leaders[1];
        int elCnt = 1;
        for (int i = 2; i < _leaders.size(); i++)
        {
            if (_leaders[i] == el)
                elCnt++;
            else
            {
                SCC scc;
                scc.leader = el;
                scc.numNodes = elCnt;
                SCCs.push_back(scc);
                
                el = _leaders[i];
                elCnt = 1;
            }
        }
        // last SCC
        SCC scc;
        scc.leader = el;
        scc.numNodes = elCnt;
        SCCs.push_back(scc);
        
        cout << " Total number of SCCs is: " << SCCs.size() << endl << "Top 5 are: " << endl;
        
        // Let's just sort them in descending order by number of components
        sort(SCCs.begin(), SCCs.end(), compareByNumSCCs);
        
        for (int i = 0; i < 5; i++)
        {
            cout << "SCC with leader " << SCCs[i].leader << " has " << SCCs[i].numNodes << " nodes." << endl;
        }
        
        // Correct result is: 434821,968,459,313,211
        assert(SCCs[0].numNodes == 434821);
        assert(SCCs[1].numNodes == 968);
        assert(SCCs[2].numNodes == 459);
        assert(SCCs[3].numNodes == 313);
        assert(SCCs[4].numNodes == 211);
    }
} // namespace
