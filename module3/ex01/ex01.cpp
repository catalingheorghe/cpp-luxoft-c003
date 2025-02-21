/* Matrix class with operator overload */

#include <iostream>
#include <vector>
#include <stdexcept>

using namespace std;

class Matrix1D {
private:
    vector<int> value;
public:
    Matrix1D(initializer_list<int> vals) : value(vals) { }
    Matrix1D(vector<int> vals) : value(vals) { }
    // should pass by const reference here
    
    void print() const {
        for (int v : value) { cout << v << " "; }
        cout << endl;
    }

    Matrix1D operator+(Matrix1D m) {
        // better to pass as constant reference
        vector<int> result_v{};
        // more efficient to initialize to expected size to not realloc internally

        if (value.size() != m.value.size()) {
            throw invalid_argument("non-matching sizes");
        }
        
        for (size_t i = 0; i < value.size(); i++) {
            result_v.push_back(value[i] + m.value[i]);
        }
        
        return Matrix1D(result_v);
    }

    
    friend ostream& operator<<(ostream& os, const Matrix1D& m);
};

ostream& operator<<(ostream& os, const Matrix1D& m) {
    for (int v : m.value) { os << v << " "; }
    return os;
}

int main()
{
    Matrix1D m1 = Matrix1D({2, 3});
    Matrix1D m2 = Matrix1D({4, 5});
    Matrix1D m3 = Matrix1D({4, 5, 6});
    Matrix1D res{};
    
    res = m1 + m2;
    res.print();
    cout << res << endl;

    // exception
    res = m1 + m3;
    res.print();
}
