#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("3307.txt", "r", stdin);

    int T, N;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        cin >> N;

        int A[N];

        int C[N + 1] = {0};
        int LisLength = 0;

        for (int j = 0; j < N; ++j)
        {
            cin >> A[j];

            int low = 0;
            int high = LisLength;

            while (low <= high)
            {
                int mid = (low + high) / 2;

                if (C[mid] < A[j])
                {
                    low = mid + 1;
                }
                else
                {
                    high = mid - 1;
                }
            }

            C[low] = A[j];

            if (low > LisLength)
            {
                LisLength = low;
            }
        }

        cout << "#" << i << " " << LisLength << endl;
    }

    return 0;
}