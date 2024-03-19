#include <iostream>

using namespace std;

int shortestPath = 1000000;

void findPath(int N, int row, int curIdx, int pathLength, int board[][2], int checkList[])
{
    if (row == N)
    {
        pathLength += abs(board[curIdx][0] - board[1][0]) + abs(board[curIdx][1] - board[1][1]);
        if (pathLength < shortestPath)
        {
            shortestPath = pathLength;
        }
        return;
    }

    for (int i = 2; i < N + 2; ++i)
    {
        if (checkList[i] == 0)
        {
            checkList[i] = 1;
            int temp = pathLength + abs(board[curIdx][0] - board[i][0]) + abs(board[curIdx][1] - board[i][1]);
            if (temp < shortestPath)
            {
                findPath(N, row + 1, i, temp, board, checkList);
            }
            checkList[i] = 0;
        }
    }
}

int main(int argc, char **argv)
{

    // freopen("1247.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        int board[N + 2][2] = {0};
        int checkList[N + 2] = {0};

        for (int j = 0; j < N + 2; ++j)
        {
            cin >> board[j][0];
            cin >> board[j][1];
        }

        shortestPath = 1000000;

        findPath(N, 0, 0, 0, board, checkList);

        cout << "#" << i << " " << shortestPath << endl;
    }

    return 0;
}