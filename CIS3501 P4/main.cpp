//Program Name: main.cpp
//Programmer Name: Anthony Vettraino
//Description: Main program to test MST and Shortest Path
//Date Created: 8/3/2021

#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "Graph.h"

using namespace std;


//Description: Main program to run MST Test Program
//Pre-condition: .out and .dat files are created
//Post-condition: Displays graph information and MST information to user and output file
int main()
{
	string outFile;
	ofstream outputFile;
	ifstream existingFile;
	cout << "Welcome to the MST and Shortest Path Test Program" << endl;
	cout << "Enter output file name: ";
	cin >> outFile;
	
	existingFile.open(outFile);
	
	//check to see if file is open
	if(!existingFile)
	{
		cout << "file " << outFile << " cannot be opened - program terminated";
		return 0;
	}
	else
	{
		existingFile.close();
		outputFile.open(outFile);
	}

	outputFile << "Output file: " << outFile << endl;
	outputFile << "Testing Default Scenario" << endl;
	cout << "Testing Default Scenario" << endl;

	//default test graph
	Graph graph1;
	graph1.primMST(outputFile);
	graph1.printMST(outputFile);

	cout << "Testing File Data" << endl;
	outputFile << "Testing File Data" << endl;
	cout << "Enter file name for graph data: ";

	ifstream dataFile;
	string dataFileInput;
	cin >> dataFileInput;

	outputFile << "File name for graph data: " << dataFileInput << endl;

	string line;
	dataFile.open(dataFileInput);

	//check to see if file is open or not
	if(!dataFile)
	{
		cout << "File " << dataFileInput << " cannot be opened or does not exist - program terminated" << endl;
		outputFile << "File " << dataFileInput << " cannot be opened or does not exist - program terminated" << endl;
		return 0;
	}
	else if (dataFile.peek() == ifstream::traits_type::eof())	//check to see if the file is empty
	{
		cout << "File " << dataFileInput << " contains not data - program terminated" << endl;
		outputFile << "File " << dataFileInput << " contains not data - program terminated" << endl;
		return 0;
	}
	else
	{
		while (!dataFile.eof()) {

			getline(dataFile, line);
			if (line == "")
				continue;
			stringstream stream(line);
			int vertices;
			int edges;
			stream >> vertices;
			stream >> edges;

			if (vertices < 0)
			{
				do
				{
					getline(dataFile, line);
				} while (line != "");
				cout << "ERROR: number of vertices: " << vertices << " is less than zero" << endl;
				cout << "Empty Graph Will Be Created" << endl;
				Graph graph(0);
				graph.primMST(outputFile);
				
			}
			else if (vertices == 0)
			{
				do
				{
					getline(dataFile, line);
				} while (line != "");
				cout << "Number of vertices: " << vertices << " is equal to zero" << endl;
				cout << "Empty Graph Will Be Created" << endl;
				Graph graph(0);
				graph.primMST(outputFile);
			}
			else if (edges < 0)
			{
				cout << "ERROR: number of edges: " << edges << " is less than zero" << endl;
				cout << "Empty Graph Will Be Created" << endl;
				Graph graph(0);
				graph.primMST(outputFile);

				do
				{
					getline(dataFile, line);
				} while (line != "");
			}
			else
			{
				cout << "Number of vertices: " << vertices << " is valid" << endl;

				cout << "Graph with " << vertices << " vertices and " << edges << " edges will be created" << endl;
				outputFile << "Graph with " << vertices << " vertices and " << edges << " edges will be created" << endl;

				Graph graph(vertices);

				cout << "Number of edges to process is: " << edges << endl << endl;
				outputFile << "Number of edges to process is: " << edges << endl << endl;;

				vector<pair<int, int>> addedEdges;

				for (int i = 0; i < edges; i++)
				{
					int src, dest, weight;
					getline(dataFile, line);
					if (line == "")	//check to see if graph has listed edges
					{
						cout << "Error - No listed edges" << endl;
						outputFile << "Error - No listed edges" << endl;
						return 0;
					}
					else
					{
						stringstream streamNext(line);

						streamNext >> src;
						streamNext >> dest;
						streamNext >> weight;

						//check for repeated edges
						bool repeat = false;
						for (int i = 0; i < addedEdges.size(); i++)
						{
							if (addedEdges[i] == make_pair(src, dest) || addedEdges[i] == make_pair(dest, src))
								repeat = true;
						}
						if (src < 0 || dest < 0 || weight <= 0)
						{
							graph.addEdge(src, dest, weight, outputFile);
						}
						else if (!repeat)
						{
							graph.addEdge(src, dest, weight, outputFile);
							addedEdges.push_back(make_pair(src, dest));
							addedEdges.push_back(make_pair(dest, src));
						}
						else
						{
							cout << "Error - Edge: (" << src << " , " << dest << ") already exists!" << endl;
							outputFile << "Error - Edge: (" << src << " , " << dest << ") already exists!" << endl;
							repeat = false;
						}
					}
				}
				addedEdges.clear();
				if (graph.isGraphConnected() == false) //graph is disconnected so make the subgraphs
				{
					graph.printGraph(outputFile);
					graph.connectedParts(outputFile);
				}
				else
				{
					graph.printGraph(outputFile);
					graph.primMST(outputFile);
					graph.printMST(outputFile);
				}

				int selection{};

				do
				{
					// intial start vertex to create shortest path
					cout << "Please select a starting vertex from 0 - " << vertices - 1 << " to create a shortest path: ";
					cin >> selection;
					if (!cin || selection < 0 || selection >= vertices)
					{
						cout << "Error - not a valid vertex" << endl;

					}
					else
					{
						cin.clear();
						cin.ignore();
						fflush(stdin);
						graph.dijkstras(selection, outputFile);
					}
				} while (!cin || selection < 0 || selection >= vertices);

				graph.~Graph();
			}

		}
	}
	//display thank you message
	cout << "Thank you for running the MST and Shortest Path Test Program written by Anthony Vettraino!" << endl;
	outputFile << "Thank you for running the MST and Shortest Path Test Program written by Anthony Vettraino!" << endl;

	outputFile.close(); //close outputFile
	dataFile.close();	//close dataFile


	return 0;
}