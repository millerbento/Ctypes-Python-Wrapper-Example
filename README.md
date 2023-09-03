## A simple example of how to compile a C++ class and make it callable in Python

# Create a C++ file called "foo.cpp"

#include <iostream>

class Foo{
    public:
        void bar(){
            std::cout << "Hello" << std::endl;
        }
};

# Since ctypes can only talk to C functions, you need to provide those declaring them as extern "C"

extern "C" {
    Foo* Foo_new(){ return new Foo(); }
    void Foo_bar(Foo* foo){ foo->bar(); }
}

# Next you have to compile this to a shared library

g++ -c -fPIC foo.cpp -o foo.o
g++ -shared -o libfoo.so foo.o


# And finally you have to write your python wrapper (fooWrapper.py)

from ctypes import cdll
lib = cdll.LoadLibrary('./libfoo.so')

class Foo(object):
    def __init__(self):
        self.obj = lib.Foo_new()

    def bar(self):
        lib.Foo_bar(self.obj)

# Once you have that you can call it like

f = Foo()
f.bar() #and you will see "Hello" on the screen


## Why CTYPES? What about SWIG and BOOST?

The Python standard library includes ctypes, while swig and boost are not part of it. Unlike swig and boost, which depend on extension modules and are thus linked to specific Python minor versions, independent shared objects are not constrained by this limitation. Creating wrappers for swig or boost can be a challenging task, while ctypes does not impose any build requirements.

## Tested it using a M1 Mac, the compilation code can be different if you're using a different system