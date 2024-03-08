#include <iostream>
#include <list>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("1230.txt", "r", stdin);

    int tcnum = 10;

    for (int i = 1; i <= tcnum; ++i)
    {
        int n;
        cin >> n;

        list<int> v(n);
        list<int>::iterator iter, iter_end;

        for (int j = 0; j < n; ++j)
        {
            int temp;
            cin >> temp;
            v.push_back(temp);
        }

        int m;
        cin >> m;

        for (int j = 0; j < m; ++j)
        {
            char c;
            cin >> c;

            int x, y, s;

            switch (c)
            {
            case 'I':
                cin >> x >> y;

                iter = v.begin();
                advance(iter, x);

                for (int k = 0; k < y; ++k)
                {
                    cin >> s;
                    v.insert(iter, s);
                }

                break;

            case 'D':
                cin >> x >> y;

                iter = v.begin();
                advance(iter, x + 1);

                iter_end = iter;
                advance(iter_end, y);

                v.erase(iter, iter_end);

                break;

            case 'A':
                cin >> y;
                for (int k = 0; k < y; ++k)
                {
                    cin >> s;
                    v.emplace_back(s);
                }
                break;
            }
        }

        cout << "#" << i << " ";

        for (int j = 0; j < 10; ++j)
        {
            cout << v.front() << " ";
            v.pop_front();
        }
        cout << endl;
    }

    return 0;
}