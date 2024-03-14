#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Edge
{
    int s, e;
    long long w;
};

struct cmp
{
    bool operator()(Edge e1, Edge e2)
    {
        return e1.w > e2.w;
    }
};

long long V;
double E;
int parent[1000];
int rnk[1000];

// vector<int> parent;
// vector<int> rnk;
priority_queue<Edge, vector<Edge>, cmp> pq;

int find_set(int x)
{
    if (x != parent[x])
        parent[x] = find_set(parent[x]);
    return parent[x];
}

void union_set(int x, int y)
{
    x = find_set(x);
    y = find_set(y);

    if (rnk[x] > rnk[y])
        parent[y] = x;
    else
    {
        parent[x] = y;

        if (rnk[x] == rnk[y])
        {
            rnk[y]++;
        }
    }
}

long long kruskal()
{
    double res = 0;

    for (int i = 1; i <= V; ++i)
    {
        parent[i] = i;
        rnk[i] = 0;
    }

    while (!pq.empty())
    {
        Edge edge = pq.top();

        pq.pop();

        if (find_set(edge.s) != find_set(edge.e))
        {
            union_set(edge.s, edge.e);
            res += E * edge.w;
            // cout << "w: " << edge.w << " E*w: " << E * edge.w << " res: " << res << endl;
        }
    }
    return res;
}
int main(int argc, char **argv)
{

    freopen("1251.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        int N;
        cin >> N;

        // cout << i << "번째 N: " << N << endl;

        vector<pair<long long, long long>> island(N);

        // parent.resize(N, 0);
        // rnk.resize(N, 0);

        for (int j = 0; j < N; ++j)
            cin >> island[j].first;

        for (int j = 0; j < N; ++j)
            cin >> island[j].second;

        cin >> E;
        V = 0;

        long long minDist = 0;
        int minIdx = 0;
        for (int j = 0; j < N - 1; ++j)
        {
            for (int k = j + 1; k < N; ++k)
            {
                long long w = (island[j].first - island[k].first) * (island[j].first - island[k].first) + (island[j].second - island[k].second) * (island[j].second - island[k].second);
                pq.push({j + 1, k + 1, minDist});
                V++;
            }
            // cout << "pushed: " << j + 1 << " " << k + 1 << " " << w << endl;
        }

        // cout << i << "번째 V: " << V << endl;

        long long res = kruskal();

        cout << "#" << i << " " << res << endl;
    }

    return 0;
}