#include <iostream>

using namespace std;

int minPipe;
int board[50][50] = {0};

// direction: 0 - right, 1 - down, 2 - left, 3 - up
void connectPipe(int N, int row, int col, int pipeLength, int direction)
{
    // 이미 최소값을 찾은 경우
    if (minPipe == N + N - 1)
        return;
    // 지나간 길이거나 파이프가 없는 경우
    if (board[row][col] == 0)
        return;
    // 현재위치에서 최단거리로 가도 최소값보다 크거나 같은 경우
    if (pipeLength + row + col - 1 >= minPipe)
        return;

    // 출발점에 도착한 경우 진입 방향과 파이프 종류 확인 후 최소값 갱신
    if (row == 0 && col == 0)
    {
        if ((direction == 2 && board[row][col] <= 2) || (direction == 3 && board[row][col] >= 3))
        {
            minPipe = pipeLength + 1;
        }
        return;
    }

    // 일자 파이프인 경우 방향 유지한 채 다음 위치로 이동
    if (board[row][col] <= 2)
    {
        int nextRow = row;
        int nextCol = col;
        if (direction == 0)
        {
            nextCol++;
        }
        else if (direction == 1)
        {
            nextRow++;
        }
        else if (direction == 2)
        {
            nextCol--;
        }
        else if (direction == 3)
        {
            nextRow--;
        }

        if (nextRow < N && nextCol < N && nextRow >= 0 && nextCol >= 0)
        {
            if (board[nextRow][nextCol] != 0)
            {
                board[row][col] = 0;
                connectPipe(N, nextRow, nextCol, pipeLength + 1, direction);
                board[row][col] = 1;
            }
        }
    }

    // 꺾인 파이프인 경우 2가지 방향모두 탐색
    else
    {
        board[row][col] = 0;
        if (direction == 0 || direction == 2)
        {
            // ->┘, └<- 위쪽 먼저 진행 (입구 방향)
            if (row - 1 >= 0 && board[row - 1][col] != 0)
            {
                connectPipe(N, row - 1, col, pipeLength + 1, 3);
            }
            // ->┐, ┌<-
            if (row + 1 < N && board[row + 1][col] != 0)
            {
                connectPipe(N, row + 1, col, pipeLength + 1, 1);
            }
        }
        else if (direction == 1 || direction == 3)
        {
            // <-┐, <-┘ 왼쪽 먼저 진행 (입구 방향)
            if (col - 1 >= 0 && board[row][col - 1] != 0)
            {
                connectPipe(N, row, col - 1, pipeLength + 1, 2);
            }
            // └->, ┌->
            if (col + 1 < N && board[row][col + 1] != 0)
            {
                connectPipe(N, row, col + 1, pipeLength + 1, 0);
            }
        }
        board[row][col] = 3;
    }
}

int main(int argc, char **argv)
{

    // freopen("4340.txt", "r", stdin);

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < N; ++k)
            {
                cin >> board[j][k];
            }
        }

        minPipe = N * N;

        // connectPipe(N, 0, 0, 0, 0);

        // 도착점부터 탐색
        connectPipe(N, N - 1, N - 1, 0, 2);

        cout << "#" << i << " " << minPipe << endl;
    }

    return 0;
}