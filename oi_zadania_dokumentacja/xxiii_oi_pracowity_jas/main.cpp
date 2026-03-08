#include <iostream>
#include <vector>

using namespace std;

vector<int> permutacja;
vector<long long> silnia;
long long n;
int ende = 0;
long long M = 1e9 + 7;

int base = 1;
vector<long long> drzewo;

long long mal(long long a, long long b, long long c){
    if (a + b < c)
        return a + b - c + 1e9 + 7;
    return a + b - c;
}

long long odp(int a, int b){
    a += base;
    b += base;
    a--;
    b++;
    long long wynik = 0;
    while(b - a > 1){
        if(!(a&1)){
            wynik += drzewo[a + 1];
        }
        if(b&1){
            wynik += drzewo[b - 1];
        }
        a >>= 1;
        b >>= 1;
    }
    return wynik;
}

void aktu(int v, int val){
    v += base;
    drzewo[v] = val;
    v >>= 1;
    while(v > 0){
        drzewo[v] = drzewo[2 * v + 1] + drzewo[2 * v];
        v >>= 1;
    }
}


int main()
{
    //preproces silnia
    silnia.resize(1e6 + 1);
    silnia[1] = 1;
    for (long long i = 2; i <= 1e6; i++)
        silnia[i] = (silnia[i - 1] * i) % M;
    cin >> n;
    //n = 1e6;
    permutacja.resize(n);
    for (int i = 0; i < n; i++)
        cin >> permutacja[i];
        //permutacja[i] = n - i;

    long long result2 = 0;
    long long c;
    long long mnoznik = 0;
    long long used = 0;
    int yes = 0;
    while(base < n)
        base <<= 1;
    drzewo.resize(base << 1);
    for (int i = 0; i < n; i++)
        aktu(i, 1);


    for (int i = 1; i < n; i++){ //bo leci sie do przedostatniej
        c = permutacja[i - 1] - i;
        aktu(permutacja[i -1] - 1, 0);
        if (c || yes){ /////ile tych operacji// koszt operacji
            c = odp(0, permutacja[i - 1] - 1);      // zero odpowiada jedynce
            result2 += ((mal(c ,mnoznik, used)) % M) * ((n - i + 2) / 2); // jeszcze mnozenie przez operacje
            result2 %= M;
            mnoznik += c;
            mnoznik %= M;
            used = mnoznik;
            mnoznik *= (n - i);
            mnoznik %= M;
            yes = 1;
        }
        if (result2 < 0)
            yes = 0;
    }
    cout << result2 << endl;
    return 0;
}