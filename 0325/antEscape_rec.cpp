// TestCase 10개, 제한시간 C++ 1초

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
        priority_queue<pair<pair<int, int>, int>> right_ants;

        int right_ants_count = 0;

        for (int i = 0; i < N; ++i)
        {
            int x, y, dir;
            cin >> x >> y >> dir;
            ants_pos[i] = make_pair(x, y);
            ants_dir[i] = dir;
            if (dir == 4)
            {
                right_ants_count++;
                right_ants.push(make_pair(make_pair(x, -y), i + 1));
            }
        }

        if (right_ants_count < K)
        {
            cout << "#" << t << " 0 0" << endl;
            continue;
        }

        for (int i = 1; i < K; ++i)
        {
            right_ants.pop();
        }
        int kth_x = right_ants.top().first.first;
        int kth_y = -right_ants.top().first.second;
        int kth_index = right_ants.top().second;

        int index = myLoop(kth_x, kth_y, 4, ants_pos, ants_dir);

        cout << kth_x << " " << kth_y << " " << kth_index << endl;
        // 빠져나간 개미의 수
        int escape_count = 0;
        // 경과 시간
        int count = 0;
        // 1 ~ k번째로 빠져나간 개미의 index 저장
        vector<pair<int, int>> result;

        cout << "#" << t << " " << count << " " << result[K - 1].second << endl;
    }

    return 0;
}