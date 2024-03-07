#include <iostream>
#include <cmath>

using namespace std;

int n = 18;
int nonprime[12] = {0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18};

int comb(int n, int r)
{
    if (r == 0 || n == r)
        return 1;
    else
        return comb(n - 1, r - 1) + comb(n - 1, r);
}

double making(double p)
{
    double pr_sum = 0.0;
    for (int i = 0; i < 12; i++)
    {
        int r = nonprime[i];
        pr_sum += comb(n, r) * pow(p, r) * pow(1 - p, n - r);
    }
    return pr_sum;
}

int main(int argc, char **argv)
{

    // freopen("1266.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        double skill_a, skill_b;
        cin >> skill_a >> skill_b;
        double p1 = making(skill_a / 100);
        double p2 = making(skill_b / 100);

        cout << "#" << i << " ";
        cout << fixed;
        cout.precision(6);
        cout << 1 - p1 * p2 << endl;
    }

    return 0;
}