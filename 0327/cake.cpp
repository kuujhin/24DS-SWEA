#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> N;

        int chulsu[N];
        int younghee[N];
        for (int i = 0; i < N; ++i)
        {
            cin >> chulsu[i];
        }

        for (int i = 0; i < N; ++i)
        {
            cin >> younghee[i];
        }

        // Brute force
        // Table (i, j) 는 i~j 까지 케이크를 먹었을 때의 만족도
        int chulsu_table[N][N] = {0};
        int younghee_table[N][N] = {0};
        for (int i = 0; i < N; ++i)
        {
            chulsu_table[i][i] = chulsu[i];
            younghee_table[i][i] = younghee[i];
            for (int j = 1; j < N; ++j)
            {
                chulsu_table[i][(i + j) % N] = chulsu_table[i][(i + j - 1) % N] + chulsu[(i + j) % N];
                younghee_table[i][(i + j) % N] = younghee_table[i][(i + j - 1) % N] + younghee[(i + j) % N];
            }
        }

        // 철수가 start번 조각부터 chulsu_count개의 조각을 먹었을 때의 최대 만족도
        int answer = -300000001;
        for (int start = 0; start < N; ++start)
        {
            for (int chulsu_count = 1; chulsu_count < N; ++chulsu_count)
            {
                int chulsu_like = chulsu_table[start][(start + chulsu_count - 1) % N];

                int min_index = start + chulsu_count;
                int max_index = start + N - 1;
                int younghee_like_max = -300000001;

                for (int i = min_index; i <= max_index; ++i)
                {
                    int younghee_like = max(younghee_table[min_index % N][i % N], younghee_table[i % N][max_index % N]);
                    younghee_like_max = max(younghee_like_max, younghee_like);
                }

                answer = max(answer, chulsu_like + younghee_like_max);
            }
        }

        cout << "#" << t << " " << answer << endl;
    }

    return 0;
}