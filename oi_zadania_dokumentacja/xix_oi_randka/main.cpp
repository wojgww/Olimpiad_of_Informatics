#include <iostream>
#include <vector>
#include <queue>

using namespace std;

void bfs_skladowe(int w, vector<vector<int>> &graf, vector<bool> &odw, int n, int it, vector<int> &slabe_skladowe);
void bfs_cykli(int w, vector<int> &graf, vector<int> &odw, int n, vector<vector<int>> &cykl, int &it);
void bfs_lca(int w, vector<vector<int>> &graf, vector<bool> &odw, int n, vector<int> &odl,
             vector<int> &pot2, vector<int> &ojciec, vector<vector<int>> &jump);

const int MAX = 18;

int main()
{
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, k;
    cin >> n >> k;
    vector<int> graf;
    graf.resize(n + 1);
    for(int i =1; i <= n; i++)
        cin >> graf[i];
    vector<vector<int>> operacje;
    operacje.resize(k);
    for (int i= 0; i < k; i++){
        operacje[i].resize(2);
        cin >> operacje[i][0] >> operacje[i][1];
    }
    vector<vector<int>> graf_slaby; //do wyznaczenia slabych skladowych
    graf_slaby.resize(n + 1);
    vector<int> slabe_skladowe;
    slabe_skladowe.resize(n + 1);
    int it= 1;
    for (int i = 1; i <= n; i++)
    {
        graf_slaby[i].push_back(graf[i]);
        graf_slaby[graf[i]].push_back(i);
    }
    vector<bool> odw;
    odw.resize(n + 1);
    for (int i = 1; i <= n; i++){
        if (!odw[i])
            bfs_skladowe(i, graf_slaby, odw, n, it++, slabe_skladowe);
    }
    vector<int> cykl_ze_skladowej;
    cykl_ze_skladowej.resize(n + 1); //ze skladowej do cykla
    for (int i =0; i <= n; i++)
        odw[i] = 0;
    vector<vector<int>> cykl;
    cykl.resize(n + 1);
    it = 0;
    vector<int> odw2;
    odw2.resize(n + 1);
    for (int i = 1; i <= n; i++)
        if (!odw[i])
            bfs_cykli(i, graf, odw2, n, cykl, it);
    for (int i = 1; i <= n; i++){
        if (cykl[i].size())
            cykl_ze_skladowej[slabe_skladowe[cykl[i][0]]] = i;
        else
            break;
    }
    vector<int> pozycja_na_cyklu;
    pozycja_na_cyklu.resize(n + 1);
    for (int i = 0; i <= n; i++)
        pozycja_na_cyklu[i] = -1;
    for (int i = 1; i <= it; i++)
        for (int j = 0; j < cykl[i].size(); j++)
            pozycja_na_cyklu[cykl[i][j]] = j;
    //mamy cykle //mamy spojne // teraz odleglosci kolejno od cykli
    vector<vector<int>> graf_transp;
    graf_transp.resize(n + 1);
    for (int i =1; i <= n; i++)
        graf_transp[graf[i]].push_back(i);
    vector<int> odl;
    odl.resize(n +1);
    for (int i = 1; i <= n; i++)
        odl[i] = -1;
    for (int i = 1; i <= it; i++)
        for (int j = 0; j < cykl[i].size(); j++){
            odl[cykl[i][j]] = 0;
            odw[cykl[i][j]] = 1;
        }
    //potem od nich puszczac bfs-a po transponowanym grafie ktory bedzie od razu robil strukture jumpow dla lca
    vector<vector<int>> jump;
    jump.resize(n + 1);
    //2^18 to jest maks
    for (int i = 1; i<= n; i++){
        jump[i].resize(MAX + 1);
        jump[i][0] = graf[i];
    }
    //w kazdym drzewie jest cykl
    vector<int> pot2;
    int c = 1;
    for (int i = 0; i < 20; i++){
        pot2.push_back(c);
        c <<= 1;
    }
    for (int i = 1; i <= it; i++)
        for (int j = 0; j < cykl[i].size(); j++)//bfs
            bfs_lca(cykl[i][j], graf_transp, odw, n, odl, pot2, graf, jump);

    for (int i = 0; i < k; i++)
    {
        int a = operacje[i][0];
        int b = operacje[i][1];
        int x = 0, y = 0;
        //teraz zrownanie wysokosci   //odl[a];
        if (slabe_skladowe[a] != slabe_skladowe[b]){
            cout << -1 << " " << -1 << '\n';
            continue;
        }
        else
        {
            if (odl[a] < odl[b])//odl[x] odl[y]
            {//b musi nadgonic // dazymy do jak najmniejszej odleglosci od wierzcholka
                y = odl[b] - odl[a];
                x =0;
                for (int j = 18; j >= 0; j--){
                    if (odl[b] - odl[a] >= pot2[j]){
                        b = jump[b][j];
                    }
                }
            }
            if (odl[b] < odl[a])//odl[x] odl[y]
            {//b musi nadgonic // dazymy do jak najmniejszej odleglosci od wierzcholka
                y = 0;
                x = odl[a] - odl[b];
                for (int j = 18; j >= 0; j--){
                    if (odl[a] - odl[b] >= pot2[j]){
                        a = jump[a][j];
                    }
                }
            }
            if (a == b){
                cout << x << " " << y << '\n';
                continue;
            }
            if (odl[a] == odl[b])
            {//teraz lca do gory
                for (int j = 18; j >= 0; j--){
                    if(odl[a] >= pot2[j])
                        if (jump[a][j] != jump[b][j]){ // jak jest rozny to skakac bo to oznacza ze do tej pory sie nie polaczyly
                            a = jump[a][j];
                            b = jump[b][j];
                            x += pot2[j];
                            y += pot2[j];
                        }
                }
                if (odl[a] != 0){
                    a = jump[a][0];
                    b = jump[b][0];
                    x++;
                    y++;
                }
                if (a == b){
                    cout << x << " " << y << '\n';
                    continue;
                }
                //leza razem na cyklu
                int x1, y1;
                if(pozycja_na_cyklu[a] < pozycja_na_cyklu[b]){ // ...a....b..
                    x1 = x + pozycja_na_cyklu[b] - pozycja_na_cyklu[a];
                    y1 = y + cykl[cykl_ze_skladowej[slabe_skladowe[a]]].size() - pozycja_na_cyklu[b] + pozycja_na_cyklu[a];
                    if (max(x1, y) < max(x, y1))
                        cout << x1 << " " << y << '\n';
                    else if (max(x, y1) < max(x1, y))
                        cout << x << " " << y1 << '\n';
                    else{ // rowne
                        if (min(x1, y) <= min(x, y1))
                            cout << x1 << " " << y << '\n';
                        else
                            cout << x << " " << y1 << '\n';
                    }
                }
                else{ // ...b....a..
                    y1 = y + pozycja_na_cyklu[a] - pozycja_na_cyklu[b];
                    x1 = x + cykl[cykl_ze_skladowej[slabe_skladowe[a]]].size() - pozycja_na_cyklu[a] + pozycja_na_cyklu[b];
                    if (max(x1, y) < max(x, y1))
                        cout << x1 << " " << y << '\n';
                    else if (max(x, y1) < max(x1, y))
                        cout << x << " " << y1 << '\n';
                    else{ // rowne
                        if (min(x1, y) <= min(x, y1))
                            cout << x1 << " " << y << '\n';
                        else
                            cout << x << " " << y1 << '\n';
                    }
                }
            }
        }
    }
    return 0;
}

void bfs_lca(int w, vector<vector<int>> &graf, vector<bool> &odw, int n, vector<int> &odl,
             vector<int> &pot2, vector<int> &ojciec, vector<vector<int>> &jump) //ojciec to po prostu zwykly graf
{
    queue <int> q;
    q.push(w);
    odw[w] = true;
    while(q.size()){
        w = q.front();
        q.pop();
        for (int i = 1; i <= MAX; i++)
            if (odl[w] >= pot2[i])
                jump[w][i] = jump[jump[w][i - 1]][i - 1];
        for (int i = 0; i < graf[w].size(); i++)
        {
            if(!odw[graf[w][i]]){
                odw[graf[w][i]] = true;
                odl[graf[w][i]] = odl[w] + 1;
                q.push(graf[w][i]);
            }
        }
    }
}

void bfs_cykli(int w, vector<int> &graf, vector<int> &odw, int n, vector<vector<int>> &cykl, int &it)
{
    int itt = w;
    queue <int> q;
    q.push(w);
    odw[w] = itt;
    int last = 0;
    while(q.size()){
        w = q.front();
        q.pop();
        if(!odw[graf[w]]){
            odw[graf[w]] = itt;
            q.push(graf[w]);
        }
        else if(odw[graf[w]] == itt)
        {//byl juz odwiedzony (jest cykl)
            last = w;
            break;
        }
    }
    if (last)
    {
        it++;
        w = graf[last];
        cykl[it].push_back(w);
        while(w != last)
        {
            w = graf[w];
            cykl[it].push_back(w);
        }
    }

}

void bfs_skladowe(int w, vector<vector<int>> &graf, vector<bool> &odw, int n, int it, vector<int> &slabe_skladowe)
{
    queue <int> q;
    q.push(w);
    odw[w] = true;
    while(q.size()){
        w = q.front();
        q.pop();
        slabe_skladowe[w] =it;
        for (int i = 0; i < graf[w].size(); i++)
        {
            if(!odw[graf[w][i]]){
                odw[graf[w][i]] = true;
                q.push(graf[w][i]);
            }
        }
    }
}

void bfs(int w, vector<int> &graf, vector<bool> &odw, vector<int> &odl, int n)
{
    queue <int> q;
    q.push(w);
    odw[w] = true;
    while(q.size()){
        w = q.front();
        q.pop();
        if(!odw[graf[w]]){
            odw[graf[w]] = true;
            odl[graf[w]] = odl[w] + 1;
            q.push(graf[w]);
        }
    }
}

