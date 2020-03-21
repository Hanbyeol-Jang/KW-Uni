#include <iostream>
#include "Tree.h"                    //Tree 헤더 참조
#include "TreeNode.h"                //TreeNode 헤더 참조
#include "InorderIterator.h"         //InorderIterator 헤더 참조
using namespace std;

int main()
{
	InorderIterator<char> t;

	t.Next();                        //Next함수 호출
	t.Next();

	cout << endl;

	return 0;
}