#include <iostream>

using namespace std;

// main
int T, N;
int map[100][100] = {0};

// findMat
int subMat[100][6] = {0};
int k = 0;

void findMat()
{
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            if (map[i][j] != 0)
            {
                bool flag = false;
                for (int p = 0; p < k; ++p)
                {
                    if (subMat[p][1] <= j && subMat[p][3] >= j && subMat[p][0] <= i && subMat[p][2] >= i)
                    {
                        flag = true;
                        break;
                    }
                }

                if (flag)
                {
                    continue;
                }

                int temp1 = i;
                int temp2 = j;

                subMat[k][0] = i;
                subMat[k][1] = j;

                while (map[i][j + 1] != 0 && j + 1 < N)
                {
                    j++;
                }
                while (map[i + 1][j] != 0 && i + 1 < N)
                {
                    i++;
                }
                subMat[k][2] = i;
                subMat[k][3] = j;

                subMat[k][4] = i - temp1 + 1;
                subMat[k][5] = j - temp2 + 1;

                k++;
                i = temp1;
            }
        }
    }
}

void sortMat(int temp[], int d[])
{
    for (int i = 0; i < k; ++i)
    {
        bool flag[k] = {false};
        temp[0] = subMat[i][4];
        temp[1] = subMat[i][5];

        flag[i] = true;

        int p = 2;
        while (p < k + 1)
        {
            bool find = false;
            for (int j = 0; j < k; ++j)
            {
                if (subMat[j][4] == temp[p - 1] && !flag[j])
                {
                    temp[p] = subMat[j][5];
                    flag[j] = true;
                    p++;
                    find = true;
                    break;
                }
            }
            if (find && p == k + 1)
            {
                for (int j = 0; j < k + 1; ++j)
                {
                    d[j] = temp[j];
                }
                break;
            }
            if (!find)
                break;
        }
    }
}

int main(int argc, char **argv)
{

    // freopen("1260.txt", "r", stdin);

    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N;
        for (int i = 0; i < N; ++i)
        {
            for (int j = 0; j < N; ++j)
            {
                cin >> map[i][j];
            }
        }

        // 행렬탐색
        k = 0;
        findMat();

        // for (int i = 0; i < k; ++i)
        // {

        //     cout << subMat[i][4] << " ";
        //     cout << subMat[i][5] << " ";

        //     cout << endl;
        // }

        // 행렬정렬
        int temp[k + 1] = {0};
        int d[k + 1] = {0};
        sortMat(temp, d);

        // for (int i = 0; i < k + 1; ++i)
        // {
        //     cout << d[i] << " ";
        // }

        // Matrix Chain Multiplication
        int M[k + 1][k + 1] = {0};

        for (int r = 2; r <= k; ++r)
        {
            for (int i = 1; i <= k - r + 1; ++i)
            {
                int j = i + r - 1;
                M[i][j] = 1000000;
                for (int k = i; k <= j - 1; ++k)
                {
                    M[i][j] = min(M[i][j], M[i][k] + M[k + 1][j] + d[i - 1] * d[k] * d[j]);
                }
            }
        }

        cout << "#" << t << " " << M[1][k] << endl;
    }

    return 0;
}