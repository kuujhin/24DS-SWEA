#include <iostream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{

    FILE *sfp;
    sfp = freopen("1974.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        bool isValid = true;
        string str[9][9];
        for (int j = 0; j < 9; ++j)
        {
            for (int k = 0; k < 9; ++k)
            {
                cin >> str[j][k];
            }
        }

        for (int j = 0; j < 9; ++j)
        {
            int rowSum = 0;
            int colSum = 0;

            for (int k = 0; k < 9; ++k)
            {
                rowSum += stoi(str[j][k]);
                colSum += stoi(str[k][j]);
            }

            if (rowSum != 45 || colSum != 45)
            {
                isValid = false;
                break;
            }

            int blockSum = 0;
            int x = j / 3 * 3;
            int y = j % 3 * 3;
            for (int k = 0; k < 3; ++k)
            {
                for (int m = 0; m < 3; ++m)
                {
                    blockSum += stoi(str[x + k][y + m]);
                }
            }

            if (blockSum != 45)
            {
                isValid = false;
                break;
            }
        }

        cout << "#" << i << " " << isValid << endl;
    }

    fclose(sfp);
    return 0;
}