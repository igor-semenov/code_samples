#include "common.hpp"
#include <exception>

class MayThrowInDestructor {

public:
    MayThrowInDestructor() : exceptions_(std::uncaught_exceptions()) {}
    ~MayThrowInDestructor() noexcept(false) {
        if (std::uncaught_exceptions() > exceptions_) {
            std::cerr << "~MayThrowInDestructor() stack unwinding, not throwing\n";
        } else {
            std::cerr << "~MayThrowInDestructor() normal case, throwing\n";
            throw_int_func();
        }
    }

private:
    const int exceptions_;

};

class ThrowCatchInDestructor {

public:
    ~ThrowCatchInDestructor() noexcept(false) {
        try {
            MayThrowInDestructor may_throw;
        } catch (int i) {
            std::cerr << "Catched int in ~ThrowCatchInDestructor(): " << i << "\n";
        }
    }

private:
    PrintInDestructor member_;

};

int main(int, char**) {

    try {
        ThrowCatchInDestructor stack_unwind;
        std::cerr << "ThrowInDestructor stack unwinding\n";
        throw "BANG!";
    } catch (int i) {
        std::cerr << "Catched int exception: " << i << "\n";
    } catch (const char* s) {
        std::cerr << "Catched const char* exception: " << s << "\n";
    } catch (...) {
        std::cerr << "Catched unknown exception\n";
    }
    
    return 0;

}

