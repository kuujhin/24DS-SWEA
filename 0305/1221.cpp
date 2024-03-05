#include <iostream>
#include <algorithm>

using namespace std;

int main(int argc, char **argv)
{

    // FILE *sfp;
    // sfp = freopen("1221.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int num;
        cin >> num;

        int len = 0;
        cin >> len;

        string str[10000];
        int cnt[10] = {0};

        for (int j = 0; j < len; ++j)
        {
            cin >> str[j];
        }

        for (int j = 0; j < len; ++j)
        {
            switch (str[j][0])
            {
            case 'Z':
                cnt[0]++;
                break;
            case 'O':
                cnt[1]++;
                break;
            case 'T':
                if (str[j][1] == 'W')
                    cnt[2]++;
                else
                    cnt[3]++;
                break;
            case 'F':
                if (str[j][1] == 'O')
                    cnt[4]++;
                else
                    cnt[5]++;
                break;
            case 'S':
                if (str[j][1] == 'I')
                    cnt[6]++;
                else
                    cnt[7]++;
                break;
            case 'E':
                cnt[8]++;
                break;
            case 'N':
                cnt[9]++;
                break;
            }
        }

        cout << "#" << i << " ";

        for (int j = 0; j < 10; ++j)
        {
            for (int k = 0; k < cnt[j]; ++k)
            {
                switch (j)
                {
                case 0:
                    cout << "ZRO ";
                    break;
                case 1:
                    cout << "ONE ";
                    break;
                case 2:
                    cout << "TWO ";
                    break;
                case 3:
                    cout << "THR ";
                    break;
                case 4:
                    cout << "FOR ";
                    break;
                case 5:
                    cout << "FIV ";
                    break;
                case 6:
                    cout << "SIX ";
                    break;
                case 7:
                    cout << "SVN ";
                    break;
                case 8:
                    cout << "EGT ";
                    break;
                case 9:
                    cout << "NIN ";
                    break;
                }
            }
        }

        cout << endl;
    }

    // fclose(sfp);
    return 0;
}