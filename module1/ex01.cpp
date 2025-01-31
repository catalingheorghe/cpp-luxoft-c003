/* Get a string as input. Check if it is a palindrome.
 * extra: ignore cases, spaces, punctuation
 */

#include <iostream>
#include <string>
#include <cctype>

bool is_palindrome(const std::string& s)
{
    // NOTE pass string by reference (valid for any object)

    std::string clean_s = "";
    // NOTE this will be a small struct on the stack and main stuff on heap
    // NOTE string, same as for vector: memory will be released when out of scope
    // automatically, no need to do anything
    // NOTE no need to initialized to empty string, also

    // NOTE use size_t instead of int for iterator
    for (size_t i = 0; i < s.length(); i++) {
        if (std::isalnum(s[i])) {
            clean_s += std::tolower(s[i]);
        }
    }
    // even better, this would be a separate function

    //std::cout << "input  : " << s << "\n";
    //std::cout << "cleaned: " << clean_s << "\n";
            
    for (size_t i = 0, j = (clean_s.length() -1); i < j; i++, j--) {
        //std::cout << clean_s[i] << " " << clean_s[j] << "\n";
        if (clean_s[i] != clean_s[j]) {
            return false;
        }
    }

    // NOTE could also use a 'for each' loop (for (char ch : s))
    
    return true;

    /* alternatives
     * - if you want to optimize, you can do some fancy logic on the indexes
     * - could use std::reverse to reverse a container and check against it
     */
}

int main()
{
    std::string s;

    std::cout << "input string:\n";
    getline(std::cin, s);
    // NOTE only "cin >> s" would stop at the first space

    if (is_palindrome(s)) {
        std::cout << "yes";
    } else {
        std::cout << "no";
    }
    std::cout << "\n";

    return 0;
}

