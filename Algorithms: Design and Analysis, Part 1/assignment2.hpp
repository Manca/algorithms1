//
//  assignment2.cpp
//  Algorithms: Design and Analysis, Part 1
//
//  Programming Assignment 2
//
//  Created by Nenad Mancevic on 2/10/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
//  Problem:
//
/***********************
    Download the text file here (http://bit.ly/1vhCUlY)
    The file contains all of the integers between 1 and 10,000 
    (inclusive, with no repeats) in unsorted order. The integer 
    in the ith row of the file gives you the ith entry of an input array.

    Your task is to compute the total number of comparisons used to 
    sort the given input file by QuickSort. As you know, the number 
    of comparisons depends on which elements are chosen as pivots, 
    so we'll ask you to explore three different pivoting rules.
     
    You should not count comparisons one-by-one. Rather, when there 
    is a recursive call on a subarray of length m, you should simply 
    add m−1 to your running total of comparisons. 
    (This is because the pivot element is compared to each of the 
    other m−1 elements in the subarray in this recursive call.)
     
    1) For the first part of the programming assignment, you should 
    always use the first element of the array as the pivot element.
     
    2) Compute the number of comparisons (as in Problem 1), always 
    using the final element of the given array as the pivot element.
    (just before the main Partition subroutine, you should exchange 
    the pivot element (i.e., the last element) with the first element)
     
    3) Compute the number of comparisons (as in Problem 1), using 
    the "median-of-three" pivot rule. In more detail, you should 
    choose the pivot as follows:

    Consider the first, middle, and final elements of the given array.
    Identify which of these three elements is the median, and use this 
    as your pivot.
************************/

#include <vector>
using namespace std;

namespace assignment2 {
    
    // helper function
    void swap(int& a, int& b)
    {
        int tmp = a;
        a = b;
        b = tmp;
    }
    
    // main partition function
    int partition(vector<int>& input, int left, int right)
    {
        int p = input[left];
        int i = left + 1;
        
        for (int j = left + 1; j < right; j++)
        {
            if (input[j] < p)
            {
                swap(input[i], input[j]);
                i++;
            }
        }
        swap(input[left], input[i-1]);
        
        return (i-1);
    }

    // first problem
    int noCompFirst = 0;
    int partitionFirst(vector<int>& input, int left, int right)
    {
        noCompFirst += right - left - 1;
        
        return partition(input, left, right);
    }
    
    // second problem
    int noCompLast = 0;
    int partitionLast(vector<int>& input, int left, int right)
    {
        noCompLast += right - left - 1;
        
        // swap the last element with the first
        swap(input[right-1], input[left]);
        
        return partition(input, left, right);
    }
    
    // third problem
    int noCompMedian = 0;
    int partitionMedian(vector<int>& input, int left, int right)
    {
        noCompMedian += right - left - 1;
        
        int midInd = (left + right - 1) / 2;
        // initially pivot position is unknown
        int p = -1;
        
        // compute the median of the three elements (first, median, last)
        // and assign its index to the pivot
        if (input[left] < input[midInd])
        {
            if (input[left] >= input[right-1])
                p = left;
            else if (input[midInd] < input[right-1])
                p = midInd;
        }
        else
        {
            if (input[midInd] >= input[right-1])
                p = midInd;
            else if (input[left] < input[right-1])
                p = left;
        }
        // fallback
        if (p == -1)
            p = right - 1;
        
        // bring the median pivot to the beginning
        swap(input[left], input[p]);
        
        return partition(input, left, right);
    }
    
    // entry point to the algorithm
    // partitionType: 1, 2, 3
    void QuickSort(vector<int>& input, int left, int right, int partitionType)
    {
        if (left == right)
            return;
        
        int pivotIndex = -1;
        switch (partitionType)
        {
            case 1: pivotIndex = partitionFirst(input, left, right); break;
            case 2: pivotIndex = partitionLast(input, left, right); break;
            case 3: pivotIndex = partitionMedian(input, left, right); break;
        }
        QuickSort(input, left, pivotIndex, partitionType);
        QuickSort(input, pivotIndex+1, right, partitionType);
    }
    
} // assignment2
