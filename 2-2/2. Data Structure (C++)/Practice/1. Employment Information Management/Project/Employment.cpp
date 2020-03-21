#include "Employment.h"

Employment::Employment()
{
	memset(this->rCodeName.first, 0, sizeof(char) * STR_MAX);
	memset(this->rCodeName.second, 0, sizeof(char) * STR_MAX);
	memset(this->company, 0, sizeof(char) * STR_MAX);
	memset(this->qualification, 0, sizeof(char) * STR_MAX);
	memset(this->working_condition, 0, sizeof(char) * STR_MAX);
	memset(this->to, 0, sizeof(char) * STR_MAX);
	this->pDown = NULL;
	this->pNext = NULL;
}

Employment::~Employment()
{
	/* You must fill in here */
}

/* You must fill in the member function definitions of the Employment class here */
