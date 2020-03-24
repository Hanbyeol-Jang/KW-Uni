#include <iostream>

using namespace std;

#define INDEX 5
#define Infinity 999 

int check_path[INDEX];
int dist[INDEX];
int S[INDEX];

// 각 노드들의 정보
int Adj[INDEX][INDEX] = {
	{ 0, 10, 3, Infinity, Infinity },
	{ Infinity, 0, 1, 2, Infinity },
	{ Infinity, 4, 0, 8, 2 },
	{ Infinity, Infinity, Infinity, 0, 7 },
	{ Infinity, Infinity, Infinity, 9, 0 } };

void Dijkstra(int s, int Q);
int Extract_Min(int n);

void main() {
	Dijkstra(0, INDEX);

	cout << "각 노드에서의 거리들\n";
	for (int i = 0; i < 5; i++) {
		cout << i << "," << dist[i] << endl;
	}

	cout << "정렬된 순서\n";
	for (int i = 0; i < 5; i++) {
		cout << S[i] << " ";
	}
	cout << endl;
}


// 최소 거리를 가지는 값부터 반환
int Extract_Min(int num) {
	int min;

	// 처음부터 확인을 하면서 배열의 앞의 요소부터 접근을 한다.
	for (int i = 0; i <num; i++) {
		if (check_path[i] != 1) {
			min = i;
			break;
		}
	}

	// 선택하지 않은 값 들 중 최소 값을 찾는다.
	for (int i = 0; i < num; i++) {
		if (check_path[i] != 1 && dist[i] < dist[min]) {
			min = i;
		}
	}

	return min;
}

void Dijkstra(int s, int Q) {
	int u, v, S_index=0;

	// 처음에 모든 거리를 무한대로 설정한다.
	for (u = 0; u < Q; u++) {
		dist[u] = Infinity;
	}

	dist[s] = 0;	// 출발지점을 0으로 설정한다.

	for (int i = 0; i < Q; i++) {	// Q의 배열이 공집합이 될 때까지 돈다.
		u = Extract_Min(Q);	// 최소 값을 가져온다.
		check_path[u] = 1;	// 지나간 경로 체크
		S[S_index++] = u;

		// 무한대이므로 확인할 필요가 없음
		if (dist[u] == Infinity) {
			return;
		}

		for (v = 0; v<Q; v++) {	// v에 대해서 인접노드들을 돈다.
			// v가 Q배열안에 있고 인접노드의 거리보다 key값이 더 크고 인접노드가 연결되어있을 경우
			if (check_path[v] != 1 && dist[v] > dist[u] + Adj[u][v] && Adj[u][v] != Infinity) {
				dist[v] = dist[u] + Adj[u][v];		// Decrease-Key
			}
		}

	}
}