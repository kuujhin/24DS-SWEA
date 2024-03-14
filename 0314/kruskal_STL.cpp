#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int V, E;

// disjoint-set 정의
const int MAX_SIZE = 10;

int parent[MAX_SIZE] = { 0, };
int rnk[MAX_SIZE] = { 0, };

void make_set(int x) {
	parent[x] = x;
	rnk[x] = 0;
}

// path compresion이 적용된 find_set()
int find_set(int x) {
	if (x != parent[x])
		parent[x] = find_set(parent[x]);
	return parent[x];
}

void union_set(int x, int y) {
	x = find_set(x);
	y = find_set(y);

	if (rnk[x] > rnk[y])
		parent[y] = x;
	else {
		parent[x] = y;

		if (rnk[x] == rnk[y]) {
			rnk[y]++;
		}
	}
}


const int EDGE_SIZE = 20;
const int INFS = 999;

vector<pair<int, pair<int, int>>> edge(EDGE_SIZE);

// O(V^2)
int kruskal_STL(int s) {
	// make_set()
	for (int i = 1; i <= V; ++i) {
		parent[i] = i;
		rnk[i] = 0;
	}

	sort(edge.begin(), edge.end());

	int mst_weight = 0;

	for (auto it = edge.begin(); it != edge.end(); it++) {
		int w = it->first;
		int u = it->second.first;
		int v = it->second.second;

		if (find_set(u) != find_set(v)) {
			union_set(u, v);
			mst_weight += w;

			printf("%d - %d : %d\n", u, v, w);
		}
	}
	return mst_weight;
}

int main() {
	freopen("kruskal_input.txt", "r", stdin);

	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		int s, e, w;
		cin >> s >> e >> w;
		edge.push_back({ w, {s,e} });
	}

	int edgeSum = kruskal_STL(0);

	cout << "간선의 합 : " << edgeSum << endl;
}