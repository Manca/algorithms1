//
//  assignment5.hpp
//  Algorithms: Design and Analysis, Part 1
//
//  Programming Assignment 6
//
//  Created by Nenad Mancevic on 3/3/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problems:
//
/***********************
     Problem 1:
     Download the text file here (http://bit.ly/1DLZCIM)
     
     The goal of this problem is to implement a variant of the 2-SUM algorithm 
     (covered in the Week 6 lecture on hash table applications).
     The file contains 1 million integers, both positive and negative 
     (there might be some repetitions!).This is your array of integers, 
     with the ith row of the file specifying the ith entry of the array.
     
     Your task is to compute the number of target values t in the interval 
     [-10000,10000] (inclusive) such that there are distinct numbers x,y in 
     the input file that satisfy x+y=t. (NOTE: ensuring distinctness requires 
     a one-line addition to the algorithm from lecture.)
     
     Problem 2:
     Download the text file here (http://bit.ly/18hppx9)
     
     The goal of this problem is to implement the "Median Maintenance" algorithm 
     (covered in the Week 5 lecture on heap applications). 
     The text file contains a list of the integers from 1 to 10000 in unsorted order;
     you should treat this as a stream of numbers, arriving one by one. Letting xi 
     denote the ith number of the file, the kth median mk is defined as the median 
     of the numbers x1,…,xk. (So, if k is odd, then mk is ((k+1)/2)th smallest number 
     among x1,…,xk; if k is even, then mk is the (k/2)th smallest number among x1,…,xk.)
     
     You should compute (m1+m2+m3+⋯+m10000)mod10000.
 ************************/


#include <fstream>
#include <list>
#include <unordered_map>
#include <unordered_set>

namespace assignment6
{
    typedef std::unordered_map<long long, std::list<long long>> hashTable;
    typedef std::unordered_set<int> seenSums;
    
    hashTable _hash;
    seenSums  _sums;
    
    
    int computeTargetSums(const string& fileName)
    {
        ifstream file(fileName, ios::in);
        
        std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
        if (file.is_open())
        {
            long long num;
            while ( file >> num)
            {
                _hash[num / 20000].push_front(num);
            }
        }
        
        // for every x in our hash table, find y that satisfies t = x + y
        for (auto pair : _hash)
        {
            for (auto num : pair.second)
            {
                auto searchMin = _hash.find((-10000 - num)/20000);
                auto searchMax = _hash.find((-10000 - num)/20000 + 1);
                if (searchMin != _hash.end())
                {
                    for (auto num2 : searchMin->second)
                        if (num + num2 >= -10000 && num + num2 <= 10000)
                            _sums.insert(num+num2);
                }
                
                if (searchMax != _hash.end())
                {
                    for (auto num2 : searchMax->second)
                        if (num + num2 >= -10000 && num + num2 <= 10000)
                            _sums.insert(num+num2);
                }
            }
        }
        
        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        std::cout << "Done. Time took to find all the sums: "
        << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << " ms" << endl;
        
        return _sums.size();
    }
}