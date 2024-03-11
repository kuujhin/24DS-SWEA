#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{

    freopen("1257.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int k;
        cin >> k;

        string str[400];
        cin >> str[0];

        int len = str[0].size();
        for (int j = 1; j < len; ++j)
        {
            str[j] = str[0].substr(j);
        }

        sort(str, str + len);

        int LCP[400] = {0};
        int length[400] = {0};

        length[0] = str[0].size();
        for (int j = 1; j < len; ++j)
        {
            length[j] = str[j].size();
            int t = 0;
            while (str[j][t] == str[j - 1][t])
            {
                ++t;
            }
            LCP[j] = t;
            length[j] -= t;
        }

        int sum = 0;
        int j = 0;
        bool isOver = false;
        while (k - length[j] > 0)
        {
            k -= length[j++];
            if (j == len)
            {
                isOver = true;
                break;
            }
        }

        string ans = isOver ? "none" : str[j].substr(0, LCP[j] + k);

        cout << "#" << i << " " << ans << endl;
    }

    return 0;
}