#include <stdio.h>

#define MAX_N 1400
#define CMD_INIT 1
#define CMD_ADD 2
#define CMD_COST 3

int init(int N, int sCity[], int eCity[], int mCost[]);
void add(int sCity, int eCity, int mCost);
int cost(int mHub);

static bool run()
{
    int q;
    scanf("%d", &q);
    int n;
    int sCityArr[MAX_N], eCityArr[MAX_N], mCostArr[MAX_N];
    int sCity, eCity, mCost, mHub;
    int cmd, ans, ret = 0;
    bool okay = false;
    for (int i = 0; i < q; ++i)
    {
        scanf("%d", &cmd);
        switch (cmd)
        {
        case CMD_INIT:
            okay = true;
            scanf("%d", &n);
            for (int j = 0; j < n; ++j)
            {
                scanf("%d %d %d", &sCityArr[j], &eCityArr[j], &mCostArr[j]);
            }
            scanf("%d", &ans);
            ret = init(n, sCityArr, eCityArr, mCostArr);
            if (ans != ret)
                okay = false;
            break;
        case CMD_ADD:
            scanf("%d %d %d", &sCity, &eCity, &mCost);
            add(sCity, eCity, mCost);
            break;
        case CMD_COST:
            scanf("%d %d", &mHub, &ans);
            ret = cost(mHub);
            if (ans != ret)
                okay = false;
            break;
        default:
            okay = false;
            break;
        }
    }
    return okay;
}
int main()
{
    setbuf(stdout, NULL);
    // freopen("input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }
    return 0;
}

////////////////////////////////////////////////
///////////// User Code ////////////////////////
////////////////////////////////////////////////
#include <vector>
#include <queue>
#include <cstring>

#define MAX_CITY 600

using namespace std;

// 인접 리스트
vector<pair<int, int>> adj[MAX_CITY];
// 입력순으로 도시 번호 저장
int city_index[MAX_CITY];
// 총 도시 개수
int nums;

// 도시간 거리 저장 테이블(dijkstra)
int city_dist[MAX_CITY][MAX_CITY];

int init(int N, int sCity[], int eCity[], int mCost[])
{
    // 인접 리스트, 총 도시 개수, 도시간 거리 테이블 초기화
    for (int i = 0; i < MAX_CITY; i++)
        adj[i].clear();
    int city_count = 0;
    memset(city_dist, -1, sizeof(city_dist));

    // 입력 순으로 도시 번호 저장
    // 이미 입력된 도시 번호인지 확인
    for (int i = 0; i < N; i++)
    {
        bool start_city_exist = false;
        bool end_city_exist = false;

        int start_city;
        int end_city;

        for (int j = 0; j < city_count; j++)
        {
            if (city_index[j] == sCity[i])
            {
                start_city_exist = true;
                start_city = j;
            }
            if (city_index[j] == eCity[i])
            {
                end_city_exist = true;
                end_city = j;
            }
            if (start_city_exist && end_city_exist)
                break;
        }

        if (!start_city_exist)
        {
            start_city = city_count;
            city_index[start_city] = sCity[i];
            city_count++;
        }
        if (!end_city_exist)
        {
            end_city = city_count;
            city_index[end_city] = eCity[i];
            city_count++;
        }

        adj[start_city].push_back({end_city, mCost[i]});
    }

    nums = city_count;

    return nums;
}

void add(int sCity, int eCity, int mCost)
{
    // 시작 도시번호와 끝 도시번호의 인덱스 찾아 인접리스트에 추가
    // 길이 추가가 되었으므로 도시간 거리 테이블 초기화
    int start_city;
    int end_city;
    for (int i = 0; i < nums; i++)
    {
        if (city_index[i] == sCity)
            start_city = i;
        if (city_index[i] == eCity)
            end_city = i;
    }

    adj[start_city].push_back({end_city, mCost});

    memset(city_dist, -1, sizeof(city_dist));

    return;
}

// 다익스트라 알고리즘
// 시작점에서 모든 지점까지의 최단거리 계산 후 테이블에 저장
// 도착지점까지의 최단거리 반환
int dijkstra(int start, int end)
{
    vector<int> dist(nums, 987654321);
    priority_queue<pair<int, int>> pq;

    dist[start] = 0;
    city_dist[start][start] = 0;
    pq.push({0, start});

    while (!pq.empty())
    {
        int cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[cur] < cost)
            continue;

        int size = adj[cur].size();
        for (int i = 0; i < size; i++)
        {
            int next = adj[cur][i].first;
            int nextDist = cost + adj[cur][i].second;

            if (dist[next] > nextDist)
            {
                dist[next] = nextDist;
                city_dist[start][next] = nextDist;
                pq.push({-nextDist, next});
            }
        }
    }

    return dist[end];
}

int cost(int mHub)
{
    // 허브 도시 인덱스 탐색
    int start = 0;
    for (int i = 0; i < nums; i++)
    {
        if (city_index[i] == mHub)
            start = i;
    }

    // 허브 도시 인덱스를 기준으로 모든 도시간 거리 계산
    // 이미 계산된 도시간 거리인 경우 테이블 참조
    // 허브 도시에서 모든 도시로 가는 거리의 합
    int forward_dist = 0;
    for (int i = 0; i < nums; i++)
    {
        if (city_dist[start][i] == -1)
        {
            city_dist[start][i] = dijkstra(start, i);
        }
        forward_dist += city_dist[start][i];
    }
    // 모든 도시에서 허브 도시로 오는 거리의 합
    int backward_dist = 0;
    for (int i = 0; i < nums; i++)
    {
        if (city_dist[i][start] == -1)
            city_dist[i][start] = dijkstra(i, start);
        backward_dist += city_dist[i][start];
    }

    return forward_dist + backward_dist;
}