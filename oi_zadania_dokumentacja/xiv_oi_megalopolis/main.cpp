#include <iostream>
#include <vector>
#include <utility>

using namespace std;

void dfs(int current, int odleglosc, vector<vector<int>> &graf, vector<pair<int, int>> &przedzialy, vector<int> &kolejnosc, int *odleglosci, int n, int &count);
int odp(int v, long long wart, vector<int> &drzewo1);
void aktu(int a, int b, vector<int> &drzewo1);

int pot2(int a)
{
    int c = 1;
    while (c < a)
        c *= 2;
    return c;
}

class operacje
{
public:
    char znak;
    int a;
    int b;
};

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<vector<int>> graf;
    graf.resize(n + 1);
    int a;
    int b;
    for (int i = 0; i < n-1; i++)
    {
        cin >> a;
        cin >> b;
        graf[a].push_back(b); //graf skierowany od mniejszych do wiekszych
        //graf[b].push_back(a);
    }
    int m;
    cin >> m;
    operacje *op = new operacje[n + m - 1];
    for (int i = 0; i < n + m - 1; i++)
    {
        cin >> op[i].znak;
        if (op[i].znak == 'A')
        {
            cin >> op[i].a;
            cin >> op[i].b;
        }
        else
            cin >> op[i].a;
    }
    int base = pot2(n);
    vector<int> kolejnosc;
    int *odleglosci = new int[n + 1];

    vector<pair<int, int>> przedzialy;// = new pair<int, int>[n + 1];
    przedzialy.resize(n + 1);

    int count = 0;
    //problem prawdopodobnie jest  z dfs ktory jest rekurencyjny  ------ !!!!!nie, jest prosblem z czyms innym
    dfs(1, 0, graf, przedzialy, kolejnosc, odleglosci, n, count);

    vector<int> drzewo1;
    drzewo1.resize(2 * base);
    //for (int i = 0; i < 2 *base; i++)
    //    drzewo1[i] = 0;

    //teraz operacje odpowiednio aktualizowac i zwracac wyniki w drzewie
    int current;
    for (int i = 0; i < n + m -1; i++)
    {
        if (op[i].znak == 'A')
        {//przedzial od   b  !!!!! jeszcze update basem trzeba  bez -1 bo one sa od 0 numerowane
            int a1 = op[i].a;
            int b1 = op[i].b;
            aktu(przedzialy[op[i].b].first + base, przedzialy[op[i].b].second + base, drzewo1);
        }
        if (op[i].znak == 'W')
        {
            //current = odleglosci[op[i].a];
            int a1 = op[i].a;
            current = odp(przedzialy[op[i].a].first + base, odleglosci[op[i].a], drzewo1);
            cout << current << endl;
        }
    }
    delete[] op;
    //delete[] przedzialy;
    //delete[] drzewo1;
    delete[] odleglosci;
    return 0;
}

void dfs(int current, int odleglosc, vector<vector<int>> &graf, vector<pair<int, int>> &przedzialy, vector<int> &kolejnosc, int *odleglosci, int n, int &count)
{
    odleglosci[current] = odleglosc;
    przedzialy[current].first = count;
    kolejnosc.push_back(current);
    count++;
    for (int i = 0; i < graf[current].size(); i++)
    {
        dfs(graf[current][i], odleglosc + 1, graf, przedzialy, kolejnosc, odleglosci, n, count);
    }
    przedzialy[current].second = count - 1;

}


//const int base = 1 << 10;
//long long drzewo1[base << 1];

//w tym drzewie odwolujemy sie po indeksach poszczegolnych komorek - nie po indeksach lisci
//aby wywolac operacje na jakims przedziale nalezy do przedzialu dodac wartosc base - ktora jest
//poczatkiem lisci (wartosci)

int odp(int v, long long wart, vector<int> &drzewo1){ //odpowiadamy - przechodzimy z dolu drzewa do gory
    int result = wart;
    while(v > 0){
        wart += drzewo1[v];
        v >>= 1;
    }
    return wart;
}

void aktu(int a, int b, vector<int> &drzewo1){ //aktualizujemy - ustawiamy -1
    long long wyni = 0;
    a--;
    b++;
    while(b - a > 1){
        if(!(a&1)){ // operacja and 00000000001 z a tylko ostatni bit sprawdza - sprawdza czy jest nieparzysta
            // potem jeszcze odwracamy czyli sprawdza czy jest parzysta
            drzewo1[a + 1] -= 1;
        }
        if(b&1){
            drzewo1[b - 1] -= 1;
        }
        a >>= 1;
        b >>= 1;
    }
}

