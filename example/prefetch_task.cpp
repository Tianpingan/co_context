#include "co_context/prefetch_task.hpp"
#include <co_context/all.hpp>
#include <iostream>
#include <vector>
using namespace co_context;
task<> f() {
    auto vec = std::vector<int>(10);
    vec[0] = 100;
    auto it = vec.begin();
    auto y = co_await prefetch(*it);
    std::cout << "y = " << y << std::endl;
}

int main() {
    io_context ctx;
    ctx.co_spawn(f());
    ctx.start();
    ctx.join();
    return 0;
}

// Output:
// g() is running...
// h() is running...
// g() got error: -125 Operation canceled
// h() got error: -125 Operation canceled
