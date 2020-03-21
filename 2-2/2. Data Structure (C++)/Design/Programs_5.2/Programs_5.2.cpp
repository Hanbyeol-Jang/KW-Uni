#include <iostream>
#include "Tree.h"                    //Tree 헤더 참조
#include "TreeNode.h"                //TreeNode 헤더 참조
using namespace std;

int main()
{
	Tree<char> T;                    //Tree class를 char형으로 선언

	T.Preorder();                     //Preorder 함수 호출
	cout << endl;

	return 0;
}