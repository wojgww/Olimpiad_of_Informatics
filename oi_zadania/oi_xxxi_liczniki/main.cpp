#include <iostream>
#include <vector>
#include <algorithm>
//no one zbytnio nie dziala !!!!!!!!!!!!!!!!!!!!!!!!!!
using namespace std;

bool compare(pair<int, int> a, pair<int, int> b)
{
    return a.first > b.first;
}
int findr(int a, vector<int> &r, int n);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> c; //c i s razem
    c.resize(n);
    vector<vector<int>> a;
    a.resize(m + 1);
    vector<vector<int>> b;
    b.resize(m + 1);
    vector<vector<bool>> a_used;
    a_used.resize(m + 1);
    for (int i = 0; i < n; i++)
        cin >> c[i].first;
    for (int i = 0; i < n; i++)
        cin >> c[i].second;
    for (int i = 0; i <= m; i++)
    {
        b[i].resize(n);
        a[i].resize(n);
        a_used[i].resize(n);
    }
    for (int i = 1; i <= m; i++)
        for (int j = 0; j < n; j++)
            cin >> a[i][j];
    sort(c.begin(), c.end(), compare);
    for (int i = 1; i <= m; i++)
        sort(a[i].begin(), a[i].end());
    //teraz zachlanny algorytm
    for (int i = 0; i < n; i++)
    {
        b[0][i] = c[i].second;
    }

    vector<int> re; //reprezentanci
    re.resize(n);
    for (int i = 0; i < n; i++)
        re[i] = i;

    for (int i = 1; i <= m; i++)
    {
        for (int j = 0; j < n; j++)
        {

            bool yes = 0;
            int l = 0;

            int r = n - 1;
            int mid;
            while(r > l)
            { //dla przykladu 11111111(1)000000000 znalezc zaznaczony element
                mid = (l + r) /2;
                if (a[i][mid] < b[i - 1][j])
                    l = mid + 1;
                else
                    r = mid;
            }
            //l - indeks od ktorego szukamy wolnego miejsca
/*
            for (int k = 0; k + l < n; k++)
            {
                if (!a_used[i][k + l])
                {
                    yes = 1;
                    a_used[i][k + l] = 1;
                    b[i][j] = a[i][k + l];
                    break;
                }
            }
*/
            if (a_used[i][l])
            {
                l = findr(l, re, n);
            }
            if (l == -1)
            {
                cout << "NIE";
                return 0;
                //nie da sie wykonac zadania - odpowiedz to nie
            }
            a_used[i][l] = 1;
            b[i][j] = a[i][l];
            re[l] = l + 1;
        }
    }
    //wystarczy teraz obliczyc odpowiedz
    unsigned long long suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += (long long)(b[m][i] - c[i].second) * c[i].first;
    }
    cout << suma;

    return 0;
} //fdsafsd

int findr(int a, vector<int> &r, int n)
{
    int f = r[a];
    if (f >= n)
        return -1;
    if (f != a)
    {
        f = findr(f, r, n);
    }
    r[a] = f;
    return r[a];
}
