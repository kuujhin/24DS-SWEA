#include <iostream>
#include <unordered_set>

using namespace std;

int main(int argc, char **argv)
{

    freopen("2948.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        int N, M;
        cin >> N >> M;

        unordered_set<string> mySet;
        int count = 0;
        string temp;

        for (int j = 0; j < N; ++j)
        {
            cin >> temp;
            mySet.emplace(temp);
        }

        for (int j = 0; j < M; ++j)
        {
            cin >> temp;
            if (mySet.find(temp) != mySet.end())
            {
                count++;
            }
        }

        cout << "#" << i << " " << count << endl;
    }

    return 0;
}