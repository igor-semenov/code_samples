#pragma once
#include <iostream>

class PrintInDestructor {

public:
    ~PrintInDestructor() noexcept {
        std::cerr << "~PrintInDestructor() invoked\n";
    }

};

inline void throw_int_func() {
    std::cerr << "throw_int_func() invoked\n";
    throw 1;
}

