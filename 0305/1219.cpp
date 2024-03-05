#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // FILE *sfp;
    // sfp = freopen("1219.txt", "r", stdin);

    int tcnum = 10;

    for (int i = 1; i <= tcnum; ++i)
    {
        int edge1[100] = {0};
        int edge2[100] = {0};

        int node[100] = {1};
        int visited[100] = {0};

        int testnum, arrownum;
        cin >> testnum >> arrownum;

        for (int j = 0; j < arrownum; ++j)
        {
            int x, y;
            cin >> x >> y;

            if (edge1[x] == 0)
                edge1[x] = y;

            else
                edge2[x] = y;
        }

        bool flag = true;
        while (flag)
        {
            flag = false;

            for (int j = 0; j < 100; ++j)
            {
                if (node[j] == 1 && visited[j] == 0)
                {
                    node[edge1[j]] = 1;
                    node[edge2[j]] = 1;
                    visited[j] = 1;

                    if (j == 99)
                        break;

                    flag = true;
                    break;
                }
            }
        }

        if (visited[99] == 1)
            cout << "#" << i << " " << 1 << endl;
        else
            cout << "#" << i << " " << 0 << endl;
    }

    // fclose(sfp);
    return 0;
}