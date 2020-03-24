#include <iostream>

using namespace std;

#define INDEX 5
#define Infinity 999 

int dist[INDEX];

// 각 노드들의 정보
int Adj[INDEX][INDEX] = {
	{ 0, -1, 4, Infinity, Infinity },
	{ Infinity, 0, 3, 2, 2 },
	{ Infinity, Infinity, 0, Infinity, Infinity },
	{ Infinity, 1, 5, 0, Infinity },
	{ Infinity, Infinity, Infinity, -3, 0 } };

void Bellman_Ford(int s, int Q);

void main() {
	Bellman_Ford(0, INDEX);		

	cout << "각 노드에서의 거리들\n";
	for (int i = 0; i < 5; i++) {
		cout << i << "," << dist[i] << endl;
	}

}

void Bellman_Ford(int s, int Q) {
	int u, v;

	// 처음에 모든 거리를 무한대로 설정한다.
	for (u = 0; u < Q; u++) {
		dist[u] = Infinity;
	}

	dist[s] = 0;	// 출발지점을 0으로 설정한다.

	
	for (int i = 1; i < Q; i++) {	// vertex-1번 만큼 for문을 돌려준다.
		for (u = 0; u < Q; u++) {	// 각각의 edge들에 대해서 확인을 해준다.
			for (v = 0; v < Q; v++) {
				if (Adj[u][v] == Infinity) {
					// 그냥 통과
				}
				else if (dist[v] > dist[u] + Adj[u][v]) {	// relaxation step
					dist[v] = dist[u] + Adj[u][v];
				}
			}
		}
	}

	for (u = 0; u < Q; u++) {	// 각각의 edge들에 대해서 확인을 해준다.
		for (v = 0; v < Q; v++) {
			if (Adj[u][v] == Infinity) {
				// 그냥 통과
			}
			else if (dist[v] > dist[u] + Adj[u][v]) {	// Negative-weight cycle이 존재할 경우이다.
				cout << "report that a negative-weight cycle exists" << endl;
			}
		}
	}

}