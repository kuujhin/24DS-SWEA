#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    freopen("test.txt", "r", stdin);

    int T;
    cin >> T;

    for (int t = 1; t <= T; ++t)
    {
        string str;
        cin >> str;

        cout << "#" << t << " " << endl;
    }

    return 0;
}