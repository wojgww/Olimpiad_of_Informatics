#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dijkstra(vector<vector<pair<int, long long>>> &graf, vector<long long> &odl, vector<bool> &visited, int n, int y);

int main()
{
    int n;
    cin >> n;
    vector<long long> metale;
    metale.resize(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> metale[i];
    int m;
    cin >> m;
    long long a, b, c;
    vector<vector<pair<int, long long>>> graf1;
    graf1.resize(n + 1);

    vector<vector<pair<int, long long>>> graf2;
    graf2.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        cin >> a >> b >> c;
        graf1[a].push_back(make_pair(b, c));
        graf2[b].push_back(make_pair(a, c));
    }
    vector<long long> odl1;
    odl1.resize(n + 1);
    vector<long long> odl2;
    odl2.resize(n + 1);
    vector<bool> visited;
    visited.resize(n + 1);
    //1 - ZLOTO
    for (int i = 0; i <= n; i++)
    {
        odl1[i] = (long long)(n) * 100000000;
        odl2[i] = (long long)(n) * 100000000;
        visited[i] = 0;
    }
    dijkstra(graf1, odl1, visited, n, 1);
    for (int i = 0; i <= n; i++)
        visited[i] = 0;
    dijkstra(graf2, odl2, visited, n, 1);

    long long min = 10000000000, current;
    for (int i = 1; i <= n; i++)
    {
        current = odl1[i] + odl2[i] + metale[i] /2;
        if (current < min)
            min = current;
    }
    cout << min;

    return 0;
}

void dijkstra(vector<vector<pair<int, long long>>> &graf, vector<long long> &odl, vector<bool> &visited, int n, int y){
    odl[y] = 0;
    priority_queue <pair <long long, int> > q;
    q.push(make_pair(0, y));
    while(q.size()){
        int w = q.top().second;
        q.pop();
        if(visited[w]){
            continue;
        }
        visited[w] = true;
        for(int i = 0; i < graf[w].size(); i++)// : graf[w]){
        {
            if(odl[graf[w][i].first] > odl[w] + graf[w][i].second)
            {
                odl[graf[w][i].first] = odl[w] + graf[w][i].second;
                q.push(make_pair(-odl[graf[w][i].first], graf[w][i].first));
            }
        }
    }
}
