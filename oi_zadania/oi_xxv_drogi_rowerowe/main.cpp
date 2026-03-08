#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void dfs_post_order(vector<vector<int>> &lista, int w, vector<bool> &visited, vector<int> &kolejnosc);
int dfs(vector<vector<int>> &lista, int w, vector<int> &wierzch, vector<bool> &visited);
void dfst(vector<vector<int>> &lista_transponowana, int w,
          vector<bool> &visited, int k, vector<int> &spojna, vector<int> &wielkosc);

int main()
{
    int n, m;
    cin >> n >> m;
    vector<vector<int>> lista;
    lista.resize(n + 1);
    int a, b;
    for (int i =0; i < m; i++)
    {
        cin >> a >> b;
        lista[a].push_back(b);
    }
    //plan jest taki
    //kiedy jest droga z u do v to w takim razie musi byc
    //albo droga z v do u co oznacza cykl
    //albo nie moze byc drogi z v do u   a drog z u do v moze byc tylko jedna
    //
    //kiedy sa juz polaczone dwustronnie wierzcholki u i v to nie moze od nich odchodzic krawedz
    //ktora nie bedzie nalezala do ich spojnej skladowej poniewaz wtedy bedzie mozna dojsc do
    //tego wierzcholka od krawedzi na wiecej niz jeden sposob (bo mozna poruszac sie cyklicznie)
    //tak samo jest z przypadkiem kiedy krawedz dochodzi do silnie spojnej skladowej, wtedy moze przejsc
    //do wierzcholkow z silnej spojnej skladowej na wiecej niz jeden sposob
    //
    //wiec graf podzieli sie na silnie spojne skladowe i jednostronne sciezki

    //graf postorder
    //odwrotny post order na transponowanym grafie
    vector<bool> visited;
    visited.resize(n + 1);
    vector<int> wierzch;
    wierzch.resize(n + 1);
    vector<int> kolejnosc;
    for (int i = 1; i <= n; i++)
    {
        if (!visited[i])
            dfs_post_order(lista, i, visited, kolejnosc);
    }

    reverse(kolejnosc.begin(), kolejnosc.end());
    //teraz po odwroconych post orderach robimy kolejno dfsy ktore tworza silnie spojne skladowe
    vector<vector<int>> lista_transponowana;
    lista_transponowana.resize(n + 1);
    for (int i = 1; i <= n; i++)
        for (int j = 0; j < lista[i].size(); j++)
            lista_transponowana[lista[i][j]].push_back(i);
    vector<int> wielkosc;
    wielkosc.resize(n + 1); // wielkosc spojnych (wielkosc i-tej spojnej)
    vector<int> spojna;
    spojna.resize(n + 1);
    for (int i = 0; i <= n; i++)
        visited[i] = 0;
    int k = 1;
    for (int i = 0; i < n; i++)
    {
        if (!visited[kolejnosc[i]])
        {
            dfst(lista_transponowana, kolejnosc[i], visited, k, spojna, wielkosc);
            k++;
        }
    }
    for (int i =  1; i <= n; i++)
        visited[i] = 0;
    //trzeba teraz zrobic graf silnych spojnych skladowych
    vector<vector<int>> lista_spojnych;
    lista_spojnych.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < lista[i].size(); j++)
        {
            if (spojna[i] != spojna[lista[i][j]])
                lista_spojnych[spojna[i]].push_back(spojna[lista[i][j]]);
        }
    }
    for (int i =1; i<= n; i++)
    {
        //od spojnych
        wierzch[i] = wielkosc[i];
    }


    for (int i = 1; i < k; i++)
    {
        if (!visited[i])
        {
            dfs(lista_spojnych, i, wierzch, visited);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        //if (wielkosc[spojna[i]] == 1)
        //{
        cout << wierzch[spojna[i]] - 1 << '\n';
        //}
        //else
        //    cout << wielkosc[spojna[i]] - 1 << '\n';
    }


    return 0;
}

int dfs(vector<vector<int>> &lista, int w, vector<int> &wierzch, vector<bool> &visited) // ten dfs na tych co nie naleza do spojnych
{
    int suma = wierzch[w];
    visited[w] = 1;
    for (int i = 0; i < lista[w].size(); i++)
    {
        if (visited[lista[w][i]])
            suma += wierzch[lista[w][i]];
        else
            suma += dfs(lista, lista[w][i], wierzch, visited);
    }
    wierzch[w] = suma;
    return suma;
}

void dfs_post_order(vector<vector<int>> &lista, int w, vector<bool> &visited, vector<int> &kolejnosc)
{
    visited[w] = 1;
    for (int i = 0; i < lista[w].size(); i++)
        if(!visited[lista[w][i]])
            dfs_post_order(lista, lista[w][i], visited, kolejnosc);
    kolejnosc.push_back(w);
}

void dfst(vector<vector<int>> &lista_transponowana, int w,
          vector<bool> &visited, int k, vector<int> &spojna, vector<int> &wielkosc)
{
    visited[w] = 1;
    wielkosc[k]++;
    spojna[w] = k;
    for (int i =0; i < lista_transponowana[w].size(); i++)
    {
        if (!visited[lista_transponowana[w][i]])
            dfst(lista_transponowana, lista_transponowana[w][i], visited, k, spojna, wielkosc);
    }
}
