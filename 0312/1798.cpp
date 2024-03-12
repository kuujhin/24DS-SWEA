#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;
int maxTime = 9 * 60;

int maxScore;
string maxPath;
int endIndex, totalIndex;

void _search(int score, int currentTime, int currentIndex,
             int leftDay, bool isStart, string path,
             vector<vector<int>> tourpoint, vector<vector<int>> timetable)
{
    if (leftDay < 0)
        return;

    // 방문 한 적 없는 다음 여행지로 이동
    // [index, type, time, score, visited]
    for (int i = 0; i < totalIndex; ++i)
    {
        if (tourpoint[i][4] == 0 && i != currentIndex)
        {
            // 공항인 경우 마지막 날인지 확인
            if (tourpoint[i][1] == 0 && !isStart)
            {
                if (leftDay > 0)
                    continue;
                else
                {
                    // 마지막날인 경우 만족도 비교 후 종료
                    if (score > maxScore)
                    {
                        cout << "return airport" << endl;
                        cout << "path: " << path << " score: " << score << endl;
                        cout << "score: " << score << " time: " << currentTime << endl;
                        maxScore = score;
                        maxPath = path;
                    }
                    return;
                }
            }
            // 호텔인 경우 다음 날 장소 탐색
            if (tourpoint[i][1] == 2)
            {
                string newPath = path + " " + to_string(tourpoint[i][0]);

                // cout << "return hotel" << endl;
                // cout << "path: " << path << " score: " << score << endl;
                // cout << "score: " << score << " time: " << currentTime << endl;
                _search(score, 0, i, leftDay - 1, false, newPath, tourpoint, timetable);
            }

            // 관광지인 경우 이동 시간과 관광 시간 및 만족도를 계산
            else
            {

                int moveTime = timetable[currentIndex][i];
                if (moveTime == 0)
                    moveTime = timetable[i][currentIndex];
                int tourTime = tourpoint[i][2];

                int newTime = moveTime + tourTime + currentTime;
                if (newTime > maxTime)
                    return;

                int newScore = score + tourpoint[i][3];

                string newPath = path + " " + to_string(tourpoint[i][0]);

                cout << "score: " << newScore << " time: " << newTime << " index: " << i;
                cout << " day: " << leftDay << " path: " << newPath << endl;

                tourpoint[i][4] = 1;
                _search(newScore, newTime, i, leftDay, false, newPath, tourpoint, timetable);
                tourpoint[i][4] = 0;
            }
        }
    }
}

int main(int argc, char **argv)
{

    freopen("1798.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= 1; ++i)
    {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> timetable(n, vector<int>(n, 0));

        for (int j = 0; j < n; ++j)
        {
            for (int k = j + 1; k < n; ++k)
            {
                cin >> timetable[j][k];
            }
        }

        vector<vector<int>> point(n, vector<int>(5, 0));
        // [index, type, time, score, visited]
        for (int j = 0; j < n; ++j)
        {
            char temp;
            cin >> temp;
            switch (temp)
            {
            case 'A':
                endIndex = j;
                point[j][0] = j;
                break;
            case 'P':
                int time, score;
                cin >> time >> score;
                point[j][0] = j;
                point[j][1] = 1;
                point[j][2] = time;
                point[j][3] = score;
                break;
            case 'H':
                point[j][0] = j;
                point[j][1] = 2;
                break;
            }
        }

        totalIndex = n;
        maxScore = -1;

        // for (int j = 0; j < n; ++j)
        // {
        //     cout << point[j][0] << " " << point[j][1] << " " << point[j][2] << " " << point[j][3] << " " << point[j][4] << endl;
        // }
        _search(0, 0, 0, m, true, " ", point, timetable);

        cout << "#" << i << maxPath << endl;
    }

    return 0;
}