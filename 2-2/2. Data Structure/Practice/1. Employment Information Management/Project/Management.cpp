#include "Management.h"

Management::Management()
{
	this->m_2DLL = new List_2D();
	this->m_Circular = new List_Circular();
	this->m_BST = new BST();

	//Clear existing out file contents
	ofstream fout1, fout2, fout3;
	fout1.open("OUT_FIND.txt", ios::trunc);
	fout2.open("OUT_DELETE.txt", ios::trunc);
	fout3.open("OUT_PRINT.txt", ios::trunc);
	fout1.close();
	fout2.close();
	fout3.close();
}

Management::~Management()
{
	/* You must fill in here */
}

/* You must fill in the member function definitions of the Management class here */
