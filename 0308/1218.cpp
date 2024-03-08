#include <iostream>
#include <stack>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("1218.txt", "r", stdin);

    int tcnum = 10;

    for (int i = 1; i <= tcnum; ++i)
    {
        int isValid = 1;
        int len;
        stack<char> myStack;

        cin >> len;

        for (int j = 0; j < len; ++j)
        {
            char temp;
            cin >> temp;

            if (!isValid)
                continue;

            if (temp == '(' || temp == '{' || temp == '[' || temp == '<')
            {
                myStack.push(temp);
            }
            else if (temp == ')' || temp == '}' || temp == ']' || temp == '>')
            {
                if (myStack.empty())
                {
                    isValid = 0;
                }
                else
                {
                    char top = myStack.top();
                    myStack.pop();

                    if ((temp == ')' && top != '(') || (temp == '}' && top != '{') || (temp == ']' && top != '[') || (temp == '>' && top != '<'))
                    {
                        isValid = 0;
                    }
                }
            }
        }

        cout << "#" << i << " " << isValid << endl;
    }

    return 0;
}