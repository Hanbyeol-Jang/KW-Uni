#ifndef _BST_H_
#define _BST_H_

#include "Employment.h"
#include "Region.h"

class BST
{
private:
	Region* root;

public:
	BST();
	~BST();
		
	void SetRoot(Region* pNode);
	Region* GetRoot();
	
	bool Insert(Region* pNode);
	bool Delete(Region* pNode);
	Employment* Search(char* region_code);
};
#endif