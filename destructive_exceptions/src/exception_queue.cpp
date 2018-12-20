#include "common.hpp"
#include <exception>
#include <functional>
#include <iostream>
#include <stack>

using exceptions_queue = std::stack<std::exception_ptr>;

// Get exceptions queue for current thread
exceptions_queue& get_queue() {
    thread_local exceptions_queue queue_;
    return queue_;
}

// Invoke functor and save exception in queue
void safe_invoke(std::function<void()> f) noexcept {
    try {
        f();
    } catch (...) {
        get_queue().push(std::current_exception());
    }
}

class ThrowInDestructor {

public:
    ~ThrowInDestructor() noexcept {
        std::cerr << "~ThrowInDestructor() invoked\n";
        safe_invoke([]() {
            throw_int_func();
        });
    }

private:
    PrintInDestructor member_;

};

int main(int, char**) {

    safe_invoke([]() {
        ThrowInDestructor bad;
        throw "BANG!";
    });

    auto& q = get_queue();
    while (!q.empty()) {
        try {
            std::exception_ptr ex = q.top();
            q.pop();
            if (ex != nullptr) {
                std::rethrow_exception(ex);
            }
        } catch (int i) {
            std::cerr << "Catched int exception: " << i << "\n";
        } catch (const char* s) {
            std::cerr << "Catched const char* exception: " << s << "\n";
        } catch (...) {
            std::cerr << "Catched unknown exception\n";
        }
    }

    return 0;

}

