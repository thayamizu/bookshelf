#include <algorithm>
#include <iostream>
#include <vector>

struct Card
{
    char suite, value;
};

bool operator>(const Card &left, const Card &right)
{
    return left.value > right.value;
}

bool operator<(const Card &left, const Card &right)
{
    return left.value < right.value;
}

bool operator!=(const Card &left, const Card &right)
{
    return left.value != right.value;
}

/**
 * 配列の内容を出力
 * @param std::vector<int> v
 * @param int n
 */
void print(const std::vector<Card> &v)
{
    const auto size = v.size();
    for (size_t i = 0; i < size - 1; i++)
    {
        std::cout << v[i].suite << v[i].value << " ";
    }

    std::cout << v[size - 1].suite << v[size - 1].value << std::endl;
}

/**
 * bubble-sort 
 * @param std::vector<int> &v; 
 */
void bubble_sort(std::vector<Card> &v)
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
void selection_sort(std::vector<Card> &v)
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
        }
    }
}

bool is_stable(const std::vector<Card> &a, const std::vector<Card> &b)
{
    const auto size = a.size();
    for (size_t i = 0; i < size; i++)
    {
        if (a[i].suite != b[i].suite)
        {
            return false;
        }
    }

    return true;
}

int main(int argc, char const *argv[])
{
    using namespace std;

    int n;
    cin >> n;

    auto a = vector<Card>(n);
    for (int i = 0; i < n; i++)
    {
        cin >> a[i].suite >> a[i].value;
    }

    auto b = a;

    bubble_sort(a);
    print(a);
    cout << "Stable" << endl;
    selection_sort(b);
    print(b);
    if (is_stable(a, b))
    {
        cout << "Stable" << endl;
    }
    else
    {
        cout << "Not stable" << endl;
    }

    return 0;
}
