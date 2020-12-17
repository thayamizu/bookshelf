#include <algorithm>
#include <iostream>
#include <vector>

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
 * bubble-sort 
 * @param std::vector<int> &v; 
 */
void bubble_sort(std::vector<int> &v)
{
    using std::swap;

    const int size = v.size();
    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = size - 1; j >= i + 1; j--)
        {
            if (v[j] < v[j - 1])
            {
                swap(v[j], v[j - 1]);
            }
        }
    }
}

/**
 * selection-sort 
 * @param std::vector<int> &v; 
 */
void selection_sort(std::vector<int> &v, int &n)
{
    using std::swap;

    const int size = v.size();
    for (size_t i = 0; i < size; i++)
    {
        int min_i = i;
        for (size_t j = i; j < size; j++)
        {
            if (v[j] < v[min_i])
            {
                min_i = j;
            }
        }
        if (v[i] != v[min_i])
        {
            swap(v[i], v[min_i]);
            n++;
        }
    }
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
    selection_sort(a, count);
    print(a);
    cout << count << endl;
    return 0;
}
