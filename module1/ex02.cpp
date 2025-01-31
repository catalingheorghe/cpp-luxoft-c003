/* Read an array from input (n numbers). Reverse it */

#include <iostream>
#include <vector>

void reverse_it(std::vector<int>& v)
{
    // note the & above in the parameter; w/o it, no reverse

    for (int i = 0, j = v.size() - 1; i < j; i++, j--) {
        int tmp;
        tmp = v[i];
        v[i] = v[j];
        v[j] = tmp;
    }

    return;
}

void print_vector(const std::vector<int>& v)
{
    for (auto i : v) {
        std::cout << i << " ";
    }
    std::cout << "\n";
}

int main()
{
    std::vector<int> v{1, 2, 3};
    //int n;

    //std::cout << "num elements: ";
    //std::cin >> n;
 
    reverse_it(v);

    print_vector(v);

    return 0;
}

// what about some simple unit tests here? with doctest?


