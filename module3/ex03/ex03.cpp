/* Complex number class and the rule of five */

#include <iostream>

using namespace std;

class ComplexNum {
private:
    double *real, *imag;
public:
    ComplexNum() {
        real = new double(0.0);
        imag = new double(0.0);
    }
    ComplexNum(double r, double i) {
        real = new double(r);
        imag = new double(i);
    }
    ComplexNum(const ComplexNum& c) {
        real = new double(*c.real);
        imag = new double(*c.imag);
    }

    ~ComplexNum() { cout << "dtor" << this << endl; delete real; delete imag; }

    ComplexNum& operator=(const ComplexNum& c) {
        if (this != &c) {
            delete real; delete imag;
            real = new double(*c.real);
            imag = new double(*c.imag);
        }
        return *this;
    }

    // rule of three done => assignments and initializations will do deep copies

    ComplexNum(ComplexNum&& c) {
        real = c.real;
        imag = c.imag;
        c.real = new double(0.0); // setting these to nullptr would mean having checks everywhere
        c.imag = new double(0.0);
    }

    ComplexNum& operator=(ComplexNum&& c) {
        delete real; delete imag;
        real = c.real;
        imag = c.imag;
        c.real = new double(0.0);
        c.imag = new double(0.0);
        return *this;
    }

    // rule of five done

    void set_real(double real) { *this->real = real; }

    ComplexNum operator+(ComplexNum c) {
        return ComplexNum(*this->real + *c.real, *this->imag + *c.imag);
    }

    void print() const { cout << "(" << *real << ", " << *imag << "i) " << this << endl; }
    friend ostream& operator<<(ostream& os, const ComplexNum& c);
};

ostream& operator<<(ostream& os, const ComplexNum& c) {
    cout << "(" << *c.real << ", " << *c.imag << "i) " << &c;
    return os;
}

int main() {
    ComplexNum c1{1.0, 2.0};
    ComplexNum c2;

    c1.print();
    c2.print();

    ComplexNum c3;
    c3 = c1; // operator= does a deep copy here
    cout << "c3: " << c3 << endl;
    c1.set_real(3.0);
    cout << "c3: " << c3 << endl;
    cout << "c1: " << c1 << endl;

    cout << endl;

    ComplexNum c4 = c3; // copy constructor does a deep copy here
    cout << "c4: " << c4 << endl;
    c1.set_real(6.0);
    cout << "c4: " << c4 << endl;
    cout << "c3: " << c3 << endl;

    cout << endl;

    c4 = c1 + c3; // 2 dtors are called here on temporary created objects
    cout << "c4: " << c4 << endl;

    cout << endl;

    ComplexNum tmp = move(c4);
    // if move ctor not defined, tmp will be new and c4 will still exist
    // if defined, tmp will be "new" but with internal pointers to former c4; c4 will be re-newed
    cout << "tmp: " << tmp << endl;
    cout << "c4: " << c4 << endl;
    tmp.set_real(10.0);
    cout << "tmp: " << tmp << endl;
    cout << "c4: " << c4 << endl;

    c4 = move(c1);
    // if move assignment operator not defined, will act like a normal assignment (?)
    // if defined, c4 pointers will point to former c1's; c1 will be re-newed
    cout << "c4: " << c4 << endl;
    cout << "c1: " << c1 << endl;
    c4.set_real(20.0);
    cout << "c4: " << c4 << endl;
    cout << "c1: " << c1 << endl;
}