#include <iostream>
#include <vector>


using namespace std;

int main()
{
    int n;
    cin >> n;
    if (n == 0){
        cout << "TAK";
        return 0;
    }
    if (n == 1){
        cout << "NIE";
        return 0;
    }
    vector<int> s;
    s.resize(n + 1);
    int a, b;
    for (int i = 0; i < n; i++){
        cin >> a >> b;
        //na potrzebe testow
        //a++;
        //b++;
        //
        s[a] = b;
    }
    if (s[n] == n){
        cout << "NIE";
        return 0;
    }
    int minz, maxz;
    minz = 42943482;
    maxz = -1;
    int current = n;
    int last = 0;
    int yes = 0;
    for (int i = n -1; i >= 1; i--){// w zlym miejscu konczy bo tutaj
        if (maxz > s[i] && current == i){
            cout << "TAK";
            return 0;
        }
        if (current == i)
            continue;
        if (s[current] > s[i]){
            yes = 1;
        }
        else{
            maxz = max(maxz, s[i]);
            minz = min(minz, s[i]);
            maxz = max(maxz, s[current]);
            minz = min(minz, s[current]);
            current = i - 1;
            if (yes){
                cout << "TAK";
                return 0;
            }
        }
    }
    if (current == 0){
        cout << "TAK";
        return 0;
    }
    if (current == 1){
        if (s[1] < maxz){
            cout << "TAK";
            return 0;
        }
    }
    int maksz = -1;
    for (int i = 1; i < current; i++)
        maksz = max(maksz, s[i]);
    if (maksz > minz){// && (yes == 1 || n % 2 == 0)){
        cout << "TAK";
        return 0;
    }
    cout << "NIE";
    return 0;
}
/*

*/
