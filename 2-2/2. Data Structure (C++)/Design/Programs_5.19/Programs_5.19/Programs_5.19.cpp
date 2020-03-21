#include "BST.h"								//BST ��� ����

int main()
{
	int num;									//int�� ���� num ����

	BST<int, char> data;						//First �� int��, Second �� char �� class ����

	pair<int, char> p1(30, 'A');				//5���� pair ����, ������ �Է�
	pair<int, char> p2(5, 'B');
	pair<int, char> p3(2, 'C');
	pair<int, char> p4(40, 'D');
	pair<int, char> p5(80, 'E');

	data.Insert(p1);							//5���� pair�� insert �ؼ� Binary Search Tree ����
	data.Insert(p2);
	data.Insert(p3);
	data.Insert(p4);
	data.Insert(p5);

	cout << "Input number that you search: ";						//ã�� ���� �Է� ��
	cin >> num;														//num �� ����

	if (data.Get(num))
		cout << "There is the number in BST. " << endl;				//ã�� ���ڰ� BST �� ������ ���
	else
		cout << "There is NOT the number in BST. " << endl;			//ã�� ���ڰ� BST �� ������ ���

	return 0;
}