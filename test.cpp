#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

    // FILE *sfp;
    // sfp = freopen("1221.txt", "r", stdin);

    int tcnum;
    cin >> tcnum;

    for (int i = 1; i <= tcnum; ++i)
    {
        string str;
        cin >> str;

        cout << "#" << i << " " << str << endl;
    }

    // fclose(sfp);
    return 0;
}