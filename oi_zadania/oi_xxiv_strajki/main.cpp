#include <iostream>
#include <vector>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int m;
    vector<vector<int>> graf;
    graf.resize(n + 1);
    int a, b;
    for (int i = 0; i < n - 1; i++){
        cin >> a;
        cin >> b;
        graf[a].push_back(b);
        graf[b].push_back(a);
    }
    cin >> m;
    int x;
    long long wynik = 1;
    vector<int> off;
    off.resize(n + 1);
    int count = 0;
    //wierzcholki 500+
    vector<vector<int>> w500; //sasiadujacy 500+ wierzcholki
    w500.resize(n + 1);
    for (int i = 1; i <= n; i++){
        if (graf[i].size() >= 500){
            for (int j = 0; j < graf[i].size(); j++){
                w500[graf[i][j]].push_back(i);
            }
        }
    }
    vector<int> offs;
    offs.resize(n + 1);
    vector<int> result;
    result.resize(m);
    int c;
    for (int i = 0; i < m; i++){
        cin >> x;
        if (x > 0){
            off[x] = 1;
            count++;
            c = 0;
            for (int i = 0; i < w500[x].size(); i++)
                if(off[w500[x][i]])
                    c++;
            wynik += (graf[x].size() - 1 - offs[x] -c);
            if (graf[x].size() < 500)
                for (int j = 0; j < graf[x].size(); j++){
                    offs[graf[x][j]]++;
                }
        }
        else{
            x = -x;
            off[x] = 0;
            count--;
            c = 0;
            for (int i = 0; i < w500[x].size(); i++)
                if(off[w500[x][i]])
                    c++;
            wynik -= (graf[x].size() - 1 - offs[x] - c);
            if(graf[x].size() < 500)
                for (int j = 0; j < graf[x].size(); j++){
                    offs[graf[x][j]]--;
                }
        }
        result[i] = wynik;
        if (count == n)
            result[i] = 0;
    }
    for (int i = 0; i < m; i++){
        cout << result[i] << endl;
    }
    cout << endl;
    return 0;
}
