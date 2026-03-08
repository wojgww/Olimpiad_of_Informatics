#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool compare(pair<long long, long long> a, pair<long long, long long> b)
{
    return a.first < b.first;
}

int main()
{
    long long n, k;
    cin >> n;
    cin >> k;
    vector<pair<long long, long long>> boxes;
    vector<vector<pair<long long, long long>>> matches;
    matches.resize(2);
    matches[0].resize(n);
    matches[1].resize(n);
    boxes.resize(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> boxes[i].first;
        boxes[i].second = i + 1;
    }
    sort(boxes.begin(), boxes.end(), compare);
    long long it1 = n -1;
    long long rest;
    long long it2 = 0;
    long long used = 0;
    for (long long i = 0; i < n; i++)
    {
        if (boxes[i].first >= k)
        {
            it1 = i;
            break;
        }
    }

    /*
    for (long long i = 0; i < n; i++)
    {
        if (boxes[it1].first <= k)
        {
            it1--;
            if (boxes[it1].first <= k)
            {
                //da sie ulozyc
                break;
            }
        }
        if (boxes[i].first >= k)
        {
            it2 = i;
            break;
        }

        if (boxes[i].first < k)
        {
            rest = k - boxes[i].first;
            boxes[it1].first -= rest;
            used++;
            matches[0][i] = make_pair(boxes[i].second, k - rest);
            matches[1][i] = make_pair(boxes[it1].second, rest);
        }
        else
            break;
    }
//k = 10   it2                                 it1
    //     10  12  13  16  19  20  21  24  24   4   2   4   9   3   2
*/
    for (long long i = 0; i < n; i++)
    {
        if (it1 < n)
            if (boxes[it1].first <= k)
                it1++;
        //if (it1 < it2)
        //{
           //da sie ulozyc (jest pewne)
        //}
        //iterujemy sie od n - 1;
        //laczymy  it1 - 1 z n - 1 do it1
        if(boxes[i].first > k)
        {
            cout << "NIE";
            return 0;
        }

        rest =  k - boxes[i].first;
        matches[0][i] = make_pair(boxes[i].second, boxes[i].first);
        boxes[i].first = 0;
        if (it1 < n)
        {
            boxes[it1].first -= rest;
            used++;
            matches[1][i] = make_pair(boxes[it1].second, rest);
        }
        //naturalnie to jedno przesuniecie

    }

    cout << "TAK" << '\n';
    long long count = 0;
    for (long long i = 0; i < n; i++)
    {
        count = 0;
        if (matches[0][i].second > 0)
        {
            count++;
            if (matches[1][i].second > 0)
            {
                count++;
            }
        }
        cout << count << " ";
        if (count >= 1)
            cout << matches[0][i].first << " " << matches[0][i].second;
        if (count == 2)
            cout << " " << matches[1][i].first << " " << matches[1][i].second;
        cout << '\n';
    }

        //od it1 wlacznie sa mniejsze od i
    return 0;
}
