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

#include "assignment1.hpp"
#include "assignment2.hpp"


int main(int argc, const char * argv[]) {

    /*** Assignment 1 test cases ***/
    // TEST CASE 1:
    vector<int> vec{4, 5, 6, 1, 3};
    
    long long inversions = assignment1::Count(vec);
    
    cout << "Number of inversions is: " << inversions << endl;
    
    // TEST CASE 2:
    // load file
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
    
    
}
