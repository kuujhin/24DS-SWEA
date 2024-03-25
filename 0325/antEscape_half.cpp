#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("test.txt", "r", stdin);

    int T, M, N, K;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        cin >> M >> N >> K;

        vector<pair<double, double>> ants_pos(N);
        vector<int> ants_dir(N);

        int right_ants_count = 0;

        for (int i = 0; i < N; ++i)
        {
            int x, y, dir;
            cin >> x >> y >> dir;
            ants_pos[i] = make_pair(x, y);
            ants_dir[i] = dir;
            if (dir == 4)
                right_ants_count++;
        }

        // 빠져나간 개미의 수
        int escape_count = 0;
        // 경과 시간
        int count = 0;
        // 1 ~ k번째로 빠져나간 개미의 index 저장
        vector<pair<int, int>> result;

        // K개의 개미가 빠져나갈 가능성이 없는 경우 종료
        if (right_ants_count < K)
        {
            cout << "#" << t << " 0 0" << endl;
            continue;
        }

        while (escape_count < K)
        {
            // 경과 시간 증가
            count++;

            // 해당 타임에 빠져나간 개미들을 저장할 pq
            priority_queue<pair<int, int>> escape_ants;

            // 첫번째 절반 이동
            for (int i = 0; i < N; ++i)
            {
                // 경계를 나간 경우 무시
                if (ants_dir[i] == -1)
                    continue;

                // 이동
                if (ants_dir[i] == 1)
                    ants_pos[i].second += 0.5;

                else if (ants_dir[i] == 2)
                    ants_pos[i].second -= 0.5;

                else if (ants_dir[i] == 3)
                    ants_pos[i].first -= 0.5;

                else if (ants_dir[i] == 4)
                    ants_pos[i].first += 0.5;

                // 180도 중간에서 만나는 경우
                for (int j = 0; j < i; ++j)
                {
                    if (ants_pos[i] == ants_pos[j])
                    {
                        int temp = ants_dir[i];
                        ants_dir[i] = ants_dir[j];
                        ants_dir[j] = temp;
                    }
                }
            }

            // 두번째 절반 이동
            for (int i = 0; i < N; ++i)
            {
                // 경계를 나간 경우 무시
                if (ants_dir[i] == -1)
                    continue;
                // 두번째 이동
                if (ants_dir[i] == 1)
                    ants_pos[i].second += 0.5;

                else if (ants_dir[i] == 2)
                    ants_pos[i].second -= 0.5;

                else if (ants_dir[i] == 3)
                    ants_pos[i].first -= 0.5;

                else if (ants_dir[i] == 4)
                    ants_pos[i].first += 0.5;

                // 서로 부딪히는 경우 방향 교환
                for (int j = 0; j < i; ++j)
                {
                    if (ants_pos[i] == ants_pos[j])
                    {
                        int temp = ants_dir[i];
                        ants_dir[i] = ants_dir[j];
                        ants_dir[j] = temp;
                    }
                }

                // 다른 경계에 닿은 경우 무시 처리
                if (ants_pos[i].first == 0 || ants_pos[i].second == 0 || ants_pos[i].second == M)
                {
                    ants_dir[i] = -1;
                    ants_pos[i].first = -1;
                    ants_pos[i].second = -1;
                }

                // x=M에 닿은 경우 y좌표가 작은 것부터 출력
                // pq를 이용하여 y좌표와 index를 저장
                else if (ants_pos[i].first == M)
                {
                    escape_count++;
                    escape_ants.push(make_pair(-ants_pos[i].second, i + 1));
                }
            }

            // pq에 들어있는 도착한 개미들을 result에 저장
            int kth_escape_ants = escape_ants.size();
            for (int i = 0; i < kth_escape_ants; ++i)
            {
                result.push_back(escape_ants.top());
                escape_ants.pop();
            }
        }

        cout << "#" << t << " " << count << " " << result[K - 1].second << endl;
    }

    return 0;
}