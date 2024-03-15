#include <iostream>
#include <vector>
#include <stack>
#include <string>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("1232.txt", "r", stdin);

    int T = 10;

    int N, index, l, r;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        stack<pair<char, pair<int, int>>> symbolStack;
        vector<float> resultTree(N + 1, 0);

        for (int j = 0; j < N; ++j)
        {
            cin >> index;

            string s;
            cin >> s;

            char c = s[0];

            if (c == '+' || c == '-' || c == '*' || c == '/')
            {
                cin >> l >> r;
                symbolStack.push(make_pair(c, make_pair(l, r)));
            }
            else
            {
                resultTree[index] = stoi(s);
            }
        }

        for (int j = N; j > 0; --j)
        {
            if (resultTree[j] == 0)
            {
                char c = symbolStack.top().first;
                int leftIndex = symbolStack.top().second.first;
                int rightIndex = symbolStack.top().second.second;

                symbolStack.pop();
                float left = resultTree[leftIndex];
                float right = resultTree[rightIndex];
                if (c == '+')
                {
                    resultTree[j] = left + right;
                }
                else if (c == '-')
                {
                    resultTree[j] = left - right;
                }
                else if (c == '*')
                {
                    resultTree[j] = left * right;
                }
                else if (c == '/')
                {
                    resultTree[j] = left / right;
                }
            }
        }

        cout << "#" << i << " " << resultTree[1] << endl;
    }

    return 0;
}