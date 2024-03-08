#include <iostream>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("7534.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n;
        cin >> n;

        vector<int> numberlist(n);
        for (int j = 0; j < n; ++j)
        {
            cin >> numberlist[j];
        }

        if (numberlist[n - 1] != 1)
        {
            cout << "#" << i << " NO" << endl;
            continue;
        }

        int list_count = 0;
        int stack_count = 0;
        stack<int> myStack;
        bool isValid = true;
        string result = "";
        while (list_count < n)
        {
            if (myStack.empty())
            {
                if (stack_count == n)
                {
                    break;
                }
                stack_count++;
                myStack.push(stack_count);
                result += "+";
            }
            else if (myStack.top() != numberlist[list_count])
            {
                if (stack_count == n)
                {
                    isValid = false;
                    break;
                }
                stack_count++;
                myStack.push(stack_count);
                result += "+";
            }
            else
            {
                if (myStack.empty())
                {
                    break;
                }
                myStack.pop();
                result += "-";
                list_count++;
            }
        }

        isValid ? cout << "#" << i << " " << result << endl : cout << "#" << i << " NO" << endl;
    }

    return 0;
}