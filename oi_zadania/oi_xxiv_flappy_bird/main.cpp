#include <iostream>
#include <utility>

using namespace std;

struct obstacle
{
    int x;
    long long a;
    long long b;
};

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    long long x;
    int n;

    cin >> n;
    cin >> x;

    obstacle *przeszkody = new obstacle[n + 1];

    for (int i = 0; i < n; i++)
    {
        cin >> przeszkody[i].x;
        cin >> przeszkody[i].a;
        cin >> przeszkody[i].b;
    }


    //program

    pair<int, int> zakres_p = make_pair(0,0);
    int position = 0;
    pair<int, int> zakres_s;
    int distance;
    pair<int, int> zakres_k;
    pair<int, int> zakres_o;
    //int first;
    //int second;
    int status;


    for (int i = 0; i < n; i++)
    {
        distance = przeszkody[i].x - position;
        zakres_s = make_pair(zakres_p.first - distance, zakres_p.second + distance);
        zakres_o = make_pair(przeszkody[i].a + 1, przeszkody[i].b - 1);
        //czesc wspolna
        zakres_k.first = max(zakres_s.first, zakres_o.first);
        zakres_k.second = min(zakres_s.second, zakres_o.second);
        //status = (zakres_p.first % 2 + distance % 2) % 2;
/*
        if (zakres_k.first % 2 != status)
            zakres_k.first++;
        if (zakres_k.second % 2 != status)
            zakres_k.second--;
*/
        if (((long long)zakres_k.first + zakres_p.first + distance) % 2)
            zakres_k.first++;
        if (((long long)zakres_k.second + zakres_p.second + distance) % 2)
            zakres_k.second--;

        if (zakres_k.first > zakres_k.second)
        {
            cout << "NIE";
            return 0;
        }

        position = przeszkody[i].x;
        zakres_p = zakres_k;
    }

    int punkt = zakres_k.first;

    //cout << punkt << "\n";

    int wynik = przeszkody[n - 1].x / 2 + punkt / 2;

    if (punkt % 2 && punkt > 0)
        wynik++;

    //if (przeszkody[n - 1].x % 2 && punkt % 2 == 0)
    //    wynik++;

    cout << wynik;

    delete[] przeszkody;
    return 0;
}
