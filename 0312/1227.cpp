#include <iostream>
// #include <stack>
#include <queue>

using namespace std;

int main(int argc, char **argv)
{

    freopen("1227.txt", "r", stdin);

    for (int i = 1; i <= 10; ++i)
    {
        int tcnum;
        cin >> tcnum;

        int maze[100][100];
        int start_x, start_y, end_x, end_y;

        for (int j = 0; j < 100; ++j)
        {
            for (int k = 0; k < 100; ++k)
            {
                char temp;
                cin >> temp;
                maze[j][k] = temp - '0';
                if (maze[j][k] == 2)
                {
                    start_x = k;
                    start_y = j;
                }
                if (maze[j][k] == 3)
                {
                    end_x = k;
                    end_y = j;
                }
            }
        }

        int x = start_x;
        int y = start_y;
        int up, down, left, right;
        bool find = false;

        //////// stack을 이용한 DFS /////////
        ////////  13,556kb, 20ms   /////////
        // stack<int> crossroads;

        //////// queue를 이용한 BFS /////////
        queue<int> crossroads;

        while (1)
        {
            up = maze[y - 1][x];
            down = maze[y + 1][x];
            left = maze[y][x - 1];
            right = maze[y][x + 1];
            if (up == 3 || down == 3 || left == 3 || right == 3)
            {
                find = true;
                break;
            }

            if (!up && down && left && right)
            {
                maze[y][x] = 1;
                y--;
            }
            else if (up && !down && left && right)
            {
                maze[y][x] = 1;
                y++;
            }
            else if (up && down && !left && right)
            {
                maze[y][x] = 1;
                x--;
            }
            else if (up && down && left && !right)
            {
                maze[y][x] = 1;
                x++;
            }
            else
            {
                if (!up)
                {
                    crossroads.push(y);
                    crossroads.push(x);
                    maze[y][x] = 1;
                    y--;
                }
                else if (!down)
                {
                    crossroads.push(y);
                    crossroads.push(x);
                    maze[y][x] = 1;
                    y++;
                }
                else if (!left)
                {
                    crossroads.push(y);
                    crossroads.push(x);
                    maze[y][x] = 1;
                    x--;
                }
                else if (!right)
                {
                    crossroads.push(y);
                    crossroads.push(x);
                    maze[y][x] = 1;
                    x++;
                }
                else
                {
                    if (crossroads.empty())
                    {
                        break;
                    }
                    // stack을 이용한 DFS
                    // x = crossroads.top();
                    // crossroads.pop();
                    // y = crossroads.top();
                    // crossroads.pop();

                    // queue를 이용한 BFS
                    y = crossroads.front();
                    crossroads.pop();
                    x = crossroads.front();
                    crossroads.pop();
                }
            }
        }
        if (find)
            cout << "#" << tcnum << " " << 1 << endl;
        else
            cout << "#" << tcnum << " " << 0 << endl;
    }

    return 0;
}