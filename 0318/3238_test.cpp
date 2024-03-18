#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <cmath>

using namespace std;

int tree[4000001];

void update(int start, int end, int index, int cur_idx, int val, int start_idx)
{
    if (indexend)
        return;
    if (cur_idx == start_idx + index - 1)
    {
        tree[cur_idx] = val;
        return;
    }
    else if (start == end)
        return;
    else
    {
        int mid = (start + end) / 2;
        update(start, mid, index, 2 * cur_idx, val, start_idx);
        update(mid + 1, end, index, cur_idx * 2 + 1, val, start_idx);
        tree[cur_idx] = max(tree[cur_idx * 2], tree[cur_idx * 2 + 1]);
    }
}

int find_max(int start, int end, int left, int right, int cur_idx)
{
    if (left > end || right < start)
        return -1000000001;
    if (left <= start && end <= right)
        return tree[cur_idx];
    return max(find_max(start, (start + end) / 2, left, right, 2 * cur_idx), find_max((start + end) / 2 + 1, end, left, right, 2 * cur_idx + 1));
}

int main()
{
    int N, M;
    scanf("%d %d", &N, &M);
    int h = (int)ceil(log(N) / log(2));
    int start_index = 1 << h;

    for (int i = 1; i <= start_index * 2; i++)
    {
        tree[i] = -1000000001;
    }
    for (int i = 1; i <= M; i++)
    {
        int order;
        scanf("%d ", &order);

        if (order == 1)
        {
            int k;
            long long val;
            scanf("%d %d", &k, &val);

            update(1, start_index - 1, k, 1, val, start_index);
        }
        else if (order == 2)
        {
            int s, e;
            scanf("%d %d", &s, &e);
            int result = find_max(1, start_index - 1, s, e, 1);
            if (result != -1000000001)
            {
                printf("%d\n", result);
            }
        }
        else
        {
            int k;
            scanf("%d", &k);
            update(1, start_index - 1, k, 1, -1000000001, start_index);
        }
    }
}