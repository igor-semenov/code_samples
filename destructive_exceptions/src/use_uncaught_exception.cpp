#include "common.hpp"
#include <exception>

class ThrowInDestructor {

public:
    ~ThrowInDestructor() noexcept(false) {
        if (std::uncaught_exception()) {
            std::cerr << "~ThrowInDestructor() stack unwinding, not throwing\n";
        } else {
            std::cerr << "~ThrowInDestructor() normal case, throwing\n";
            throw_int_func();
        }
    }

private:
    PrintInDestructor member_;

};

int main(int, char**) {

    try {
        ThrowInDestructor normal;
        std::cerr << "ThrowInDestructor normal destruction\n";
    } catch (int i) {
        std::cerr << "Catched int exception: " << i << "\n";
    }

    try {
        ThrowInDestructor stack_unwind;
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

