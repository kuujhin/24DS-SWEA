#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{

    FILE *sfp;
    sfp = freopen("8898.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n, m, c1, c2;
        cin >> n >> m >> c1 >> c2;

        vector<int> cow(n);
        vector<int> horse(m);
        vector<int> distance(m);

        for (int j = 0; j < n; ++j)
        {
            cin >> cow[j];
        }
        for (int j = 0; j < m; ++j)
        {
            cin >> horse[j];
        }

        sort(cow.begin(), cow.end());
        sort(horse.begin(), horse.end());

        int index;
        int count = 0;
        int _min;

        for (int j = 0; j < m; ++j)
        {
            if (cow.begin() + index > cow.end())
                break;
            index = lower_bound(cow.begin() + index, cow.end(), horse[j]) - cow.begin();

            if (index == 0)
            {
                distance[j] = abs(cow[0] - horse[j]);
            }
            else if (index == n)
            {
                distance[j] = abs(cow[n - 1] - horse[j]);
            }
            else
            {
                distance[j] = min(abs(cow[index] - horse[j]), abs(cow[index - 1] - horse[j]));
            }

            if (j == 0)
                _min = distance[0];

            if (distance[j] == _min)
            {
                count++;
            }
            else if (distance[j] < _min)
            {
                _min = distance[j];
                count = 1;
            }
        }

        int xdiff = abs(c1 - c2);

        cout << "#" << i << " " << _min + xdiff << " " << count << endl;
    }

    fclose(sfp);
    return 0;
}