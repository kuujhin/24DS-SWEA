#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

// 16진수->2진수 string
string hexToBinary(char hex)
{
    switch (hex)
    {
    case '0':
        return "0000";
    case '1':
        return "0001";
    case '2':
        return "0010";
    case '3':
        return "0011";
    case '4':
        return "0100";
    case '5':
        return "0101";
    case '6':
        return "0110";
    case '7':
        return "0111";
    case '8':
        return "1000";
    case '9':
        return "1001";
    case 'A':
        return "1010";
    case 'B':
        return "1011";
    case 'C':
        return "1100";
    case 'D':
        return "1101";
    case 'E':
        return "1110";
    case 'F':
        return "1111";
    }
    return "0000";
}

// 2진수로 변환된 배열을 입력으로 받아 암호코드로 추정되는 부분을 찾아 set에 저장
set<string> find_Segment(const vector<string> &code, int N, int M)
{
    set<string> code_list;

    for (int r = 0; r < N; ++r)
    {
        for (int c = M - 1; c >= 0; --c)
        {
            if (code[r][c] != '0')
            {
                code_list.insert(code[r].substr(0, c + 1));
                break;
            }
        }
    }

    return code_list;
}

// 추정된 암호코드를 디코딩하고 검증하여 정상적인 암호코드인지 확인
int decode_validate(const set<string> &code_list, const map<string, int> &dict)
{
    int answer = 0;
    vector<vector<int>> patterns;

    for (auto &encoded : code_list)
    {
        string new_code = "";
        for (char digit : encoded)
        {
            new_code += hexToBinary(digit);
        }
        vector<int> result;
        int c1 = 0, c2 = 0, c3 = 0;
        for (int i = new_code.length() - 1; i >= 0; --i)
        {
            if (c2 == 0 && c3 == 0 && new_code[i] == '1')
                c1++;
            else if (c1 > 0 && c3 == 0 && new_code[i] == '0')
                c2++;
            else if (c1 > 0 && c2 > 0 && new_code[i] == '1')
                c3++;
            else if (c1 > 0 && c2 > 0 && c3 > 0 && new_code[i] == '0')
            {
                int min_cnt = min(min(c1, c2), c3);
                c1 /= min_cnt;
                c2 /= min_cnt;
                c3 /= min_cnt;
                string pattern = to_string(c1) + to_string(c2) + to_string(c3);
                result.push_back(dict.at(pattern));
                c1 = c2 = c3 = 0;
                if (result.size() == 8)
                {
                    bool isNewPattern = true;
                    for (auto &pat : patterns)
                    {
                        if (pat == result)
                        {
                            isNewPattern = false;
                            break;
                        }
                    }
                    if (isNewPattern)
                    {
                        patterns.push_back(result);
                        int total = 0;
                        for (int j = 0; j < 8; ++j)
                        {
                            if (j % 2 == 0)
                                total += result[j];
                            else
                                total += result[j] * 3;
                        }
                        if (total % 10 == 0)
                        {
                            for (int num : result)
                                answer += num;
                        }
                    }
                    result.clear();
                }
            }
        }
    }
    return answer;
}

int main()
{
    map<string, int> dict = {{"112", 0}, {"122", 1}, {"221", 2}, {"114", 3}, {"231", 4}, {"132", 5}, {"411", 6}, {"213", 7}, {"312", 8}, {"211", 9}};
    int test_case;
    int T;
    cin >> T;

    for (test_case = 1; test_case <= T; ++test_case)
    {
        int N, M;
        cin >> N >> M;

        vector<string> code(N);

        for (int i = 0; i < N; ++i)
        {
            cin >> code[i];
        }

        set<string> code_list = find_Segment(code, N, M);
        int answer = decode_validate(code_list, dict);

        cout << "#" << test_case << " " << answer << "\n";
    }
    return 0;
}