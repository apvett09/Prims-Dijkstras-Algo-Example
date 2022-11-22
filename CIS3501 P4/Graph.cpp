//Program Name: Graph.cpp
//Programmer Name: Anthony Vettraino
//Description: Graph class implementation file
//Date Created: 8/3/2021

#include "Graph.h"
#include "resultSetClass.h"
#include "minHeapPQ.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <list>
#include <iomanip>

using namespace std;

//Description: No-args constructor
//Pre-condition: Graph object has been created
//Post-condition: assign 0 to numberOfVertices,
//                displays deafult graph message
//                initializes two adjacency lists to 0
Graph::Graph()
{
	adjacencyListGraph = new AdjList[0];
	adjacencyListMST = new AdjList[0];
	numberOfVertices = 0;
	cout << "Default - Empty Graph Created" << endl;
}

//Description: 1 argument constructor
//Pre-condition: Graph object has been created and instantiated
//Post-condition: assign vertices to numberOfVertices,
//                initializes two adjacency lists and assigns nullptr to their head
Graph::Graph(int vertices)
{
	numberOfVertices = vertices;
	// the following creates an array of AdjList structures. Those structures containing Edge object pointers
	// we assign the Edge-pointer's nextEdge ptr to nullptr so they point to nothing
	adjacencyListGraph = new AdjList[vertices];
	adjacencyListMST = new AdjList[vertices];
	for (int i = 0; i < vertices; i++)
	{
		adjacencyListGraph[i].head = nullptr;
		adjacencyListMST[i].head = nullptr;
	}
}

//Description: Fucntion to add and edge to adjacency list
//Pre-condition: Graph object has been created and calls addEdge with 3 paramaters passed to it
//Post-condition: displays error messages based on if conditions are met or not, otherwise
//                adds edge source, destination, weight and edge destination, source, weight to adjcencyListGraph
void Graph::addEdge(int source, int destination, int weight, ostream &output) 
{
	if (numberOfVertices == 0) {
		cout << "Empty Graph - Cannot Add Edge: " << source << ", " << destination << ", " << weight << endl;
		output << "Empty Graph - Cannot Add Edge: " << source << ", " << destination << ", " << weight << endl;
	}
	else if (source < 0 || destination < 0 || source > numberOfVertices - 1 || destination > numberOfVertices - 1) {
		cout << "Invalid Source or Destination Vertex - Cannot Add Edge: " << source << ", "
			<< destination << ", " << weight << " - Edge request ignored" << endl;
		output << "Invalid Source or Destination Vertex - Cannot Add Edge: " << source << ", "
			<< destination << ", " << weight << " - Edge request ignored" << endl;
	}
	else if (weight <= 0) {
		cout << "Invalid Weight - Cannot Add Edge: " << source << ", "
			<< destination << ", " << weight << " - Edge request ignored" << endl;
		output << "Invalid Weight - Cannot Add Edge: " << source << ", "
			<< destination << ", " << weight << " - Edge request ignored" << endl;
	}
	else {

		//add edge from source to destination
		// we dynamically allocate a new Edge and assign its nextEdge ptr to point to nullptr
		// we then assign the new Edge's nextEdge to point to the Edge ptr currently at adjacencyListGraph[sourceVertex]
		// we then assign the newly created Edge to the position in the adjacencyListGraph where the previous Edge-pointer was stored. 
		// that newly created Edge's nextEdge ptr points to the Edge that was previously in that position in the adjacencyListGraph, so it is not lost
		Edge* sdEdge = new Edge(source, destination, weight);
		sdEdge->nextEdge = nullptr;
		sdEdge->nextEdge = adjacencyListGraph[source].head; 
		adjacencyListGraph[source].head = sdEdge;	
		cout << "Edge Added: " << source << ", " << destination << ", " << weight << endl;
		output << "Edge Added: " << source << ", " << destination << ", " << weight << endl;

		//add edge from destination to source because undirected graph
		Edge* dsEdge = new Edge(destination, source, weight);
		dsEdge->nextEdge = nullptr;
		dsEdge->nextEdge = adjacencyListGraph[destination].head;
		adjacencyListGraph[destination].head = dsEdge;
		cout << "Edge Added: " << destination << ", " << source << ", " << weight << endl;
		output << "Edge Added: " << destination << ", " << source << ", " << weight << endl;
		//count++;
	}
}

//Description: Fucntion to print adjacencyListGraph info
//Pre-condition: Graph object has been created and adjacenyListGraph contains edges
//Post-condition: displays adjacencyListGraph info to user and output file
void Graph::printGraph(ostream &output) 
{
	cout << "\nFull Graph - Adjacency List" << endl;
	output << "\nFull Graph - Adjacency List" << endl;
	for (int i = 0; i < numberOfVertices; i++)
	{
		Edge* temp = adjacencyListGraph[i].head;
		cout << "Adj[" << i << "] -> ";
		output << "Adj[" << i << "] -> ";
		while (temp)
		{
			cout << "(" << temp->destinationVertex << "," << temp->edgeWeight << ") ";
			output << "(" << temp->destinationVertex << "," << temp->edgeWeight << ") ";
			temp = temp->nextEdge;
		}
		cout << endl;
		output << endl;
	}
	cout << endl;
	output << endl;
}

//Description: Prim's Algorithm
//Pre-condition: Graph object has been created and adjacenyListGraph contains edges
//Post-condition: displays error message if number of vertices is 0, otherwise
//                adds correct edges to adjacencyListMST and
//                prints minimum spanning tree data to user and output file
void Graph::primMST(ostream &output)
{
	if (numberOfVertices == 0) {
		cout << "Empty Graph - No MST" << endl;
	}
	else
	{
		pqData extractedPQData;
		pqData intoPQData;
		vector<bool> mst(numberOfVertices, false);
		vector<resultSetClass> resultSet(numberOfVertices);	
		vector<int> weights(numberOfVertices, INT_MAX);

		weights.at(0) = 0;

		minHeapPQ minHeap(numberOfVertices * 2);

		for (int i = 0; i < numberOfVertices; i++)
		{
			Edge* temp = adjacencyListGraph[i].head;
			if (adjacencyListGraph[i].head != nullptr)
			{
				intoPQData.keyWeight = weights.at(i);
				intoPQData.keyDestinationVertex = i;
				intoPQData.keySourceVertex = i;

				minHeap.insert(intoPQData);
				resultSet[i].parent = -1;
				mst.at(i) = true;
				//temp = temp->nextEdge;
				break;
			}

			
		}

		while (!minHeap.empty())
		{
			extractedPQData = minHeap.extractMin();

			if (mst[extractedPQData.keyDestinationVertex] == false && mst[extractedPQData.keySourceVertex] == true)
			{
				//add to adjacencyListMST
				mst.at(extractedPQData.keyDestinationVertex) = true;

				Edge* sdEdge = new Edge(extractedPQData.keySourceVertex, extractedPQData.keyDestinationVertex, extractedPQData.keyWeight);
				sdEdge->nextEdge = nullptr;
				sdEdge->nextEdge = adjacencyListMST[extractedPQData.keySourceVertex].head;
				adjacencyListMST[extractedPQData.keySourceVertex].head = sdEdge;

				Edge* dsEdge = new Edge(extractedPQData.keyDestinationVertex, extractedPQData.keySourceVertex, extractedPQData.keyWeight);
				dsEdge->nextEdge = nullptr;
				dsEdge->nextEdge = adjacencyListMST[extractedPQData.keyDestinationVertex].head;
				adjacencyListMST[extractedPQData.keyDestinationVertex].head = dsEdge;
			}

			Edge* temp = adjacencyListGraph[extractedPQData.keyDestinationVertex].head;
			while (temp)
			{
				if (mst[temp->destinationVertex] == false) {
					if (weights[temp->destinationVertex] > temp->edgeWeight)
					{
						intoPQData.keyWeight = temp->edgeWeight;
						intoPQData.keyDestinationVertex = temp->destinationVertex;
						intoPQData.keySourceVertex = temp->sourceVertex;
						minHeap.insert(intoPQData);

						resultSet[temp->destinationVertex].parent = extractedPQData.keyDestinationVertex;
						resultSet[temp->destinationVertex].weight = temp->edgeWeight;
						weights[temp->destinationVertex] = temp->edgeWeight;
					}
				}
				temp = temp->nextEdge;
			}
		}
		int totalMSTWeight = 0;
		cout << "Minimum Spanning Tree" << endl;
		output << "Minimum Spanning Tree" << endl;
		for (int nbr = 1; nbr < numberOfVertices; nbr++)
		{
			if (resultSet[nbr].parent > -1 && resultSet[nbr].weight > -1) {
				cout << "Edge: " << nbr << "-" << resultSet[nbr].parent << " weight: " << resultSet[nbr].weight << endl;
				output << "Edge: " << nbr << "-" << resultSet[nbr].parent << " weight: " << resultSet[nbr].weight << endl;
				totalMSTWeight += resultSet[nbr].weight;
			}
		}
		cout << "Total cost of MST: " << totalMSTWeight << endl;
		output << "Total cost of MST: " << totalMSTWeight << endl;
		cout << endl;
		output << endl;
	}
	
}

//Description: Function to print MST info
//Pre-condition: adjacencyListMST contains edges or is empty
//Post-condition: displays adjacencyListMST graph data to user and output file
void Graph::printMST(ostream &output)
{
	
	if (numberOfVertices == 0) {
		cout << "Empty Graph - No MST" << endl;
	}
	else
	{
		output << "MST Graph - Adjacency List" << endl;
		cout << "MST Graph - Adjacency List" << endl;
		for (int i = 0; i < numberOfVertices; i++)
		{
			Edge* temp = adjacencyListMST[i].head;
			
			if (adjacencyListGraph[i].head != nullptr)
			{
				cout << "Adj[" << i << "] -> ";
				output << "Adj[" << i << "] -> ";
				while (temp)
				{
					cout << "(" << temp->destinationVertex << "," << temp->edgeWeight << ") ";
					output << "(" << temp->destinationVertex << "," << temp->edgeWeight << ") ";
					temp = temp->nextEdge;
				}
				cout << endl;
				output << endl;
			}
			
		}
		cout << endl;
		output << endl;
	}
}

//Description: Graph class destructor
//Pre-condition: Graph class object has been created
//Post-condition: deallocates objects in the adjacency list
Graph::~Graph()
{
	Edge* temp;
	Edge* next;
	for (int i = 0; i < numberOfVertices; i++)
	{
		temp = adjacencyListGraph[i].head;
		while (temp)
		{
			next = temp->nextEdge;
			temp = nullptr;
			delete temp;
			temp = next;
		}
	}
	for (int i = 0; i < numberOfVertices; i++)
	{
		temp = adjacencyListMST[i].head;
		while (temp)
		{
			next = temp->nextEdge;
			temp = nullptr;
			delete temp;
			temp = next;
		}
	}
}

//Description: Function to create iterations of Dijkstras shortest path table
//Pre-condition: Graph class object has been created and user selects valid starting vertex
//Post-condition: Displays to user and output file iterations of Dijkstras shortest path table,
//                Displays shortest path from users selection or more iterations of Dijkstras based on users menu selection
//                Exits to end of file or next graph
void Graph::dijkstras(int src, ostream &output)
{
	vector<int> distance(numberOfVertices, INT_MAX);
	vector<string> known(numberOfVertices, "FALSE");
	vector<int> parent(numberOfVertices, -1);

	minHeapPQ minHeap(numberOfVertices * 2);

	pqData extractedPQData;
	pqData intoPQData;

	for (int i = 0; i < numberOfVertices; i++)
	{
		if (i == src)
		{
			distance.at(i) = 0;
			intoPQData.keySourceVertex = i;
			intoPQData.keyWeight = 0;
			minHeap.insert(intoPQData);
		}
		else
		{
			distance.at(i) = INT_MAX;
			intoPQData.keySourceVertex = i;
			intoPQData.keyWeight = distance.at(i);
			minHeap.insert(intoPQData);
		}
	}

	int count1 = 0;
	int selection{};
	while (!minHeap.empty() && count1 < numberOfVertices)
	{
		extractedPQData = minHeap.extractMin();
		
		int vertex = extractedPQData.keySourceVertex;

		Edge* temp = adjacencyListGraph[vertex].head;
		while (temp != nullptr)
		{
			int destination = temp->destinationVertex;

			if (distance.at(vertex) != INT_MAX && temp->edgeWeight + distance.at(vertex) < distance.at(destination))
			{
				distance.at(destination) = distance.at(vertex) + temp->edgeWeight;
				intoPQData.keySourceVertex = destination;
				intoPQData.keyWeight = distance.at(destination);
				minHeap.insert(intoPQData);
				parent.at(destination) = vertex;
			}
			temp = temp->nextEdge;
		}
		known.at(vertex) = "TRUE";
		count1++;

		cout << "Vertex" << setw(8) << "Known" << setw(18) << "Distance" << setw(8) << "Parent" << endl;
		output << "Vertex" << setw(8) << "Known" << setw(18) << "Distance" << setw(8) << "Parent" << endl;
		for (int i = 0; i < numberOfVertices; i++)
		{
			cout << setw(2) << i << setw(12) << known.at(i) << setw(16) << distance.at(i) << setw(8) << parent.at(i) << endl;
			output << setw(2) << i << setw(12) << known.at(i) << setw(16) << distance.at(i) << setw(8) << parent.at(i) << endl;
		}
		cout << endl;
		output << endl;
	}

	do
	{
		// Display menu
		cout << "Please select an action:" << endl;
		cout << "   1) Destination request - program will return the path and cost or 'No Path' if no path exists." << endl;
		cout << "   2) New starting vertex - program generates new shortest path table." << endl;
		cout << "   3) Exit to next graph in input file or end program if no more graphs in input file ." << endl;
		cin >> selection;

		if (selection == 1)
		{
			int userSel;
			//print path
			do
			{
				cout << "Please select a vertex destination number from 0 - " << numberOfVertices - 1 << " : ";
				cin >> userSel;
				if (!cin || userSel < 0 || userSel >= numberOfVertices)
				{
					cout << "Error - not a valid vertex" << endl;
				}
				else
				{
					output << "User has selected " << userSel << " as a destination vertex" << endl;
					printPath(userSel, parent, distance, output);
					cout << endl;
					output << endl;
					if (distance[userSel] != INT_MAX)
					{
						cout << "Total Path Cost: " << distance[userSel] << endl;
						output << "Total Path Cost: " << distance[userSel] << endl;
					}
				}

			} while (!cin || userSel < 0 || userSel >= numberOfVertices);
			cin.clear();
			cin.ignore();
			fflush(stdin);
		}
		else if (selection == 2)
		{
			int userSel;
			do
			{
				cout << "Please select a vertex number from 0 - " << numberOfVertices - 1 << " : ";
				cin >> userSel;
				if (!cin || userSel < 0 || userSel >= numberOfVertices)
				{
					cout << "Error - not a valid vertex" << endl;
				}
				else
				{
					output << "User has selected " << userSel << " as a new starting vertex" << endl;
					dijkstras(userSel, output);
				}
			} while (!cin || userSel < 0 || userSel >= numberOfVertices);
			cin.clear();
			cin.ignore();
			fflush(stdin);
		}
		else if (selection == 3)
		{
			break;
		}
		else
		{
			cout << "Unknown selection, please try again" << endl;
		}
	} while (selection != 3);
}



//Description: Function to create subgraphs if original graph is not fully connected
//Pre-condition: Graph object is created with valid number of vertices.
//               isGraphConnected function returns false
//Post-condition: displays unconnected subgraphs of original graph along with corresponding MSTs
void Graph::connectedParts(ostream& output)
{

	bool* visited = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
		visited[i] = false;

	

	for (int i = 0; i < numberOfVertices; i++)
	{
		
		if (visited[i] == false)
		{
			bool* visitedSubGraph = new bool[numberOfVertices];
			for (int i = 0; i < numberOfVertices; i++)
				visitedSubGraph[i] = false;

			Graph g1(numberOfVertices);
			DFsearch(i, visited, visitedSubGraph);

			
			vector<pair<int, int>> addedEdges;
			for (int v = 0; v < numberOfVertices; v++)
			{
				if (visitedSubGraph[v] == true)
				{
					Edge* temp = adjacencyListGraph[v].head;
					while (temp)
					{
						bool repeat = false;
						for (int i = 0; i < addedEdges.size(); i++)
						{
							if (addedEdges[i] == make_pair(temp->sourceVertex, temp->destinationVertex) || addedEdges[i] == make_pair(temp->destinationVertex, temp->sourceVertex))
								repeat = true;
						}
						if (temp->sourceVertex < 0 || temp->destinationVertex < 0 || temp->edgeWeight <= 0)
						{
							
						}
						else if (!repeat)
						{
							g1.addEdge(temp->sourceVertex, temp->destinationVertex, temp->edgeWeight, output);
							addedEdges.push_back(make_pair(temp->sourceVertex, temp->destinationVertex));
							addedEdges.push_back(make_pair(temp->destinationVertex, temp->sourceVertex));
							count++;
							
						}
						else
						{
							repeat = false;
						}
						temp = temp->nextEdge;
					}
				}
			}
			delete[] visitedSubGraph;
			cout << endl;
			output << endl;
			
			if (count == 0)
			{
				cout << "Minimum Spanning Tree" << endl;
				output << "Minimum Spanning Tree" << endl;
				cout << "Edge: " << i << " - " << i << " weight: 0" << endl;
				output << "Edge: " << i << " - " << i << " weight: 0" << endl;
				cout << "Total cost of MST: 0" << endl;
				output << "Total cost of MST: 0" << endl;
				cout << endl;
				output << endl;
				cout << "MST Graph - Adjacency List" << endl;
				output << "MST Graph - Adjacency List" << endl;
				cout << "Adj[" << i << "] ->" << endl;
				output << "Adj[" << i << "] ->" << endl;
				count = 0;
				g1.~Graph();
			}
			else
			{
				g1.primMST(output);
				g1.printMST(output);
				count = 0;
				g1.~Graph();
			}
		}
	}
	delete[] visited;
}


//Description: Function to check which vertices are connected to one another
//Pre-condition: Graph object has been created with valid number of vertices
//Post-condition: updates passed in parameter arrays to true if the vertices are connected
void Graph::DFsearch(int vertex, bool visited[], bool visitedSubGraph[])
{
	visitedSubGraph[vertex] = true;
	visited[vertex] = true;

	Edge* temp = adjacencyListGraph[vertex].head;
	while (temp)
	{
		if (!visited[temp->destinationVertex]) {
			DFsearch(temp->destinationVertex, visited, visitedSubGraph);
	
		}
		temp = temp->nextEdge;	
	}

}


//Description: Function to print the path from the user's selected path destination
//Pre-condition: Graph object has been created with valid number of vertices
//Post-condition: displays path from source to user's selected destination, to user and output file
//				  displays "No Path" if there is no path from the source to the user selected destination
void Graph::printPath(int dest, vector<int> parent, vector<int> distance, ostream &output)
{
	if (distance[dest] == INT_MAX)
	{
		cout << "No Path";
		output << "No Path";
	}

	if (parent[dest] == -1 && distance[dest] != INT_MAX)
	{
		cout << dest << " ";
		output << dest << " ";
		return;
	}

	if (distance[dest] != INT_MAX)
	{
		printPath(parent[dest], parent, distance, output);
		cout << dest << " ";
		output << dest << " ";
	}
	
}


//Description: Function to check if graph object is fully connected
//Pre-condition: graph object has been created with vaild number of vertices
//Post-condition: returns false if the graph is not fully connected
//				  returns true if the graph object is fully connected
bool Graph::isGraphConnected()
{
	bool* visited = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
		visited[i] = false;

	bool* visitedSubGraph = new bool[numberOfVertices];
	for (int i = 0; i < numberOfVertices; i++)
		visitedSubGraph[i] = false;

	Edge* temp = adjacencyListGraph[0].head;
	while (temp)
	{
		if (!visited[temp->destinationVertex]) {
			DFsearch(temp->destinationVertex, visited, visitedSubGraph);
		}

		temp = temp->nextEdge;
	}
	for (int i = 0; i < numberOfVertices; i++)
	{
		if (visited[i] == false)
			return false;
	}
	delete[] visited;
	return true;
}