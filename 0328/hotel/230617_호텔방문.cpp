// *** main.cpp ***
#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

void init(int N, int mBrands[]);
void connect(int mHotelA, int mHotelB, int mDistance);
int merge(int mHotelA, int mHotelB);
int move(int mStart, int mBrandA, int mBrandB);

#define MAX_N 5000

#define CMD_INIT 100
#define CMD_CONNECT 200
#define CMD_MERGE 300
#define CMD_MOVE 400

static bool run()
{
	int query_num;
	scanf("%d", &query_num);

	int ans;
	bool ok = false;

	for (int q = 0; q < query_num; q++)
	{
		int query;
		scanf("%d", &query);
		if (query == CMD_INIT)
		{
			int N;
			int mBrands[MAX_N];
			scanf("%d", &N);
			for (int i = 0; i < N; i++) {
				scanf("%d", &mBrands[i]);
			}
			init(N, mBrands);
			ok = true;
		}
		else if (query == CMD_CONNECT)
		{
			int mHotelA, mHotelB, mDistance;
			scanf("%d %d %d", &mHotelA, &mHotelB, &mDistance);
			connect(mHotelA, mHotelB, mDistance);
		}
		else if (query == CMD_MERGE)
		{
			int mHotelA, mHotelB;
			scanf("%d %d", &mHotelA, &mHotelB);
			int ret = merge(mHotelA, mHotelB);
			scanf("%d", &ans);
			if (ans != ret)
			{
				ok = false;
			}
		}
		else if (query == CMD_MOVE)
		{
			int mStart, mBrandA, mBrandB;
			scanf("%d %d %d", &mStart, &mBrandA, &mBrandB);
			int ret = move(mStart, mBrandA, mBrandB);
			scanf("%d", &ans);
			if (ans != ret)
			{
				ok = false;
			}
		}
	}
	return ok;
}

int main()
{
	setbuf(stdout, NULL);
	freopen("input.txt", "r", stdin);
	int T, MARK;
	scanf("%d %d", &T, &MARK);

	for (int tc = 1; tc <= T; tc++)
	{
		int score = run() ? MARK : 0;
		printf("#%d %d\n", tc, score);
	}
	return 0;
}


// *** user.cpp ***
#include <vector>
#include <queue>
#include <map>

#define INF 0x7fffffff

using namespace std;

typedef pair<int, int> pii;
//using pii = pair<int, int>;

vector<int> areaBrand;
map<int, int> brandCnt;
vector<vector<pii>> g;
int n;

void init(int N, int mBrands[]) {
	areaBrand.clear();
	brandCnt.clear();
	g.clear();
	areaBrand.resize(N);
	g.resize(N);

	n = N; // 현재 TC의 호텔(지역)수
	for (int i = 0; i < N; ++i) {
		areaBrand[i] = mBrands[i];
		brandCnt[mBrands[i]]++;
	}
}

void connect(int mHotelA, int mHotelB, int mDistance) {
	g[mHotelA].emplace_back(mDistance, mHotelB);
	g[mHotelB].emplace_back(mDistance, mHotelA);
}

int merge(int mHotelA, int mHotelB) {
	int brandA = areaBrand[mHotelA];
	int brandB = areaBrand[mHotelB];

	if (brandA == brandB) {
		return brandCnt[brandA];
	}

	for (int i = 0; i < n; ++i) {
		if (areaBrand[i] == brandB) {
			areaBrand[i] = brandA;
		}
	}

	brandCnt[brandA] += brandCnt[brandB];
	brandCnt[brandB] = 0;

	return brandCnt[brandA];
}

int move(int mStart, int mBrandA, int mBrandB) {

	int ans = 0;
	int chkA = 0, chkB = 0;

	priority_queue<pii, vector<pii>, greater<pii>> pq;
	vector<int> dists(n, INF);
	vector<int> visited(n, 1);

	dists[mStart] = 0;
	pq.emplace(0, mStart);

	while (!pq.empty()) {
		int dist = pq.top().first;
		int area = pq.top().second;
		pq.pop();

		if (!visited[area]) continue;
		int brand = areaBrand[area];

		if (dist) {
			if (brand == mBrandA) {
				ans += dist;
				mBrandA = -1;
			}
			else if (brand == mBrandB) {
				ans += dist;
				mBrandB = -1;
			}
			if (mBrandA + mBrandB == -2) {
				break;
			}
		}
		visited[area] = 0;
		for (auto& t : g[area]) {
			int w = t.first, v = t.second;
			if (visited[v] && dists[v] > dist + w) {
				dists[v] = dist + w;
				pq.emplace(dists[v], v);
			}
		}
	}

	return ans;
}
