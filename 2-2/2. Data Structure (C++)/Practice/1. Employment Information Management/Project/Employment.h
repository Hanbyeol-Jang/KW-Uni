#ifndef _EMPLOYMENT_H_
#define _EMPLOYMENT_H_

#include <cstring>
#include <utility>

#define STR_MAX 60

class Employment
{
private:
	std::pair<char[STR_MAX],char[STR_MAX]> rCodeName;
	char company[STR_MAX];
	char qualification[STR_MAX];
	char working_condition[STR_MAX];
	char to[STR_MAX];
	Employment* pDown;	//Employment node in 2D Linked List
	Employment* pNext;	//Employment node in Circular Linked List pointer

public:
	Employment();
	~Employment();

	//Getter,Setter Methods
	void SetRegionCode(char* region_code);
	void SetRegionName(char* region_name);
	void SetCompany(char* company);
	void SetQualification(char* qualification);
	void SetWorkingCondition(char* working_condition);
	void SetTo(char* to);
	void SetDown(Employment* pDown);
	void SetNext(Employment* pNext);

	char* GetRegionCode();
	char* GetRegionName();
	char* GetCompany();
	char* GetQualification();
	char* GetWorkingCondition();
	char* GetTo();
	Employment* GetDown();
	Employment* GetNext();
};
#endif