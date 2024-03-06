#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

    freopen("9999.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        int L, N;
        cin >> L >> N;

        vector<int> s(N);
        vector<int> e(N);
        for (int j = 0; j < N; ++j)
        {
            cin >> s[j] >> e[j];
        }

        cout << "#" << i << " " << endl;
    }

    return 0;
}