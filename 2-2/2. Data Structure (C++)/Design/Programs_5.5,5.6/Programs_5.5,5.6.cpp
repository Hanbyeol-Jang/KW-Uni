#include <iostream>
#include "Tree.h"                    //Tree ��� ����
#include "TreeNode.h"                //TreeNode ��� ����
#include "InorderIterator.h"         //InorderIterator ��� ����
using namespace std;

int main()
{
	InorderIterator<char> t;

	t.Next();                        //Next�Լ� ȣ��
	t.Next();

	cout << endl;

	return 0;
}