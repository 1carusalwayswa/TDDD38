#include <iostream>

class TestClass {
private:
    int val;
public:
    TestClass(int val) : val(val) {}

    void getValFromOther(TestClass& other) {
        val = other.val;
    }

    void printVal() {
        std::cout << val << '\n';
    }
};

class TestClassDerived : public TestClass {
public:
    TestClassDerived(int val) : TestClass(val) {}
};

int main() {
    TestClassDerived a(5);
    TestClass b(10);
    a.getValFromOther(b);

    a.printVal();
    return 0;
}

/*
    Class access control is base on the class, not the object.
    In the above example, the getValFromOther function is a member of the TestClass class, 
    so it can access the private member of the TestClass class.

    If we want to deal with a object, like some motify operation, and need to motify the private member of the object,
    we can make a new class public inherit from the class, and pass the object to the new class.
    In this way, the new class can access the private member of the object.
    It is decorators pattern.
*/