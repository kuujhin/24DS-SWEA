#pragma warning(disable:4996)

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_N 100001

using namespace std;

using ll = long long;
using lipair = pair<ll, int>;


ll d[MAX_N];
bool visit[MAX_N];
vector<vector<lipair> > g(MAX_N);

priority_queue<lipair, vector<lipair>, greater<lipair>> pq;

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);

	freopen("input.txt", "r", stdin);

	int T;
	scanf("%d", &T);


	for (int tc = 1; tc <= T; tc++) {
		int N, M;
		scanf("%d %d", &N, &M);

		memset(d, 0x7f, sizeof d); // 0x7f7f7f7f
		memset(visit, 0, sizeof visit);
		

		for (int i = 1; i <= N; ++i) {
			g[i].clear();
		}

		for (int j = 0; j < M; j++) {
			int s, e;	ll c;
			scanf("%d %d %lld", &s, &e, &c);

			g[s].emplace_back(make_pair( c, e ));
			g[e].emplace_back(make_pair( c, s ));
		}

		d[1] = 0;
		pq.push(make_pair(0, 1));

		ll sum = 0;
		//ll prevWeight = -1;
		int mst = N;
		while (!pq.empty()) {	
			int w = pq.top().second;
			pq.pop();

			if (visit[w]) continue;

			visit[w] = true;
			//prevWeight = d[w];
			sum += d[w];
			--mst;

			for (auto& p : g[w]) {
				int v = p.second;
				ll weight = p.first;
				if (!visit[v] &&
					weight >= d[w] &&			// 부모노드 보다 크거나 같아야 함
					weight < d[v]) 
				{
					d[v] = weight;
					pq.push(p);
				}
			}
		}
		printf("#%d %lld \n", tc, (mst == 0) ? sum : -1);
	}

	return 0;
}