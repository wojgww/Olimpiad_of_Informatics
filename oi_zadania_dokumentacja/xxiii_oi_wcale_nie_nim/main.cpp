#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int base;
vector<pair<int, int>> drzewo;

void aktu(int v, int val){
    v += base;
    drzewo[v].first = val;
    drzewo[v].second = v - base;
    v >>= 1;
    while(v > 0){
        if (drzewo[v << 1].first >= drzewo[(v << 1) + 1].first)
            drzewo[v] = drzewo[v << 1];
        else
            drzewo[v] = drzewo[(v << 1) + 1];
        v >>= 1;
    }
}


int main()
{
    int n;
    cin >> n;
    int x;
    vector<int> stoski;
    for (int i =0 ; i < n; i++){
        cin >> x;
        stoski.push_back(x);
    }
    long long operacje = 0;
    int a, b, k;
    int jedynki = 0;
    int jedwa = 0;
    base = 1;
    while(base < n)
        base <<= 1;
    int count;
    drzewo.resize(base << 1);
    for (int i = 0; i < n; i++){
        a = stoski[i];
        b = stoski[i];
        count = 0;
        while(min(a,b) != 1){
            k = min(a, b) / 2;
            b = min(a,b) - k;
            a = k;
            operacje += 2;
            count++;
            if (a == b)
                count = 0;
        }
        aktu(i, count);
        if(max(a,b) == 2)
            jedwa++;
        else if(max(a,b) == 1)
            jedynki++;
    }
    int plus = 0;
    if (jedwa){
        while(jedwa > 0){
            //robimy usuwamy a potem robimy plusa
            aktu(drzewo[1].second, 0);
            jedwa--;
            operacje += 4;
            plus = 1;
            operacje += 4;
            if (!jedwa)
                break;
            if (drzewo[1].first == 1){  
                jedynki++;
                jedwa--;
            }
            else{
                aktu(drzewo[1].second, drzewo[1].first - 1);
            }
            plus = 0;
        }
        //operacje += jedwa * 4;
        if (!jedynki)
            operacje--;
    }
    if (jedynki){ //+4 rechy i wybor gracza 2
        if (plus){
            operacje += jedynki * 2 - 1;
        }
        else{
            operacje += jedynki * 2 + 1;
        }
    }
    cout << operacje << endl;

    return 0;
}
