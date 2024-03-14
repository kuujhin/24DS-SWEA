#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int V, E;
vector<int> parent;
vector<int> rnk;
priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>> pq;

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
    for (int i = 0; i < V; ++i)
    {
        parent[i] = i;
        rnk[i] = 0;
    }
    long long res = 0;

    while (!pq.empty())
    {
        int w = pq.top().first * (-1);
        int s = pq.top().second.first;
        int e = pq.top().second.second;
        pq.pop();

        if (find_set(s) != find_set(e))
        {
            union_set(s, e);
            res += w;
        }
    }
    return res;
}
int main(int argc, char **argv)
{

    freopen("3124.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> V >> E;

        parent.resize(V + 1);
        rnk.resize(V + 1);

        for (int j = 0; j < E; ++j)
        {
            int s, e, w;
            cin >> s >> e >> w;

            pq.push({w * (-1), {s, e}});
        }

        long long res = kruskal();

        cout << "#" << i << " " << res << endl;
    }

    return 0;
}