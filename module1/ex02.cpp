/* Read an array from input (n numbers). Reverse it */

#include <iostream>
#include <vector>
// vector is safer/better than int arr[] (downside: a bit more memory)

void reverse_it(std::vector<int>& v)
{
    // NOTE w/o reference (&) above, copy is passed, not reversed

    for (size_t i = 0, j = v.size() - 1; i < j; i++, j--) {
        int tmp;
        tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
        // or builtin "swap()"
    }

    return;
}

void print_vector(const std::vector<int>& v)
{
    std::cout << "Vector: ";
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n"; // or "cout << endl"
    // NOTE printf is standard C, not really cpp; cpp offers alternatives
}

int main()
{
    std::vector<int> v{};
    size_t n = 0;

    std::cout << "num elements: ";
    std::cin >> n;
    for (size_t i = 0; i < n; i++) {
        int val = 0;
        std::cin >> val;
        v.push_back(val);
    }
 
    reverse_it(v);

    print_vector(v);

    return 0;
}

// what about some simple unit tests here? with doctest?


