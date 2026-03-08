#include <iostream>
#include <vector>

using namespace std;

int n;
vector<vector<int>> graf;
vector<pair<int, int>> dp;
int ma = 0;
vector<int> visited;

void dfs(int w);

int main()
{
    cin >> n;
    graf.resize(n);
    visited.resize(n);
    dp.resize(n);

    int a, b;
    for (int i = 0; i < n -1; i++){
        cin >> a >> b;
        a--; b--;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    if (n <= 2){
        cout << 0 << endl;
        return 0;
    }
    int w = 0;
    //for(int i = 0; i < n; i++)
    //    w = max(w, int(graf[i].size()));
    for (int i = 0; i < n; i++){
        if (graf[i].size() > 1){
            dfs(i);
            break;
        }
    }
    for (int i = 0; i < n; i++){
        if (int(graf[i].size()) == n - 1){
            cout << n - 2 << endl;
            return 0;
        }
    }

    int maks = 0;
    for (int i = 0; i < n; i++)
        maks = max(maks, max(w, max(dp[i].first - 1, dp[i].second)));
    cout << maks << endl;
    return 0;
}

void dfs(int w){
    if (graf[w].size() == 1){
        dp[w].first = 1;
        return;
    }
    visited[w] = 1;
    int maks = 0;
    int v1 = 0, v2 = 0;
    for (int i = 0; i < graf[w].size(); i++){
        if (!visited[graf[w][i]]){
            dfs(graf[w][i]);
            maks = dp[graf[w][i]].second;
            if (dp[graf[w][i]].first >= v1){
                v2 = v1;
                v1 = dp[graf[w][i]].first;
            }
            else if (dp[graf[w][i]].first > v2)
                v2 = dp[graf[w][i]].first;
        }
    }
    dp[w].first = v1 + graf[w].size() - 2;
    dp[w].second = max(maks, v1 + v2 + int(graf[w].size()) - 2);
}
