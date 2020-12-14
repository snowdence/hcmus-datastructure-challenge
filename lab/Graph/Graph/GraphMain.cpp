#include <iostream>
#include "Graph.h"

int main()
{
	Graph graph;
	/*graph.readAdjFromFile("graph2.txt");
	graph.printAdjList();
	graph.printAdjMatrix();*/
	graph.readMatrixFromFile("graph1.txt");

	graph.printAdjList();
	graph.printAdjMatrix(); 
}
