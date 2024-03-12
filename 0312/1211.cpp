#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    freopen("1211.txt", "r", stdin);

    for (int i = 1; i <= 10; ++i)
    {
        int tcnum;
        cin >> tcnum;

        int ladder[100][102] = {
            0,
        };

        for (int j = 0; j < 100; ++j)
        {
            for (int k = 1; k <= 100; ++k)
            {
                cin >> ladder[j][k];
            }
        }

        int min_count = 0;
        int min_index = 0;
        for (int j = 1; j <= 100; ++j)
        {
            int x = j;
            int y = 0;
            int xcount = 0;
            if (ladder[0][j] == 1)
            {
                while (y < 100)
                {
                    if (ladder[y][x - 1] == 1)
                    {
                        while (ladder[y][x - 1] == 1)
                        {
                            x--;
                            xcount++;
                        }
                    }
                    else if (ladder[y][x + 1] == 1)
                    {
                        while (ladder[y][x + 1] == 1)
                        {
                            x++;
                            xcount++;
                        }
                    }

                    y++;
                }

                if (min_count == 0)
                {
                    min_count = xcount;
                    min_index = j;
                }
                if (min_count >= xcount)
                {
                    min_count = xcount;
                    min_index = j;
                }
            }
        }

        cout << "#" << i << " " << min_index - 1 << endl;
    }

    return 0;
}