#ifndef _LIST_H_
#define _LIST_H_

#include "Graph.h"

class ListGraph : public Graph
{
private:
	map < int, int >* m_List;

public:	
	ListGraph(bool type, bool directed, bool weighted, int size);
	~ListGraph();
		
	void getIncidentEdges(int vertex, map<int, int>* m);
	void	insertEdge(int from, int to, int weight);
	bool	printGraph(ofstream *fout);

};

#endif