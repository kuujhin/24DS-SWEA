#include <iostream>

using namespace std;

char bin[2000 + 1][2000 + 1];
char NUMS[64] = {
    0,
};

int main(int argc, char **argv)
{
    freopen("test.txt", "r", stdin);

    // 암호 매칭과정의 시간복잡도 : O (1)
    NUMS[13] = 0;
    NUMS[25] = 1;
    NUMS[19] = 2;
    NUMS[61] = 3;
    NUMS[35] = 4;
    NUMS[49] = 5;
    NUMS[47] = 6;
    NUMS[59] = 7;
    NUMS[55] = 8;
    NUMS[11] = 9;

    int sX, sY, eX, eY = -1; // 암호코드가 존재하는 좌표 중 x, y 좌표의 최솟값과 최댓값
    int final_result = 0;    // 최종 결과값

    int tcnum;
    cin >> tcnum;

    int i, j;
    int N, M;
    int x, y;
    for (int tc = 1; tc <= tcnum; ++tc)
    {
        cin >> N;
        cin >> M;

        sX = sY = eX = eY = -1;
        x = 1;
        y = 0;
        final_result = 0;
        bool isEmptyLine = true;
        // 데이터 읽기
        for (i = 1; i <= N; ++i)
        {
            for (j = 0; j < 4 * M;)
            {
                char temp;
                cin >> temp;

                // 0을 입력받은 경우 16진수를 2진수로 바로 변환
                if (temp != '0')
                {
                    isEmptyLine = false;
                    // 16진수를 10진수로 변환 후 2진수로 변환
                    if (temp <= '9')
                        temp -= '0';
                    else
                        temp = temp - 'A' + 10;

                    bin[i][++j] = (temp & 0x08) ? '1' : '0';
                    bin[i][++j] = (temp & 0x04) ? '1' : '0';
                    bin[i][++j] = (temp & 0x02) ? '1' : '0';
                    bin[i][++j] = (temp & 0x01) ? '1' : '0';

                    // 암호코드가 존재하는 좌표 중 x, y 좌표의 최솟값과 최댓값을 찾아 해당 범위만 탐색한다.
                    if (sX < 0 && sY < 0)
                    {
                        sX = j;
                        sY = i;
                    }
                    sX = min(sX, j);
                    eX = max(eX, j);
                    eY = i;
                }
                // if (temp == '0' && !isEmptyLine)
                if (temp == '0')
                {
                    bin[i][++j] = '0';
                    bin[i][++j] = '0';
                    bin[i][++j] = '0';
                    bin[i][++j] = '0';
                }
                else
                {
                    // j += 4;
                }
            }
        }

        int index = 7;
        int odd = 0;
        int even = 0;

        for (i = sY; i <= eY; i++) // 위에서 아래로 탐색
        {
            for (j = eX; j >= sX; --j) // 오른쪽에서 왼쪽으로 탐색
            {
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
                    int ratio = min(count[0], min(count[1], count[2]));
                    count[0] /= ratio;
                    count[1] /= ratio;
                    count[2] /= ratio;
                    int total = count[0] + count[1] + count[2];

                    // res 값에 기본 크기의 암호코드 값을 저장한다.
                    int res = 0;
                    for (int k = 0; k < count[0]; ++k)
                        res = res | (1 << k);
                    for (int k = count[0] + count[1]; k < total; ++k)
                        res = res | (1 << k);

                    res = NUMS[res];

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