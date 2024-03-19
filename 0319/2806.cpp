#include <iostream>

using namespace std;

int count = 0;

void nQueen(int N, int row, int *board)
{
    if (row == N)
    {
        count++;
        return;
    }

    for (int i = 0; i < N; ++i)
    {
        bool isPossible = true;

        for (int j = 0; j < row; ++j)
        {
            if (board[j] == i || abs(row - j) == abs(i - board[j]))
            {
                isPossible = false;
                break;
            }
        }

        if (isPossible)
        {
            board[row] = i;
            nQueen(N, row + 1, board);
        }
    }
}

int main(int argc, char **argv)
{

    // freopen("2806.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        int board[N] = {0};
        count = 0;

        nQueen(N, 0, board);

        cout << "#" << i << " " << count << endl;
    }

    return 0;
}