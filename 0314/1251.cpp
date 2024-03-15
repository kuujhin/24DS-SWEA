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

int main(int argc, char **argv)
{

    freopen("1251.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        int N;
        cin >> N;


        vector<pair<long long, long long>> island(N + 1);
priority_queue<Edge, vector<Edge>, cmp> pq;



        for (int j = 1; j <= N; ++j)
            cin >> island[j].first;

        for (int j = 1; j <= N; ++j)
            cin >> island[j].second;

        cin >> E;
        V = 0;

        long long minDist = 0;
        int minIdx = 0;
        for (int j = 1; j <= N - 1; ++j)
        {
            for (int k = j + 1; k <= N; ++k)
            {
                long long w = (island[j].first - island[k].first) * (island[j].first - island[k].first) + (island[j].second - island[k].second) * (island[j].second - island[k].second);
                pq.push({j, k, w});
                V++;
                // if (i == 10)
                //     cout << "pushed: " << j << " " << k << " " << w << endl;
            }
        }

        long long res = 0;

        for (int x = 1; x <= V; ++x)
        {
            parent[x] = x;
            rnk[x] = 0;
        }

        while (!pq.empty())
        {
            Edge edge = pq.top();
            if (i == 10)
                cout << "pq.top(): " << edge.s << " " << edge.e << " " << edge.w << endl;
            pq.pop();

            if (find_set(edge.s) != find_set(edge.e))
            {
                union_set(edge.s, edge.e);
                res += edge.w;
                // cout << "w: " << edge.w << " E*w: " << E * edge.w << " res: " << res << endl;
            }
        }

        res = E * res + 0.5;

        cout << "#" << i << " " << res << endl;
    }

    return 0;
}