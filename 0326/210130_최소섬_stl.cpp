#include <iostream>
#include <vector>
#include <map>
#include <queue>

using namespace std;

int main() {
	freopen("input.txt", "r", stdin);

	int TC;
	scanf("%d", &TC);

	for (int tc = 1; tc <= TC; tc++) {
		int N, M, K;
		int sn, en;
		long long val;
		scanf("%d %d %d", &N, &M, &K);

		//전체 간선도
		vector< map<int, long long> > g(N + 1);

		//섬의 보급 식량
		map<int, long long> food;

		vector<long long> distance(N + 1, 1000000 * 10001LL);

		//입력시 반대로 받음
		vector<bool> visited(N + 1, false);
		for (int i = 0; i < M; i++) {
			scanf("%d %d %lld", &sn, &en, &val);
			g[en].emplace(sn, val);
		}

		for (int i = 0; i < K; i++) {
			scanf("%d %lld", &en, &val);
			food.emplace(en, val);
		}

		priority_queue<pair<long long, int>, vector<pair<long long, int> >, greater<pair<long long, int> > > pq;

		//N번  출발
		pq.emplace(0, N);
		distance[N] = 0;

		int u, v, e;
		while (!pq.empty()) {
			u = pq.top().second;
			pq.pop();

			if (visited[u]) {
				continue;
			}
			if (u == 1) {
				break;
			}

			visited[u] = true;
			for (auto& t : g[u]) {
				long long nextDistance = distance[u] + t.second - food[t.first];
				if (!visited[t.first] && distance[t.first] > nextDistance) {
					distance[t.first] = nextDistance;
					if (distance[t.first] < 0) {
						distance[t.first] = 0;
					}
					pq.emplace(distance[t.first], t.first);
				}
			}
		}
		printf("#%d %lld\n", tc, distance[1]);
	}
	return 0;
}
