#include <iostream>

using namespace std;

#define INDEX 5
#define Infinity 999 

int dist[INDEX];

// �� ������ ����
int Adj[INDEX][INDEX] = {
	{ 0, -1, 4, Infinity, Infinity },
	{ Infinity, 0, 3, 2, 2 },
	{ Infinity, Infinity, 0, Infinity, Infinity },
	{ Infinity, 1, 5, 0, Infinity },
	{ Infinity, Infinity, Infinity, -3, 0 } };

void Bellman_Ford(int s, int Q);

void main() {
	Bellman_Ford(0, INDEX);		

	cout << "�� ��忡���� �Ÿ���\n";
	for (int i = 0; i < 5; i++) {
		cout << i << "," << dist[i] << endl;
	}

}

void Bellman_Ford(int s, int Q) {
	int u, v;

	// ó���� ��� �Ÿ��� ���Ѵ�� �����Ѵ�.
	for (u = 0; u < Q; u++) {
		dist[u] = Infinity;
	}

	dist[s] = 0;	// ��������� 0���� �����Ѵ�.

	
	for (int i = 1; i < Q; i++) {	// vertex-1�� ��ŭ for���� �����ش�.
		for (u = 0; u < Q; u++) {	// ������ edge�鿡 ���ؼ� Ȯ���� ���ش�.
			for (v = 0; v < Q; v++) {
				if (Adj[u][v] == Infinity) {
					// �׳� ���
				}
				else if (dist[v] > dist[u] + Adj[u][v]) {	// relaxation step
					dist[v] = dist[u] + Adj[u][v];
				}
			}
		}
	}

	for (u = 0; u < Q; u++) {	// ������ edge�鿡 ���ؼ� Ȯ���� ���ش�.
		for (v = 0; v < Q; v++) {
			if (Adj[u][v] == Infinity) {
				// �׳� ���
			}
			else if (dist[v] > dist[u] + Adj[u][v]) {	// Negative-weight cycle�� ������ ����̴�.
				cout << "report that a negative-weight cycle exists" << endl;
			}
		}
	}

}