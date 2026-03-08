#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

void bfs(queue<int> &q, vector<vector<bool>> &graf, vector<vector<bool>> &visited, vector<vector<int>> &odl, int n, int m);

int main()
{
    int n;
    int m;
    cin >> n >> m;
    vector<vector<bool>> graf;
    vector<vector<bool>> visited;
    vector<vector<int>> odl;
    graf.resize(n);
    visited.resize(n);
    odl.resize(n);
    queue<int> q;
    string a;
    for (int i = 0; i < n; i++)
    {
        graf[i].resize(m);
        visited[i].resize(m);
        odl[i].resize(m);
        cin >> a;
        for (int j = 0; j < m; j++)
        {
            if (a[j] == '1')
                graf[i][j] = 1;
            else
                graf[i][j] = 0;
            if (a[j] == '1')
            {
                q.push(i * m + j);
                visited[i][j] = 1;
                odl[i][j] = 0;
            }
            else
            {
                visited[i][j] = 0;
                odl[i][j] = -1;
            }
        }
    }//
    //bfs prosto
    bfs(q,graf,visited,odl,n,m);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            cout << odl[i][j] << " ";
        }
        cout << endl;
    }


    return 0;
}

void bfs(queue<int> &q, vector<vector<bool>> &graf, vector<vector<bool>> &visited, vector<vector<int>> &odl, int n, int m)
{ //n wierszy  po m znakow !!!!!!!!!!!!!!!!!!
    //i * n + j
    pair<int, int> current;
    int x, y;
    int w;
    while(q.size())
    {
        w = q.front();
        q.pop();
        current = make_pair(w / m, w % m);
        //dodac 8 wierzcholkow
        if (current.first + 1 < n) //pierwszy
        {
            if (visited[current.first + 1][current.second] == 0)
            {
                odl[current.first + 1][current.second] = odl[current.first][current.second] + 1;
                visited[current.first + 1][current.second] = 1;
                q.push((current.first+ 1) * m + current.second);
            }
        }
        if (current.first - 1 >= 0)
        {
            if (visited[current.first - 1][current.second] == 0)
            {
                odl[current.first - 1][current.second] = odl[current.first][current.second] + 1;
                visited[current.first - 1][current.second] = 1;
                q.push((current.first- 1) * m + current.second);
            }
        }
        if (current.second + 1 < m)
        {
            if (visited[current.first][current.second + 1] == 0)
            {
                odl[current.first][current.second + 1] = odl[current.first][current.second] + 1;
                visited[current.first][current.second + 1] = 1;
                q.push(current.first * m + current.second + 1);
            }
        }
        if (current.second - 1 >= 0)
        {
            if (visited[current.first][current.second - 1] == 0)
            {
                odl[current.first][current.second - 1] = odl[current.first][current.second] + 1;
                visited[current.first][current.second - 1] = 1;
                q.push(current.first * m + current.second - 1);
            }
        }
    }
}
