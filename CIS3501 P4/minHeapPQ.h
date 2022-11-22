//Program Name: minHeapPQ.h
//Programmer Name: Anthony Vettraino
//Description: minHeapPQ class header for declaration
//Date Created: 8/3/2021

#pragma once
#include<vector>
#include<iostream>
#include "Graph.h"

using namespace std;

class minHeapPQ
{
private:
	int size;	// current size of the heap
	int capacity;	//max size of heap
	vector<pqData> heap;	//store elements as a vector
	int parent(int i);	//returns the parent index
	int left(int i);	//returns left child
	int right(int i);	//returns right child
	
public:
	minHeapPQ(int capacity);	//constructor
	void insert(pqData inNode);	//insert key into min heap
	pqData extractMin();	//extract min element
	void heapify(int i);	//heapify a sub-tree
	bool empty();	// see if heap is empty
};
