#ifndef _BpTreeDataNode_H_
#define _BpTreeDataNode_H_

#include "BpTreeNode.h"
class BpTreeDataNode : public BpTreeNode
{
private:
	map <string, Characterdata*> mapData;
	BpTreeNode* pNext;
	BpTreeNode* pPrev;
public:
	BpTreeDataNode(){
		pNext = NULL;
		pPrev = NULL;
	}
	~BpTreeDataNode(){
	}
	void setNext(BpTreeNode* pN){pNext = pN;}
	void setPrev(BpTreeNode* pN){pPrev = pN;}
	BpTreeNode* getNext(){return pNext;}
	BpTreeNode* getPrev(){return pPrev;}

	void insertDataMap(string n, Characterdata* pN){
		mapData.insert(map<string, Characterdata*>::value_type(n,pN));
	}

	void deleteMap(string n){
		mapData.erase(n);
	}
	map<string, Characterdata*> *getDataMap(){return &mapData;}
};

#endif