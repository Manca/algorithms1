//
//  assignment1.cpp
//  Algorithms: Design and Analysis, Part 1
//
//  Programming Assignment 1
//
//  Created by Nenad Mancevic on 2/2/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem:
//
/***********************
    Download the text file here (http://bit.ly/1z79yXK)
    This file contains all of the 100,000 integers between 1 and 100,000 
    (inclusive) in some order, with no integer repeated.

    Your task is to compute the number of inversions in the file given, 
    where the ith row of the file indicates the ith entry of an array.
 
    Because of the large size of this array, you should implement the 
    fast divide-and-conquer algorithm covered in the video lectures.
************************/

#include <iostream>
#include <vector>
using namespace std;

namespace assignment1
{
    // counting inversions
    long long CountSplitInv(vector<int> &input, const vector<int>& left, const vector<int>& right)
    {
        vector<int> result;
        long long inversions = 0;
        
        int i = 0, j = 0;
        
        for (int k = 0; k < (left.size() + right.size()); k++)
        {
            if (i < left.size() && left[i] < right[j])
            {
                result.push_back(left[i]);
                i++;
            }
            else if (j < right.size() && right[j] <= left[i])
            {
                result.push_back(right[j]);
                j++;
                
                // inversion found (it's a split inversion)!
                inversions += left.size() - i;
                
                // if you want to print the inversions, uncomment this code
                //for (int o = i; o < left.size(); o++)
                //    cout << right[(j - 1)] << ", " << left[o] << endl;
            }
            else if (i < left.size())
            {
                result.push_back(left[i]);
                i++;
            }
            else if (j < right.size())
            {
                result.push_back(right[j]);
                j++;
            }
        }
        input = result;
        
        return inversions;
    }

    // entry point to the algorithm
    long long Count(vector<int> &input)
    {
        if (input.size() == 1)
            return 0;
        else
        {
            // prepare two subarrays
            auto mid = input.begin() + (input.size()/2);
            vector<int> left(input.begin(), mid);
            vector<int> right(mid, input.end());
            
            // find inversions in each half of the array
            long long x = Count(left);
            long long y = Count(right);
            
            // finally if there are split inversions find them two
            long long z = CountSplitInv(input, left, right);
            
            // the result is the sum of the inversions in each step
            return x + y + z;
        }
    }
}

void TestCase1()
{
    
}
