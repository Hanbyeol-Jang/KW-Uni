#ifndef _LIST_2D_H
#define _LIST_2D_H

#include "Employment.h"
#include "Region.h"
#include <cstring>

class List_2D
{
private:
	Region* pHead;

public:
	List_2D();
	~List_2D();

	void SetHead(Region* pNode);
	Region* GetHead();

	void Insert(Region* pNode);
	void Insert(Employment* pNode);
	bool Delete(Employment* pNode);
};
#endif