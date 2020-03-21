#pragma warning(disable : 4996)


#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "GraphMethod.h"

class Manager
{
private:
	Graph* graph;
	ofstream fout;
	int load;
	int d_size;

public:
	Manager();
	~Manager();

	void	run(const char * command_txt);
	
	bool	LOAD(char* filename);
	bool	PRINT();
	
	bool	mDijkstra(int from, ofstream *fout);
	bool	mKruskal(ofstream *fout);
	bool	mBFS(int ver, ofstream *fout);
	bool	mDFS(int ver, ofstream *fout);
	bool	mDFS_R(int ver, ofstream *fout);
	void	printErrorCode(int n);	
};

#endif