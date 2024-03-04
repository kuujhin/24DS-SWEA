#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // FILE *sfp;
    // sfp = freopen("3260_in.txt", "r", stdin);

    int num;
    cin >> num;

    for (int i = 0; i < num; i++)
    {
        string a, b;
        cin >> a >> b;

        int a_len = a.length();
        int b_len = b.length();

        if (a_len < b_len)
        {
            for (int j = 0; j < b_len - a_len; j++)
            {
                a = "0" + a;
            }
        }
        else if (a_len > b_len)
        {
            for (int j = 0; j < a_len - b_len; j++)
            {
                b = "0" + b;
            }
        }

        int len = a.length();
        for (int j = len - 1; j >= 1; j--)
        {
            if (a[j] - '0' + b[j] - '0' > 9)
            {
                a[j - 1] = a[j - 1] + 1;
                a[j] = (a[j] - '0' + b[j] - '0') % 10 + '0';
            }
            else
            {
                a[j] = a[j] + b[j] - '0';
            }
        }

        if (a[0] - '0' + b[0] - '0' > 9)
        {
            a[0] = (a[0] - '0' + b[0] - '0') % 10 + '0';
            cout << "#" << i + 1 << " "
                 << "1" << a << "\n";
        }
        else
        {
            a[0] = a[0] + b[0] - '0';
            cout << "#" << i + 1 << " " << a << "\n";
        }
    }

    // fclose(sfp);
    return 0;
}