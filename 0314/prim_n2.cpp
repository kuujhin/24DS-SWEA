#include <iostream>

const int GRAPH_SIZE = 10;
const int INFS = 999;

int V;

int G[GRAPH_SIZE][GRAPH_SIZE];

int parent[GRAPH_SIZE];
int weight[GRAPH_SIZE];
bool inQ[GRAPH_SIZE];

using namespace std;



int extractMin() {
	int minVertex = -1;
	int minWeight = INFS;

	for (int i = 0; i < V; ++i) {
		if (inQ[i] == true && minWeight > weight[i]) {
			minVertex = i;
			minWeight = weight[i];
		}
	}
	return minVertex;
}


// O(V^2)
int prim(int s) {
	for (int i = 0; i < V; ++i) {
		parent[i] = -1;
		weight[i] = INFS;
		inQ[i] = true;
	}

	weight[s] = 0;

	int vertext = V;
	while (vertext--) {
		int u = extractMin();
		inQ[u] = false;

		for (int v = 0; v < V; ++v) {
			if (inQ[v] == true && G[u][v] < weight[v])
			{
				parent[v] = u;
				weight[v] = G[u][v];
			}
		}
	}

	// MST에 포함된 간선의 가중치의 합
	int sum = 0;
	for (int i = 1; i < V; ++i) {
		sum += weight[i];
		printf("%d - %d : %d\n", parent[i], i, weight[i]);
	}

	return sum;
}

int main() {
	freopen("prim_input.txt", "r", stdin);

	cin >> V;

	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			cin >> G[i][j];

			if (i != j && G[i][j] == 0) {
				G[i][j] = INFS;
			}
		}
	}

	int edgeSum = prim(0);

	cout << "간선의 합 : " << edgeSum << endl;
}