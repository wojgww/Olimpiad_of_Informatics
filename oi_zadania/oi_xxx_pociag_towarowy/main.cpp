#include <iostream>
#include <vector>

using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> seqn;
    vector<int> seqm;
    vector<int> lastl;
    vector<int> lastr;
    seqn.resize(n);
    seqm.resize(m);
    lastl.resize(k + 1);
    lastr.resize(k + 1);
    for (int i =0; i < n; i++)
        cin >> seqn[i];
    for (int j =0; j < m; j++)
        cin >> seqm[j];
    int itj = 0;
    vector<int> seqleft;
    vector<int> seqright;
    vector<bool> seq;
    seq.resize(n);
    seqleft.resize(n);
    seqright.resize(n);
    for (int i = 0; i < n; i++)
    {
        if (itj < m)
            if (seqn[i] == seqm[itj])
            {
                itj++;
                lastl[seqn[i]] = itj;
            }
        seqleft[i] = lastl[seqn[i]];
        /*
        if (used[seqn[i]])
            seqleft[i] = 1;
        else
            seqleft[i] = 0; */
    }
    if (itj < m -1)
        for (int i = 0; i < n; i++)
            seqleft[i] = 0;
    itj = m - 1;
    //for (int i = 0; i <= k; i++)
        //used[i] = 0;
    int counter = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (itj >= 0)
            if (seqn[i] == seqm[itj])
            {
                itj--;
                counter++;
                lastr[seqn[i]] = counter;
            }
        seqright[i] = lastr[seqn[i]];
        //if (used[seqn[i]])
        //    seqright[i] = 1;
        //else
        //    seqright[i] = 0;
    }
    if (itj > 0)
        for (int i =0; i < n;i++)
            seqright[i] = 0;

    for (int i = 0; i < n; i++)
    {
        if (seqright[i] + seqleft[i] >= m)
            seq[i] = 1;
        else
            seq[i] = 0;
        //seq[i] = seqleft[i] && seqright[i];
    }
    for (int i = 0; i < n; i++)
        cout << seq[i] << " ";

    return 0;
}
