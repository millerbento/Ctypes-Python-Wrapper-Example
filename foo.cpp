#include <iostream>

class Foo{
    public:
        void bar(){
            std::cout << "It worked! You just called a C++ function using Python" << std::endl;
        }
};

extern "C" {
    Foo* Foo_new(){ return new Foo(); }
    void Foo_bar(Foo* foo){ foo->bar(); }
}