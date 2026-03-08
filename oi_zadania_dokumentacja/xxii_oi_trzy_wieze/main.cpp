#include <iostream>
#include <vector>

using namespace std;
int a, b, c;
vector<char> ciag;

void add(int i){
    if (ciag[i] == 'C')
        a++;
    else if(ciag[i] == 'B')
        b++;
    else if(ciag[i] == 'S')
        c++;
}

void minu(int i){
    if (ciag[i] == 'C')
        a--;
    else if(ciag[i] == 'B')
        b--;
    else if(ciag[i] == 'S')
        c--;
}

int main()
{
    int n;
    cin >> n;
    int maks = 0;
    ciag.resize(n);
    for (int i = 0; i <n; i++)
        cin >> ciag[i];
    a = 0, b = 0, c= 0;
    for (int k = 0; k < 3; k++){
        a= 0, b = 0; c = 0;
        for (int i = k; i < n; i++){
            add(i);
            int zero = 0;
            if (!a) zero++;
            if (!b) zero++;
            if (!c) zero++;
            if ((a != b && b != c && a != c) || zero == 2){
                maks = max(maks, i - k + 1);
            }
        }
    }
    for (int k = n - 3; k < n; k++){
        a= 0, b = 0; c = 0;
        for (int i = k; i >= 0; i--){
            add(i);
            int zero = 0;
            if (!a) zero++;
            if (!b) zero++;
            if (!c) zero++;
            if ((a != b && b != c && a != c) || zero == 2){
                maks = max(maks, k - i + 1);
            }
        }
    }
    cout << maks << endl;

    return 0;
}