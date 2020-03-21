#include "GraphMethod.h"

bool BFS(Graph* graph, int baseV, ofstream *fout)//Breadth-first Search using queue
{
	if (graph == NULL || graph->getSize() < baseV || graph->getDirected() || graph->getWeighted())//If the graph is empty
		return false;

	queue<int> print_q;
	int g_Size = graph->getSize() ;
	bool* visited = new bool[g_Size];//Create arrays as large as the graph
	for (int i = 0; i < g_Size; i++) {
		visited[i] = false;//Initialized to false
	}

	queue<int> q;
	q.push(baseV);//insert the queue
	visited[baseV] = true;
	print_q.push(baseV);//print

	map <int, int> *m = new map <int, int>;//new map<int, int>;//make a new map
	while (!q.empty()) {//Until queue is empty
		baseV = q.front();
		q.pop();

		//If it finds adjacent vertices and is not empty, push
		graph->getIncidentEdges(baseV, m);//get adjacent vertice in m

		map<int, int>::iterator it;
		for (it = m->begin(); it != m->end(); it++) {
			if (visited[it->first] == false) {// Of adjacent vertices is false that queue push
				q.push(it->first);
				visited[it->first] = true;//mark
				print_q.push(it->first);//print
			}
		}
	}	
	B_D_PRINT(graph, "BFS", print_q, fout);//print
	delete m;
	delete[] visited;//deallocate memory
	return true;
}

bool DFS(Graph* graph, int baseV, ofstream *fout)// Implemented using stack
{
	if (graph == NULL || graph->getSize() < baseV || graph->getDirected() || graph->getWeighted())//If the graph is empty
		return false;

	//int current;
	int g_Size = graph->getSize();
	bool* visited = new bool[g_Size];//Create arrays as large as the graph
	for (int i = 0; i < g_Size; i++) {
		visited[i] = false;//Initialized to false
	}
	queue<int> print_q;
	stack<int> s;//make a stack
	s.push(baseV);
	//visited[baseV] = true;

	//If it finds adjacent vertices and is not empty, push
	map <int, int> *m = new map <int, int>;//new map<int, int>;//make a new map
	graph->getIncidentEdges(baseV, m);//get adjacent vertice in m
	map<int, int>::iterator it;

	while (!s.empty()) {
		if (visited[baseV] == false) {
			visited[baseV] = true;//mark
			print_q.push(baseV);//print
		}
		m->clear();
		graph->getIncidentEdges(baseV, m);//get adjacent vertice in m
		for (it = m->begin(); it != m->end(); it++){
			if (visited[it->first] == false)
				break;
		}
		if (it == m->end()) {
			s.pop();
			if(!s.empty())
				baseV = s.top();
		}
		else {
			s.push(it->first);	//push the stack
			baseV = it->first;
		}
	}
	B_D_PRINT(graph, "DFS", print_q, fout);//print

	delete m;
	delete[] visited;//deallocate memory
	return true;
}

bool DFS_R(Graph* graph, vector<bool>* visit, int baseV, ofstream *fout, queue<int> *print_q)//Recursive
{
	visit[0][baseV] = true;
	print_q->push(baseV);
	//If it finds adjacent vertices and is not empty, push
	map <int, int> *m = new map <int, int>;//new map<int, int>;//make a new map
	graph->getIncidentEdges(baseV, m);//get adjacent vertice in m
	map<int, int>::iterator it;

	for (it = m->begin(); it != m->end(); it++) {
		if (visit[0][it->first] == false) {// Of adjacent vertices is false that vector push
			DFS_R(graph, visit, it->first, fout, print_q);//Recursive
		}
	}
	delete m;
	return true;
}

bool Kruskal(Graph* graph, ofstream *fout)
{
	if (graph->getDirected() == 1 || graph->getWeighted() == 0)
		return false;

	multimap<int, pair<int, int> > weight_edges;  //Construct a map with weight as key
	pair<int, int> edges;
	int weight,count = 0; //count is number of edge
	int total_weight = 0;
	map<int, int>* m = new map<int,int>;
	multimap<int, int>::iterator it;
	multimap<int, pair<int, int> > ::iterator w_it;
	multiset <int> *krus = new multiset<int>;
	vertexSet s(graph->getSize());

	for (int i = 0; i < graph->getSize(); i++) {//Get list from graph
		m->clear();
		graph->getIncidentEdges(i, m);
		for (it = m->begin(); it != m->end(); it++)
		{
			if (i < it->first) {
				edges = make_pair(i, it->first);//(vertex - vertex)
				weight = it->second;//weight
				weight_edges.insert(make_pair(weight, edges));
			}
		}
	}

	w_it = weight_edges.begin();
	while (count + 1 != graph->getSize() && w_it != weight_edges.end()) {//Condition of spanning tree
		if (s.Find(w_it->second.first) != s.Find(w_it->second.second)) {
			s.Union(w_it->second.first, w_it->second.second);//merge
															 //graph->insertEdge(w_it->second.first, w_it->second.second, w_it->first);//insert to graph
			total_weight += w_it->first;//////////////total weight for print
			count++;
			Krus_PRINT(graph, w_it->first, total_weight, count,fout,krus);
		}
		w_it++;
	}

	delete m;
	delete krus;
	if (graph->getSize() - 1 != count)////Condition of spanning tree
		return false;
	return true;
}

bool Dijkstra(Graph* graph, int baseV, ofstream *fout){//Dijkstra
	if (graph->getDirected() == 0 || graph->getWeighted() == 0 || graph->getSize() <= baseV)//Condition of Dijkstra
		return false;

	int Di_finish = baseV;
	int size = graph->getSize();//SIZE
	int count = 0;
	int *dist = new int[size];//distance
	bool *visit = new bool[size];//visit record
	int *path = new int[size];//prev vertex
	int print_title =0;

	queue<int> *print_qq = new queue<int>;

	map<int, int> *m = new map<int,int>;//start vertex -> < last vertex,weight>
	multimap<int, int> weight_key;
	multimap<int, int> min_key;
	multimap<int, int>::iterator it;

	for (int i = 0; i < size; i++) {//initialize
		visit[i] = 0; path[i] = -1; dist[i] = MAX;
	}

	dist[baseV] = 0;//start vertex
	int prev;
	
	while (1) {
		m->clear();
		graph->getIncidentEdges(baseV, m);//get incident edges

		weight_key.clear();
		for (it = m->begin(); it != m->end(); it++) {
			int ver = it->first;
			int weight = it->second;		//<weight,vertex>
			weight_key.insert(make_pair(weight, ver));
		}
		prev = baseV;
		for (it = weight_key.begin(); it != weight_key.end(); it++) {
			if (dist[baseV] + it->first < dist[it->second]) {
				path[it->second] = prev;
				dist[it->second] = dist[path[it->second]]+it->first;
			}
			if (visit[baseV] == 0 && it == weight_key.begin()) {//first visit
				visit[baseV] = true;//change visit array
				count++;
			}
		}
		if (weight_key.empty()) {//last vertex
			visit[baseV] = true;
			break;
		}
		////Select the closest vertex that have not visited yet
		else {
			map<int, int> min;
			for (int i = 0; i < graph->getSize(); i++) {
				if (visit[i] == 0) {
					min.insert(make_pair(dist[i], i));
				}
			}
			it = min.begin();
			if (it == min.end())
				break;
			baseV = it->second;
		}//it is have minimum distance 
	}
	////////////////////find Shortest distance/////////////////////////////
	int d_weight;
	for (int i = 0; i < graph->getSize(); i++) {
		if (i != Di_finish && visit[i] == true)
		{
			baseV = i;
			d_weight = dist[baseV];
			int dig_path = path[baseV];
			while (path[baseV] != Di_finish) {
				Dijkstra_print(i,baseV, dig_path, Di_finish, d_weight,graph->getSize(),fout, print_qq, &print_title);
				baseV = path[baseV];
			}
			Dijkstra_print(i, baseV, Di_finish, Di_finish,d_weight, graph->getSize(), fout,print_qq,& print_title);
		}
		else if (i == Di_finish);
		else
			Dijkstra_print(i, i, -1, Di_finish, -2, -1, fout, print_qq,& print_title); //Failure to visit
	}
	delete m;//delete
	delete[]visit;
	delete[]path;
	delete[]dist;
	delete print_qq;
	return true;
}

void B_D_PRINT(Graph* graph,char* name,queue<int> print_q, ofstream *fout) //BFS,DFS PRINT
{
	*fout << "========="<<name<<"========="<< endl;
	while (!print_q.empty()) {
		int print = print_q.front();
		print_q.pop();
		*fout << print << "  ";
	}
	*fout << endl;
	*fout << "=====================" << endl;
}

void Krus_PRINT(Graph* graph, int weight,int total,int count, ofstream *fout, multiset <int> *krus)
{
	krus->insert(weight);

	if (graph->getSize() == count + 1)
	{
		*fout << "=======KrusKal=======" << endl;////////////kruskal print
		multiset <int>::iterator it;
		for (it = krus->begin(); it != krus->end(); it++) {
			*fout << *it << "   ";
		}*fout << endl;
		*fout <<total<<endl;
		*fout << "=====================" << endl;
	}
	
}
void Dijkstra_print(int from, int visit,int p_visit, int arrive, int weight,int count, ofstream *fout,queue<int>* print_qq,int *print_title)//Dijkstra_print
{
	if (p_visit != arrive && from != visit) {
		print_qq->push(visit);
	}
	if(p_visit == arrive){
		if (*print_title == 0) {
			*fout << "=======Dijkstra=======" << endl;////////////Dijkstra print
			*fout <<" "<< arrive << endl; //arrive
			*print_title = 1;
		}
		*fout << "[" << from << "] "; //start
		while (!print_qq->empty()) {
			int print = print_qq->front();
			print_qq->pop();
			*fout << print << " ";
		}
		if (from != visit) *fout << visit << " ";
		*fout << arrive << "   ";
		*fout << "(" << weight << ")" << endl; //total weight

		if (from == count - 1) {
			*fout << "=========================" << endl;
		}
		else if (arrive == 7 && from + 1 == count) {
			*fout << "=========================" << endl;
			*print_title = 2;
		}
	}/////////////////////////error print 'x'
	if (weight == -2)
	{
		if (*print_title != 1) {
			*fout << "=======Dijkstra=======" << endl;////////////Dijkstra print
			*fout << " " << arrive << endl; //arrive
			*print_title = 1;
		}
		*fout << "[" << from << "] "; //start
		*fout << "x" << endl; //arrive
		if ((*print_title == 1) && (from == count - 1 || (arrive == 7 && from + 1 == count)))
		{
			*fout << "=========================" << endl;
		}
	}

}




