#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int check(vector<bool> &wynik, vector<int> &a, vector<int> &b, int n){
    long long sumabajtyny = 0, sumbbajtyny = 0, sumabitka =0,sumbbitka = 0;
    long long minbajtyny = 1123478243, minbitka = 1143792423;
    for (int i = 0; i < n; i++){  // a - wartosc dla bajtyny, b - wartosc dla bitka   , lewa strona to rzeczy od bajtyny,
        //prawa no to od bitka
        if (wynik[i]){// jest od bitka //bitek z prawej
            sumbbitka += b[i];
            sumabitka += a[i];
            minbitka = min(minbitka, (long long)(a[i]));
        }
        else{// bajtyna - 0 z lewej - a
            sumabajtyny += a[i];
            sumbbajtyny += b[i]; //bitkowi sie to nie podoba
            minbajtyny = min(minbajtyny, (long long)(b[i]));
        }
    }
    if (sumabajtyny < sumabitka - minbitka || sumbbitka < sumbbajtyny - minbajtyny)
        return 0;
    else
        return 1;
}

bool compare(pair<int, int> a, pair<int, int> b){
    return a.first > b.first;
}

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> bajtyna;
    vector<int> bitek;
    bajtyna.resize(n);
    bitek.resize(n);
    for (int i= 0; i < n; i++)
        cin >> bajtyna[i];
    for (int i = 0; i < n; i++)
        cin >> bitek[i];

    if (n <= 20){ //brute
        long long max = 1 << n;
        vector<bool> wynik;
        wynik.resize(n);
        for (long long i = 0; i < max; i++){
            for (int j = n -1; j >= 0; j--)
                if (i & (1 << j))
                    wynik[j] = 1;
                else
                    wynik[j] = 0;
            if (check(wynik, bajtyna, bitek, n))
                break;
        }
        for (int i = 0; i < n; i++)
            cout << wynik[i] << " ";

        return 0;

    }
    else{
        long long cur = 1;
        vector<bool> wynik;
        wynik.resize(n);
        long long suma_bajtyny = 0;
        long long suma_bitka = 0;
        int min_bajtyny = 1e9 + 7;
        int min_bitka = 1e9 + 7;
        vector<pair<int, int>> b;
        b.resize(n);
        for (int i = 0; i < n; i++)
            b[i] = make_pair(bajtyna[i], i);
        sort(b.begin(), b.end(), compare);
        for (int i = 0; i < n; i++){
            if (suma_bajtyny > suma_bitka){
                suma_bitka += b[i].first;
                min_bitka = b[i].first;
                wynik[b[i].second] = 1;
            }
            else{
                suma_bajtyny += b[i].first;
                min_bajtyny = b[i].first;
                wynik[b[i].second] = 0;
            }
        }
        for (int i = 0; i < n; i++){
            cout << wynik[i] << " ";
        }
        cout << endl;
        //cout << check(wynik, bajtyna, bitek, n) << endl;

        cout << endl;
        return 0;
    }


    return 0;
}
