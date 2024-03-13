#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int INFS = 9999;

int dy[4] = {0, 0, 1, -1};
int dx[4] = {1, -1, 0, 0};

int main(int argc, char **argv)
{

    // freopen("1249.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n;
        cin >> n;

        vector<vector<int>> weightMap(n + 2, vector<int>(n + 2, INFS));
        vector<vector<int>> distanceMap(n + 2, vector<int>(n + 2, INFS));

        for (int j = 1; j <= n; ++j)
        {
            for (int k = 1; k <= n; ++k)
            {
                scanf("%1d", &weightMap[j][k]);
            }
        }

        priority_queue<pair<int, pair<int, int>>> pq;

        pq.emplace(make_pair(0, make_pair(1, 1)));
        distanceMap[1][1] = 0;

        int result;

        while (!pq.empty())
        {
            int curDist = -pq.top().first;
            int curNodeY = pq.top().second.first;
            int curNodeX = pq.top().second.second;

            if (curNodeY == n && curNodeX == n)
            {
                result = curDist;
                break;
            }
            pq.pop();

            if (curDist < distanceMap[curNodeY][curNodeX])
                continue;

            for (int j = 0; j < 4; ++j)
            {
                int nextNodeY = curNodeY + dy[j];
                int nextNodeX = curNodeX + dx[j];
                int nextDist = curDist + weightMap[nextNodeY][nextNodeX];

                if (distanceMap[nextNodeY][nextNodeX] > nextDist)
                {
                    distanceMap[nextNodeY][nextNodeX] = nextDist;

                    pq.push({-nextDist, {nextNodeY, nextNodeX}});
                }
            }
        }

        cout << "#" << i << " " << result << endl;
    }

    return 0;
}