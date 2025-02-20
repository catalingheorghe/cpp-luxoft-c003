#include <iostream>

using namespace std;

class Person {
protected:
    string name;
    int age;
public:
    Person(string& name, int age) : name{name}, age{age} {
        cout << "Person ctor" << endl;
    }
    //Person() { cout << "Person () ctor" << endl; }
};

class Employee : virtual public Person {
private:
    string job;
public:
    Employee(string& name, int age, string& job) : Person(name, age), job(job) {
        cout << "Employee ctor" << endl;
    }
};

class Student : virtual public Person {
private:
       string degree;
public:
    Student(string& name, int age, string& degree) : Person(name, age), degree(degree) {
        cout << "Student ctor" << endl;
    }
};

class WorkingStudent : public Employee, public Student {
public:
    WorkingStudent(string& name, int age, string& job, string& degree)
        : Person(name, age), Employee(name, age, job), Student(name, age, degree) {
            cout << "Working student ctor" << endl;
        }
};

int main() {
    string name = "JD";
    int age = 22;
    string job = "bussboy";
    string degree = "history";

    WorkingStudent ws = WorkingStudent(name, age, job, degree);
}