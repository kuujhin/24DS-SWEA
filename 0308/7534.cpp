#include <iostream>
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

        stack<int> myStack;
        int cnt = 1;
        string result = "";
        bool isValid = true;

        for (int j = 0; j < n; ++j)
        {
            int temp;
            cin >> temp;
            while (cnt <= temp)
            {
                myStack.push(cnt++);
                result += "+";
            }

            int t = myStack.top();
            if (t != temp)
            {
                isValid = false;
            }
            myStack.pop();
            result += "-";
        }
        isValid ? cout << "#" << i << " " << result << endl : cout << "#" << i << " NO" << endl;
    }

    return 0;
}