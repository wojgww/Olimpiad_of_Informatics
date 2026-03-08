#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void dfs_dp(int w, vector<vector<int>> &graf, vector<bool> &odw, vector<int> &dp, int x, int n);

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n;
    cin >> n;
    vector<vector<int>> graf;
    graf.resize(n + 1);
    int a,b;
    for (int i = 1; i < n; i++){
        cin >> a >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    int maks= 0;
    for (int i = 0; i < n; i++)
        if (graf[i].size() > maks)
            maks = graf[i].size();
    vector<bool> odw;

    odw.resize(n + 1);
    int l = graf[1].size();
    int r = maks;
    int mid = (l+r)/2;
    vector<int> dp;
    dp.resize(n + 1);
    while(r > l){
        for (int i = 0; i <= n; i++)
            odw[i] = 0;
        dfs_dp(1, graf, odw, dp, mid, n);
        if (!dp[1])
            r = mid;
        else
            l = mid + 1;
        mid = (l+r) /2;
    }
    cout << l << '\n';
    return 0;
}
//postorderowo robimy dp
void dfs_dp(int w, vector<vector<int>> &graf, vector<bool> &odw, vector<int> &dp, int x, int n)
{
    odw[w] = 1;
    int current;
    current = -1 * x;
    for (int i = 0; i < graf[w].size(); i++){
        if (!odw[graf[w][i]]){
            odw[graf[w][i]] = 1;
            current++;
            dfs_dp(graf[w][i], graf, odw, dp, x, n);
            current += dp[graf[w][i]];
        }
    }
    dp[w] = max(0, current);
}
