#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, k;
    cin >> n >> k;
    vector<vector<long long>> pasazerowie;
    pasazerowie.resize(n + 1);
    //trzeba miec cos co przechowuje z jakiego  k  bral dp[i][j]   - np dp[i][j] bral od dp[i - 1][k]
    for (int i = 1; i < n; i++)
    {
        pasazerowie[i].resize(n - i);
        for (int j = 0; j < n - i; j++)
        {
            cin >> pasazerowie[i][j];
        }
    }
    vector<long long> wiersze;
    wiersze.resize(n + 1);
    long long suma;
    for (int i = 1; i < n; i++)
    {
        suma = 0;
        for (int j = 0; j < n - i; j++)
        {
            suma += pasazerowie[i][j];
        }
        //wiersze[i] = suma + wiersze[i + 1];
        wiersze[i] = suma;
    }
    vector<vector<long long>> macierz;
    macierz.resize(n - 1);
    for (int i = 0; i < n - 1; i++)
    {// kolumny zaczynaja sie od  2   a wiersze koncza na n - 1
        macierz[i].resize(n - 1);
        //for (int j = i; j < n - 1; j++)
        for (int j = 0; j < n - 1 - i; j++)
        {
            macierz[i][j + i] = pasazerowie[i + 1][j];
        }
    }


    vector<vector<long long>> prostokaty;
    prostokaty.resize(n + 1);    //od i tego do j - tego
    prostokaty[n].resize(n + 1);
    long long current_sum;
    for (int i = n - 1; i >= 1; i--)
    {
        prostokaty[i].resize(n + 1);
        current_sum = 0;
        //prostokaty[i + 1][j]  - wiersze[i + 1]
        for (int j = i; j >= 1; j--)
        {
            current_sum += macierz[j - 1][i - 1];
            //trzeba brac gore (sume z gory i z boku i usuwac kolejno wiersze jak sie bierze sume z boku)
            prostokaty[i][j] = prostokaty[i + 1][j] + current_sum - wiersze[i +1]; //prostokaty[i + 1][j]  - wiersze[i + 1] tylko ze sumy
        }
    }

    vector<vector<long long>> dp;
    vector<vector<int>> used;
    dp.resize(k + 1);
    used.resize(k + 1);
    for (int i = 0; i <= k; i++)
    {
        dp[i].resize(n+1);
        used[i].resize(n+1);
    }


    for (int j = 1; j <= n; j++)
    {
        dp[1][j] = prostokaty[j][1];
    }
    long long maks;
    int id1;
    for (int i = 2; i <= k; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            maks = -1;
            id1 = -1;
            //dp[i][j] obliczamy
            for (int c = j - 1; c >= 1; c--)
            {
                if (maks < dp[i - 1][c] + prostokaty[j][c + 1])
                {
                    maks = dp[i - 1][c] + prostokaty[j][c + 1];
                    id1 = c;
                }
            }
            dp[i][j] = maks;
            used[i][j] = id1;
        }
    }
    maks = 0;
    int id = - 1;
    for (int i = 1; i <= n; i++)
    {
        if (dp[k][i] > maks)
        {
            id = i;
            maks = dp[k][i];
        }
    }
    vector<int> kolejnosc;
    kolejnosc.push_back(id);
    for (int i = k; i > 1; i--)
    {
        id = used[i][id];
        kolejnosc.push_back(id);
    }
    for (int i = kolejnosc.size() - 1; i >= 0; i--)
        cout << kolejnosc[i] << " ";
    cout << endl;

    //wydrukowac - jakie stacje
    return 0;
}
