#include "BpTree.h"

bool BpTree::Insert(Characterdata* new_Character)	// function for INSERT into B+ Tree
{

	string key = new_Character->getname();		// key
	Characterdata* value = new_Character;		// value
	map<string, Characterdata*> mapData;		// map <key,value>

	mapData.insert(make_pair(new_Character->getname(), new_Character));	// insert into mapdata

	if (root == NULL)			// if root don't exist
	{ 
		BpTreeNode* pDataNode = new BpTreeDataNode;	// make new data node		
		pDataNode->insertDataMap(key, value);	// insert data
		root = pDataNode;
		return true;
	}

	BpTreeNode* pDataNode = searchDataNode(key);	// search data node with key

	map<string, Characterdata*> *m = pDataNode->getDataMap();
	if (m->find(key) == m->end())	// if any element don't have same key with Character's key 
	{
		m->insert(map<string, Characterdata*>::value_type(key, value)); // Map get new element
		if (exceedDataNode(pDataNode) == 1) // if size of map is bigger than order - 1
			splitDataNode(pDataNode);	// call splitDataNode function
	}
	else  // if a element which is in the pDataNode Map have same key with Character's key
	{
		m->find(key)->second->setpickinc();		// increase Cpick
		if (new_Character->getwin() == 1)		// check Winner
			m->find(key)->second->setwininc();  // increase Cwin
	}

	return true;
}

BpTreeNode * BpTree::searchDataNode(string n)
{
	BpTreeNode* pCur = root;
	map<string, BpTreeNode*>::iterator itIndex;

	// 'pCur->getMostLeftChild == NULL' mean if pCur is DataNode, Come out from while function
	while (pCur->getMostLeftChild() != NULL)
	{
		itIndex = pCur->getIndexMap()->begin();  //  itIndex get IndexNode's Map

		if (n < itIndex->first)	//  if Character's name is lower than n 
			pCur = pCur->getMostLeftChild();  // pCur get MostLeftChild

		else
		{					//  if Character's name is bigger than n 
			while (true)
			{
				itIndex++;  //  itIndex get next element
				if (itIndex == pCur->getIndexMap()->end() || n < itIndex->first)
				{  // if element is end or lower than n
					itIndex--; // itindex get previous element
					pCur = itIndex->second; // pCur get child of Node which pointed by element's second value
					break;
				}
			}
		}
	}

	return pCur;
}

void BpTree::splitDataNode(BpTreeNode* pDataNode)
{

	int splitPosition_data = ceil((order - 1) / 2.0) + 1; // this variable define divide point

	map<string, Characterdata*>::iterator mostleftData;  //	this variable symbolizes first element in Map
	map<string, Characterdata*>::iterator centerData;    //  this variable symbolizes divide point element ( center element )
	map<string, Characterdata*>::iterator centerData2;   //  get centerData
	mostleftData = pDataNode->getDataMap()->begin();      // mostleftData get Map from pDataNode

	for (int i = 1; i < order; i++) // this for function will find divide point and give that element to centerData
	{
		mostleftData++;
		if (i == splitPosition_data - 1) // if i is same with divide point
		{
			centerData = mostleftData;   // centerData get element
		}
	}
	centerData2 = centerData;
	//	When order is change, number of element will change. So divide point is very important.
	BpTreeNode * NewDataNode = new BpTreeDataNode();  //  create NewDataNode to divide Map
	int d = 0;

	while (1)	// NewDataNode get element that Character's name is bigger or same with centerData
	{
		NewDataNode->insertDataMap(centerData->first, centerData->second); // NewDataNode's Map receive element
		d++;
		if (d > order - splitPosition_data) // this if function pick element that Character's name is bigger or same with centerData
			break;
		centerData++;
	}

	centerData = centerData2; // Reorganization of centerData
	d = 0;  // reset d

	while (1)  // delete divided part from pDataNode's Map
	{
		pDataNode->deleteMap(mostleftData--->first);
		d++;
		if (d > order - splitPosition_data)// this if function pick element that Character's name is bigger or same with centerData
			break;
	}

	// under this line, reorganizate link of DataNodes
	NewDataNode->setNext(pDataNode->getNext());
	if (pDataNode->getNext() != NULL)
		pDataNode->getNext()->setPrev(NewDataNode);
	pDataNode->setNext(NewDataNode);
	NewDataNode->setPrev(pDataNode);

	if (pDataNode->getParent() == NULL) // if there is no ParentNode
	{
		BpTreeNode * parentNode = new BpTreeIndexNode(); // make indexNode that node is going to be parentNode
		parentNode->insertIndexMap(NewDataNode->getDataMap()->begin()->first, NewDataNode);  //  parentNode get element
		parentNode->setMostLeftChild(pDataNode);  //  pDataNode become mostLeftChild of parentNode
		pDataNode->setParent(parentNode);         //  pDataNode set Parent
		NewDataNode->setParent(parentNode);       //  NewDataNode set Parent
		root = parentNode;                        //  parentNode become root Node
	}
	else  // if ParentNode exist
	{
		NewDataNode->setParent(pDataNode->getParent());  // NewDataNode set Parent
		pDataNode->getParent()->insertIndexMap(NewDataNode->getDataMap()->begin()->first, NewDataNode); // parentNode get element
																				// if size of IndexNode's Map is bigger than order - 1 
		if (exceedIndexNode(pDataNode->getParent()) == 1)
		{
			splitIndexNode(pDataNode->getParent());  //  call splitIndexNode function
		}
	}
	return;
}

void BpTree::splitIndexNode(BpTreeNode* pIndexNode)
{

	int splitPosition_index = ceil(order / 2.0); // this variable define divide point

	BpTreeNode * NewIndexNode = new BpTreeIndexNode(); // creat NewindexNode to receive element
	map <string, BpTreeNode*>::iterator mostleftindex; //  this variable symbolizes first element in Map
	map <string, BpTreeNode*>::iterator centerindex;   //  this variable symbolizes divide point element ( center element )
	mostleftindex = pIndexNode->getIndexMap()->begin(); // mostleftindex get Map's first element

	for (int i = 0; i < order; i++) // centerindex get divide point element and NewIndexNode get element after centerindex 
	{
		if (i + 1 >= splitPosition_index)
		{
			if (i + 1 == splitPosition_index) centerindex = mostleftindex;  //  centerindex get divide point element
			else NewIndexNode->insertIndexMap(mostleftindex->first, mostleftindex->second);  //  NewIndexNode get element after centerIndex
		}

		mostleftindex++;
	}

	//  centerindex's child become MostLeftChild of NewIndexNode, and set Parent
	NewIndexNode->setMostLeftChild(centerindex->second);
	centerindex->second->setParent(NewIndexNode);

	for (int i = 0; i <= order - splitPosition_index; i++)  //  before divide, every childNode of IndexNode need to pick ParentNode After divide
	{
		if (i == 0) NewIndexNode->getIndexMap()->begin()++; // NewIndexNode's first element is centerindex, so avoid even
		else NewIndexNode->getIndexMap()->begin()++->second->setParent(NewIndexNode);  //  After centerindex element, every child of NewIndexNode connect thier parent
	}

	//delete NewIndexNode's element from existing node
	for (int i = 0; i < order - splitPosition_index; i++)
	{
		pIndexNode->deleteMap(NewIndexNode->getIndexMap()->begin()++->first);
	}


	if (pIndexNode->getParent() == NULL)  //  if pIndexNode have not Parent
	{
		BpTreeNode * rootNode = new BpTreeIndexNode();  //  make ParentNode
		pIndexNode->setParent(rootNode);				//  rootNode become pIndexNode's parent
		NewIndexNode->setParent(rootNode);				//  rootnode become NewIndexNode's parent
		rootNode->insertIndexMap(centerindex->first, NewIndexNode);		//  rootNode receive centerindex(divide point element)
		rootNode->setMostLeftChild(pIndexNode);			//  pIndexNode become MostLeftChild of ParentNode
		pIndexNode->deleteMap(centerindex->first);		//  delete centerNode from existing node(pIndexNode)
		root = rootNode;								//  rootNode become root

	}
	else  // if pIndexNode have Parent
	{
		NewIndexNode->setParent(pIndexNode->getParent());  //  existing node's parent become NewIndexNode's parent
		pIndexNode->getParent()->insertIndexMap(centerindex->first, NewIndexNode);  //  ParentNode receive element(centerIndex)
		pIndexNode->deleteMap(centerindex->first);		   //  pIndexNode delete centerindex inside of Map

		if (exceedIndexNode(pIndexNode->getParent()) == 1)  //  if Parent's mapsize if bigger than order -1
		{
			splitIndexNode(pIndexNode->getParent());  // call splitIndexnode function
		}
	}
}

bool BpTree::exceedDataNode(BpTreeNode* pDataNode)
{
	map<string, Characterdata*>  *m = pDataNode->getDataMap();

	if (m->size() > order - 1)
		return true;  //  When Map size is bigger than order - 1, return 1
	else
		return false;  //  When Map size is lower than order - 1, return 0
}

bool BpTree::exceedIndexNode(BpTreeNode* pIndexNode)
{
	map <string, BpTreeNode*>* m = pIndexNode->getIndexMap();

	if (m->size() > order - 1)
		return true;  //  When Map size is bigger than order - 1, return 1
	else
		return false;  //  When Map size is lower than order - 1, return 0
}

void BpTree::Print()
{
	BpTreeNode* pCur = root;		// visit root first

	if (root == NULL)				// if root don't exist
		return;

	map<string, Characterdata*>::iterator it, it1;

	while (pCur->getMostLeftChild() != NULL)	
		pCur = pCur->getMostLeftChild();		// move to mostleftchild

	Characterdata* data;
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "                                 PRINT CHARCTER " << endl;
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "Name\t" << "Pick\t" << "Win\t" << "WinRatio" << endl;

	while (1)
	{
		for (it = pCur->getDataMap()->begin(); it != pCur->getDataMap()->end(); it++)
		{
			it1 = it;
			if (pCur->getDataMap()->size() == 1)			// if datamap's size is 1
			{
				it1 = pCur->getDataMap()->begin();				
				data = it1->second;							// store Characterdata into data
				printCharacterInfo(data);					// call function for print form
			}
			else
			{												// or
				for (int i = pCur->getDataMap()->size(); i > 1; i--)
				{
					data = it1->second;					// store Characterdata into data
					printCharacterInfo(data);			// call function for print form
				}
			}
		}
		pCur = pCur->getNext();		// move to next
		if (!pCur)			// if pCur don't exist
			break;
	}
}

void BpTree::SearchRange(string start, string end)
{
	BpTreeNode* pCur = searchDataNode(start);	// visit first Character's name

	if (pCur == NULL)		// if pCur don't exist
		return;

	queue<Characterdata*> q;		// for ascending
	Characterdata* pCrt = NULL;

	map<string, Characterdata* >::iterator it;	//make a iterator form
	it = pCur->getDataMap()->begin();	//itindex point to first node in treenode

	while (it->first <= end)	//range is smaller than last Character'sname
	{
		if (it->first >= start)		// range is biiger than first Character'sname
			q.push(it->second);		// push it into Queue
		it++;

		if (it == pCur->getDataMap()->end())	//if the end of the node
		{
			pCur = pCur->getNext();	// move to next

			if (!pCur)			// if pCur don't exist
				break;

			it = pCur->getDataMap()->begin();
		}
	}

	if (q.empty())			// if Queue is empty
		return;

	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "                                 SEARCH " << start << "/" << end << endl;
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "Name\t" << "Pick\t" << "Win\t" << "WinRatio" << endl;
	while (!q.empty())		// if Queue is not empty
	{
		pCrt = q.front();		// store front node in Queue into pCrt
		searchCharacterInfo(pCrt);	// call function for print form
		q.pop();			// pop from Queue
	}
}

void BpTree::printCharacterInfo(Characterdata* pCharacter)		// print form of CharacterInfo when PRINT
{
	*fout << pCharacter->getname() << "\t" << pCharacter->getpick() <<
		"\t" << pCharacter->getwin() << "\t" << pCharacter->getratio() << endl;
}
void BpTree::searchCharacterInfo(Characterdata* pCharacter)		// print form of CharacterInfo when SEARCH
{
	*fout << pCharacter->getname() << "\t" << pCharacter->getpick() << "\t" <<
		pCharacter->getwin() << "\t" << pCharacter->getratio() << endl;
}
void BpTree::printPickRank()
{
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "                                   PRINT PICK " << endl;
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "Name\t" << "Pick\t" << "WinRatio" << endl;

	// print every Character information in B+ Tree
	// descending for Cpick, if Cpick is same, then descending for Cname

	BpTreeNode* pCur = root;	// visit root first

	if (root == NULL)		// if root don't exist
		return;

	map<string, Characterdata*>::iterator it, it1;	// make iterator form

	while (pCur->getMostLeftChild() != NULL)	// if MostleftChild exist
		pCur = pCur->getMostLeftChild();		// move to mostleftchild

	Characterdata* data;

	while (1)
	{				// from first of datamap to end of datamap
		for (it = pCur->getDataMap()->begin(); it != pCur->getDataMap()->end(); it++)
		{
			it1 = it;
			if (pCur->getDataMap()->size() == 1)				// for getting Character's name	
			{
				it1 = pCur->getDataMap()->begin();						
				data = it1->second;								// store Characterdata into data
				pick_heap.push(make_pair(make_pair(data->getpick(), data->getname()), data));
			}				// push to Max heap
			else
			{
				for (int i = pCur->getDataMap()->size(); i > 1; i--)
				{
					data = it1->second;			// store Characterdata into data
					pick_heap.push(make_pair(make_pair(data->getpick(), data->getname()), data));
				}		// push to Max heap
			}
		}
		pCur = pCur->getNext();		// move to next
		if (!pCur)			//	if pCur don't exist
			break;
	}

	if (pick_heap.empty())	// if Heap is empty
		return;

	while (!pick_heap.empty())	
	{							// print pick_heap
		*fout << pick_heap.top().second->getname() << "\t" << pick_heap.top().second->getpick() <<
			"\t" << pick_heap.top().second->getratio() << endl;
		pick_heap.pop();		// pop from heap
	}
}

void BpTree::printRatioRank()
{
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "                                 PRINT WINRATIO " << endl;
	*fout << "--------------------------------------------------------------------------------" << endl;
	*fout << "Name\t" << "Pick\t" << "WinRatio" << endl;

	// print every Character information in B+ Tree
	// ascending for Winratio, if Winratio is same, then ascending for Cname
	
	BpTreeNode* pCur = root;			// visit root first

	if (root == NULL)			// if root don't exist
		return;

	map<string, Characterdata*>::iterator it, it1;

	while (pCur->getMostLeftChild() != NULL)		// if MostleftChild exist
		pCur = pCur->getMostLeftChild();			// move to mostleftchild

	Characterdata* data;

	while (1)
	{				// from first of datamap to end of datamap
		for (it = pCur->getDataMap()->begin(); it != pCur->getDataMap()->end(); it++)
		{
			it1 = it;
			if (pCur->getDataMap()->size() == 1)				// for getting Character's name	
			{
				it1 = pCur->getDataMap()->begin();				
				data = it1->second;			// store Characterdata into data
				ratio_heap.push(make_pair(make_pair(data->getratio(), data->getname()), data));
			}			// push to Min heap
			else
			{
				for (int i = pCur->getDataMap()->size(); i > 1; i--)
				{
					data = it1->second;		// store Characterdata into data
					ratio_heap.push(make_pair(make_pair(data->getratio(), data->getname()), data));
				}		// push to Min heap
			}
		}
		pCur = pCur->getNext();		// move to next
		if (!pCur)		// if pCur don't exist
			break;
	}

	if (ratio_heap.empty())		// if Heap is empty
		return;

	while (!ratio_heap.empty())
	{							// print ratio_heap
		*fout << ratio_heap.top().second->getname() << "\t" << ratio_heap.top().second->getpick() <<
			"\t" << ratio_heap.top().second->getratio() << endl;
		ratio_heap.pop();		// pop from heap
	}
}
