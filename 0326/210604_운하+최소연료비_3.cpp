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

// start end�� ���� Edge�� ǥ���Ѵ�. Edge�� �������� Ʈ���� left, right�� ������ �����Ѵ�.
// leftWeight�� leftƮ�� ������ W���� ���̰�, leftTotal�� Ʈ�� depth���� ����� left Ʈ���� �� weight���� ���̴�. right�� ���ؼ��� ����.
void getMinDist(int start, int end, long long leftWeight, long long leftTotal, long long rightWeight, long long rightTotal)
{
	// left ����Ƽ������ end ��尡 ������.
	leftTotal -= leftWeight;
	leftWeight -= W[end];
	// right ����Ʈ������ start ��尡 �߰��ȴ�.
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

		// root�� ã�´�.
		for (int i = 1; i <= N; i++) {
			if (adj[i].size() == 3) {
				root = i;
				break;
			}
		}
		visited[root] = true;

		// root�� 3���� ���� ����Ǿ������Ƿ� root�� �������� 3���� ���� Ʈ���� ������ �� �ִ�.
		// �� ���� Ʈ���� Ž���ϸ� �ش� Ʈ���� weightSum�� v[i].first�� totalSum�� v[i].second�� �����Ѵ�.
		for (int i = 0; i < 3; i++) {
			visited[adj[root][i]] = true;
			getWeight(adj[root][i], v[i].first, v[i].second, 1);
		}

		answer = v[0].second + v[1].second + v[2].second;
		// root�� ����� 3���� ������ ���� �̵��ϸ鼭 �� ������ �������� Ʈ���� left�� right�� ������.
		// root�� ������ ��� ���� �̾��� ������ 2�� �̹Ƿ� getMinDist�� ���� �ϳ��� �������� �̵��� �� �ִ�.
		getMinDist(root, adj[root][0], v[0].first, v[0].second, v[1].first + v[2].first, v[1].second + v[2].second);
		getMinDist(root, adj[root][1], v[1].first, v[1].second, v[2].first + v[0].first, v[2].second + v[0].second);
		getMinDist(root, adj[root][2], v[2].first, v[2].second, v[0].first + v[1].first, v[0].second + v[1].second);

		printf("#%d %lld\n", testCase, answer);
	}
	return 0;
}
