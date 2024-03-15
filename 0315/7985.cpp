#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("7985.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        int K;
        cin >> K;

        vector<string> result(K, "");

        int totalCount = pow(2, K);

        for (int j = 1; j < totalCount; ++j)
        {
            int num;
            cin >> num;

            int shiftCount = 0;
            while (shiftCount < K)
            {
                if (j & (1 << shiftCount))
                {
                    result[shiftCount] += to_string(num) + " ";
                    break;
                }
                shiftCount++;
            }
        }

        cout << "#" << i << " ";

        for (int j = K - 1; j >= 0; --j)
        {
            cout << result[j] << endl;
        }
    }

    return 0;
}