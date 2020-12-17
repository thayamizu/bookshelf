#include <algorithm>
#include <iostream>
#include <vector>

/**
 * 配列の内容を出力
 * @param std::vector<int> v
 * @param int n
 */
void print(std::vector<int> v, int n)
{
    for (size_t i = 0; i < n - 1; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << v[n - 1] << std::endl;
}

/**
 * 挿入ソート
 * @param std::vector<int> v
 * @param int n
 */
void insertion_sort(std::vector<int> a, int n)
{
    int i, j, v;
    for (i = 1; i < n; i++)
    {
        v = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > v)
        {
            a[j + 1] = a[j];
            j--;
        }
        a[j + 1] = v;
        print(a, n);
    }
}

static const int MAX = 100;
int main()
{
    using namespace std;

    int n;
    cin >> n;
    vector<int> a = vector<int>(MAX);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    print(a, n);
    insertion_sort(a, n);

    return 0;
}