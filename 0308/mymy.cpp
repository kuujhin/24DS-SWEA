#include <iostream>
#include <string.h>

using namespace std;

char bin[2000 + 1][2000 + 1];

char code[2000 + 1][500 + 1];
char NUMS[5][5][5];

int main(int argc, char **argv)
{
    freopen("test.txt", "r", stdin);

    NUMS[2][1][1] = 0;
    NUMS[2][2][1] = 1;
    NUMS[1][2][2] = 2;
    NUMS[4][1][1] = 3;
    NUMS[1][3][2] = 4;
    NUMS[2][3][1] = 5;
    NUMS[1][1][4] = 6;
    NUMS[3][1][2] = 7;
    NUMS[2][1][3] = 8;
    NUMS[1][1][2] = 9;

    int sX, sY, eX, eY = -1; // 암호코드가 존재하는 좌표 중 x, y 좌표의 최솟값과 최댓값
    int final_result = 0;    // 최종 결과값

    int tcnum;
    cin >> tcnum;

    int i, j;
    int N, M;
    for (int tc = 1; tc <= tcnum; ++tc)
    {
        cin >> N;
        cin >> M;

        sX = sY = eX = eY = -1;
        final_result = 0;

        int x = 1;
        int y = 1;

        // 데이터 읽기
        for (i = 1; i <= N; ++i)
        {
            cin >> code[i];
            // for (j = 0; j < 4 * M;)
            if (strcmp(code[i], code[i - 1]) == 0)
                continue;

            bool isFind = false;
            bin[x][0] = '0';
            for (j = 0; j < M; ++j)
            {
                char temp = code[i][j];
                if (temp == '0' && isFind == false)
                    continue;
                isFind = true;

                // 0을 입력받은 경우 16진수를 2진수로 바로 변환
                if (temp == '0')
                {
                    bin[x][4 * y + 1] = '0';
                    bin[x][4 * y + 2] = '0';
                    bin[x][4 * y + 3] = '0';
                    bin[x][4 * y + 4] = '0';
                }
                else
                {
                    // 16진수를 10진수로 변환 후 2진수로 변환
                    if (temp <= '9')
                        temp -= '0';
                    else
                        temp = temp - 'A' + 10;

                    bin[x][4 * y + 1] = (temp & 0x08) ? '1' : '0';
                    bin[x][4 * y + 2] = (temp & 0x04) ? '1' : '0';
                    bin[x][4 * y + 3] = (temp & 0x02) ? '1' : '0';
                    bin[x][4 * y + 4] = (temp & 0x01) ? '1' : '0';

                    // 암호코드가 존재하는 좌표 중 x, y 좌표의 최솟값과 최댓값을 찾아 해당 범위만 탐색한다.
                    if (sX < 0 && sY < 0)
                    {
                        sX = y;
                        sY = x;
                    }
                    sX = min(sX, y);
                    eX = max(eX, y);
                    eY = x;
                }
                y++;
            }
            x++;
        }

        int index = 7;
        int odd = 0;
        int even = 0;

        for (i = 0; i <= x; i++) // 위에서 아래로 탐색
        {
            for (j = 4 * y; j >= 0; --j) // 오른쪽에서 왼쪽으로 탐색
            {
                // cout << bin[i][j] << endl;
                // 암호코드의 끝자리를 찾은 경우 (수직방향으로 반복되므로 맨 위의 줄일 때만 검사)
                // 0번째 줄은 초기화를 안했으므로 '1'이 나올 수 없다. 따라서 바로 붙어있는 경우에도 검사 가능
                if (bin[i][j] == '1' && bin[i - 1][j] != '1')
                {
                    // 암호코드의 끝자리를 찾았으므로 암호코드를 읽는다.
                    int count[3] = {0, 0, 0};
                    bool isFirst = true;
                    bool isSecond = true;

                    // 각 연속된 1, 0, 1의 개수를 센다. (비율을 찾기 위해)
                    while (1)
                    {
                        if (bin[i][j] == '1' && isFirst)
                        {
                            count[0]++;
                        }
                        else if (bin[i][j] == '0' && isSecond)
                        {
                            isFirst = false;
                            count[1]++;
                        }
                        else if (bin[i][j] == '1' && !isFirst)
                        {
                            isSecond = false;
                            count[2]++;
                        }
                        else
                        {
                            break;
                        }
                        j--;
                    }

                    // 코드의 가로가 길어졌는지 확인하기 위해 가장 얇은 부분의 길이를 구하여 그 값으로 모두 나누어 비율을 찾는다.
                    // 모든 암호코드 숫자는 가장 얇은 부분이 1개 이기 때문에 항상 나누어 떨어진다.
                    cout << count[0] << " " << count[1] << " " << count[2] << endl;
                    int ratio = min(count[0], min(count[1], count[2]));

                    int res = 0;
                    res = NUMS[count[2] / ratio][count[1] / ratio][count[0] / ratio];

                    // 짝수 번째 숫자와 홀수 번째 숫자를 구분하여 더한다.
                    if (index & 1)
                    {
                        even += res;
                    }
                    else
                    {
                        odd += res;
                    }
                    // 해당 암호코드의 다음 자릿수를 분석
                    index--;

                    // 8개의 자릿수를 모두 읽었으면 검증
                    if (index < 0)
                    {
                        int R = 3 * odd + even;
                        if (R % 10 == 0)
                        {
                            final_result = final_result + even + odd; // 검증에 성공하면 암호코드의 합을 더한다.
                        }
                        index = 7;
                        odd = 0;
                        even = 0;
                    }
                }
            }
        }

        cout << "#" << tc << " " << final_result << endl;
    }
    return 0;
}