/* Find second largest number in an array */

#include <iostream>
//#include <vector>
// vector is safer/better than int arr[] (downside: a bit more memory)
#include <limits> // for smallest int; "climits" would be INT_MIN

#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"

using namespace std;

int second_largest(int a[], size_t n)
{
    if (n == 0) { return 0; }
    // also, if only one element, there is no second largest
    
    // we must sort it for our alg to work
    std::sort(a, a + n);

    int max = a[0];
    int second = a[0]; 
    // numeric_limits<int>::min() does not really work for 2 el

    for (size_t i = 0; i < n; i++ ) {
        if (a[i] > max) {
            second = max;
            max = a[i];
        }
    }

    return second;
}

TEST_CASE("testing second_largest()") {
    int a1[] = { 1, 2, 3 };
    CHECK(second_largest(a1, 3) == 2);
    int a2[] = { 1, 1 };
    CHECK(second_largest(a2, 2) == 1);
    int a3[] = { 6, 5, 4 };
    CHECK(second_largest(a3, 3) == 5);
}

void print_array(int a[], size_t n)
{
    cout << "Array: ";
    for (size_t i = 0; i < n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;
}

#ifdef DOCTEST_CONFIG_DISABLE
int main()
{
    int *arr = NULL;
    size_t n = 3;

    std::cout << "num elements: ";
    std::cin >> n;

    arr = (int*) malloc(n * sizeof(int));
    if (arr == NULL) {
        std::cerr << "Error in malloc\n";
        return 1;
    }

    for (size_t i = 0; i < n; i++) {
        int val = 0;
        std::cin >> val;
        arr[i] = val;
    }

    print_array(arr, n);

    cout << second_largest(arr, n) << " \n";

    free(arr);

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

