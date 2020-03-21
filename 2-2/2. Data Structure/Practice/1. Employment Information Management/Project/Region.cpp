#include"Region.h"

Region::Region()
{
	memset(this->rCodeName.first, 0, sizeof(char) * STR_MAX);
	memset(this->rCodeName.second, 0, sizeof(char) * STR_MAX);
	this->pNext = NULL;
	this->pLeft = NULL;
	this->pRight = NULL;
	this->pDown = NULL;
}

Region::~Region()
{
	/* You must fill in here */
}

/* You must fill in the member function definitions of the Region class here */
