/* Get a string as input. Compress the repetitions.
 * aaabb -> a3b2
 */

#include <iostream>
#include <string>
#include <cctype>

#define DOCTEST_CONFIG_IMPLEMENT
#include "../doctest.h"

std::string compress_string(const std::string& s)
{
    size_t reps = 1, pos = 1;
    std::string compressed = "";

    for (pos = 1; pos < s.length(); pos++) {
        //std::cout << pos << " " << s[pos] << " " << s[pos + 1] << std::endl;
        if (s[pos] == s[pos - 1]) {
            // if you would look ahead, you go over the string length
            // NOTE but it seems the program would not fail, strangely (still works)
            reps++;
        } else {
            //std::cout << s[pos] << reps;
            compressed += s[pos - 1];
            compressed += std::to_string(reps);
            reps = 1;
        }
    }
    // last element
    //std::cout << s[pos] << reps;
    compressed += s[pos - 1];
    compressed += std::to_string(reps);

    return compressed;
}
/* or with "std::stringstream" var you can do "var << something",
 * including int, including "string.back()" to get previous element,
 * then "return stringstream.str()" for the string
 */

TEST_CASE("testing compress_string()") {
    CHECK(compress_string("abc") == "a1b1c1");
    CHECK(compress_string("aaabbc") == "a3b2c1");
}

#ifdef DOCTEST_CONFIG_DISABLE
int main()
{
    std::string s;

    std::cout << "input string:\n";
    getline(std::cin, s);
    // NOTE only "cin >> s" would stop at the first space

    std::cout << compress_string(s);
    std::cout << "\ndone\n";

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
