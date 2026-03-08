#include <iostream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include "kaslib.h"

using namespace std;

void sito_erastotenesa();
vector<bool> tab;

const unsigned long long FIR = 5E5;//  5 * 10 ^ 6  //jest liczb pierwszych 148933
const unsigned long long n = 1E18;
/*
unsigned long long nwd(unsigned long long a, unsigned long long b){
    unsigned long long pom;
    while(b!=0){
        pom = b;
        b = a%b;
        a = pom;
    }
    return a;
}
*/

unsigned long long power(unsigned long long a, unsigned long long b){
    unsigned long long c= a;
    a = 1;
    for (int i = 0; i < b; i++)
        a *= c;
    return a;
}

int main()
{
    int first = 0;
    //    cin >> tests;
    //    cin >> first;
    ///    for (int ct = 0; ct < tests; ct++)
    //    {
    vector<int> pierwsze;
    tab.resize(FIR + 1);
    sito_erastotenesa();
    int przedzial0 = 0; //1   10e3
    int przedzial1 = 0; //1   10E4
    int przedzial2 = 0; //1E4 10E5
    int przedzial3 = 0; //1E5 10E6
    for (int i = 0; i <= FIR; i++)
        if (!tab[i]){
            pierwsze.push_back(i);
            if (i < 1E3)
                przedzial0++;
            else if (i < 1e4)
                przedzial1++;
            else if(i < 1E5)
                przedzial2++;
            else
                przedzial3++;
        }
    int zgadniecia = 0;
    vector<int> ilosci; //ilosci dla kolejnych dzilnikow
    vector<int> dzielniki;
    vector<int> do_zrobienia; //przechowuje miejsce z wektora dzielniki
    do_zrobienia.resize(100); //niepotrzebnie tak duzo
    dzielniki.resize(20);
    ilosci.resize(20);
    int iter = 0; //do ilu liczb pierwszych wykorzystalismy
    int ita =0, itb = 0;//iterator od dzielniki   iterator od do_zrobienia
    int cur_operacje = 0;
    int operacje = 1E7;
    unsigned long long liczba = 1; //liczba osiagnieta ze wszystkich dzielnikow x
    unsigned long long current; //jaka liczbe osiagnelismy z zlozonych teraz liczb peirwszych
    vector<int> l;//tutaj liczby jakie teraz wykorzystalismy
    vector<int> d; // i kolejno ich ilosci
    l.resize(20);
    d.resize(20);
    int itl = 0;
    current = 1;



    while (true){
        if (operacje == 0){
            return 0;
        }
        if (liczba < 1E15 || iter <= przedzial0 || itb != 0){
            //warunki do optymalizacji, na poczatku zgadniecia rowne ~100
            if (iter == pierwsze.size() - 1 || (iter > 20 && liczba < 1e3) ||  (iter > 50 && liczba < 1e7)
                || (iter > 1000 && liczba < 4e12)){
                Szturchnij();
                iter = 0;
                ita = 0;
                itb = 0;
                operacje--;
                if (operacje == 0)
                    return 0;
                liczba = 1;
                current = 1;
                itl = 0;
                continue;
            }

            if (itb > 0){
                int il;
                while(--itb >= 0){
                    long long miejsce = n / current;
                    il = ilosci[do_zrobienia[itb]] + 1;
                    if (power(dzielniki[do_zrobienia[itb]], il) <= miejsce){
                        current *= power(dzielniki[do_zrobienia[itb]], il);
                        ilosci[do_zrobienia[itb]]++;
                    }
                    else
                        break;

                    l[itl] = dzielniki[do_zrobienia[itb]];
                    do_zrobienia[itb] = 0; //zerujemy tez
                    d[itl++] = il;
                }
                itb++;
            }
            //potem kolejno wszystkie liczby pierwsze sprawdzamy i czy mozemy je dodac
            while (current < n && iter < pierwsze.size()){
                if (n / current >= pierwsze[iter]){
                    l[itl] = pierwsze[iter];
                    d[itl++] = 1;
                    current *= pierwsze[iter];
                    iter++;
                }
                else
                    break;
            }//pytanie
            unsigned long long nw = Pytaj(current);
            //sprawdzenie czy z pytania beda jakies dzielniki
            operacje--;
            if (operacje == 0)
                return 0;
            for (int i = 0; i < itl; i++){
                if (nw % l[i] == 0){
                    if (d[i] == 1){
                        dzielniki[ita] = l[i];
                        do_zrobienia[itb++] = ita;
                        ilosci[ita++] = 1;
                    }
                    else{//teraz trzeba usunac poprzednie
                        int number;
                        for (int j = 0; j < ita; j++){
                            if (dzielniki[j] == l[i]){
                                number = j;
                                break;
                            }
                        }
                        int mpower = ilosci[number];
                        if (nw % power(dzielniki[number], mpower) == 0){
                            do_zrobienia[itb++] = number; //tutaj skonczone te ita++ cos smierdzi
                        }
                        else{
                            ilosci[number] = mpower - 1;
                        }
                    }
                }
            }
            itl = 0;
            current = 1;
            liczba = 1;
            for (int i = 0; i < ita; i++)
                liczba *= power(dzielniki[i], ilosci[i]);
        }
        if (iter >= pierwsze.size() -1 || (liczba > 1e15 && iter > 167 && itb == 0) || (liczba > 1e16 && iter > 24 && itb == 0)){
            //odpowiadanie
            if (liczba > 1e15 && itb == 0){
                Odpowiedz(liczba);
                zgadniecia++;
                iter = 0;
                ita = 0;
                itb = 0;
                operacje--;
                if (operacje == 0)
                    return 0;
                liczba = 1;
                current = 1;
            }
            iter = 0;
            ita = 0;
            itb = 0;
            operacje--;
            liczba = 1;
            current = 1;
            //cout << "x    " << x << endl;
            Szturchnij();
            if (operacje == 0)
                return 0;
        }
    }
    return 0;
}

void sito_erastotenesa() //tab wypelniona zerami  // 0 - liczba pierwsza
{
    tab[0] = 1;
    tab[1] = 1;
    int sqr = sqrt(FIR);
    for (int i= 4; i <= FIR; i+=2){
        tab[i] = 1;
    }
    for (int i = 3; i <= sqr; i++)
        if (!tab[i]){
            int c= 2 * i;
            for (int j = i * i; j <= FIR; j+=c){
                tab[j] = 1;
            }
        }
}
