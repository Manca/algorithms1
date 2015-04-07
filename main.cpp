//
//  main.cpp
//  Algorithms: Design and Analysis, Part 1
//
//  Created by Nenad Mancevic on 2/2/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
// Main program - all our assignments will be executed from here

#include <assert.h>
#include <fstream>
#include <chrono>

#include "assignment1.hpp"
#include "assignment2.hpp"
#include "assignment3.hpp"
#include "assignment4.hpp"
#include "assignment5.hpp"
#include "assignment6.hpp"

int main(int argc, const char * argv[]) {

    /*** Assignment 1 test cases ***/
    // TEST CASE 1:
    cout << "*** Assignment 1 - Test Case 1 ***" << endl;
    vector<int> vec{4, 5, 6, 1, 3};
    
    long long inversions = assignment1::Count(vec);
    
    cout << "Number of inversions is: " << inversions << endl;
    
    // TEST CASE 2:
    // load file
    cout << "*** Assignment 1 - Test Case 2 ***" << endl;
    ifstream inputFile("IntegerArray.txt", ios::in);
    vector<int> fileNumbers;

    // fill it in with numbers from the file
    if (inputFile.is_open())
    {
        int number;
        while (inputFile >> number)
        {
            fileNumbers.push_back(number);
        }
        inputFile.close();
        // do the work
        long long variations = assignment1::Count(fileNumbers);
        cout << "Total number of inversions is: " << variations << endl;
        assert(variations == 2407905288);
    }
    else
    {
        cout << "File cannot be opened!" << endl;
    }
    
    /*** Assignment 2 test cases ***/
    // TEST CASE 1:
    cout << endl << "*** Assignment 2 - Test Case 1 ***" << endl;
    ifstream as2File("QuickSort.txt", ios::in);
    vector<int> as2Input;
    
    if (as2File.is_open())
    {
        int number;
        while (as2File >> number)
        {
            as2Input.push_back(number);
        }
        as2File.close();
        
        // create three copies for each algorithm (input array is mutable)
        vector<int> as2Input1 = as2Input;
        vector<int> as2Input2 = as2Input;
        vector<int> as2Input3 = as2Input;
        
        // do the work
        assignment2::QuickSort(as2Input1, 0, (int)as2Input1.size(), 1);
        assignment2::QuickSort(as2Input2, 0, (int)as2Input2.size(), 2);
        assignment2::QuickSort(as2Input3, 0, (int)as2Input3.size(), 3);
        
        cout << "Number of comparisons for first pivot: " << assignment2::noCompFirst << endl;
        cout << "Number of comparisons for last pivot: " << assignment2::noCompLast << endl;
        cout << "Number of comparisons for median pivot: " << assignment2::noCompMedian << endl;
        
        assert(assignment2::noCompFirst == 162085);
        assert(assignment2::noCompLast == 164123);
        assert(assignment2::noCompMedian == 138382);
    }
    else
    {
        cout << "File cannot be opened!" << endl;
    }
    
    /*** Assignment 3 test cases ***/
    cout << endl << "*** Assignment 3 - Test Case 1 ***" << endl;
    assignment3::Graph graph("kargerMinCut.txt");
    for (int i = 0; i < 10; i++)
    {
        cout << "MinCut so far: " << graph.mincut() << endl;
    }
    
    // Min-Cut for this graph is 17, if we don't get exactly 17,
    // we might need to increase number of iterations above
    //assert(graph.mincut() == 17);
    
    /*** Assignment 4 test cases ***/
    cout << endl << "*** Assignment 4 - Test Case 1 ***" << endl;
    assignment4::testCase1();
    cout << "*** Assignment 4 - Test Case 2 ***" << endl;
    assignment4::testCase2();
    
    cout << "*** Assignment 4 - Main Test Case (disabled) ***" << endl;
    /**** Takes too much time... Enable when needed ****
    *
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    assignment4::computeSCC("SCC.txt");
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Total time assignment4 main case took to run: "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << "ms.\n";
    *
    ****/
    
    /*** Assignment 5 test cases ***/
    cout << endl << "*** Assignment 5 - Test Case 1 ***" << endl;
    assignment5::loadGraphAndInit("dijkstraData.txt");
    assignment5::computeShortestPaths();
    
    /*** Assignment 6 test cases ***/
    // 6.1) 2-SUM Problem
    cout << endl << "*** Assignment 6 - Problem 1 ***" << endl;
    long long sums = assignment6::computeTargetSums("algo1-programming_prob-2sum.txt");
    cout << "Number of sums is: " << sums << endl;
    
    // 6.2) Median Maintenance
    cout << endl << "*** Assignment 6 - Problem 2 ***" << endl;
    int sumOfMedians = assignment6::computeSumOfMedians("Median.txt") % 10000;
    std::cout << "The sum of medians mod 10000 is: " << sumOfMedians << std::endl;
    
}
