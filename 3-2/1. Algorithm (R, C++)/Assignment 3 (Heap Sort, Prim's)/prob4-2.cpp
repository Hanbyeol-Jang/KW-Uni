#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;
	
int A[8][8] = {				// �׷��� �� edge ������ ����
	{0, 0, 1, 0, 2, 0, 0, 0},
	{0, 0, 6, 4, 0, 9, 0, 0},
	{1, 6, 0, 0, 0, 6, 0, 0},
	{0, 4, 0, 0, 0, 0, 0, 5},
	{2, 0, 0, 0, 0, 0, 8, 4},
	{0, 9, 6, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 8, 1, 0, 9},
	{0, 0, 0, 5, 4, 0, 9, 0}
};

class V {			// vertex�� ���� ���� ������ ����
public:
	int Vertex;		// �� ��° vertex ����
	int Extract;	// Extract �Ǿ�����
	int Weight;		// ����ġ
	int Path;		// ���� ��� ����
};

priority_queue< int, vector<int>, greater<int> > Q;

void Print_Table(V v[]);	// �׷��� ���� table ���·� ����ϴ� �Լ�
void Print_Min();			// �ּҰ� ����ϴ� �Լ�
int Extract_Min(V v[]);		// �ּҰ� Extract �ϴ� �Լ�
int PRIM(V v[], int vtx);	// Prim's algorithm �����ϴ� �Լ�

int flag = 0;		// Recursive �� �� �ϴ��� ���ϴ� ����

int main(void)
{
	int num = 0;
	V v[8];					// 8���� vertex

	int i = 0, j = 0;
	int vtx = 0;

	for (i = 0; i < 8; i++)			// vertex table �ʱ�ȭ
	{
		v[i].Vertex = i;
		v[i].Extract = 0;			// Extract 0���� �ʱ�ȭ, ���߿� Extract �Ǹ� 1
		v[i].Weight = 99999999;		// ���Ѵ븦 99999999�� ǥ��
		v[i].Path = -1;				// ���� ��带 ����, ���� �������� �ʴ� vertex�� -1�� �ʱ�ȭ
	}
	Print_Table(v);

	srand((unsigned int)time(NULL));		// ������ ���ڷ�
	vtx = rand() % 8;						// �� ó�� vertex ����

	//vtx = 5;
	v[vtx].Weight = 0;				// ���õ� vertex�� key 0����

	PRIM(v, vtx);

	return 0;
}

void Print_Table(V v[])			// Vertex ���� table ���·� ����ϴ� �Լ�
{
	 int i = 0;

	 for (i = 0; i < 8; i++)	// table(2���� �迭)�� ���
		 printf("%d %d %d %d\n", v[i].Vertex, v[i].Extract, v[i].Weight, v[i].Path);
	 printf("-------------------\n");
 }
void Print_Min()
{
	printf("%d ", Q.top());			// Min Heap �� root(top) �� �ּҰ�
	printf("\n-------------------\n");
}
int Extract_Min(V v[])
{
	int i = 0, j = 0;

	for (i = 0; i < 8; i++)
	{
		if (Q.empty())					// queue���� ���� ���� ������
		{
			for (j = 0; j < 8; j++)
			{
				if (v[j].Extract != 1)		// ���� Extract ���� ���� vertex��
					Q.push(v[j].Weight);		// queue �� ����
			}

			j = 0;
			for (j = 0; j < 8; j++)
			{
				if (Q.top() == v[j].Weight && v[j].Extract != 1)	// �ּҰ��� root�� ��ġ�ϸ�
				{													// (top�� root)
					v[j].Extract = 1;				// Extract �ϰ�

					while (!Q.empty())				// queue �� ��� ������.
						Q.pop();

					return v[j].Vertex;				// Extract �� vertex ��ȯ
				}
			}
		}

		if (Q.top() == v[i].Weight && v[i].Extract != 1)	// Extract ���� ���� ����
		{													// �ּҰ��� root�� ��ġ�ϸ�
			v[i].Extract = 1;					// Extract �ϰ�
			break;
		}
	}
	while (!Q.empty())					// queue �� ��� ������.
		Q.pop();

	printf("\n");

	return v[i].Vertex;				// Extract �� vertex ��ȯ
}

int PRIM(V v[], int vtx)
{
	int i = 0, j = 0;
	int next_vtx = 0;

	printf("Vertex: %d\n", v[vtx].Vertex);		// � vertex�� Extract �Ǿ����� ���

	flag++;					
	if (flag == 8)				// vertex �� ��ŭ
		return 0;

	if (v[vtx].Weight == 0)		// �� ó�� vertext �� ����ġ�� 0�̴�
		v[vtx].Extract = 1;		// �׷� Extract 1��
	
	v[vtx].Extract == 1;		// ��ȯ�� vertex, Extract �Ǿ����Ƿ� 1��

	Print_Table(v);

	for (i = 0; i < 8; i++)
	{
		if (A[vtx][i] != 0 && v[i].Extract != 1)	// edge ���� 0�� �ƴϰ�, ���� Extract �������� vertex
		{
			if (v[i].Weight > A[vtx][i])			// edge ���� ���� ����ġ���� �۴ٸ�
			{
				v[i].Weight = A[vtx][i];			// edge ������ upate
				v[i].Path = vtx;					// ��� ����Ǿ����� ����
				Q.push(v[i].Weight);				// �ּҰ� ������ ���� ����ġ queue�� ����
			}
		}
	}
	Print_Table(v);
	next_vtx = Extract_Min(v);				// �ּҰ����� ������ vertex�� ���� vertex�� ���õȴ�.
	Print_Table(v);

	PRIM(v, next_vtx);				// ���õ� vertex�� �μ��� �־� �ٽ� Recursive �Լ� ȣ��

	return 0;
}
