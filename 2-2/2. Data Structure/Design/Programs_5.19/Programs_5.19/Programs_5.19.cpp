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

	data.Insert(p1);							//5개의 pair를 insert 해서 Binary Search Tree 생성
	data.Insert(p2);
	data.Insert(p3);
	data.Insert(p4);
	data.Insert(p5);

	cout << "Input number that you search: ";						//찾는 숫자 입력 시
	cin >> num;														//num 에 저장

	if (data.Get(num))
		cout << "There is the number in BST. " << endl;				//찾는 숫자가 BST 에 있으면 출력
	else
		cout << "There is NOT the number in BST. " << endl;			//찾는 숫자가 BST 에 없으면 출력

	return 0;
}