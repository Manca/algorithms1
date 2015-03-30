#pragma once
//
//  Heap.hpp - Auxiliary data structure that implements Min and Max Heap
//
//  Algorithms: Design and Analysis, Part 1
//
//  Created by Nenad Mancevic on 3/04/15.
//  Copyright (c) 2015 Nenad Mancevic. All rights reserved.
//
// TODO: Write tests for this Data Structure

namespace DataStructures {

    class Heap
    {
    public:
        Heap(bool min): _minHeap(min) {}
        ~Heap() {}
        
        void insert(int el)
        {
            _heap.push_back(el);
            bubbleUp(_minHeap);
        }
        
        int extractMinMax()
        {
            int result;
            if (_heap.size() > 0)
            {
                result = _heap[0];
                _heap[0] = _heap[_heap.size() - 1];
                _heap.pop_back();
                
                bubbleDown(_minHeap);
            }
            return result;
        }
        
        int size()
        {
            return _heap.size();
        }
        
        const int operator[](int idx) const
        {
            return _heap[idx];
        }
        
    private:
        bool                _minHeap;
        std::vector<int>    _heap;
        
        void bubbleUp(bool minHeap)
        {
            if (_heap.size() > 1)
            {
                int lastIndex = _heap.size() - 1;
                int parentIndex = parent(_heap.size() - 1);
                if (minHeap)
                {
                    while (parentIndex >= 0 && _heap[lastIndex] < _heap[parentIndex])
                    {
                        // exchange values
                        int tmp = _heap[parentIndex];
                        _heap[parentIndex] = _heap[lastIndex];
                        _heap[lastIndex] = tmp;
                        
                        // buuble up
                        lastIndex = parentIndex;
                        parentIndex = parent(parentIndex);
                    }
                }
                else
                {
                    while (parentIndex >= 0 && _heap[lastIndex] > _heap[parentIndex])
                    {
                        // exchange values
                        int tmp = _heap[parentIndex];
                        _heap[parentIndex] = _heap[lastIndex];
                        _heap[lastIndex] = tmp;
                        
                        // buuble up
                        lastIndex = parentIndex;
                        parentIndex = parent(parentIndex);
                    }
                }
            }
        }
        
        void bubbleDown(bool minHeap)
        {
            if (_heap.size() > 1)
            {
                int rootIndex = 0;
                int leftChildIdx = leftChild(rootIndex);
                int rightChildIdx = rightChild(rootIndex);
                
                if (_minHeap)
                {
                    int minChild = (_heap[leftChildIdx] < _heap[rightChildIdx]) ? leftChildIdx : rightChildIdx;
                    while (minChild < _heap.size() && _heap[rootIndex] > _heap[minChild])
                    {
                        // exchange
                        int tmp = _heap[minChild];
                        _heap[minChild] = _heap[rootIndex];
                        _heap[rootIndex] = tmp;
                        
                        // bubble down
                        rootIndex = minChild;
                        leftChildIdx = leftChild(rootIndex);
                        rightChildIdx = rightChild(rootIndex);
                        
                        minChild = (_heap[leftChildIdx] < _heap[rightChildIdx]) ? leftChildIdx : rightChildIdx;
                    }
                }
                else
                {
                    int maxChild = (_heap[leftChildIdx] > _heap[rightChildIdx]) ? leftChildIdx : rightChildIdx;
                    while (maxChild < _heap.size() && _heap[rootIndex] < _heap[maxChild])
                    {
                        // exchange
                        int tmp = _heap[maxChild];
                        _heap[maxChild] = _heap[rootIndex];
                        _heap[rootIndex] = tmp;
                        
                        // bubble down
                        rootIndex = maxChild;
                        leftChildIdx = leftChild(rootIndex);
                        rightChildIdx = rightChild(rootIndex);
                        
                        maxChild = (_heap[leftChildIdx] > _heap[rightChildIdx]) ? leftChildIdx : rightChildIdx;
                    }
                }
            }
        }
        
        int parent(int x)
        {
            if (_heap.size() > 0)
            {
                return floor(x/2)-(x+1)%2;
            }
            else
                return x;
        }
        
        int leftChild(int x)
        {
            int left = x*2 + 1;
            if (left < _heap.size())
                return left;
            else
                return x;
        }
        
        int rightChild(int x)
        {
            int right = x*2 + 2;
            if (right < _heap.size())
                return right;
            else
                return leftChild(x);
        }
    };
} //namespace