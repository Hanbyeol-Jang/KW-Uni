#include <iostream>
#include <string>
using namespace std;

int ComputeLength(string x, string y);			// LCS�� ���̸� ����ϴ� �Լ�

int main(void)
{
	string x = "";			// string�� ���� ���� (Sequence 2��)
	string y = "";

	cout << "Enter 1st Sequence:" << endl;
	getline(cin, x);						// ù ��° Sequence �Է¹޾� x �� ����
	x = " " + x;							// table �����ڸ��� 0���� ä��� ���� ���鹮�� ����
	cout << "Enter 2nd Sequence:" << endl;
	getline(cin, y);						// �� ��° Sequence �Է¹޾� y �� ����
	y = " " + y;							// ���鹮�� ����

	cout << endl;
	cout << "LCS Length: " << ComputeLength(x, y) << endl;	// LCS�� ���� ���
	return 0;
}

int ComputeLength(string x, string y)
{
	int m = 0, n = 0;		// Sequence �� ���̸� ���� ���� ���� �� �ʱ�ȭ
	int i = 1, j = 1;		// Sequence �� �� ��ҵ��� ���������� ���ϱ� ���� ����
	m = x.length() - 1;		// main �Լ����� ���� ���ڸ� �߰������Ƿ�, string ���̿��� -1
	n = y.length() - 1;

	int c[100][100] = { 0, };			// 100 X 100 table, ��� ��Ҹ� 0���� �ʱ�ȭ
	
	for (int a = 0; a <= m; a++)
		cout << c[0][a] <<" ";		// 1�� 0���� ä��(���)
	cout << endl;

	for (j = 1; j <= n; j++)		// y ��� �ϳ��� ��
	{
		cout << c[j][0] << " ";		// 1�� 0���� ä��(���)
		for (i = 1; i <= m; i++)	// x ��� �ϳ��� ��
		{
			if (x[i] == y[j])		// ���� ���ڶ��,
			{
				c[j][i] = c[j-1][i - 1] + 1;	// ���� ��ġ���� ��-1, ��-1 ������ +1 �� �� �־���
				cout << c[j][i] << " ";
			}
			else                     // �ٸ� ���ڶ��, ���� ���� �� ���� ���� �� �� ū ���� �־���
			{
				if (c[j-1][i] > c[j][i-1])		// �� ���� ���� ������ Ŭ ��
				{
					c[j][i] = c[j-1][i];			// �� ��(���� ��ġ���� ��-1 ��)�� �־���
					cout << c[j][i] << " ";
				}
				else								// ���� ���� �� ������ Ŭ �� or ���� ��
				{
					c[j][i] = c[j][i-1];			// ���� ��(������ġ���� ��-1)�� �־���
					cout << c[j][i] << " ";
				}
			}
		}
		cout << endl;		// y��Ұ� ���� ���ڷ� �Ѿ���� �ٹٲ�
	}
	cout << endl;

	return c[n][m];		// LCS�� ���� ��ȯ
}
