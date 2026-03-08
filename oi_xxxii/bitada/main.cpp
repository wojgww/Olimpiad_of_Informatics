#include <iostream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<int>> grafa;
vector<vector<int>> grafb;
long long mod;

void bfs(int w, vector<vector<int>> &graf, vector<pair<int, int>> &odl, vector<bool> &odw, int m,
         vector<int> &fatherb, vector<vector<int>> &sons);

class element{
public:
    int current;
    int before;
    int currenta;
    int beforea;
    element();
    element(int, int, int, int);
};

element::element(int a, int b, int c, int d){
    current = a;
    before = b;
    currenta = c;
    beforea = d;
}
element::element(){
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin >> n >> m >> k;
    int a, b;
    mod = k;
    grafa.resize(n + 1);
    grafb.resize(m + 1);
    for (int i = 0; i < n - 1; i++){
        cin >> a >> b;
        grafa[a].push_back(b);
        grafa[b].push_back(a);
    }
    for (int i = 0; i < m - 1; i++){
        cin >> a >> b;
        grafb[a].push_back(b);
        grafb[b].push_back(a);
    }
    if (n == 1){
        cout << m % mod;
        return 0;
    }
    int first;
    for (int i =1; i <= n; i++)
        if (grafa[i].size() == 1){
            first = i;
            break;
        }
    int second;
    for (int i = 1; i < m; i++){
        if (grafb[i].size() == 1){ // poczatek grafu m;
            second = i;
            break;
        }
    }
    vector<pair<int, int>> odl;
    vector<bool> odw;
    odl.resize(n + 1); // (odl, wierzcholek)
    odw.resize(n + 1);
    vector<int> fatherb, fathera;
    vector<vector<int>> sonsa, sonsb;
    sonsa.resize(n + 1);
    sonsb.resize(m + 1);
    fathera.resize(m + 1);
    fatherb.resize(m + 1);
    bfs(first, grafa, odl, odw, n, fathera, sonsa);
    vector<pair<int, int>> odl2;
    vector<bool> odw2;
    odl2.resize(m + 1);
    odw2.resize(m + 1);
    bfs(second, grafb, odl2, odw2, m, fatherb, sonsb);
    vector<vector<long long>> dynamik;
    dynamik.resize(m + 1);
    for (int i = 1; i <= m; i++)
        dynamik[i].resize(n + 1);
    int te;
    for (int i = n -1; i >= 0; i--){ //po dobrej kolejnosci musi byc to i to znaczy po odl od konca
        //jebac to i
        te = i;
        i = odl[i].second;
        int syn1, syn2; //syn to jest w grafie n czyli b i z synow tworzymy dynamika w wywolaniach
        for (int j = 1; j <= m; j++){
            int wyw1, wyw2; //wyw - to jest w grafie m czyli b
            //if (grafa[i].size() > grafb[j].size()){ //po prostu nie da sie umiescic
            if (sonsa[i].size() > sonsb[j].size()){
                dynamik[j][i] = 0;
                continue;
            }
            if (sonsb[j].size() >= 0 && sonsa[i].size() == 0){ //lisc i wiecej nie potrzeba (schodzenia w dol)
                dynamik[j][i] = 1;
                continue;
            }
            else if (sonsb[j].size() == 1 && sonsa[i].size() == 1){
                dynamik[j][i] = dynamik[ sonsb[j][0] ][sonsa[i][0]]; //wczesn8iej jeszcze grafa
                //od syna w grafie n zbiera jego dynamika - ktory jest rowniez w grafie m
            }
            else if (sonsb[j].size() == 2 && sonsa[i].size() == 1){
                dynamik[j][i] = dynamik[ sonsb[j][0] ][sonsa[i][0]] +
                                dynamik[ sonsb[j][1] ][sonsa[i][0]];
                dynamik[j][i] %= mod;
                //od syna w grafie n zbiera jego dynamika - ktory jest rowniez w grafie m
            }
            else{ //2 i 2
                dynamik[j][i] = dynamik[ sonsb[j][0] ][sonsa[i][0]] * dynamik[ sonsb[j][1] ][sonsa[i][1]]
                        + dynamik[ sonsb[j][1] ][sonsa[i][0]] * dynamik[ sonsb[j][0] ][sonsa[i][1]];
                dynamik[j][i] %= mod;
            }//no i klasa sa zrobione wszystkie warunki
        }
        i = te;
    }
    //teraz
    vector<vector<long long>> up;
    vector<long long> up_wyn;
    up_wyn.resize(m + 1);
    up.resize(m + 1);
    int current;
    int before; // do j
    int currenta;
    int beforea;
    int syn;
    queue <element> q;
    element temp;
    for (int j = 1; j <= m; j++){
        up[j].resize(n + 1);
        if (fatherb[j] != 0){
            while(!q.empty())
                q.pop();
            up_wyn[j] = 0;
            q.push(element(fatherb[j], j, sonsa[first][0], first));
            up[j][first] = 1;
            up[j][sonsa[first][0]] = 1;
            while (!q.empty()){
                temp = q.front();
                q.pop();
                //if (beforea == -1){
                //    up[j][temp.currenta] = 1;
                //    if (fatherb[temp.current] == 0)
                //        break;
                //    q.push(element(fatherb[temp.current], temp.current, sonsa[temp.currenta][0], temp.currenta));
                //}
                if (grafb[temp.current].size() < grafa[temp.currenta].size()){
                    up[j][temp.currenta] = 0;
                    continue;
                }//warunku na father nie trzeba robic
                if (sonsa[temp.currenta].size() == 0){
                    up[j][temp.currenta] *= up[j][temp.beforea]; //chyba jeszcze uwzglednic trzeba gdzie go mozna umiescic
                    up[j][temp.currenta] %= mod;
                    up_wyn[j] += up[j][temp.currenta];    // to znaczy chyba jaki ma stopien
                    up_wyn[j] %= mod;
                }
                if (sonsa[temp.currenta].size() == 1){
                    up[j][temp.currenta] *= up[j][temp.beforea];
                    up[j][temp.currenta] %= mod;
                    up[j][sonsa[temp.currenta][0]] = 1;
                    if (fatherb[temp.current] == 0)
                        break;
                    q.push(element(fatherb[temp.current], temp.current, sonsa[temp.currenta][0], temp.currenta));
                    if (sonsb[temp.current].size() == 2){
                        if (temp.before == sonsb[temp.current][0])
                            syn = sonsb[temp.current][1];
                        else
                            syn = sonsb[temp.current][0];
                        up_wyn[j] += (up[j][temp.currenta] * dynamik[syn][sonsa[temp.currenta][0]]); //bo sie konczy
                        up_wyn[j] %= mod;
                    }
                }
                if (sonsa[temp.currenta].size() == 2){ // dla 1 to poprostu przechodzimy do gory i nawet nie trzeba mnozyc
                    up[j][temp.currenta] *= up[j][temp.beforea];
                    up[j][temp.currenta] %= mod;
                    if (sonsb[temp.current][0] == temp.before)
                        syn = sonsb[temp.current][1];
                    else
                        syn = sonsb[temp.current][0];
                    up[j][sonsa[temp.currenta][0]] = dynamik[syn][sonsa[temp.currenta][1]];
                    up[j][sonsa[temp.currenta][0]] %= mod;
                    if (fatherb[temp.current] == 0)
                        break;
                    q.push(element(fatherb[temp.current], temp.current, sonsa[temp.currenta][0], temp.currenta));
                    //no i na odwrot
                    up[j][sonsa[temp.currenta][1]] = dynamik[syn][sonsa[temp.currenta][0]];
                    q.push(element(fatherb[temp.current], temp.current, sonsa[temp.currenta][1], temp.currenta));
                }
            }
        }
        else
            up_wyn[j] = 0;
    }
    long long wynik = 0;
    for (int i = 1; i <= m; i++){
        wynik += up_wyn[i];
        wynik %= mod;
        wynik += dynamik[i][first];
        wynik %= mod;
    }
    cout << wynik << endl;
    return 0;
}

void bfs(int w, vector<vector<int>> &graf, vector<pair<int, int>> &odl, vector<bool> &odw, int m,
         vector<int> &fatherb, vector<vector<int>> &sons){
    queue <pair<int, int>> q;
    q.push(make_pair(w, 0));
    odw[w] = true;
    int it = 0;
    odl[it++] = make_pair(0, w);
    int l;
    while(q.size()){
        w = q.front().first;
        l = q.front().second;
        q.pop();
        for(int i  =0; i < graf[w].size(); i++){
            if(!odw[graf[w][i]]){
                odw[graf[w][i]] = true;
                sons[w].push_back(graf[w][i]);
                odl[it++] = make_pair(l + 1, graf[w][i]);
                fatherb[graf[w][i]] = w;
                q.push(make_pair(graf[w][i], l + 1));
            }
        }
    }
}
