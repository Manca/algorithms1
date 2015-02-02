//
//  main.cpp
//  Algorithms: Design and Analysis, Part 1
//
//  Created by Nenad Mancevic on 2/2/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
// Main program - all our assignments will be executed from here

#include <assert.h>
#include "assignment1.hpp"


int main(int argc, const char * argv[]) {

    // TEST CASE 1:
    vector<int> vec{4, 5, 6, 1, 3};
    
    long long inversions = assignment1::Count(vec);
    
    cout << "Number of inversions is: " << inversions << endl;
    
    // TEST CAST 2:
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

    
}
