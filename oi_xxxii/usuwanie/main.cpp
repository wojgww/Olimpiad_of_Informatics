#include <iostream>

using namespace std;

int main()
{
    unsigned long long a, b;
    cin >> a >> b;
    if (b - a == 1 || b - a == 0){
        cout << 0 << endl;
        return 0;
    }
    unsigned long long liczb = b - a + 1;
    unsigned long long wynik;
    if (liczb % 4 == 0){
        wynik = b - a + 1;
    }
    else if ((liczb + 1) % 4 == 0 || (liczb + 3) % 4 == 0){
        wynik = b - a;
    }
    else if ((liczb + 2) % 4 == 0){
        wynik = b - a -1;
    }
    cout << wynik << endl;
    return 0;
}
