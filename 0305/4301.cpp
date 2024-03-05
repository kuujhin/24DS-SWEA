#include <iostream>
using namespace std;

int main(int argc, char **argv)
{
    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n, m;
        cin >> n >> m;
        int row = n / 4;
        int col = m / 4;
        n = n % 4;
        m = m % 4;

        int table[4][4] = {
            {0, 2 * row, 4 * row, 6 * row},
            {2 * col, 2 * (row + col) + 1, 4 * row + 2 * col + 2, 6 * row + 2 * col + 2},
            {4 * col, 4 * col + 2 * row + 2, 4 * row + 4 * col + 4, 6 * row + 4 * col + 4},
            {6 * col, 6 * col + 2 * row + 2, 6 * col + 4 * row + 4, 6 * row + 6 * col + 5},
        };
        int result = 8 * row * col + table[n][m];
        cout << "#" << i << " " << result << endl;
    }
    return 0;
}
