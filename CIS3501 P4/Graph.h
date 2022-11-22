//Program Name: Graph.h
//Programmer Name: Anthony Vettraino
//Description: Graph class header for declaration
//Date Created: 8/3/2021

#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include "Edge.h"

using namespace std;

//Description: Adjacency list
struct AdjList
{
	Edge* head;
};

//Description: data for priority queue
struct pqData
{
	int keyWeight;
	int keyDestinationVertex;
	int keySourceVertex;
};


class Graph
{
private:
	int numberOfVertices;
	AdjList* adjacencyListGraph;
	AdjList* adjacencyListMST;

public:
	int count = 0;
	Graph();
	Graph(int vertices);
	void addEdge(int source, int destination, int weight, ostream &output);
	void printGraph(ostream &output);
	void primMST(ostream &output);
	void printMST(ostream &output);
	void dijkstras(int src, ostream &output);
	void printPath(int dest, vector<int> parent, vector<int> distance, ostream &output);
	void connectedParts(ostream& output);
	void DFsearch(int vertex, bool visited[], bool visitedSubGraph[]);
	bool isGraphConnected();
	~Graph();
};