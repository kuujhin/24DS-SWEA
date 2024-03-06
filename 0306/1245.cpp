#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{
    // freopen("1245.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n;
        cin >> n;

        vector<double> pos(n);
        vector<double> weight(n);

        vector<double> balance(n);

        for (int j = 0; j < n; ++j)
        {
            cin >> pos[j];
        }
        for (int j = 0; j < n; ++j)
        {
            cin >> weight[j];
        }

        for (int j = 0; j < n - 1; ++j)
        {
            int count = 50;
            double force, mid;
            double x1 = pos[j];
            double x2 = pos[j + 1];

            while (count--)
            {
                mid = (x1 + x2) / 2;
                force = 0;
                for (int k = 0; k <= j; ++k)
                {
                    force += weight[k] / ((mid - pos[k]) * (mid - pos[k]));
                }
                for (int k = j + 1; k < n; ++k)
                {
                    force -= weight[k] / ((mid - pos[k]) * (mid - pos[k]));
                }

                if (abs(force) < 1e-13)
                {
                    break;
                }
                else
                {
                    force > 0 ? x1 = mid : x2 = mid;
                }
            }
            balance[j] = mid;
        }
        cout << "#" << i << " ";

        for (int j = 0; j < n - 1; ++j)
        {
            cout << fixed;
            cout.precision(10);
            cout << balance[j] << " ";
        }
        cout << endl;
    }

    return 0;
}