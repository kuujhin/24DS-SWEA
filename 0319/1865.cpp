#include <iostream>

using namespace std;

double maxProbability = 0;

void divideWork(int N, int row, double p, int board[][16], int checklist[])
{
    if (row == N)
    {
        if (p > maxProbability)
        {
            maxProbability = p;
        }
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        if (board[row][i] != 0 && checklist[i] == 0)
        {
            checklist[i] = 1;
            double temp = p * (double)board[row][i] / 100.0;
            if (temp > maxProbability)
            {
                divideWork(N, row + 1, temp, board, checklist);
            }
            checklist[i] = 0;
        }
    }
}

int main(int argc, char **argv)
{

    // freopen("1865.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        int board[16][16] = {0};
        int checklist[16] = {0};

        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                cin >> board[j][k];
            }
        }

        maxProbability = 0.0;

        divideWork(N, 0, 1.0, board, checklist);

        cout << fixed;
        cout.precision(6);
        cout << "#" << i << " " << maxProbability * 100 << endl;
    }

    return 0;
}