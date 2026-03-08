#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<int> current;
vector<vector<int>> odl;
vector<vector<pair<int, int>>> odo;
vector<vector<int>> odw;
int n, m;

vector<int> f;
vector<int> sssize; //sizy sss - silnie spojnych skladowych

int find(int a){
    int q = f[a];
    if (q != a){
        q = find(f[a]);
        f[a] = q;
    }
    return q;
}

void union_(int a, int b){
    a = find(a);
    b = find(b);
    if (sssize[a] >= sssize[b]){
        sssize[a] += sssize[b];
        f[b] = a;
    }
    else{
        sssize[b] += sssize[a];
        f[a] = b;
    }
}

class element{
public:
    int a, b, c, d;
    element(int x, int y, int z, int k){
        a = x;
        b = y;
        c = z;
        d = k;
    }
    element(){
    }
};

void bfsss(int w, int k, vector<vector<char>> &pionowe, vector<vector<char>> &poziome);
void bfs_t(int w, int k, vector<vector<int>> &on_pion, vector<vector<int>> &on_poz, int &tuje);

int main()
{
    cin >> m;
    cin >> n;
    long long ma = n * (m - 1) + (n - 1) * m;
    long long t = 1 << ma;
    odl.resize(m);
    odo.resize(m);
    current.resize(ma);
    vector<vector<char>> pionowe;
    vector<vector<int>> on_pion;
    pionowe.resize(m);
    on_pion.resize(m);
    odw.resize(m);
    for (int i = 0; i < m; i++){
        pionowe[i].resize(n - 1);
        odw[i].resize(n);
        odl[i].resize(n);
        odo[i].resize(n);
        on_pion[i].resize(n - 1);
    }
    //no i tam jeszcze te resizy ponaprawiac
    for (int i = 0; i < m; i++)
        for (int j = 0;j < n -1; j++)
            cin >> pionowe[i][j];
    vector<vector<char>> poziome;
    vector<vector<int>> on_poz;
    poziome.resize(m - 1);
    on_poz.resize(m - 1);
    for (int i  = 0; i < m - 1; i++){
        poziome[i].resize(n);
        on_poz[i].resize(n);
    }
    for (int i = 0; i < m - 1; i++)
        for (int j = 0; j < n; j++)
            cin >> poziome[i][j];
    vector<int> result;
    result.resize(ma);
    sssize.resize(n * m);
    f.resize(n * m);
    int cis = 0;
    int tuje = 0;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            f[i * n + j] = i * n + j;
            sssize[i * n + j] = 1;
        }
    }//no i teraz bfsss
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            if (!odw[i][j])
                bfsss(i, j, pionowe, poziome);

    for (int i = 0; i < m; i++){
        for (int j = 0; j < n - 1; j++){
            if (pionowe[i][j] == 'C'){// no to patrzymy czy powinno sie usuwac
                on_pion[i][j] = 1;
                cis++;
                int a = i * n + j;
                int b = i * n + j + 1;
                a = find(a);
                b = find(b);
                if (a != b){
                    on_pion[i][j] = 0; // wylaczamy go i laczymy
                    union_(a,b);
                    cis--;
                }
            }
        }
    }
    for (int i = 0; i < m - 1; i++){
        for (int j = 0; j < n; j++){
            if (poziome[i][j] == 'C'){// no to patrzymy czy powinno sie usuwac
                on_poz[i][j] = 1;
                cis++;
                int a = i * n + j;
                int b = (i + 1) * n + j;
                a = find(a);
                b = find(b);
                if (a != b){
                    on_poz[i][j] = 0; // wylaczamy go i laczymy
                    union_(a,b);
                    cis--;
                }
            }
        }
    }
    //teraz zostalo tylko tuje zrobic czyli bfsem pamietajac ojca
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            odw[i][j] = 0;
            odl[i][j] = 0;
            odo[i][j] = make_pair(0, 0);
        }
    }


    bfs_t(0, n /2 + 1, on_pion, on_poz, tuje);
    cout << cis + tuje << " " << cis << endl;
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n - 1; j++){
            if (on_pion[i][j])
                cout << 'Z';
            else
                cout << '.';
        }
        cout << endl;
    }
    for (int i = 0; i < m - 1; i++){
        for (int j = 0; j < n; j++){
            if (on_poz[i][j])
                cout << 'Z';
            else
                cout << '.';
        }
        cout << endl;
    }

    return 0;
}

void bfsss(int w, int k, vector<vector<char>> &pionowe, vector<vector<char>> &poziome){
    int sss = find(w * n + k);
    queue <pair<int, int>> q;  //pierw sa pionowe krotych jest (n -1) * m
    q.push(make_pair(w, k));
    odo[w][k] = make_pair(-1, -1); // ojciec
    pair<int,int> current;
    odw[w][k] = 1;
    while(q.size()){
        current = q.front();
        q.pop();
        w = current.first;
        k = current.second;
        if (w < m - 1){
            if (poziome[w][k] == 'T'){ //tutaj czy jest cis
                if (!odw[w+1][k]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w + 1, k));
                    odo[w + 1][k] = make_pair(current.first, current.second);
                    odl[w + 1][k] = odl[w][k] + 1;
                    odw[w + 1][k] = 1;
                    union_((w+1) * n + k, sss);
                }
            }
        }
        if (w > 0){
            if (poziome[w -1][k] == 'T'){ //poziome czy jest
                if (!odw[w-1][k]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w - 1, k));
                    odo[w - 1][k] = make_pair(current.first, current.second);
                    odl[w - 1][k] = odl[w][k] + 1;
                    odw[w - 1][k] = 1;
                    union_((w-1) * n + k, sss);
                }
            }
        }
        if (k < n - 1){
            if (pionowe[w][k] == 'T'){ //pionowe czy jest
                if (!odw[w][k + 1]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w, k + 1));
                    odo[w][k + 1] = make_pair(current.first, current.second);
                    odl[w][k + 1] = odl[w][k] + 1;
                    odw[w][k + 1] = 1;
                    union_(w * n + k + 1, sss);
                }
            }
        }
        if (k > 0){
            if (pionowe[w][k - 1] == 'T'){ //pionowe czy jest
                if (!odw[w][k - 1]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w, k - 1));
                    odo[w][k - 1] = make_pair(current.first, current.second);
                    odl[w][k - 1] = odl[w][k] + 1;
                    odw[w][k - 1] = 1;
                    union_(w * n + k - 1, sss);
                }
            }
        }
    }
}

void bfs_t(int w, int k, vector<vector<int>> &on_pion, vector<vector<int>> &on_poz, int &tuje){
    queue <pair<int, int>> q;  //pierw sa pionowe krotych jest (n -1) * m
    q.push(make_pair(w, k));
    odo[w][k] = make_pair(-1, -1); // ojciec
    pair<int,int> current;
    odw[w][k] = 1;
    while(q.size()){
        current = q.front();
        q.pop();
        w = current.first;
        k = current.second;
        if (w < m - 1){
            if (!on_poz[w][k]){ //tutaj czy jest cis
                if (!odw[w+1][k]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w + 1, k));
                    odo[w + 1][k] = make_pair(current.first, current.second);
                    odl[w + 1][k] = odl[w][k] + 1;
                    odw[w + 1][k] = 1;
                }
                else{ //jezeli nie ojciec
                    if (odo[w][k] != make_pair(w + 1, k)){
                        on_poz[w][k] = 1; //to jest ladnie zrobiona kolumna
                        tuje++;
                    }
                }
            }
        }
        if (w > 0){
            if (!on_poz[w -1][k]){ //poziome czy jest
                if (!odw[w-1][k]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w - 1, k));
                    odo[w - 1][k] = make_pair(current.first, current.second);
                    odl[w - 1][k] = odl[w][k] + 1;
                    odw[w - 1][k] = 1;
                }
                else{ //jezeli nie ojciec
                    if (odo[w][k] != make_pair(w - 1, k)){
                        on_poz[w -1][k] = 1; //to jest ladnie zrobiona kolumna
                        tuje++;
                    }
                }
            }
        }
        if (k < n - 1){
            if (!on_pion[w][k]){ //pionowe czy jest
                if (!odw[w][k + 1]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w, k + 1));
                    odo[w][k + 1] = make_pair(current.first, current.second);
                    odl[w][k + 1] = odl[w][k] + 1;
                    odw[w][k + 1] = 1;
                }
                else{ //jezeli nie ojciec
                    if (odo[w][k] != make_pair(w, k + 1)){
                        on_pion[w][k] = 1; //to jest ladnie zrobiona kolumna
                        tuje++;
                    }
                }
            }
        }
        if (k > 0){
            if (!on_pion[w][k - 1]){ //pionowe czy jest
                if (!odw[w][k - 1]){ //sprawdzanie czy jest zywoplot
                    q.push(make_pair(w, k - 1));
                    odo[w][k - 1] = make_pair(current.first, current.second);
                    odl[w][k - 1] = odl[w][k] + 1;
                    odw[w][k - 1] = 1;
                }
                else{ //jezeli nie ojciec
                    if (odo[w][k] != make_pair(w, k - 1)){
                        on_pion[w][k - 1] = 1; //to jest ladnie zrobiona kolumna
                        tuje++;
                    }
                }
            }
        }
    }
}