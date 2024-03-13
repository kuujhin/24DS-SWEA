#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int GRAPH_SZ = 10;
const int INFS = 99;

vector<vector<pair<int, int>>> G(GRAPH_SZ, vector<pair<int, int>>());	// 인접리스트
vector<int> dist(GRAPH_SZ, INFS);
vector<int> path(GRAPH_SZ, 0);

int V;

void shortest_Dijkstra_STL(int s) {	
	priority_queue<pair<int, int>> pq;

	pq.emplace(make_pair(0, s));
	dist[s] = 0;

	while (!pq.empty()) {
		int cur_dist = -pq.top().first;
		int cur_node = pq.top().second;
		pq.pop();

		if (cur_dist < dist[cur_node]) continue;

		for (int i = 0; i < G[cur_node].size(); ++i) {
			int next_node = G[cur_node][i].first;
			int next_dist = cur_dist + G[cur_node][i].second;

			if (dist[next_node] > next_dist) {
				dist[next_node] = next_dist;

				pq.push({ -next_dist, next_node });
				path[next_node] = cur_node;
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
		printf("%3d", dist[i]);
	}
	printf("\n");
}


void printPath(int v) {
	if (v == 0) return;
	printPath(path[v]);
	printf("%3c", v + 'A' - 1);
}

int main() {
	freopen("input.txt", "r", stdin);

	cin >> V;

	for (int i = 1; i <= V; ++i) {
		for (int j = 1; j <= V; ++j) {
			int weight;
			cin >> weight;

			if (i != j && weight > 0) {		// 인접행렬 --> 인접리스트 변환
				G[i].emplace_back(make_pair(j, weight));
			}
		}
	}

	shortest_Dijkstra_STL(1);

	cout << "최단거리 : " << dist[V] << endl;

	printDistance(V);

	cout << "최단경로 : \t";
	printPath(V);
	cout << endl;

	return 0;
}