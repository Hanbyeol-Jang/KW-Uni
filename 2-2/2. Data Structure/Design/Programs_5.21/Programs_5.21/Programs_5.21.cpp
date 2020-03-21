#include "BST.h"								//BST 헤더 참조

int main()
{
	BST<int, char> data;						//First 는 int형, Second 는 char 형 class 선언

	pair<int, char> p1(30, 'A');				//6개의 pair 생성, 데이터 입력
	pair<int, char> p2(5, 'B');
	pair<int, char> p3(2, 'C');
	pair<int, char> p4(40, 'D');
	pair<int, char> p5(80, 'E');
	pair<int, char> p6(35, 'F');

	data.Insert(p1);							//5개의 pair를 insert 해서 Binary Search Tree 생성
	data.Insert(p2);
	data.Insert(p3);
	data.Insert(p4);
	data.Insert(p5);

	data.Inorder();								//Inorder 함수 호출
	cout << endl;

	data.Insert(p6);							//6번째 pair를 insert

	data.Inorder();								//Inorder 함수 호출
	cout << endl;

	return 0;
}