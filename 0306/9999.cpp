#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

    freopen("9999.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= 2; ++i)
    {
        int L, N;
        cin >> L >> N;

        vector<int> s(N);
        vector<int> e(N);
        vector<int> t(N);

        for (int j = 0; j < N; ++j)
        {
            cin >> s[j] >> e[j];
            t[j] = e[j] - s[j];
        }

        int ans = 0;
        for (int j = 0; j < N; ++j)
        {
            int min_time = s[j];
            int max_time = s[j] + L;
            if (max_time > e[j])
            {
                max_time = e[j];
            }
            int peak_time = 0;
            int count = 0;
            while (s[count] < max_time && count < N)
            {
                if (e[count] > max_time)
                {
                    peak_time += max_time - s[count];
                }
                else
                {
                    peak_time += t[count];
                }
                count++;
            }
            if (peak_time > ans)
            {
                ans = peak_time;
            }
        }

        cout << "#" << i << " " << ans << endl;
    }

    return 0;
}