#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("1267.txt", "r", stdin);

    int tcnum = 10;

    for (int i = 1; i <= tcnum; ++i)
    {
        int v, e;
        cin >> v >> e;

        vector<vector<int>> edges(v, vector<int>(v, 0));
        vector<int> indegree(v, 0);

        for (int j = 0; j < e; ++j)
        {
            int temp1, temp2;
            cin >> temp1 >> temp2;
            edges[temp1 - 1][temp2 - 1] = 1;
            indegree[temp2 - 1]++;
        }

        string result = " ";
        for (int j = 0; j < v; ++j)
        {
            int w;
            // for (int k = v - 1; k >= 0; --k)
            for (int k = 0; k < v; ++k)
            {
                if (indegree[k] == 0)
                {
                    w = k;
                    break;
                }
            }
            result += to_string(w + 1) + " ";
            indegree[w] = -1;
            for (int k = 0; k < v; ++k)
            {
                if (edges[w][k] == 1)
                {
                    indegree[k]--;
                }
            }
        }
        cout << "#" << i << result << endl;
    }

    return 0;
}