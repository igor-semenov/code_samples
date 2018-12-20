#include "common.hpp"

class ThrowInDestructor {

public:
    ~ThrowInDestructor() noexcept(false) {
        std::cerr << "~ThrowInDestructor() invoked\n"; 
        throw_int_func();
    }

private:
    PrintInDestructor member_;

};

int main(int, char**) {

    try {
        ThrowInDestructor bad;
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

