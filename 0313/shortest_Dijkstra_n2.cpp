#include <iostream>

using namespace std;

const int GRAPH_SZ = 10;
const int INFS = 99;

int G[GRAPH_SZ][GRAPH_SZ];
int D[GRAPH_SZ];
bool U[GRAPH_SZ];

int V;

int extractMin() {
	// 아직 선택되지 않은 정점 중에서 거리값이 최소인 정점의 번호를 반환한다.
	int minVertex = 0;
	int minDist = INFS;

	for (int v = 1; v <= V; ++v) {
		if (!U[v] && minDist > D[v]) {
			minVertex = v;
			minDist = D[v];
		}
	}
	return minVertex;
}


// O(V^2)
void shortest_Dijkstra_n2(int s) {
	U[s] = true;

	for (int v = 1; v <= V; ++v) {
		D[v] = G[s][v];
	}
	D[s] = 0;

	for (int i = 1; i < V; i++) {
		int w = extractMin();
		U[w] = true;

		for (int v = 1; v <= V; ++v) {
			if (G[w][v] != INFS && D[v] > D[w] + G[w][v]) {
				D[v] = D[w] + G[w][v];
			}
		}
	}
}

void printDistance(int n) {
	printf("\n");
	printf("vertext \t");
	for (int i = 1; i <= n; ++i) {
		printf("%3c", i + 'A' - 1);
	}
	printf("\n");

	printf("distance\t");
	for (int i = 1; i <= n; ++i) {
		printf("%3d", D[i]);
	}
	printf("\n");
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> V;

	for (int i = 1; i <= V; ++i) {
		for (int j = 1; j <= V; ++j) {
			cin >> G[i][j];

			if (i != j && G[i][j] == 0) {
				G[i][j] = INFS;
			}
		}
		D[i] = INFS;
		U[i] = false;
	}

	shortest_Dijkstra_n2(1);

	cout << "최단거리 : " << D[V] << endl;

	printDistance(V);

	return 0;
}