#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

    freopen("7699.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int r, c;
        cin >> r >> c;

        vector<vector<char>> island(r, vector<char>(c, 0));
        vector<bool> visited(r * c, false);

        for (int j = 0; j < r; ++j)
            for (int k = 0; k < c; ++k)
                cin >> island[j][k];

        cout << "#" << i << " " << endl;
    }

    return 0;
}