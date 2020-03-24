#include <iostream>
#include <string>
using namespace std;

string PrintLCS(string x, string y);	// LCS�� ����ϴ� �Լ�
string Reverse(string LCS);				/* tracing backwards�� string�� �ݴ�� ����Ǵ� ����
										 �ٽ� reverse ��Ű�� �Լ�*/
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
	cout << "LCS:" << PrintLCS(x, y) << endl;	// LCS ���

	return 0;
}

string PrintLCS(string x, string y)
{
	string LCS="";			// LCS�� ���� string ����
	int m = 0, n = 0;		// Sequence �� ���̸� ���� ���� ���� �� �ʱ�ȭ
	int i = 1, j = 1;		// Sequence �� �� ��ҵ��� ���������� ���ϱ� ���� ����
	m = x.length() - 1;		// main �Լ����� ���� ���ڸ� �߰������Ƿ�, string ���̿��� -1
	n = y.length() - 1;

	int c[100][100] = { 0, };			// 100 X 100 table, ��� ��Ҹ� 0���� �ʱ�ȭ

	for (j = 1; j <= n; j++)		// y ��� �ϳ��� ��
	{
		for (i = 1; i <= m; i++)	// x ��� �ϳ��� ��
		{
			if (x[i] == y[j])		// ���� ���ڶ��,
			{
				c[j][i] = c[j - 1][i - 1] + 1;	// ���� ��ġ���� ��-1, ��-1 ������ +1 �� �� �־���
			}
			else                     // �ٸ� ���ڶ��, ���� ���� �� ���� ���� �� �� ū ���� �־���
			{
				if (c[j - 1][i] > c[j][i - 1])		// �� ���� ���� ������ Ŭ ��
				{
					c[j][i] = c[j - 1][i];			// �� ��(���� ��ġ���� ��-1 ��)�� �־���
				}
				else								// ���� ���� �� ������ Ŭ �� or ���� ��
				{
					c[j][i] = c[j][i - 1];			// ���� ��(������ġ���� ��-1)�� �־���
				}
			}
		}
	}
	
	i = m;		// tracing backwards �� ���� �ʱ�ȭ
	j = n;		// : �迭�� ������ ���� Ȯ���ؾ� �ϹǷ�, �迭�� ���̸� �־���
	
	while (1)			// 2 Sequence�� ��� ��ҵ��� ���ϴ� Loop
	{
		if (i == 0 || j == 0)			// ��� Ȯ�� ������ Loop�� �������� 
			break;

		if (c[j][i] == c[j][i - 1])		// ���� ���� ���� ���� ���ٸ�
		{
			i--;						// �������� �̵�
			continue;
		}
		else if (c[j][i] == c[j - 1][i])	// ���� ���� �� ���� ���ٸ�
		{
			j--;							// ���� �̵�
			continue;
		}
		else							// ���� ���� ���� ������ �ٸ��� ���� ������ �ٸ���
		{								// ��, �밢�� + 1 �� ����̴�
			LCS = LCS + x[i];			// �밢�� + 1 �� ���� 2 Sequence�� ��Ҹ� �񱳽�,
			i--;						// �� ���ڰ� ���� �� �̹Ƿ�, �� ���� LCS�� �־��ش�
			j--;						// �� ��, �밢������ �̵�
			continue;
		}
	}
	LCS = Reverse(LCS);				// tracing backwards �����Ƿ� string �� reverse ��Ų��

	return LCS;						// �ϼ��� LCS ��ȯ
}

string Reverse(string LCS)
{
	string temp = "";				// �ӽ÷� ����� string ����
	int len = 0;						// string�� ���̸� ���� ���� ����
	len = LCS.length()-1;				// �迭�� index�� 0���� �����ϹǷ� ����-1 ����

	for (int i = 0; i <= len; i++)
	{
		temp = temp + LCS[len - i];		// string�� ������ ���ں��� ������ ���ʷ� �־��ش�
	}

	return temp;				// reverse �� string ��ȯ
}
