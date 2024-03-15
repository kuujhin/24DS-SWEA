#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char **argv)
{

    // freopen("1248.txt", "r", stdin);

    int T;
    cin >> T;

    for (int i = 1; i <= T; ++i)
    {
        int V, E, A, B;
        cin >> V >> E >> A >> B;

        vector<vector<int>> binaryTree(V + 1, vector<int>(5, 0));
        // Left, Right, Parent, Height, Size

        for (int j = 0; j < E; j++)
        {
            int parent, child;
            cin >> parent >> child;

            if (binaryTree[parent][0] == 0)
            {
                binaryTree[parent][0] = child;
            }
            else
            {
                binaryTree[parent][1] = child;
            }

            binaryTree[child][2] = parent;
            if (binaryTree[child][4] == 0)
            {
                binaryTree[child][4] = 1;
            }

            while (parent != 0)
            {
                if (binaryTree[parent][3] < binaryTree[child][3] + 1)
                {
                    binaryTree[parent][3] = binaryTree[child][3] + 1;
                }

                binaryTree[parent][4] = binaryTree[binaryTree[parent][0]][4] + binaryTree[binaryTree[parent][1]][4] + 1;

                child = parent;
                parent = binaryTree[parent][2];
            }
        }

        while (A != 0 || B != 0)
        {
            if (binaryTree[A][3] < binaryTree[B][3])
            {
                A = binaryTree[A][2];
            }
            else if (binaryTree[A][3] > binaryTree[B][3])
            {
                B = binaryTree[B][2];
            }
            else
            {
                if (A == B)
                {
                    break;
                }
                A = binaryTree[A][2];
                B = binaryTree[B][2];
            }
        }

        cout << "#" << i << " " << A << " " << binaryTree[A][4] << endl;
    }

    return 0;
}