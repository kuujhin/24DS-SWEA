#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int GRAPH_SZ = 10;
const int INFS = 99;			// INF, INFINITE, INFINTY, INT_MAX(2^31 -1) : 사용하면 안됨.!\

vector<vector<int>> G(GRAPH_SZ, vector<int>(GRAPH_SZ, 0));
vector<int> D(GRAPH_SZ, INFS);

int V;

void shortest_BFS_STL(int s) {
	queue<int> q;

	q.push(s);
	D[s] = 0;

	while (!q.empty()) {		
		int v = q.front(); q.pop();

		for (int w = 1; w <= V; ++w) {
			if (G[v][w] && D[w] > D[v] + G[v][w]) {
				D[w] = D[v] + G[v][w];

				q.push(w);
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
		}
	}

	shortest_BFS_STL(1);

	cout << "최단거리 : " << D[V] << endl;

	printDistance(V);

	return 0;
}