#include <iostream>
#include <cmath>
using namespace std;

long long max_result = 1;

void loop(int left_coin, int left_box, int stair, long long result)
{

    if (left_box == 1)
    {
        result = result * (stair + left_coin);
        if (result > max_result)
        {
            max_result = result;
        }
        return;
    }

    if (left_coin == 0)
    {
        result = result * pow(stair, left_box);
        if (result > max_result)
        {
            max_result = result;
        }
        return;
    }

    int max = left_coin / left_box;
    for (int i = 0; i <= max; ++i)
    {
        loop(left_coin - (i * left_box), left_box - 1, stair + i, result * (stair + i));
    }
    return;
}

int main(int argc, char **argv)
{

    freopen("1265.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n, p;
        cin >> n >> p;

        loop(n - p, p, 1, 1);

        cout << "#" << i << " " << max_result << endl;
    }

    return 0;
}