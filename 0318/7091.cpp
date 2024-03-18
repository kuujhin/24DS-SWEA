#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    freopen("7091.txt", "r", stdin);

    int T, H, W, N, M;
    int count = 0;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        count = 0;
        cin >> H >> W >> N >> M;

        string student[H][W];
        int studentCount = 0;
        string teacher[N][M];
        int teacherCount[N - H + 1][M - W + 1] = {0};

        for (int j = 0; j < H; ++j)
        {
            for (int k = 0; k < W; ++k)
            {
                cin >> student[j][k];
                if (student[j][k] == "o")
                    studentCount++;
            }
        }

        for (int j = 0; j < N; ++j)
        {
            for (int k = 0; k < W; ++k)
            {
                cin >> teacher[j][k];
                if (teacher[j][k] == "o")
                {
                    for (int p = 0; p < H; ++p)
                    {
                        for (int q = 0; q < W; ++q)
                        {
                            if (j + p < N && k + q < M)
                            {
                                teacherCount[j + p][k + q]++;
                            }
                        }
                    }
                }
            }
        }

        for (int j = 0; j < N - H + 1; ++j)
        {
            for (int k = 0; k < M - W + 1; ++k)
            {
                if (studentCount == teacherCount[j][k])
                {
                    if (student[0][0] == teacher[j][k])
                    {
                        for (int p = 0; p < H; ++p)
                        {
                            for (int q = 0; q < W; ++q)
                            {
                                if (student[p][q] != teacher[j + p][k + q])
                                {
                                    break;
                                }
                                if (p == H - 1 && q == W - 1)
                                {
                                    count++;
                                }
                            }
                        }
                    }
                }
            }
        }

        cout << "#" << i << " " << count << endl;
    }

    return 0;
}