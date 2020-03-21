#include "ListGraph.h"

ListGraph::ListGraph(bool type, bool directed, bool weighted, int size) : Graph(type, directed, weighted, size)//Initialize the constructor
{		
	m_List = new map < int, int >[m_Size];//  dynamic allocation 
}

ListGraph::~ListGraph()//Destructor
{
		m_List->clear();
		delete[]m_List;
}

void ListGraph::getIncidentEdges(int vertex, map<int, int>* m)//get adjacent edges
{
	//vertex = m->begin()->first;
	map<int, int>::iterator it;
	for (it = m_List[vertex].begin(); it != m_List[vertex].end(); it++)//insert to edges in map of vertex
		m->insert(make_pair(it->first,it->second));
}

void ListGraph::insertEdge(int from, int to, int weight) //Insert to Edge in ListGraph
{
	m_List[from].insert(make_pair(to, weight));
}

bool	ListGraph::printGraph(ofstream *fout)
{
	if (m_List == NULL)// if m_List is empty 
		return false;//it is false

	map < int, int > ::iterator it;

	*fout << "=========PRINT==========" << endl;
	for (int i = 0; i < m_Size; i++) {
		*fout << i << "   ";
		for (it = m_List[i].begin(); it != m_List[i].end(); it++) {
			*fout << it->first << "," << it->second<<"   ";//print all
		}*fout << endl;
	}
	*fout << "========================" << endl;
	return true;
}