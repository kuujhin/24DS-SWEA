#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    freopen("test.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        string str;
        cin >> str;

        cout << "#" << i << " " << endl;
    }

    return 0;
}