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
#include <vector>
#include <queue>
#include <climits>
using namespace std;

int hotelN, brand[5000];
vector<pair<int, int>> conn[5000];

void init(int N, int mBrands[])
{
    for (int i = 0; i < N; i++)
        conn[i].clear();
    hotelN = N;
    copy(mBrands, mBrands + N, brand);
}
void connect(int mHotelA, int mHotelB, int mDistance)
{
    conn[mHotelA].emplace_back(make_pair(mHotelB, mDistance));
    conn[mHotelB].emplace_back(make_pair(mHotelA, mDistance));
}
int merge(int mHotelA, int mHotelB)
{
    int mBrandA = brand[mHotelA], mBrandB = brand[mHotelB];
    int cnt = 0;
    for (int i = 0; i < hotelN; i++)
    {
        if (brand[i] == mBrandB)
        {
            brand[i] = mBrandA;
            cnt++;
        }
        else if (brand[i] == mBrandA)
            cnt++;
    }
    return cnt;
}
int move(int mStart, int mBrandA, int mBrandB)
{
    int dist[5000];
    for (int i = 0; i < hotelN; i++)
        dist[i] = INT_MAX;
    bool visited[5000] = {false};
    priority_queue<pair<int, int>> pq;
    for (auto dest : conn[mStart])
        pq.emplace(make_pair(-dest.second, dest.first));
    visited[mStart] = true;

    pair<int, int> cur;
    while (!pq.empty())
    {
        cur = pq.top();
        pq.pop();
        if (visited[cur.second])
            continue;
        visited[cur.second] = true;
        dist[cur.second] = -cur.first;

        for (auto dest : conn[cur.second])
            pq.emplace(make_pair(cur.first - dest.second, dest.first));
    }

    int minDistA = INT_MAX, minDistAIdx = -1, minDistB = INT_MAX;
    for (int i = 0; i < hotelN; i++)
    {
        if (brand[i] == mBrandA && dist[i] < minDistA && i != mStart)
        {
            minDistA = dist[i];
            minDistAIdx = i;
        }
    }

    for (int i = 0; i < hotelN; i++)
    {
        if (brand[i] == mBrandB && dist[i] < minDistB && i != mStart && i != minDistAIdx)
            minDistB = dist[i];
    }

    return minDistA + minDistB;
}