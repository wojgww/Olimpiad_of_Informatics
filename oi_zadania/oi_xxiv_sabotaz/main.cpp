#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    int n;
    int k;
    cin >> n;
    cin >> k;
    int *tree = new int[n + 1];
    tree[0] = -1;
    tree[1] = 1;
    for (int i = 2; i <= n; i++)
        cin >> tree[i];

    int *leafs = new int[n + 1];
    leafs[0] = 0;
    leafs[1] = 0;

    for (int i = 2; i < n; i++)
        leafs[i] = 1;

    //znajdowanie dzieci
    for (int i = 2; i < n; i++)
        leafs[tree[i]] = 0;

    vector<int> leaf;
    for (int i = 2; i <= n; i++)
        if (leafs[i])
            leaf.push_back(i);

    int *max = new int[n + 1];
    max[0] = -1;
    //max[1] = n;
    for (int i = 1; i <= n; i++)
        max[i] = 1;


    for (int i = n; i > 1; i--)
        max[tree[i]] += max[i];

    double minimal;

    double *morale = new double[n + 1];

    for (int i = 0; i <= n; i++)
        morale[i] = 0;

    for (int i = 0; i < leaf.size(); i++)
        morale[leaf[i]] = 1;

    for (int i = n; i > 0; i--)
    {
        //morale[tree[i]];
        minimal = min(morale[i], (double)max[i] / (max[tree[i]] - 1));
        if (morale[tree[i]] < minimal)
            morale[tree[i]] = minimal;
    }

    double result = 0;
    int change = 0;
    for (int i = 1; i <= n; i++)
    {
        if (max[i] > k)
            if (result < morale[i])
            {
                change = 1;
                result = morale[i];
            }
    }

    //result  = 1 dla 2g

//    cout << "\n";
    if (n == 2 && k == 1)
        result = 1;
    cout << result << "\n";

    delete[] morale;
    delete[] max;
    delete[] leafs;
    delete[] tree;

    return 0;
}
