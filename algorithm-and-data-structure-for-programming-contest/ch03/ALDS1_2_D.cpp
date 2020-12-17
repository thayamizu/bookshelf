#include <algorithm>
#include <iostream>
#include <deque>
#include <vector>

long long count = 0;
/**
 * 配列の内容を出力
 * @param std::vector<int> v
 * @param int n
 */
void println(const std::vector<int> &v)
{
    const auto n = v.size();
    for (size_t i = 0; i < n - 1; i++)
    {
        std::cout << v[i] << std::endl;
    }
    std::cout << v[n - 1] << std::endl;
}

/**
 * 配列の内容を出力
 * @param std::vector<int> v
 * @param int n
 */
void print(const std::vector<int> &v)
{
    const auto n = v.size();
    for (size_t i = 0; i < n - 1; i++)
    {
        std::cout << v[i] << " ";
    }
    std::cout << v[n - 1] << std::endl;
}

/**
 * 配列の内容を出力
 * @param std::vector<int> v
 * @param int n
 */
void reverse_print(const std::vector<int> &v)
{
    const auto n = v.size();
    for (size_t i = n - 1; i > 0; i--)
    {
        std::cout << v[i] << " ";
    }
    std::cout << v[0] << std::endl;
}
/**
 * 挿入ソート
 * @param std::vector<int> v
 * @param int n
 */
void insertion_sort(std::vector<int> &a, int g)
{
    int i, j, v;
    const auto size = a.size();
    for (i = g; i < size; i++)
    {
        v = a[i];
        j = i - g;
        while (j >= 0 && a[j] > v)
        {
            a[j + g] = a[j];
            j -= g;
            count++;
        }
        a[j + g] = v;
    }
}

/**
 * 挿入ソート
 * @param std::vector<int> v
 * @param int n
 */
void shell_sort(std::vector<int> &a)
{
    const auto size = a.size();
    auto g = std::vector<int>();

    auto v = 1;
    do
    {
        g.push_back(v);
        v = (3 * v) + 1;

    } while (size > v);

    const auto m = g.size();
    std::cout << m << std::endl;
    reverse_print(g);

    for (auto it = g.rbegin(); it != g.rend(); it++)
    {
        insertion_sort(a, *it);
    }

    std::cout << count << std::endl;
    println(a);
}

int main(int argc, char const *argv[])
{
    using namespace std;

    int n;
    cin >> n;
    vector<int> a = vector<int>(n);

    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }

    int count = 0;
    shell_sort(a);

    return 0;
}
