#include <iostream>
#include <cstring>
#include <deque>

#define MAX 1001
#define MAX_DEGREE int(1001 * 0.55)

using namespace std;

typedef pair<int, int> pairInt;

int adjLst[MAX][MAX_DEGREE] = {
    0,
};
int visit[MAX];
int degree[MAX];

int main(int argc, char **argv)
{

    cin.tie(0);
    cin.sync_with_stdio(0);

    deque<pairInt> deq;

    int T, N;
    cin >> T;

    for (int tc = 1; tc <= T; ++tc)
    {
        cin >> N;

        int dist_sum = 987654321;
        memset(degree, 0, sizeof degree);
        memset(visit, 0, sizeof visit);

        for (int i = 1; i <= N; ++i)
        {
            for (int j = 1; j <= N; ++j)
            {
                int n;
                cin >> n;
                if (n)
                    adjLst[i][degree[i]++] = j;
            }
        }

        for (int i = 1; i <= N; ++i)
        {

            deq = {};
            deq.push_back(pairInt(i, 0));
            visit[i] = i;

            int count = N;
            int cc = 0;
            while (!deq.empty())
            {
                int v = deq.front().first;
                int dist = deq.front().second;
                deq.pop_front();

                cc += dist;

                // for early break
                if ((--count) == 0)
                    break;

                for (int j = 0; j < degree[v]; ++j)
                {
                    int node = adjLst[v][j];
                    if (visit[node] != i)
                    {
                        visit[node] = i;
                        deq.push_back(pairInt(node, dist + 1));
                    }
                }
            }
            if (dist_sum > cc)
            {
                dist_sum = cc;
            }
        }

        cout << '#' << tc << ' ' << dist_sum << '\n';
    }
    return 0;
}
