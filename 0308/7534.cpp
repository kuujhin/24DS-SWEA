#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char **argv)
{

    freopen("7534.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n;
        cin >> n;

        vector<int> inputList(n);
        for (int j = 0; j < n; ++j)
        {
            cin >> inputList[j];
        }

        if (inputList[n - 1] != 1)
        {
            cout << "#" << i << " NO" << endl;
            continue;
        }

        int input_list_count = 0;
        int stack_count = 0;
        stack<int> myStack;
        bool isValid = true;
        string result = "";
        vector<int> pushedList(n + 1);

        while (1)
        {
            if (pushedList[inputList[input_list_count]] == 1)
            {
                if (myStack.top() == inputList[input_list_count])
                {
                    isValid = false;
                    break;
                }
                else
                {
                    myStack.pop();
                    result += "-";
                    input_list_count++;
                }
            }
            else
            {
                for (int j = stack_count; j <= inputList[input_list_count]; ++j)
                {
                    myStack.push(stack_count++);
                    result += "+";
                    pushedList[j] = 1;
                }
            }
        }

        isValid ? cout << "#" << i << " " << result << endl : cout << "#" << i << " NO" << endl;
    }

    return 0;
}