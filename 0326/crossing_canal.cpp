#include <iostream>
#include <vector>
#include <cstring>
#include <queue>

using namespace std;

vector<int> adj[300001];
int weight[300001];
vector<queue<int>> q(3);
long long w[3];
long long f[3];
long long fuel_root = 0;
// 중앙의 섬을 회의장으로 했을 때를 기준으로 세 방향으로 섬들이 뻗어나가는 모양
// 각 방향에 대해서 한칸 씩 회의장을 이동하였을 때 연료비의 변화를 계산
// 이때 연로비의 변화는 다음과 같이 계산 가능
// 다른 두 방향의 연료비의 합 - 해당 방향 연료비 합 + 중앙 섬의 연료비 + 2 * 해당 방향으로 이동한 섬의 연료비의 합

void check_line(int cur, int parent, queue<int> &myq, long long &weight_sum)
{
    myq.push(parent);

    int count = 1;
    while (1)
    {
        weight_sum += weight[cur];
        fuel_root += weight[cur] * count++;

        int size = adj[cur].size();
        if (size == 1)
        {
            myq.push(cur);
            break;
        }
        int next = adj[cur][0];
        if (next == myq.back())
        {
            next = adj[cur][1];
        }
        myq.push(cur);
        cur = next;
    }
    myq.pop();
    return;
}

int main(int argc, char **argv)
{
    // freopen("test.txt", "r", stdin);

    int T, N, W;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N;

        // 인접리스트 생성
        memset(adj, 0, sizeof(adj));
        for (int i = 0; i < N - 1; ++i)
        {
            int x, y;
            cin >> x >> y;

            adj[x].push_back(y);
            adj[y].push_back(x);
        }

        // 각 노드의 가중치 입력
        // 루트 노드 찾기 (문제 조건에 의해 루트 노드에서 세 방향으로 나가는 모양만 가능)
        int root;
        memset(weight, 0, sizeof(weight));
        for (int i = 1; i <= N; ++i)
        {
            cin >> weight[i];

            int size = adj[i].size();
            if (size == 3)
            {
                root = i;
            }
        }

        fuel_root = 0;
        int w0 = weight[root];

        // 각 방향에 대하여 노드들을 순서대로 큐에 넣음
        // 해당 방향의 연료비 합과 루트 기준으로 총연료비를 계산
        check_line(adj[root][0], root, q[0], w[0]);
        check_line(adj[root][1], root, q[1], w[1]);
        check_line(adj[root][2], root, q[2], w[2]);

        // 루트 노드가 회의 장소일 때 총 연료비
        // int fuel_origin = f[0] + f[1] + f[2];
        int fuel_origin = fuel_root;

        int diff = w[0] + w[1] + w[2] + w0;

        int fuel_line[3];
        int diff_line[3];

        for (int i = 0; i < 3; ++i)
        {
            fuel_line[i] = fuel_origin;
            diff_line[i] = diff - 2 * w[i];

            while (diff_line[i] < 0)
            {
                cout << "fuel_line[" << i << "]: " << fuel_line[i] << endl;
                cout << "diff_line[" << i << "]: " << diff_line[i] << endl;
                fuel_line[i] += diff_line[i];
                diff_line[i] += 2 * (weight[q[i].front()]);
                q[i].pop();

                if (q[i].empty())
                    break;
            }
            while (!q[i].empty())
            {
                q[i].pop();
            }
        }

        cout << "fuel_origin: " << fuel_origin << endl;
        cout << "fuel_line[0]: " << fuel_line[0] << endl;
        cout << "fuel_line[1]: " << fuel_line[1] << endl;
        cout << "fuel_line[2]: " << fuel_line[2] << endl;

        int ans = min(fuel_line[0], min(fuel_line[1], fuel_line[2]));
        cout << "#" << t << " " << ans << endl;
    }

    return 0;
}