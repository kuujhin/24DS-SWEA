#include <iostream>
#include <queue>
#include <vector>

using namespace std;

vector<vector<pair<int, long long>>> G(1000, vector<pair<int, long long>>());

const long long INFS = 999999999999999999;

int N;
double E;

double prim()
{
    priority_queue<pair<long long, int>, vector<pair<long long, int>>, greater<pair<long long, int>>> pq;

    vector<long long> key(N, INFS);
    vector<int> parent(N, -1);
    vector<bool> inMST(N, false);

    pq.push({0, 0});
    key[0] = 0;

    while (!pq.empty())
    {
        int u = pq.top().second;
        pq.pop();

        if (inMST[u])
            continue;
        inMST[u] = true;

        for (int i = 0; i < G[u].size(); ++i)
        {
            int v = G[u][i].first;
            long long weight = G[u][i].second;

            if (!inMST[v] && key[v] > weight)
            {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
    double res = 0;
    for (int i = 1; i < N; ++i)
    {
        res += E * key[i];
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
        cin >> N;

        vector<pair<long long, long long>> island(N);

        for (int j = 0; j < N; ++j)
            cin >> island[j].first;

        for (int j = 0; j < N; ++j)
            cin >> island[j].second;

        cin >> E;

        for (int j = 0; j < N - 1; ++j)
        {
            for (int k = j + 1; k < N; ++k)
            {
                long long w = (island[j].first - island[k].first) * (island[j].first - island[k].first) + (island[j].second - island[k].second) * (island[j].second - island[k].second);
                G[j].push_back({k, w});
                G[k].push_back({j, w});
            }
        }

        long long res = prim();

        cout << "#" << i << " " << res << endl;
    }

    return 0;
}