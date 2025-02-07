/* Find all even numbers in a vector
 * use std::copy_if, for_each plus lambda
 * 
 * CXXFLAGS="-Wall -Werror -DDOCTEST_CONFIG_DISABLE" make ex06
 * CXXFLAGS="-Wall -Werror" make ex06
 */

#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"

using namespace std;

TEST_CASE("testing TODO") {
    // TODO
}

void printVector(const vector<int>& v)
{
    cout << "Vector: ";
    for (auto i : v) {
        cout << i << " ";
    }
    cout << "\n"; // or "cout << endl"
    // NOTE printf is standard C, not really cpp; cpp offers alternatives
}
// std::copy(v.begin(), v.end(), std::ostream_iterator<int>(std::cout, " "));

#ifdef DOCTEST_CONFIG_DISABLE
int main()
{
    vector<int> v { 3, 2, 4, 1, 6, 5 };
    vector<int> even_v {};

    printVector(v);

    // print even numbers
    std::cout << "even numbers are: ";
    std::copy_if(v.begin(), v.end(),
            std::ostream_iterator<int>(std::cout, " "),
            [](int x) { return x % 2 == 0; });
    std::cout << std::endl;

    // now copy them to another vector and...
    std::copy_if(v.begin(), v.end(),
            std::back_inserter(even_v),
            [](int x) { return x % 2 == 0; });

    // ... print with a for each
    std::cout << "new vector with even numbers" << std::endl;
    std::for_each(even_v.begin(), even_v.end(),
            [](const int x){ std::cout << x << ' '; });
    std::cout << std::endl;

    return 0;
}
#else
int main()
{
    doctest::Context context;
    int res = context.run();
    if (context.shouldExit())
        return res;

    return res;
}
#endif
