#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<vector<int>> operacje;
    operacje.resize(k);
    for (int i = 0; i < k; i++)
    {
        operacje[i].resize(3);
        cin >> operacje[i][0] >> operacje[i][1] >> operacje[i][2]; //a l d
    }
    int sqr = 320; //w zaokragleniu pierwiastek z 100 000 czyli maks n
    vector<vector<int>> do_zrobienia;
    do_zrobienia.resize(sqr);
    vector<int> wynik;
    wynik.resize(n + 1);
    int a;
    for (int i = 0; i < k; i++)
    {
        if (operacje[i][2] >= sqr)
        {
            //manualnie robimy (brutem)
            a = operacje[i][0];
            for (int j = 0; j < operacje[i][1]; j++)
            {
                wynik[a]++;
                a += operacje[i][2];
            }
        }
        else
        {
            do_zrobienia[operacje[i][2]].push_back(i);
        }
    }
    vector<int> adding;
    adding.resize(n + 1);
    vector<int> added;
    added.resize(n + 1);
    int current;
    int l, d;
    for (int i = 1; i < sqr; i++)
    {
        for (int j = 0; j < do_zrobienia[i].size(); j++)
        {
            a = operacje[do_zrobienia[i][j]][0];
            l = operacje[do_zrobienia[i][j]][1];
            d = operacje[do_zrobienia[i][j]][2];
            adding[a]++;
            if (a + l * d <= n)
                adding[a + l * d]--;
        }
        for (int j = 1; j <= n; j++)
        {
            current = adding[j];
            if (d < j)
            {
                current += added[j - d];
            }
            added[j] = current;
            wynik[j] += added[j];
        }
        for (int j = 1; j <= n; j++)
        {
            adding[j] = 0;
            added[j] = 0;
        }
    }
    for (int i = 1; i <= n; i++)
        cout << wynik[i] << " ";
    cout << '\n';

    return 0;
}
