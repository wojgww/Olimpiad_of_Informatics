#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

int n, s;
long long mink = 0;

void permutacje(long long sum, vector<bool> lista, int cur, int k);

int main()
{
    cin >> n >> s;
    vector<int> liczba;
    vector<vector<int>> miejsca;
    vector<int> it;
    miejsca.resize(1e6 + 1);
    liczba.resize(1e6 + 1);
    it.resize(1e6 + 1);
    priority_queue<pair<int, int>> q;
    int a;
    for (int i = 0; i < n; i++){
        cin >> a;
        a++; //bo tytul
        a %= s;
        liczba[a]++;
        miejsca[a].push_back(i);
    }
    for (int i= 0; i <= 1e6; i++)
        if (liczba[i])
            q.push(make_pair(liczba[i], i));
    pair<int, int> x;
    pair<int, int> y;
    long long sum = 0;
    vector<int> wynik;
    while (!q.empty()){
        x = q.top();

        q.pop();
        if ((sum + x.second) % s == s - 1){
            if(q.empty()){
                sum = 0;
                mink++;
                x.first--;
                wynik.push_back(miejsca[x.second][it[x.second]]);
                if (int(wynik.size()) == n)
                    mink--;
                it[x.second]++;
                if (x.first)
                    q.push(make_pair(x.first, x.second));
            }
            else{
                y = q.top();
                q.pop();
                sum += y.second;
                sum %= s;
                y.first--;
                wynik.push_back(miejsca[y.second][it[y.second]]);
                it[y.second]++;
                if (y.first)
                    q.push(make_pair(y.first, y.second));
                q.push(make_pair(x.first, x.second));
            }
        }
        else{
            sum += x.second;
            sum %= s;
            x.first--;
            wynik.push_back(miejsca[x.second][it[x.second]]);
            it[x.second]++;
            if (x.first)
                q.push(make_pair(x.first, x.second));
        }
    }

    cout << mink << endl;
    for (int i = 0; i < n; i++){
        cout << wynik[i] + 1 << " ";
    }
    cout << endl;
    return 0;
}
