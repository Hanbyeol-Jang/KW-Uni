#include "Manager.h"

Manager::Manager()//Initialize the constructor
{
	fout.open("log.txt", ios::app);//file open to log.txt
	load = 0;
	graph = NULL;
}

Manager::~Manager()//Destructor
{
	delete graph;
	fout.close();//file close
}

void Manager::run(const char* command_txt)
{
	ifstream fin;		fin.open(command_txt);
		
	if(!fin)//If the file does not open
	{
		cout<<"[ERROR] command file open error!"<<endl;
		return;
	}
	
	char*	str=NULL;
	char*	str2=NULL;
	char	buf[128]={0};

	while(fin.getline(buf, 64))//Read one line in file
	{
		str=strtok(buf, " \t\n");	
		
		if (strcmp(str, "LOAD") == 0)//LOAD
		{
			if ((str = strtok(NULL, " \t\n")) == NULL)
				printErrorCode(100);//ERROR CODE

			if (load == 1)
			{
				printErrorCode(100);//If the function has already been called
			}
			else if ((str2 = strtok(NULL, " \t\n")) != NULL || !LOAD(str))//If there is one more parameter
			{//and LOAD function call
				printErrorCode(100);
			}
			else {
				load = 1;
				fout << "======== LOAD ========" << endl;
				fout << "Success" << endl;
				fout << "=======================" << endl;
			}
		}
		///////////////////////////////////////////PRINT///////////////////////////////////////////////////////////////
		else if (strcmp(str, "PRINT") == 0)//PRINT
		{
			if (load != 1)
				printErrorCode(200);//ERROR CODE

			else if ((str2 = strtok(NULL, " \t\n")) != NULL || !PRINT())//If there is one more parameter
			{//and PRINT function call
				printErrorCode(200);
			}
		}
		//////////////////////////////////////////BFS////////////////////////////////////////////////////////////////
		else if (strcmp(str, "BFS") == 0)//BFS
		{
			str2 = strtok(NULL, " \t\n");
			if(str2 == NULL)
				printErrorCode(300);

			else {
				int	ver = atoi(str2);
				if (load != 1)
					printErrorCode(300);//ERROR CODE
				else if ((str2 = strtok(NULL, " \t\n")) != NULL || !mBFS(ver,&fout))//If there is one more parameter
				{//and BFS function call
					printErrorCode(300);
				}
			}
		}
		//////////////////////////////////////////DFS////////////////////////////////////////////////////////////////
		else if (strcmp(str, "DFS") == 0)//DFS
		{
			str2 = strtok(NULL, " \t\n");
			if(str2 == NULL)
				printErrorCode(400);

			else{
				int ver = atoi(str2);
				if (load != 1)
					printErrorCode(400);//ERROR CODE
				else if ((str2 = strtok(NULL, " \t\n")) != NULL || !mDFS(ver, &fout))//If there is one more parameter
				{//and DFS function call
					printErrorCode(400);
				}
			}
		}
		//////////////////////////////////////////DFS_R////////////////////////////////////////////////////////////////
		else if (strcmp(str, "DFS_R") == 0)//DFS_R
		{
			str2 = strtok(NULL, " \t\n");
			if (str2 == NULL)
				printErrorCode(500);

			else{
				int ver = atoi(str2);

				if (load != 1)
					printErrorCode(500);//ERROR CODE

				else if ((str2 = strtok(NULL, " \t\n")) != NULL || !mDFS_R(ver, &fout))//If there is one more parameter
				{//and DFS_R function call
					printErrorCode(500);
				}
			}
		}
		//////////////////////////////////////////Kruskal////////////////////////////////////////////////////////////////
		else if (strcmp(str, "Kruskal") == 0)//Kruskal
		{
			if (load != 1)
				printErrorCode(600);//ERROR CODE

			else if ((str2 = strtok(NULL, " \t\n")) != NULL || !mKruskal(&fout))//If there is one more parameter
			{//and Kruskal function call
				printErrorCode(600);
			}
		}
		//////////////////////////////////////////Dijkstra////////////////////////////////////////////////////////////////
		else if (strcmp(str, "Dijkstra") == 0)//Dijkstra
		{
			str2 = strtok(NULL, " \t\n");
			int from = atoi(str2);

			if (load != 1)
				printErrorCode(700);//ERROR CODE

			else if ((str2 = strtok(NULL, " \t\n")) != NULL || !mDijkstra(from, &fout))//If there is one more parameter
			{//and Dijkstra function call
				printErrorCode(700);
			}
		}
		else if (strcmp(str, "EXIT") == 0)//EXIT
		{
			break;
		}
		
		///////////////////////////////////////////////////////////////////////////////////////////////////////////////
		else
			continue;

		fout<<endl;
	}	
	fin.close();
}

bool Manager::LOAD(char* filename)//LOAD
{
	char*	str=NULL;
	char*	str2=NULL;
	char	buf[128]={0};
	char	buf2[128]={0};

	ifstream fin;
	fin.open(filename);//file open 
	
	if(!fin){return false;} // if file is not open

	char* weighted = NULL;
	char* size = NULL;
	char* err = NULL;

	fin.getline(buf, 64);//Read one line in file
	str = strtok(buf, " \t\n");
	str2 = strtok(NULL, " \t\n");
	weighted = strtok(NULL, " \t\n");
	
	bool dir;//Directionality in graph
	if (strcmp(str2, "0") == 0)	dir = 0;
	else dir = 1;

	bool wei;//Weighted graphs?
	if (strcmp(weighted, "0") == 0)	wei = 0;
	else wei = 1;

	err = strtok(NULL, " \t\n");

	fin.getline(buf2, 64);
	size = strtok(buf2, " \t\n");

	int from, to, weight,count=0;
	
	if (str == NULL || str2 == NULL || weighted == NULL || size == NULL || err != NULL)//If list information is insufficient or overflow
		return false;

	if (strcmp(str, "L") == 0){//graph type is LIST
		graph = new ListGraph(0,dir,wei,atoi(size));///////New graph dynamic allocation
		d_size = atoi(size);
		int l_count = 0;
		while (fin.getline(buf, 64)) {//Read one line in file
			str = NULL; str2 = NULL; 
			str = strtok(buf, " \t\n");
			str2 = strtok(NULL, " \t\n");
			if (l_count == 0 && str2 != NULL) {//When the graph format is wrong
				return false;
			}
			l_count++;
			if (count > d_size) // size over
				return false;
			if (str == NULL)
				break;
			if (str2 == NULL) {// start vertex
				from = atoi(str);
				count++;
			} 			
			else {//to, weight
				to = atoi(str);
				weight = atoi(str2);
				graph->insertEdge(from, to, weight);
			}
		}
		if (count != 0) { //size to small
			if (count < d_size)
				return false;
			}
	}
	else if (strcmp(str, "M") == 0){//graph type is MATRIX
		graph = new MatrixGraph(1,dir,wei, atoi (size));///////New graph dynamic allocation
		d_size = atoi(size);
		str = NULL; str2 = NULL;
		for (int i = 0; i < atoi(size); i++) 
		{
			fin.getline(buf, 64); //Read one line in file
			str = strtok(buf, " \t\n");//first
			if(str == NULL)// //  // Graph size is different
				return false;
			int j = 1;
			graph->insertEdge(i, 0, atoi(str));
			while(j<d_size) {
				str2 = strtok(NULL, " \t\n");//from second to size
				if (str2 == NULL) // Graph size is different(TO SMALL)
					return false;
				graph->insertEdge(i, j, atoi(str2));//insert	
				j++;
			}
			str2 = strtok(NULL, " \t\n");//from second to size
			if (str2 != NULL) // Graph size is different(TO MANY)
				return false;
		}
		fin.getline(buf, 64); //Read one line in file
		str = strtok(buf, " \t\n");//first
		if (str != NULL)// //  // Graph size is different(TO MANY)
			return false;
	}
	else { return false; }

	return true;
}

bool	 Manager::PRINT() { // PRINT
	bool t_f = 0;
	t_f =  graph->printGraph(&fout);
	return t_f;
}

bool	 Manager::mDFS_R(int ver, ofstream *fout) { //Rrcursive
	if (graph->getSize() < ver || graph->getDirected() || graph->getWeighted())
		return false;
	//vector<bool> visit(d_size,0); //vetor initinalize
	queue<int> *print_q = new queue<int>;
	vector<bool> *visit = new vector<bool>;
	visit->resize(graph->getSize());
	bool t_f = DFS_R(graph, visit, ver, fout, print_q);  //call DFS_R
	B_D_PRINT(graph, "DFS_R", *print_q, fout);//Recursive
	delete visit;
	delete print_q;
	return t_f;
}
bool	 Manager::mDijkstra(int from, ofstream *fout) {
	
	return Dijkstra(graph, from, fout);

}
bool	 Manager::mKruskal(ofstream *fout) {
	return  Kruskal(graph, fout);

}
bool	 Manager::mBFS(int ver, ofstream *fout) {
	return BFS(graph, ver, fout);

}
bool	 Manager::mDFS(int ver, ofstream *fout) {
	return  DFS(graph, ver, fout);
}

void Manager::printErrorCode(int n)
{
	fout<<"======== ERROR ========"<<endl;
	fout<<n<<endl;
	fout<<"======================="<<endl;
}