#include <iostream>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string x;   // wszystko zamieniamy na 9
    cin >>  x;
    int l = x.size();
    int zero = -1;
    int yes = 1;
    if (l == 1 && x[0] == '1'){
        cout << 1;
        return 0;
    }
    else if (x[0] == '1'){
        for (int i = 1; i < l; i++)
            if (x[i] != '0'){
                yes = 0;
                break;
            }
    }
    else
        yes = 0;
    if (yes){
        cout << 1;
        return 0;
    }
    int operacje = 0;
    int kosztp = 0;
    //tutaj kod
    for (int i =0; i < l; i++){
        if (x[i] != '0' && x[i] != '9'){
            if (i < l - 6){
                kosztp += 9 - x[i] + '0';
            }
            operacje += 9 - x[i] + '0';
        }
    }
    int dziewiatki = 4839484;
    if (l > 2 && x[l - 1] != '0')
        for (int i = l - 2; i >= 0; i--){ // oooooo dziewiatki jest problem przy normalnym
            if (x[i] == '9'){
                dziewiatki = i;
            }
            else
                break;
        }
    int last_zero = 0;
    for (int i = l - 1; i >= 0; i--){
        if (x[i] == '0'){
            last_zero = i;
            break;
        }
    }
    if(last_zero){
        while (x[last_zero] == '0')
            last_zero--;
        last_zero++;
    }

    int last_zero2 = 0;
    if (l > 7){
        for (int i = l - 7; i >= 0; i--){
            if (x[i] == '0'){
                last_zero2 = i;
                break;
            }
        }
        if (last_zero2){
            while (x[last_zero2] == '0' && last_zero2 >= 0)
                last_zero2--;
            last_zero2++;
        }
    }

    int przeskoki = 0;
    for (int i = 0; i < l - 1; i++)
        if (x[i] != '0' && i < dziewiatki) //do tego rozwiazania dziewiatki musza inaczej dzialac
            przeskoki++; //przeskoki tez sa zle dla koszt6 - taki sam warunek jak do operacji
    int przeskoki2 = 0;
    for (int i = l - 7; i >= 0; i--){
        if (x[i] != '9'){
            //jak zero to tak samo tylko jeden mniej
            przeskoki2 = i + 1;
            if (x[i] == '0'){
                przeskoki2--;
            }
            break;
        }
    }

    int koszt6 = 434743224;
    if (l > 7){
        koszt6 = ('9' - x[l -1]) + ('9' - x[l - 2]) * 10 + ('9' - x[l - 3]) * 1e2
                 + ('9' - x[l -4]) * 1e3 + ('9' - x[l-5]) * 1e4 + ('9' - x[l - 6]) * 1e5;
        //przeskoki operacje
        koszt6 += kosztp + 2 + max(przeskoki2, last_zero2);
    }
    else
        koszt6 = operacje + przeskoki + 2;
    cout << min((operacje + przeskoki + 2), (koszt6));
    //cout << operacje + przeskoki + 2 << endl << koszt6;

    return 0;
}
