#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class tama {
public:
    int h;
    int i; //kolumna
    int i2;
    int j; //wiersz
    int j2;
    tama();
    tama(int h, int i, int i2, int j, int j2);
};

bool compare(tama a, tama b){
    return a.h < b.h;
}

long long find(long long k, vector<vector<int>> &r, int n){
    if (k == -1)
        return -1;
    while(r[k / n][k % n] != k)
    {
        if (k == -1)
            break;
        k = r[k / n][k % n];
    }
    return k;
}

const int mod = 1000000007;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, h;
    cin >> m >> n >> h;
    vector<tama> tamy;
    int w;
    for (int j = 0; j < m; j++){
        for (int i = 0; i < n - 1; i++){
            cin >> w;
            tamy.push_back(tama(w, i, i+1, j, -1));
        }
    }
    for (int j = 0; j < m - 1; j++){
        for (int i = 0;i < n; i++){
            cin >> w;
            tamy.push_back(tama(w, i, -1, j, j + 1));
        }
    }
    sort(tamy.begin(), tamy.end(), compare);
    vector<vector<long long>> komorka;
    komorka.resize(m);
    vector<vector<int>> czas;
    czas.resize(m);
    vector<vector<int>> lider;
    lider.resize(m);
    vector<int> lsize;
    lsize.resize(m * n);
    for (int i = 0; i < m; i++){
        komorka[i].resize(n);
        czas[i].resize(n);
        lider[i].resize(n);
        for (int j = 0; j < n; j++){
            komorka[i][j] = 2;
            czas[i][j] = 1;
            lider[i][j] = i * n + j;
            lsize[i * n + j] = 1;
        }
    }
    for (int it = 0; it < tamy.size(); it++){
        int lider1, lider2;
        if (tamy[it].j2 == -1){
            lider1 = find(lider[tamy[it].j][tamy[it].i], lider, n);
            lider2 = find(lider[tamy[it].j][tamy[it].i2], lider, n);
        }
        else{
            lider1 = find(lider[tamy[it].j][tamy[it].i], lider, n);
            lider2 = find(lider[tamy[it].j2][tamy[it].i], lider, n);
        }
        if (lider1 != lider2){
            long long sum1 = komorka[lider1 / n][lider1 % n] + tamy[it].h - czas[lider1 / n][lider1 % n];
            sum1 %= mod;
            long long sum2 = komorka[lider2 / n][lider2 % n] + tamy[it].h - czas[lider2 / n][lider2 % n];
            sum2 %= mod;
            //if(tamy[it].h >= h){
            //    sum1--;
            //    sum2--;
            //}
            if (lsize[lider1] >= lsize[lider2]){
                lsize[lider1] += lsize[lider2];
                lider[lider2 / n][lider2 % n] = lider1;
                komorka[lider1 / n][lider1 % n] = sum1 * sum2;
                komorka[lider1 / n][lider1 % n] %= mod;
                czas[lider1 / n][lider1 % n] = tamy[it].h;
                //if (tamy[it].h >= h)
                //    komorka[lider1 / n][lider1 % n]--;
            }
            else{
                lsize[lider2] += lsize[lider1];
                lider[lider1 / n][lider1 % n] = lider2;
                komorka[lider2 / n][lider2 % n] = sum1 * sum2;
                czas[lider2 / n][lider2 % n] = tamy[it].h;
                komorka[lider2 / n][lider2 % n] %= mod;
                //if (tamy[it].h >= h)
                //    komorka[lider2 / n][lider2 % n]--;
            }
        }
    }
    //moze sie zdarzyc ze tama nie bedzie przekroczona
    long long result = find(lider[0][0], lider, n);
    int add = h - czas[result /n][result % n];
    cout << (komorka[result / n][result % n] + add) % mod << '\n';
    return 0;
}

tama::tama(){
    h = 0;
    i = 0;
    i2 = 0;
    j = 0;
    j2 = 0;
}
tama::tama(int h, int i, int i2, int j, int j2){
    this->h = h;
    this->i = i;
    this->i2 = i2;
    this->j = j;
    this->j2 = j2;
}
