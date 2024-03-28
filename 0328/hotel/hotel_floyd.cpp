#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>

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

///////////////////////////////////////////
//////////////// user code ////////////////
///////////////////////////////////////////
#include <iostream>
#include <vector>
#include <cstring>

#define MAX_N 5000

using namespace std;

vector<vector<int>> map(MAX_N, vector<int>(MAX_N));
int brands[MAX_N];
int nums;

bool connect_flag = false;

void floyd()
{
    for (int k = 0; k < nums; ++k)
    {
        for (int i = 0; i < nums; ++i)
        {
            for (int j = 0; j < nums; ++j)
            {
                if (map[i][j] > map[i][k] + map[k][j])
                {
                    map[i][j] = map[i][k] + map[k][j];
                }
            }
        }
    }

    return;
}

void init(int N, int mBrands[])
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (i == j)
                map[i][j] = 0;
            else
                map[i][j] = 987654321;
        }
    }

    memcpy(brands, mBrands, sizeof(int) * N);

    nums = N;

    return;
}

void connect(int mHotelA, int mHotelB, int mDistance)
{
    map[mHotelA][mHotelB] = mDistance;
    map[mHotelB][mHotelA] = mDistance;

    connect_flag = true;

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
    if (connect_flag == true)
    {
        floyd();
        connect_flag = false;
    }

    int hotelX;
    int hotelX_dist = 987654321;
    for (int i = 0; i < nums; ++i)
    {
        if (i != mStart && brands[i] == mBrandA && map[mStart][i] < hotelX_dist)
        {
            hotelX = i;
            hotelX_dist = map[mStart][i];
        }
    }

    int hotelY_dist = 987654321;
    for (int i = 0; i < nums; ++i)
    {
        if (i != mStart && i != hotelX && brands[i] == mBrandB && map[mStart][i] < hotelY_dist)
        {
            hotelY_dist = map[mStart][i];
        }
    }

    int min_dist = hotelX_dist + hotelY_dist;

    return min_dist;
}