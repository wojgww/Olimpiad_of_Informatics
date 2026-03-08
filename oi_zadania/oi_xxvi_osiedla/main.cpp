#include <iostream>
#include <vector>

using namespace std;

class krawedz
{
    public:
    int a, b;
    int id;
    krawedz(int x, int y, int i);
    krawedz();
};

void dfs(int w, vector<vector<krawedz>> &graf, vector<int> &preorder, vector<int> &low, int c,
         vector<vector<int>> &dwuspojne, int &it, vector<int> &krawedzie, vector<bool> &skierowanie, vector<krawedz> &m_krawedzi);

int main()
{
    //dfsem przechodzimy przez wszystkie krawedzie
    //post-orderem robimy dwuspojne
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    vector<vector<krawedz>> graf;
    vector<krawedz> m_krawedzi;
    m_krawedzi.resize(m + 1);
    graf.resize(n + 1);
    int a, b;
    for (int i = 0; i < m; i++){
        cin >> a >> b;
        graf[a].push_back(krawedz(a, b, i));
        graf[b].push_back(krawedz(b, a, i));
        m_krawedzi[i] = krawedz(a, b, i);
    }
    vector<vector<int>> dwuspojne;
    dwuspojne.resize(n);
    vector<int> mosty;
    vector<int> preorder;
    preorder.resize(n + 1);
    vector<int> low;
    low.resize(n + 1);
    int it = 0;
    vector<int> krawedzie;
    krawedzie.resize(max(m +  1, n + 1));
    vector<bool> skierowanie;
    skierowanie.resize(m + 1);
    //teraz puszczamy dfs-a i posorderowo bedziemy znajdowali cykle
    //dfsa bedzie trzeba wykonac wiele razy bo nie wszysktie wierzcholki naleza do jednej spojnej skladowej
    for (int i = 1; i <= n; i++){
        if (!preorder[i]){//dfs (trzeba go urozmaicic wyszukiwaniem dwuspojnych
            dfs(i, graf, preorder, low, 1, dwuspojne, it, krawedzie, skierowanie, m_krawedzi);   // jezeli nie da sie przejsc w gore w low to jest nowa spojna od nowego wierzcholka (jest most)
            //teraz po tym robimy skierowanie grafu
        }
    }
    cout << it << '\n';
    for (int i = 0; i <m; i++){
        if (skierowanie[i] == 0)
            cout << '<';
        else
            cout << '>';
    }
    return 0;
}

void dfs(int w, vector<vector<krawedz>> &graf, vector<int> &preorder, vector<int> &low, int c,
         vector<vector<int>> &dwuspojne, int &it, vector<int> &krawedzie, vector<bool> &skierowanie, vector<krawedz> &m_krawedzi){ //krawedzie - z ktorego przyszedl
    preorder[w] = c;
    low[w] = preorder[w];
    bool yes = 0;
    for (int i =0; i < graf[w].size(); i++){
        if (!preorder[graf[w][i].b]){
            krawedzie[graf[w][i].id] = 1;
            if (m_krawedzi[graf[w][i].id].a == graf[w][i].a)
                skierowanie[graf[w][i].id] = 0;
            else
                skierowanie[graf[w][i].id] = 1;
            dfs(graf[w][i].b, graf, preorder, low, c + 1, dwuspojne, it, krawedzie, skierowanie, m_krawedzi);
            low[w] = min(low[w], low[graf[w][i].b]);
        }
        else{
            //nie moze byc to ojciec
            if (!krawedzie[graf[w][i].id]){
                low[w] = min(low[w], low[graf[w][i].b]);
                //skierowanie do wiekszego do mniejszego post ordera
                if (preorder[m_krawedzi[graf[w][i].id].a] > preorder[m_krawedzi[graf[w][i].id].b])
                    skierowanie[graf[w][i].id] = 0;
                else
                    skierowanie[graf[w][i].id] = 1;
            }
        }
    }
    if(low[w] == preorder[w]){ //krawedz ktora prowadzi do w to most
        //krawedzie[w] = 0;
        it++;
    }
}

krawedz::krawedz(int x, int y, int i){
    a = x;
    b = y;
    id = i;
}

krawedz::krawedz(){
    a = 0;
    b = 0;
    id = 0;
}
