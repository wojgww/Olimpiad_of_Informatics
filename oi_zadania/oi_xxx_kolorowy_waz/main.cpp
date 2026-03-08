#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int m, p, n;
    cin >> m >> p >> n;
    vector<vector<int>> snacks;
    snacks.resize(m + 1);
    int x, y, c;
    for (int i = 1; i <= m; i++)
        snacks[i].resize(m + 1);
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= m; j++)
            snacks[i][j] =  -1;
    for (int i = 0; i < p; i++)
    {
        cin >> y >> x >> c;
        snacks[y][x] = c;
    }
    vector<int> snake;
    snake.push_back(0);
    int current = 0;
    vector<vector<int>> time;
    time.resize(m + 1);
    for (int i = 1; i <= m; i++)
        time[i].resize(m + 1);
    for (int i = 1; i <= m; i++)
        for (int j = 1; j <= m ; j++)
            time[i][j] = -1;
    time[1][1] = 0;
    pair<int, int> position = make_pair(1, 1); // y x
    for (int i = 0; i < n; i++)
    {
        char task;
        cin >> task;
        if (task == 'Z')
        {
            int a, b;
            cin >> a >> b;
            //koniec snake to jest jego glowa
            //order od konca
            if (time[a][b] >= 0)
            {
                int order = current - time[a][b];
                if (order >= snake.size())
                    cout << -1 << '\n';
                else
                {
                    cout << snake[snake.size() - order - 1] << '\n';
                }
            }
            else
            {
                cout << -1 << '\n';
            }
        }
        else
        {
            current++;
            if(task == 'G')
                position = make_pair(position.first -1, position.second);
            else if(task == 'D')
                position = make_pair(position.first + 1, position.second);
            else if(task == 'L')
                position = make_pair(position.first, position.second - 1);
            else
                position = make_pair(position.first, position.second + 1);
            time[position.first][position.second] = current;
            if(snacks[position.first][position.second] >= 0)
            {
                snake.push_back(snacks[position.first][position.second]);
                snacks[position.first][position.second] = -1;
            }
        }
    }

    return 0;
}
