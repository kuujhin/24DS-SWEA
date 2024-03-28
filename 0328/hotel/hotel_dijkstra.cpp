#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <ctime>

#define MAX_N 5000
#define CMD_INIT 100
#define CMD_CONNECT 200
#define CMD_MERGE 300
#define CMD_MOVE 400

void init(int N, int mBrands[]);
void connect(int mHotelA, int mHotelB, int mDistance);
int merge(int mHotelA, int mHotelB);
int move(int mStart, int mBrandA, int mBrandB);

static bool run()
{
    int query_num;
    scanf("%d", &query_num);
    int ans;
    bool ok = false;
    for (int q = 0; q < query_num; q++)
    {
        int query;
        scanf("%d", &query);
        if (query == CMD_INIT)
        {
            int N;
            int mBrands[MAX_N];
            scanf("%d", &N);
            for (int i = 0; i < N; i++)
            {
                scanf("%d", &mBrands[i]);
            }
            init(N, mBrands);
            ok = true;
        }
        else if (query == CMD_CONNECT)
        {
            int mHotelA, mHotelB, mDistance;
            scanf("%d %d %d", &mHotelA, &mHotelB, &mDistance);
            connect(mHotelA, mHotelB, mDistance);
        }
        else if (query == CMD_MERGE)
        {
            int mHotelA, mHotelB;
            scanf("%d %d", &mHotelA, &mHotelB);
            int ret = merge(mHotelA, mHotelB);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
        else if (query == CMD_MOVE)
        {
            int mStart, mBrandA, mBrandB;
            scanf("%d %d %d", &mStart, &mBrandA, &mBrandB);
            int ret = move(mStart, mBrandA, mBrandB);
            scanf("%d", &ans);
            if (ans != ret)
            {
                ok = false;
            }
        }
    }
    return ok;
}

int main()
{
    clock_t start, finish;

    start = clock();

    setbuf(stdout, NULL);
    freopen("hotel_input.txt", "r", stdin);
    int T, MARK;
    scanf("%d %d", &T, &MARK);
    for (int tc = 1; tc <= T; tc++)
    {
        int score = run() ? MARK : 0;
        printf("#%d %d\n", tc, score);
    }

    finish = clock();
    printf("Time: %f\n", (double)(finish - start) / CLOCKS_PER_SEC);

    return 0;
}

///////////////////////////////////////////
//////////////// user code ////////////////
///////////////////////////////////////////
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

#define MAX_N 5000
#define INFS 987654321
using namespace std;

vector<pair<int, int>> adj[MAX_N];
int brands[MAX_N];
int nums;

vector<vector<int>> dist(MAX_N, vector<int>(MAX_N, INFS));

bool dijkstra_flag[MAX_N];

void dijkstra(int start)
{
    for (int i = 0; i < nums; ++i)
    {
        dist[start][i] = INFS;
    }
    dist[start][start] = 0;

    priority_queue<pair<int, int>> pq;
    pq.push({0, start});

    while (!pq.empty())
    {
        int cost = -pq.top().first;
        int cur = pq.top().second;
        pq.pop();

        if (dist[start][cur] < cost)
        {
            continue;
        }

        int size = adj[cur].size();
        for (int i = 0; i < size; ++i)
        {
            int next = adj[cur][i].first;
            int nextDist = cost + adj[cur][i].second;

            if (dist[start][next] > nextDist)
            {
                dist[start][next] = nextDist;
                pq.push({-nextDist, next});
            }
        }
    }
    return;
}

void init(int N, int mBrands[])
{
    for (int i = 0; i < N; ++i)
        adj[i].clear();
    memcpy(brands, mBrands, sizeof(int) * N);
    memset(dijkstra_flag, true, sizeof(dijkstra_flag));
    nums = N;

    return;
}

void connect(int mHotelA, int mHotelB, int mDistance)
{
    adj[mHotelA].push_back({mHotelB, mDistance});
    adj[mHotelB].push_back({mHotelA, mDistance});

    memset(dijkstra_flag, true, sizeof(dijkstra_flag));

    return;
}

int merge(int mHotelA, int mHotelB)
{
    int brandA = brands[mHotelA];
    int brandB = brands[mHotelB];
    int count = 0;
    for (int i = 0; i < nums; ++i)
    {
        if (brands[i] == brandA)
        {
            count++;
        }
        else if (brands[i] == brandB)
        {
            brands[i] = brandA;
            count++;
        }
    }

    return count;
}

int move(int mStart, int mBrandA, int mBrandB)
{
    if (dijkstra_flag[mStart])
    {
        dijkstra(mStart);
        dijkstra_flag[mStart] = false;
    }

    int hotelX;
    int hotelX_dist = INFS;
    for (int i = 0; i < nums; ++i)
    {
        if (i != mStart && brands[i] == mBrandA && dist[mStart][i] < hotelX_dist)
        {
            hotelX = i;
            hotelX_dist = dist[mStart][i];
        }
    }

    int hotelY_dist = INFS;
    for (int i = 0; i < nums; ++i)
    {
        if (i != mStart && i != hotelX && brands[i] == mBrandB && dist[mStart][i] < hotelY_dist)
        {
            hotelY_dist = dist[mStart][i];
        }
    }

    int min_dist = hotelX_dist + hotelY_dist;

    return min_dist;
}