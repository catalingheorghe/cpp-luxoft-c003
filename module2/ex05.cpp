/* Custom sort
 * 
 * CXXFLAGS="-Wall -Werror -DDOCTEST_CONFIG_DISABLE" make ex05
 * CXXFLAGS="-Wall -Werror" make ex05
 */

#include <iostream>
#include <vector>

#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"

using namespace std;

void customSort(vector<int> &v, bool (*compare)(int, int))
{
    if (compare == NULL) return;

    // "good" old bubble sort
    for (size_t i = 0; i < v.size() - 1; i++) {
        for (size_t j = i + 1; j < v.size(); j++) {
            if (compare(v[i], v[j]) == false) {
                swap(v[i], v[j]);
            }
        }
    }

    return;
}

// if a < b (ascending), true
bool compareAsc(int a, int b)
{
    if (a < b)
        return true;
    else
        return false;
}

// if a > b (descending), true
bool compareDesc(int a, int b)
{
    return !compareAsc(a, b); // :)
}


TEST_CASE("testing compareAsc/Desc") {
    CHECK(compareAsc(1, 2) == true);
    CHECK(compareAsc(1, 1) == false);
    CHECK(compareAsc(2, 1) == false);
    CHECK(compareDesc(1, 2) == false);
    CHECK(compareDesc(1, 1) == true); // :)
    CHECK(compareDesc(2, 1) == true);
}

TEST_CASE("testing compareAsc/Desc") {
    vector<int> v { 3, 2, 4, 1, 6, 5 };
    vector<int> res { 1, 2, 3, 4, 5, 6 };

    customSort(v, compareAsc);
    CHECK(v == res);

    v = { 1, 2, 3 };
    res = { 3, 2, 1 };
    customSort(v, compareDesc);
    CHECK(v == res);
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

    cout << "comapreAsc" << endl;
    printVector(v);
    customSort(v, compareAsc);
    printVector(v);

    cout << "compareDesc" << endl;
    printVector(v);
    customSort(v, compareDesc);
    printVector(v);
    
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
