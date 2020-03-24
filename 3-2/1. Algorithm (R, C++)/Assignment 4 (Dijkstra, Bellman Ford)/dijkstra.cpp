#include <iostream>

using namespace std;

#define INDEX 5
#define Infinity 999 

int check_path[INDEX];
int dist[INDEX];
int S[INDEX];

// �� ������ ����
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

	cout << "�� ��忡���� �Ÿ���\n";
	for (int i = 0; i < 5; i++) {
		cout << i << "," << dist[i] << endl;
	}

	cout << "���ĵ� ����\n";
	for (int i = 0; i < 5; i++) {
		cout << S[i] << " ";
	}
	cout << endl;
}


// �ּ� �Ÿ��� ������ ������ ��ȯ
int Extract_Min(int num) {
	int min;

	// ó������ Ȯ���� �ϸ鼭 �迭�� ���� ��Һ��� ������ �Ѵ�.
	for (int i = 0; i <num; i++) {
		if (check_path[i] != 1) {
			min = i;
			break;
		}
	}

	// �������� ���� �� �� �� �ּ� ���� ã�´�.
	for (int i = 0; i < num; i++) {
		if (check_path[i] != 1 && dist[i] < dist[min]) {
			min = i;
		}
	}

	return min;
}

void Dijkstra(int s, int Q) {
	int u, v, S_index=0;

	// ó���� ��� �Ÿ��� ���Ѵ�� �����Ѵ�.
	for (u = 0; u < Q; u++) {
		dist[u] = Infinity;
	}

	dist[s] = 0;	// ��������� 0���� �����Ѵ�.

	for (int i = 0; i < Q; i++) {	// Q�� �迭�� �������� �� ������ ����.
		u = Extract_Min(Q);	// �ּ� ���� �����´�.
		check_path[u] = 1;	// ������ ��� üũ
		S[S_index++] = u;

		// ���Ѵ��̹Ƿ� Ȯ���� �ʿ䰡 ����
		if (dist[u] == Infinity) {
			return;
		}

		for (v = 0; v<Q; v++) {	// v�� ���ؼ� ���������� ����.
			// v�� Q�迭�ȿ� �ְ� ��������� �Ÿ����� key���� �� ũ�� ������尡 ����Ǿ����� ���
			if (check_path[v] != 1 && dist[v] > dist[u] + Adj[u][v] && Adj[u][v] != Infinity) {
				dist[v] = dist[u] + Adj[u][v];		// Decrease-Key
			}
		}

	}
}