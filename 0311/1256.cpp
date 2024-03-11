#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{

    freopen("1256.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int k;
        cin >> k;

        string str[400];
        cin >> str[0];

        int len = str[0].size();
        for (int i = 1; i < len; ++i)
        {
            str[i] = str[0].substr(i);
        }

        sort(str, str + len);

        if (k > len)
            cout << "#" << i << " none" << endl;

        else
            cout << "#" << i << " " << str[k - 1] << endl;
    }

    return 0;
}