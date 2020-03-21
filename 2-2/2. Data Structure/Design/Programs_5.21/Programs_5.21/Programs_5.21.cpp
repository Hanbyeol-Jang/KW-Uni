#include "BST.h"								//BST ��� ����

int main()
{
	BST<int, char> data;						//First �� int��, Second �� char �� class ����

	pair<int, char> p1(30, 'A');				//6���� pair ����, ������ �Է�
	pair<int, char> p2(5, 'B');
	pair<int, char> p3(2, 'C');
	pair<int, char> p4(40, 'D');
	pair<int, char> p5(80, 'E');
	pair<int, char> p6(35, 'F');

	data.Insert(p1);							//5���� pair�� insert �ؼ� Binary Search Tree ����
	data.Insert(p2);
	data.Insert(p3);
	data.Insert(p4);
	data.Insert(p5);

	data.Inorder();								//Inorder �Լ� ȣ��
	cout << endl;

	data.Insert(p6);							//6��° pair�� insert

	data.Inorder();								//Inorder �Լ� ȣ��
	cout << endl;

	return 0;
}