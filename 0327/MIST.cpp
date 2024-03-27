#include <iostream>
#include <vector>
#include <queue>

#define INFS 1111111111

using namespace std;

vector<int> weight(100001);
vector<int> parent(100001);
vector<bool> inMST(100001);

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);

    int T, N, M;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N >> M;

        // 인접 리스트 입력
        vector<pair<int, int>> adj[N + 1];
        for (int i = 0; i < M; ++i)
        {
            int start, end, cost;
            cin >> start >> end >> cost;
            adj[start].push_back({end, cost});
            adj[end].push_back({start, cost});
        }

        // Prim 알고리즘
        fill(weight.begin(), weight.end(), INFS);
        fill(parent.begin(), parent.end(), -1);
        fill(inMST.begin(), inMST.end(), false);
        priority_queue<pair<int, int>> pq;

        weight[1] = 0;
        pq.push({0, 1});

        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();

            if (inMST[u])
                continue;
            inMST[u] = true;

            for (auto v : adj[u])
            {
                int index = v.first;
                int cost = v.second;

                // 부모의 가중치도 체크
                if (!inMST[index] && weight[index] > cost && weight[u] <= cost)
                {
                    weight[index] = cost;
                    parent[index] = u;
                    pq.push({-weight[index], index});
                }
            }
        }

        // 결과 출력
        // MST가 아닌 경우 -1 출력
        long long sum = 0;
        for (int i = 2; i <= N; ++i)
        {
            if (inMST[i])
                sum += weight[i];
            else
            {
                sum = -1;
                break;
            }
        }

        cout << "#" << t << " " << sum << endl;
    }

    return 0;
}