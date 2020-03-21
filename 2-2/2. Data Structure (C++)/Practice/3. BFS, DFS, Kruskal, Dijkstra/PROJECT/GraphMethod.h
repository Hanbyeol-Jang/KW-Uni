#ifndef _GRAPHMETHOD_H_
#define _GRAPHMETHOD_H_

#include "ListGraph.h"
#include "MatrixGraph.h"
#include "vertexSet.h"

bool BFS(Graph* graph, int vertex, ofstream *fout);
bool DFS(Graph* graph, int vertex, ofstream *fout);
bool DFS_R(Graph* graph, vector<bool>* visit, int vertex, ofstream *fout, queue<int> *print_q);
bool Kruskal(Graph* graph, ofstream *fout);
bool Dijkstra(Graph* graph, int vertex, ofstream *fout);
void B_D_PRINT(Graph* graph, char*name, queue<int> print_q, ofstream *fout);
void Krus_PRINT(Graph* graph, int weight, int total, int count, ofstream *fout, multiset <int> *krus);
void Dijkstra_print(int from, int visit, int p_visit, int arrive, int weight, int count, ofstream *fout,queue<int>* print_qq,int *print_title);//Dijkstra_print
#endif