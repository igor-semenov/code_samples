#include "common.hpp"

class ThrowCatchInDestructor {

public:
    ~ThrowCatchInDestructor() noexcept(false) {
        try {
            throw_int_func();
        } catch (int i) {
            std::cerr << "Catched int in ~ThrowCatchInDestructor(): " << i << "\n";
        }
    }

private:
    PrintInDestructor member_;

};

int main(int, char**) {

    try {
        ThrowCatchInDestructor good;
        std::cerr << "ThrowCatchInDestructor instance created\n";
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

