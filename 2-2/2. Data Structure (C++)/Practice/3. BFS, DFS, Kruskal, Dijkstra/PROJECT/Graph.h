#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <iostream>
#include <cstring>
#include <string.h>
#include <fstream>
#include <map>
#include <set>
#include <math.h>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <stack>

using namespace std;

#define MAX 999999

class Graph{
protected:
	bool	m_Type;//0:List 1:Matrix
	bool	m_Directed;//0:undirected 1:directed
	bool	m_Weighted;//0:unweighted 1:weighted;
	int	m_Size;

public:
	Graph(bool type, bool directed, bool weighted, int size);
	virtual~Graph();

	bool getDirected();
	bool getWeighted();
	int	getSize();
	
	virtual void getIncidentEdges(int vertex, map<int, int>* m) = 0;
	virtual void	insertEdge(int from, int to, int weight) = 0;
	virtual	bool	printGraph(ofstream *fout) = 0;
};

#endif