#include <iostream>

using namespace std;

int V, E;

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
	int select;
} edge[EDGE_SIZE];

// O(V^2)
int kruskal(int s) {
	// make_set()
	for (int i = 1; i <= V; ++i) {
		parent[i] = i;
		rnk[i] = 0;
	}

	// asc sort : 이미 정렬된 데이터이므로 생략

	int selected = 0;
	int idx = 0;

	while (selected < V - 1) {
		int u = edge[idx].s;
		int v = edge[idx].e;
		int w = edge[idx].w;

		if (find_set(u) != find_set(v)) {
			edge[idx].select = 1;
			union_set(u, v);
			selected++;
		}
		idx++;
	}

	// MST에 포함된 간선의 가중치의 합
	int sum = 0;
	for (int i = 0; i < E; ++i) {
		if (edge[i].select == 1) {
			sum += edge[i].w;
			printf("%d - %d : %d\n", edge[i].s, edge[i].e, edge[i].w);
		}
	}

	return sum;
}

int main() {
	freopen("kruskal_input.txt", "r", stdin);

	cin >> V >> E;

	for (int i = 0; i < E; i++) {
		cin >> edge[i].s >> edge[i].e >> edge[i].w;
		edge[i].select = 0;
	}

	int edgeSum = kruskal(0);

	cout << "간선의 합 : " << edgeSum << endl;
}