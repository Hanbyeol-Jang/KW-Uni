#include "MatrixGraph.h"		


MatrixGraph::MatrixGraph(bool type, bool directed, bool weighted, int size) : Graph(type, directed, weighted, size)//Initialize the constructor
{
	//2 dimensional arrangement dynamic allocation
	m_Mat = new int*[size];
	for (int i = 0; i < size; i++)
	{
		m_Mat[i] = new int[size];
		memset(m_Mat[i], 0, sizeof(int)*size);////Initialize the 2 dimensional arrangement 
	}
}

MatrixGraph::~MatrixGraph()//Destructor
{
	for (int i = 0; i < m_Size; ++i) {// delete dynamic allocation of two dimensional arrays
		delete[] m_Mat[i];
	}
	delete[] m_Mat;
}

void MatrixGraph::getIncidentEdges(int vertex, map<int, int>* m)//get adjacent edges
{	
	for (int i = 0; i < m_Size; i++) {    ////insert to edges in map of vertex
		if (m_Mat[vertex][i] != 0)
			m->insert(make_pair(i, m_Mat[vertex][i]));
	}
}

void MatrixGraph::insertEdge(int from, int to, int weight)//Insert to Edge in MatrixGraph
{
	m_Mat[from][to] = weight;
	//m_Mat[to][from] = weight;
}

bool	MatrixGraph::printGraph(ofstream *fout)
{
	if (m_Mat == NULL) return false; //error

	*fout << "=========PRINT==========" << endl;

	for (int i = 0; i < m_Size; i++) {
		for (int j = 0; j < m_Size; j++) {//print all
			*fout << m_Mat[i][j] << "  ";
		}*fout << endl;
	}

	*fout << "========================" << endl;
	return true;
}
