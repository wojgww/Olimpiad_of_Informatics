#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n;
    int s;
    cin >> n >> s;
    vector<long long> l;
    vector<long long> r;
    l.resize(n);
    r.resize(n);
    for (int i = 0; i < n -1; i++){
        cin >> l[i];
        cin >> r[i];
    }
    int maxlewa, maxprawa;
    maxlewa = s - 1;
    maxprawa = n - s;
    long long diff = 48392492384;
    int it = -1;
    vector<int> result;
    result.resize(n); // 0 - lewa   1 - prawa
    bool yes = 0;
    int last = -1;
    for (int i = 0; i < n - 1; i++){
        if (yes == 0){
            if (last == 0){
                if (i > maxlewa){ //kurwa ta lewa
                    result[it] = 1;
                    yes = 1;
                }
            }
            else if (last == 1){
                if (i > maxprawa){
                    result[it] = 0;
                    yes = 1;
                }
            }
        }
        if (l[i] <= r[i]){
            result[i] = 0;
            if (last == 1)
                yes = 1;
            last = 0;
            if (r[i] - l[i] < diff){
                diff = r[i] - l[i];
                it = i;
            }
        }
        else{
            result[i] = 1;
            if (last == 0)
                yes = 1;
            last = 1;
            if (l[i] - r[i] < diff){
                diff = l[i] - r[i];
                it = i;
            }
        }
    }
    if (yes == 0 && (s != 1 && s != n)){
        result[it] = (result[it] + 1) % 2;
    }
    long long suma = 0;
    vector<pair<int,int>> ilerazy; //0 lub 1    ile razy
    int current = 1;
    last = result[0];
    if (result[0] == 0)
        suma+= l[0];
    else
        suma+= r[0];

    for (int i = 1; i < n - 1; i++){
        if (result[i] == last){
            current++;
        }
        else{
            ilerazy.push_back(make_pair(current, last));
            current = 1;
        }
        if (result[i] == 0)
            suma+= l[i];
        else
            suma+= r[i];
        last = result[i];
    }
    ilerazy.push_back(make_pair(current, last));
    vector<int> sciezka;
    int left = 0;
    int right = n - 1;
    s--;
    sciezka.push_back(s);
    int j;
    int inc = 0;
    for (int i = 0; i < int(ilerazy.size()); i++){ //jeszcze uwzglednianie s
        inc = 0;
        if (ilerazy[i].second == 0){
            j = left + ilerazy[i].first - 1;
            if (s <= j && s != -1){
                j++;
                inc = 1;
            }
            for (; j >= left; j--){
                if (j == s)
                    continue;
                sciezka.push_back(j);
            }
            left += (ilerazy[i].first + inc);
            if (inc)
                s = -1;
        }
        else{
            j = right - ilerazy[i].first + 1;
            if (s >= j && s != -1){
                j--;
                inc = 1;
            }
            for (; j <= right; j++){
                if (j == s)
                    continue;
                sciezka.push_back(j);
            }
            right -= (ilerazy[i].first + inc);
            if (inc)
                s = -1;
        }
    }
    cout << suma << endl;
    for (int i = 0; i < n; i++){
        cout << sciezka[i] + 1 << ' ';
    }
    cout << endl;

    return 0;
}
