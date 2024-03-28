#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define INFS 987654321

using namespace std;

int T, S, C;
int pos[3][2];
int map[502][502] = {-1};

int di[4] = {0, 0, 1, -1};
int dj[4] = {1, -1, 0, 0};

pair<int, int> parent[502][502];

// Dijsktra Algorithm + parent 저장
int dijkstra(int starti, int startj, int endi, int endj, bool flag = false)
{
    vector<vector<int>> dist(S + 1, vector<int>(C + 1, INFS));
    dist[starti][startj] = 0;
    priority_queue<pair<int, pair<int, int>>> pq;
    pq.push({0, {starti, startj}});

    if (flag)
    {
        memset(parent, 0, sizeof(parent));
        parent[starti][startj] = {0, 0};
    }

    while (!pq.empty())
    {
        int curi = pq.top().second.first;
        int curj = pq.top().second.second;
        int curDist = -pq.top().first;
        pq.pop();

        if (curi == endi && curj == endj)
            return curDist;

        if (dist[curi][curj] < curDist)
            continue;

        for (int i = 0; i < 4; ++i)
        {
            int nexti = curi + di[i];
            int nextj = curj + dj[i];

            if (map[nexti][nextj] == -1)
                continue;

            int nextDist = curDist + map[curi][curj];
            if (dist[nexti][nextj] > nextDist)
            {
                dist[nexti][nextj] = nextDist;
                pq.push({-dist[nexti][nextj], {nexti, nextj}});
                if (flag)
                    parent[nexti][nextj] = {curi, curj};
            }
        }
    }
    return -1;
}

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);

    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> S >> C;

        for (int i = 0; i < 3; ++i)
        {
            cin >> pos[i][0] >> pos[i][1];
        }

        memset(map, -1, sizeof(map));
        for (int i = 1; i <= S; ++i)
        {
            for (int j = 1; j <= C; ++j)
            {
                cin >> map[i][j];
            }
        }

        // 따로 가는 경우
        int min_dist = dijkstra(pos[0][0], pos[0][1], pos[2][0], pos[2][1]);
        min_dist += dijkstra(pos[1][0], pos[1][1], pos[2][0], pos[2][1]);

        // 만나서 가는 경우
        // Dijsktra 2번 사용
        int dist = dijkstra(pos[0][0], pos[0][1], pos[1][0], pos[1][1], true);

        pair<int, int> parent_pos = parent[pos[1][0]][pos[1][1]];

        // 만나러 온 길의 비용 제거
        while (parent_pos != make_pair(0, 0))
        {
            map[parent_pos.first][parent_pos.second] = 0;
            parent_pos = parent[parent_pos.first][parent_pos.second];
        }

        dist += dijkstra(pos[1][0], pos[1][1], pos[2][0], pos[2][1]);
        if (min_dist > dist)
            min_dist = dist;

        cout << "#" << t << " " << min_dist << endl;
    }

    return 0;
}