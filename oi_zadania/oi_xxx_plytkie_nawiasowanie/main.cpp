#include <iostream>

using namespace std;

int main()
{
    int n, h;
    cin >> n >> h;
    string brackets;
    cin >> brackets;
    int current = 0;
    int result = 0;
    for (int i = 0; i < brackets.size(); i++)
    {
        if (brackets[i] == '(')
        {
            current++;
            if (current > h)
            {
                result++;
                current -= 2;
            }
        }
        else
        {
            current--;
            if (current < 0)
            {
                result++;
                current += 2;
            }
        }
    }
    cout << result << '\n';
    return 0;
}
