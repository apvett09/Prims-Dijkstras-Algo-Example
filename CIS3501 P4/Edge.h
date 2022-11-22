//Program Name: Edge.h
//Programmer Name: Anthony Vettraino
//Description: Edge class header for declaration and implementation
//Date Created: 8/3/2021

#pragma once

class Edge
{
public:
	int sourceVertex;
	int destinationVertex;
	int edgeWeight;
	Edge* nextEdge = nullptr;

	//Description: no-args constructor
	//Pre-condition: resultSetClass object has been created
	//Post-condition: assignes -1 to sourceVertex, destinationVertex, edgeWeight
	Edge()
	{
		sourceVertex = -1;
		destinationVertex = -1;
		edgeWeight = -1;
	}

	//Description: 3 argument constructor
	//Pre-condition: resultSetClass object has been created and instantiated
	//Post-condition: assings source to sourceVertex,
	//                assings destination to destinationVertex
	//                assigns weight to edgeWeight
	Edge(int source, int destination, int weight)
	{
		sourceVertex = source;
		destinationVertex = destination;
		edgeWeight = weight;
	}
};
