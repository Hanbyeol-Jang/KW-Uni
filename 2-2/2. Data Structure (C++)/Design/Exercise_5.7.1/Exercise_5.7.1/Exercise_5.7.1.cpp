#include "BST.h"								//BST 헤더 참조

int main()
{
	int num;									//int형 변수 num 선언

	BST<int, char> data;						//First 는 int형, Second 는 char 형 class 선언

	pair<int, char> p1(30, 'A');				//5개의 pair 생성, 데이터 입력
	pair<int, char> p2(5, 'B');
	pair<int, char> p3(2, 'C');
	pair<int, char> p4(40, 'D');
	pair<int, char> p5(80, 'E');
	pair<int, char> p6(35, 'F');

	data.Insert(p1);							//6개의 pair를 insert 해서 Binary Search Tree 생성
	data.Insert(p2);
	data.Insert(p3);
	data.Insert(p4);
	data.Insert(p5);
	data.Insert(p6);

	data.Inorder();								//Inorder 함수 호출
	cout << endl;

	cout << "Input number that you delete in this BST : ";
	cin >> num;

	data.Delete(num);							//Delete 함수 호출
	data.Inorder();								//Inorder 함수 호출
	cout << endl;

	return 0;
}