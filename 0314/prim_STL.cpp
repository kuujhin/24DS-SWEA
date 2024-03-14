#include <iostream>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

const int GRAPH_SIZE = 10;
const int INFS = 999;

int V; 

vector<vector<pair<int, int>>> G(GRAPH_SIZE, vector<pair<int, int>>());

// O(ElogV)
int prim(int s) {
	priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
	vector<int> key(V, INFS);
	vector<int> parent(V, -1);
	vector<bool> inMST(V, false);


	pq.push({ 0, s });
	key[s] = 0;

	while (!pq.empty()) {
		int u = pq.top().second; 
		pq.pop();
		
		if (inMST[u]) continue;
		inMST[u] = true;

		for (int i = 0; i < G[u].size(); ++i) {
			int v = G[u][i].first;
			int weight = G[u][i].second;

			if (!inMST[v] && key[v] > weight) {
				key[v] = weight;
				parent[v] = u;
				pq.push({ key[v], v });
			}
		}
 	}

	// MST에 포함된 간선의 가중치의 합
	int sum = 0;
	for (int i = 1; i < V; ++i) {
		sum += key[i];
		printf("%d - %d : %d\n", parent[i], i, key[i]);
	}

	return sum;
}

int main() {
	freopen("prim_input.txt", "r", stdin);

	cin >> V;

	for (int i = 0; i < V; ++i) {
		for (int j = 0; j < V; ++j) {
			int weight;
			cin >> weight;

			if (i != j && weight > 0) {
				G[i].push_back({ j, weight });
			}
		}
	}

	int edgeSum = prim(0);

	cout << "간선의 합 : " << edgeSum << endl;
}