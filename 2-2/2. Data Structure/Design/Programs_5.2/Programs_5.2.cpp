#include <iostream>
#include "Tree.h"                    //Tree ��� ����
#include "TreeNode.h"                //TreeNode ��� ����
using namespace std;

int main()
{
	Tree<char> T;                    //Tree class�� char������ ����

	T.Preorder();                     //Preorder �Լ� ȣ��
	cout << endl;

	return 0;
}