#include <cstdio>

#include <vector>
#include <algorithm>

using namespace std;

long long answer;
vector<vector<int>> adj;
vector<long long> W;
vector<bool> visited;
vector<pair<long long, long long>> v;

void getWeight(int now, long long &weightSum, long long &totalSum, long long depth)
{
	weightSum += W[now];
	totalSum += W[now] * depth;

	for (int i = 0; i < adj[now].size(); i++) {
		if (!visited[adj[now][i]]) {
			visited[adj[now][i]] = true;
			getWeight(adj[now][i], weightSum, totalSum, depth + 1);
		}
	}
}

// start end를 통해 Edge를 표현한다. Edge를 기준으로 트리를 left, right로 나누어 생각한다.
// leftWeight는 left트리 노드들의 W값의 합이고, leftTotal은 트리 depth까지 고려한 left 트리의 총 weight값의 합이다. right에 대해서도 같다.
void getMinDist(int start, int end, long long leftWeight, long long leftTotal, long long rightWeight, long long rightTotal)
{
	// left 서브티리에는 end 노드가 빠진다.
	leftTotal -= leftWeight;
	leftWeight -= W[end];
	// right 서브트리에는 start 노드가 추가된다.
	rightWeight += W[start];
	rightTotal += rightWeight;

	answer = min(answer, leftTotal + rightTotal);

	for (int i = 0; i < adj[end].size(); i++) {
		int next = adj[end][i];
		if (next != start) {
			getMinDist(end, next, leftWeight, leftTotal, rightWeight, rightTotal);
		}
	}
}

int main() {

	freopen("input.txt", "r", stdin);

	int T, N, a, b, root;
	scanf("%d", &T);

	for (int testCase = 1; testCase <= T; testCase++) {
		scanf("%d", &N);
		adj.assign(N + 1, vector<int>(0, 0));
		visited.assign(N + 1, false);
		W.assign(N + 1, 0);
		v.assign(3, { 0, 0 });

		for (int i = 0; i < N - 1; i++) {
			scanf("%d %d", &a, &b);
			adj[a].push_back(b);
			adj[b].push_back(a);
		}
		for (int i = 1; i <= N; i++) {
			scanf("%lld", &W[i]);
		}

		// root를 찾는다.
		for (int i = 1; i <= N; i++) {
			if (adj[i].size() == 3) {
				root = i;
				break;
			}
		}
		visited[root] = true;

		// root는 3개의 점과 연결되어있으므로 root를 기준으로 3개의 서브 트리를 구상할 수 있다.
		// 각 서브 트리를 탐색하며 해당 트리의 weightSum을 v[i].first에 totalSum을 v[i].second에 저장한다.
		for (int i = 0; i < 3; i++) {
			visited[adj[root][i]] = true;
			getWeight(adj[root][i], v[i].first, v[i].second, 1);
		}

		answer = v[0].second + v[1].second + v[2].second;
		// root와 연결된 3개의 간선을 따라 이동하면서 그 간선을 기준으로 트리를 left와 right로 나눈다.
		// root를 제외한 모든 노드는 이어진 간선이 2개 이므로 getMinDist를 따라 하나의 방향으로 이동할 수 있다.
		getMinDist(root, adj[root][0], v[0].first, v[0].second, v[1].first + v[2].first, v[1].second + v[2].second);
		getMinDist(root, adj[root][1], v[1].first, v[1].second, v[2].first + v[0].first, v[2].second + v[0].second);
		getMinDist(root, adj[root][2], v[2].first, v[2].second, v[0].first + v[1].first, v[0].second + v[1].second);

		printf("#%d %lld\n", testCase, answer);
	}
	return 0;
}
