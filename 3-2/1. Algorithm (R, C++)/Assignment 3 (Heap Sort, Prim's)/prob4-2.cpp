#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>
using namespace std;
	
int A[8][8] = {				// 그래프 및 edge 정보를 저장
	{0, 0, 1, 0, 2, 0, 0, 0},
	{0, 0, 6, 4, 0, 9, 0, 0},
	{1, 6, 0, 0, 0, 6, 0, 0},
	{0, 4, 0, 0, 0, 0, 0, 5},
	{2, 0, 0, 0, 0, 0, 8, 4},
	{0, 9, 6, 0, 0, 0, 1, 0},
	{0, 0, 0, 0, 8, 1, 0, 9},
	{0, 0, 0, 5, 4, 0, 9, 0}
};

class V {			// vertex에 대한 각종 정보를 저장
public:
	int Vertex;		// 몇 번째 vertex 인지
	int Extract;	// Extract 되었는지
	int Weight;		// 가중치
	int Path;		// 이전 노드 저장
};

priority_queue< int, vector<int>, greater<int> > Q;

void Print_Table(V v[]);	// 그래프 정보 table 형태로 출력하는 함수
void Print_Min();			// 최소값 출력하는 함수
int Extract_Min(V v[]);		// 최소값 Extract 하는 함수
int PRIM(V v[], int vtx);	// Prim's algorithm 적용하는 함수

int flag = 0;		// Recursive 몇 번 하는지 정하는 변수

int main(void)
{
	int num = 0;
	V v[8];					// 8개의 vertex

	int i = 0, j = 0;
	int vtx = 0;

	for (i = 0; i < 8; i++)			// vertex table 초기화
	{
		v[i].Vertex = i;
		v[i].Extract = 0;			// Extract 0으로 초기화, 나중에 Extract 되면 1
		v[i].Weight = 99999999;		// 무한대를 99999999로 표시
		v[i].Path = -1;				// 이전 노드를 저장, 아직 접근하지 않는 vertex는 -1로 초기화
	}
	Print_Table(v);

	srand((unsigned int)time(NULL));		// 임의의 숫자로
	vtx = rand() % 8;						// 맨 처음 vertex 정함

	//vtx = 5;
	v[vtx].Weight = 0;				// 선택된 vertex의 key 0으로

	PRIM(v, vtx);

	return 0;
}

void Print_Table(V v[])			// Vertex 정보 table 형태로 출력하는 함수
{
	 int i = 0;

	 for (i = 0; i < 8; i++)	// table(2차원 배열)로 출력
		 printf("%d %d %d %d\n", v[i].Vertex, v[i].Extract, v[i].Weight, v[i].Path);
	 printf("-------------------\n");
 }
void Print_Min()
{
	printf("%d ", Q.top());			// Min Heap 의 root(top) 는 최소값
	printf("\n-------------------\n");
}
int Extract_Min(V v[])
{
	int i = 0, j = 0;

	for (i = 0; i < 8; i++)
	{
		if (Q.empty())					// queue에서 빼낼 값이 없으면
		{
			for (j = 0; j < 8; j++)
			{
				if (v[j].Extract != 1)		// 아직 Extract 되지 않은 vertex를
					Q.push(v[j].Weight);		// queue 에 삽입
			}

			j = 0;
			for (j = 0; j < 8; j++)
			{
				if (Q.top() == v[j].Weight && v[j].Extract != 1)	// 최소값이 root와 일치하면
				{													// (top이 root)
					v[j].Extract = 1;				// Extract 하고

					while (!Q.empty())				// queue 를 모두 빼낸다.
						Q.pop();

					return v[j].Vertex;				// Extract 된 vertex 반환
				}
			}
		}

		if (Q.top() == v[i].Weight && v[i].Extract != 1)	// Extract 되지 않은 것중
		{													// 최소값이 root와 일치하면
			v[i].Extract = 1;					// Extract 하고
			break;
		}
	}
	while (!Q.empty())					// queue 를 모두 빼낸다.
		Q.pop();

	printf("\n");

	return v[i].Vertex;				// Extract 된 vertex 반환
}

int PRIM(V v[], int vtx)
{
	int i = 0, j = 0;
	int next_vtx = 0;

	printf("Vertex: %d\n", v[vtx].Vertex);		// 어떤 vertex가 Extract 되었는지 출력

	flag++;					
	if (flag == 8)				// vertex 수 만큼
		return 0;

	if (v[vtx].Weight == 0)		// 맨 처음 vertext 는 가중치가 0이다
		v[vtx].Extract = 1;		// 그럼 Extract 1로
	
	v[vtx].Extract == 1;		// 반환된 vertex, Extract 되었으므로 1로

	Print_Table(v);

	for (i = 0; i < 8; i++)
	{
		if (A[vtx][i] != 0 && v[i].Extract != 1)	// edge 값이 0이 아니고, 아직 Extract 되지않은 vertex
		{
			if (v[i].Weight > A[vtx][i])			// edge 값이 기존 가중치보다 작다면
			{
				v[i].Weight = A[vtx][i];			// edge 값으로 upate
				v[i].Path = vtx;					// 어디에 연결되었는지 저장
				Q.push(v[i].Weight);				// 최소값 선정을 위해 가중치 queue에 삽입
			}
		}
	}
	Print_Table(v);
	next_vtx = Extract_Min(v);				// 최소값으로 선정된 vertex가 다음 vertex로 선택된다.
	Print_Table(v);

	PRIM(v, next_vtx);				// 선택된 vertex를 인수로 넣어 다시 Recursive 함수 호출

	return 0;
}
