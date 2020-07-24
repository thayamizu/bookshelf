#include <algorithm>
#include <iostream>
#include <vector>

static const int MAX = 200000;

int main()
{
    using namespace std;

    int n;
    cin >> n;
    vector<int> r = vector<int>(MAX);

    for (int i = 0; i < n; i++)
    {
        cin >> r[i];
    }

    int max_value = -2000000000;
    int min_value = r[0];

    for (int i = 1; i < n; i++)
    {
        max_value = max(max_value, r[i] - min_value);
        min_value = min(min_value, r[i]);
    }

    cout << max_value << endl;

    return 0;
}