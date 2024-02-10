#pragma once
#include "co_context/detail/thread_meta.hpp"
#include "co_context/detail/worker_meta.hpp"
#include <coroutine>
#include <mmintrin.h>
#include <xmmintrin.h>
namespace co_context::detail {
template <typename T>
struct prefetch_task_awaiter {
    T& m_value;
    prefetch_task_awaiter(T& value) : m_value(value) {} 
    constexpr bool await_ready() noexcept { return false; }

    auto await_suspend(std::coroutine_handle<> current) noexcept {
        // std::addressof 用来获取对象或者函数参数的实际地址。
        _mm_prefetch((std::addressof(m_value)), _MM_HINT_NTA);
        auto &worker = *detail::this_thread.worker;
        worker.co_spawn_unsafe(current);
    }

    T& await_resume() const noexcept {
        return m_value;
    }
};
}