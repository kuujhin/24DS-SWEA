#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

long long init(long long *arr, long long *tree, long long node, long long start, long long end)
{
    if (start == end)
    {
        return tree[node] = arr[start];
    }
    else
    {
        return tree[node] = max(init(arr, tree, node * 2, start, (start + end) / 2), init(arr, tree, node * 2 + 1, (start + end) / 2 + 1, end));
    }
}

long long _max(long long *tree, long long node, long long start, long long end, long long left, long long right)
{
    if (left > end || right < start)
    {
        return -1000000001;
    }
    if (left <= start && end <= right)
    {
        return tree[node];
    }
    return max(_max(tree, node * 2, start, (start + end) / 2, left, right), _max(tree, node * 2 + 1, (start + end) / 2 + 1, end, left, right));
}

void update(long long *tree, long long node, long long start, long long end, long long index, long long newValue)
{
    if (index < start || index > end)
    {
        return;
    }
    if (start == end)
    {
        tree[node] = newValue;
        return;
    }
    else
    {
        tree[node] = max(tree[node], newValue);
        update(tree, node * 2, start, (start + end) / 2, index, newValue);
        update(tree, node * 2 + 1, (start + end) / 2 + 1, end, index, newValue);
    }
}

int main(int argc, char **argv)
{

    // freopen("3238_jungol.txt", "r", stdin);

    int T = 1;

    for (int i = 1; i <= T; ++i)
    {
        int N, M;
        cin >> N >> M;

        long long *arr = new long long[N + 1];

        // vector<long long> arr(N, -1000000001);

        int h = (int)ceil(log(N) / log(2));
        int treeSize = (1 << (h + 1));

        long long *tree = new long long[treeSize];

        for (int j = 0; j < treeSize; ++j)
        {
            tree[j] = -1000000001;
        }

        // init(arr, tree, 1, 0, N - 1);

        for (int j = 0; j < M; ++j)
        {
            int orderType;
            cin >> orderType;

            switch (orderType)
            {
            case 1:
                int k, val;
                cin >> k >> val;
                update(tree, 1, 0, N - 1, k - 1, val);
                break;
            case 2:
            {
                int s, e;
                cin >> s >> e;
                long long temp = _max(tree, 1, 0, N - 1, s - 1, e - 1);
                if (temp > -1000000001)
                {
                    cout << temp << endl;
                }
                break;
            }
            case 3:

                cin >> k;
                update(tree, 1, 0, N - 1, k - 1, -1000000001);
                break;
            }
        }

        // cout << "#" << i << " " << endl;
        // for (int j = 0; j < treeSize; ++j)
        // {
        //     cout << tree[j] << " ";
        // }
    }

    return 0;
}