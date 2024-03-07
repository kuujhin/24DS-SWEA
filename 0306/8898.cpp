#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{

    freopen("8898.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n, m, c1, c2;
        cin >> n >> m >> c1 >> c2;

        vector<int> cow(n);
        vector<int> horse(m);

        for (int j = 0; j < n; ++j)
        {
            cin >> cow[j];
        }
        sort(cow.begin(), cow.end());

        int index;
        int count = 0;
        int _min;
        int d;

        for (int j = 0; j < m; ++j)
        {
            cin >> horse[j];

            index = lower_bound(cow.begin(), cow.end(), horse[j]) - cow.begin();

            if (index == 0)
            {
                d = abs(cow[0] - horse[j]);
            }
            else if (index == n)
            {
                d = abs(cow[n - 1] - horse[j]);
            }
            else
            {
                d = min(abs(cow[index] - horse[j]), abs(cow[index - 1] - horse[j]));
            }

            if (j == 0)
                _min = d;

            if (d == _min)
            {
                count++;
            }
            else if (d < _min)
            {
                _min = d;
                count = 1;
            }
        }

        int xdiff = abs(c1 - c2);

        cout << "#" << i << " " << _min + xdiff << " " << count << endl;
    }

    return 0;
}