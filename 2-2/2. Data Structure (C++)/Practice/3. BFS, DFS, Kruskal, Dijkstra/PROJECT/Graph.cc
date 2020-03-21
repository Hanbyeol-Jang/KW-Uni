#include "Graph.h"

Graph::Graph(bool type, bool directed, bool weighted, int size)//Initialize the constructor
{
	m_Type = type;
	m_Directed = directed;
	m_Weighted = weighted;
	m_Size = size;
}

Graph::~Graph()//virtual
{}

bool Graph::getDirected() //0:undirected 1:directed
{
	return m_Directed;
}
bool Graph::getWeighted()//0:unweighted 1:weighted;
{
	return m_Weighted;
}

int Graph::getSize()//List Size
{
	return m_Size;
}