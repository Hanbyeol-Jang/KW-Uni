#pragma once
#include "Characterdata.h"
class BpTreeNode
{
private:
	BpTreeNode* pParent;
	BpTreeNode* pMostLeftChild;

public:
												// 생성자에서 열필요없음
	BpTreeNode() 
	{
		pParent = NULL;
		pMostLeftChild = NULL;
	}
	
	~BpTreeNode() {
	}

	void setMostLeftChild(BpTreeNode* pN) { pMostLeftChild = pN; }
	void setParent(BpTreeNode* pN) { pParent = pN; }

	BpTreeNode* getParent() { return pParent; }
	BpTreeNode* getMostLeftChild() { return pMostLeftChild; }

	virtual void setNext(BpTreeNode* pN) {}
	virtual void setPrev(BpTreeNode* pN) {}
	virtual BpTreeNode* getNext() { return NULL; }
	virtual BpTreeNode* getPrev() { return NULL; }
//---------------------------Virtual----------------------------------
	virtual void insertDataMap(string n, Characterdata* pN) {}
	virtual void insertIndexMap(string n, BpTreeNode* pN) {}
	virtual void deleteMap(string n) {}

	virtual map<string, BpTreeNode*>* getIndexMap() { map<string, BpTreeNode*> m; return &m; }
	virtual map<string, Characterdata*> *getDataMap()
	{
		map<string, Characterdata*> m;
		return &m;
	}

};