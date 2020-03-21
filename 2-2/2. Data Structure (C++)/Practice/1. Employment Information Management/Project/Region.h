#ifndef _REGION_H_
#define _REGION_H_

#include<utility>
#include <cstring>
#include "Employment.h"

#define STR_MAX 60

class Region
{
private:
	std::pair<char[STR_MAX], char[STR_MAX]> rCodeName;
	Region* pNext;		//Next Region node in 2D Linked List
	Region* pLeft;		//Left region node in Binary Search Tree 
	Region* pRight;		//Right region node in Binary Search Tree
	Employment* pDown;	//Employment node in 2D Linked List
	
public:
	Region();
	~Region();

	//Getter,Setter Methods
	void SetRegionCode(char* region_code);
	void SetRegionName(char* region_name);
	void SetNext(Region* pNext);
	void SetLeft(Region* pLeft);
	void SetRight(Region* pRight);
	void SetDown(Employment* pDown);
	
	char* GetRegionCode();
	char* GetRegionName();
	Region* GetNext();
	Region* GetLeft();
	Region* GetRight();
	Employment* GetDown();
};
#endif