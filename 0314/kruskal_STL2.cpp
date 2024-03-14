#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

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

struct Edge {
	int s, e, w;
};

struct cmp {
	bool operator()(Edge e1, Edge e2) {
		return e1.w > e2.w;
	}
};

priority_queue < Edge, vector<Edge>, cmp> pq;

// O(ElogV)
int kruskal_STL(int s) {
	// make_set()
	for (int i = 1; i <= V; ++i) {
		parent[i] = i;
		rnk[i] = 0;
	}

	int mst_weight = 0;

	while (!pq.empty()) {
		Edge edge = pq.top(); pq.pop();

		if (find_set(edge.s) != find_set(edge.e)) {
			union_set(edge.s, edge.e);
			mst_weight += edge.w;

			printf("%d - %d : %d\n", edge.s, edge.e, edge.w);
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

		pq.push({ s, e, w });
	}

	int edgeSum = kruskal_STL(0);

	cout << "간선의 합 : " << edgeSum << endl;
}