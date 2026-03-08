#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> obiezyswiaty;
    obiezyswiaty.resize(k);
    for (int i = 0; i < k; i++)
    {
        cin >> obiezyswiaty[i];
    }
    vector<vector<int>> macierz; //macierz sasiedztw
    macierz.resize(n + 1);
    for (int i = 1; i <= n; i++)
        macierz[i].resize(n + 1);
    vector<vector<int>> sciezki;
    sciezki.resize(n + 1);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        macierz[a][b] = 1;
        sciezki[a].push_back(b);
    }
    int yes = 1;
    for (int i = 0; i < k - 1; i++)
    {
        if (obiezyswiaty[i] != obiezyswiaty[i + 1])
        {
            yes = 0;
            break;
        }
    }
    if (yes)
    {
        cout << "TAK" << '\n' << 0;
        return 0;
    }
    //jak algorytm dziala //musimy znalezc pierwszy moment kiedy sie spotkaja wszystkie obiezyswiaty
    //bedziemy robic to wyszukiwaniem binarnym na przedziale od   0  do n^2
    //jezeli zwroci true to zawezamy przedzial z prawej strony, w przeciwnym wypadku odwrotnie
    //bedziemy sprawdzac na macierzy w wyszukiwaniu binarnym, ktora bedzie odpowiednio aktualizowana
    //jak aktualizowac - bedziemy przechowywac lewy przedzial, ktory bedziemy odpowienio powiekszac do mida
    //aby robic to za kazdym razie w czasie n^3 (czasie mnozenia macierzy)  to trzeba na poczatku obliczyc
    //wszystkie macierze do kolejnych poteg dwojki
    //wiec czas zajmie n^3 log n^2  wiec   2n^3 log n    --- O(n^3 log n)
    int pot2 = 1;
    int it = 0;
    while(pot2 < n * n)
    {
        pot2 <<= 1;
        it++;
    }
    vector<vector<vector<int>>> macierze2;
    macierze2.resize(it + 1);
    for (int i = 0; i <= it; i++)
    {
        macierze2[i].resize(n + 1);
        for (int j = 1; j <= n; j++)
            macierze2[i][j].resize(n+ 1);
    }
    macierze2[0] = macierz;
    for (int itt = 1; itt <= it; itt++)
    {
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int sum = 0;
                for (int l = 1; l <= n; l++)
                    sum |= (macierze2[itt -1][i][l] & macierze2[itt -1][l][j]);
                macierze2[itt][i][j] = sum;
            }
        }
    }
    //wyszukiwanie binarne
    int l, r, mid;
    l = 0;
    r = pot2;
    mid = pot2 / 2;
    int itt = it - 1; //co sie dodaje teraz

    vector<vector<int>> left;
    vector<vector<int>> midl;
    left.resize(n + 1);
    midl.resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        left[i].resize(n + 1);
        midl[i].resize(n + 1);
    }
    for (int i= 1; i <= n; i++)
        left[i][i] = 1;

    while (l < r -1)
    {
        //midl = left * macierze2[itt]
        mid = (l + r) / 2;
        for (int i = 1; i <= n; i++)
        {
            for (int j = 1; j <= n; j++)
            {
                int sum = 0;
                for (int l = 1; l <= n; l++)
                    sum |= (left[i][l] & macierze2[itt][l][j]);
                midl[i][j] = sum;
            }
        }
        //sprawdzanie i na podstawie tego zmniejszanie przedzialu
        int yes = 1;
        for (int i = 1;i <= n; i++)
        {
            yes = 1;
            for (int j = 0; j < k; j++)
            {
                if (!midl[obiezyswiaty[j]][i])
                {
                    yes = 0;
                    break;
                }
            }
            if (yes)
                break;
        }
        if (yes)
        {
            r = mid;
        }
        else
        {
            l = mid;
            left = midl;
        }
        itt--;
    }
    //l == r

    yes = 1; //blad w zadaniu to jest ze daje NIE na niektore mozliwe TAK
    for (int i = 1;i <= n; i++)
    {
        yes = 1;
        for (int j = 0; j < k; j++)
        {
            if (!left[obiezyswiaty[j]][i])
            {
                yes = 0;
                break;
            }
        }
        if (yes)
        {
            cout << "TAK" << '\n' << l;
            return 0;
        }
    }
    for (int i = 1;i <= n; i++)
    {
        yes = 1;
        for (int j = 0; j < k; j++)
        {
            if (!midl[obiezyswiaty[j]][i])
            {
                yes = 0;
                break;
            }
        }
        if (yes)
        {
            cout << "TAK" << '\n' << mid;
            return 0;
        }
    }

    vector<vector<int>> nmidl;
    nmidl.resize(n + 1);
    for (int i = 1; i <= n; i++)
        nmidl[i].resize(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            int sum = 0;
            for (int l = 1; l <= n; l++)
                sum |= (midl[i][l] & macierze2[0][l][j]);
            nmidl[i][j] = sum;
        }
    }
    for (int i = 1;i <= n; i++)
    {
        yes = 1;
        for (int j = 0; j < k; j++)
        {
            if (!nmidl[obiezyswiaty[j]][i])
            {
                yes = 0;
                break;
            }
        }
        if (yes)
        {
            cout << "TAK" << '\n' << mid + 1;
            return 0;
        }
    }

    cout << "NIE" << '\n';
    //cout << "TAK" << '\n';
    return 0;
}
