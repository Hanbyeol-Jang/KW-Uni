#ifndef _LIST_CIRCULAR_H
#define  _LIST_CIRCULAR_H

#include "Employment.h"
#include <iostream>

class List_Circular
{
private:
	Employment* pHead;
public:
	List_Circular();
	~List_Circular();

	void SetHead(Employment* pNode);
	Employment* GetHead();	

	void Insert(Employment* pNode);		
	Employment* Delete(Employment* pNode);	
};
#endif