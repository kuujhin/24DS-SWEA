#include <iostream>
#include <string>

using namespace std;

// 중복된 수가 존재하는지 체크
bool checktwice(string num)
{
    int check[10] = {0};
    bool flag = false;
    int size = num.size();
    for (int i = 0; i < size; i++)
    {
        check[num[i] - '0']++;
        if (check[num[i] - '0'] > 1)
        {
            flag = true;
            break;
        }
    }
    return flag;
}

// 첫번째 자리부터 탐색하여 최대값을 찾아 교환
int change(string num, int count, int change_count, int max_change)
{
    int size = num.size();

    // 교환 횟수가 최대 교환 횟수와 같아 졌을 때 그대로 반환
    if (change_count == max_change)
    {
        return stoi(num);
    }

    // 모든 자릿수를 탐색했을 때
    if (count == size)
    {
        // 남은 교환이 2n번 남은경우 이거나 중복된 수가 존재하는 경우 그대로 반환
        if (((max_change - change_count) % 2 == 0) || checktwice(num))
        {
            return stoi(num);
        }
        // 그 외의 경우 마지막 두 자리를 교환하여 최대한 큰 수를 유지
        else
        {
            swap(num[size - 1], num[size - 2]);
            return stoi(num);
        }
    }

    int max = num[count] - '0'; // 현재 자릿수의 최댓값
    int max_count = 0;          // 최댓값의 개수
    int max_index;              // 마지막으로 등장하는 최댓값 인덱스
    int max_list[6] = {0};      // 최대값의 인덱스를 저장
    int list_index = 0;         // 최댓값 체크

    // 현재 자릿수의 수보다 큰 숫자들 탐색
    for (int i = count; i < size; i++)
    {
        if (num[i] - '0' == max)
        {
            max_count++;
            max_list[list_index++] = i;
            max_index = i;
        }
        else if (num[i] - '0' > max)
        {
            max_count = 1;
            max = num[i] - '0';
            list_index = 0;
            max_list[list_index++] = i;
            max_index = i;
        }
    }

    // 현재 자릿수의 수보다 큰 수가 존재하는 경우 교환 진행
    if (max > num[count] - '0')
    {
        // 최댓값이 2개 이상인 경우
        if (max_count > 1)
        {
            int less_count = 0;
            for (int i = count; i < max_list[0]; i++)
            {
                if (num[i] - '0' < max)
                {
                    less_count++;
                }
            }

            // 최댓값과 몇개나 바꿀지 계산. 남은 교환 횟수와 최댓값보다 작은 수의 개수를 고려
            int t = min(less_count, max_change - change_count);

            swap(num[max_list[list_index - t]], num[count]);
            return change(num, count + 1, change_count + 1, max_change);
        }

        // 최댓값이 1개인 경우 단순 교환 진행 후 다음 자릿수 탐색
        else
        {
            swap(num[max_index], num[count]);
            return change(num, count + 1, change_count + 1, max_change);
        }
    }

    // 현재 자릿수의 수가 최대값인 경우 다음 자릿수 탐색
    else
    {
        return change(num, count + 1, change_count, max_change);
    }
}

int main(int argc, char **argv)
{

    freopen("1244.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        string str;
        cin >> str;

        int cnt;
        cin >> cnt;

        cout << "#" << i << " " << change(str, 0, 0, cnt) << endl;
    }

    return 0;
}