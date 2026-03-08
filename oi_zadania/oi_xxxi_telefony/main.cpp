#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
//ktory z lewej - a z lewej kiedy 1
/* funkcja rosnaca (a - mniejsze z lewej)
bool compare(a, b)
{
    if (a < b)
        return 1;
    else
        return 0;
}
w przypadku rownosci zwracac zawsze zero


*/
bool compare1(pair<int, int> a, pair<int, int> b)
{
    if (a.first < b.first)
    {
        return 1;
    }
    else if(b.first < a.first)
    {
        return 0;
    }
    else
    {
        if (a.second < b.second)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    int n;
    cin >> n;
    vector<vector<int>> lista;
    lista.resize(n + 1);
    int k;
    int c;
    int yes2;
    for (int i = 1; i <= n; i++)
    {
        yes2 = 1;
        cin >> k;
        lista[i].push_back(k + 1);
        for (int j = 0; j < k; j++)
        {
            cin >> c;
            if (c > i && yes2 == 1)
            {
                lista[i].push_back(i);
                yes2 = 0;
            }
            lista[i].push_back(c);
        }
        if (yes2 == 1)
            lista[i].push_back(i);
    }

    vector<bool> done;
    done.resize(n + 1);
    bool yes = 1;
    vector<int> city;
    city.resize(n + 1);
    int current = 1;
    for (int i = 1; i <= n; i++)
    {
        if (done[i])
            continue;
        k = lista[i][0];
        done[i] = 1;
        city[i] = current;
        for (int j = 1; j <= k; j++)
        {
            if (lista[i][0] == lista[lista[i][j]][0])
            {
                yes = 1;
                //taka sama dlugosc
                for (int l = 1; l <= lista[i][0]; l++)
                {
                    if (lista[i][l] != lista[lista[i][j]][l])
                    {
                        yes = 0;
                        break;
                    }
                }
                if (yes)
                {
                    done[lista[i][j]] = 1;
                    city[lista[i][j]] = current;
                }
            }
        }
        current++;
    }
    int quantity = current - 1;
    vector<pair<int, int>> graf_lista;
    for (int i = 1; i <= n; i++)
    {
        current = city[i];
        k = lista[i][0];
        for (int j = 1; j <= k; j++)
        {
            if (city[lista[i][j]] != current)
            {
                graf_lista.push_back(make_pair( min(current, city[lista[i][j]]), max(current, city[lista[i][j]]) ));
            }
        }
    }
    sort(graf_lista.begin(), graf_lista.end(), compare1);

    if (quantity == 1 && n > 1)
    {
        city[1] = 2;
        quantity++;
        graf_lista.push_back(make_pair(1, 2));
    }
    cout << quantity << '\n';
    for (int i = 1; i <= n; i++)
        cout << city[i] << " ";
    cout << '\n';
    if (graf_lista.size())
    {
        cout << graf_lista[0].first << ' ' << graf_lista[0].second << '\n';
        for (int i = 1; i < graf_lista.size(); i++)
        {
            if(graf_lista[i - 1] != graf_lista[i])
                cout << graf_lista[i].first << ' ' << graf_lista[i].second << '\n';
        }
    }
    return 0;
}
