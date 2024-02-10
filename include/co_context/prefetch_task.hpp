#pragma once
#include "co_context/detail/prefetch_task_awaiter.hpp"
#include <co_context/detail/attributes.hpp>
namespace co_context {
inline namespace lazy {
    template <typename T>
    [[CO_CONTEXT_AWAIT_HINT]]
    inline detail::prefetch_task_awaiter<T> prefetch(T& value) noexcept {
        return detail::prefetch_task_awaiter<T>(value);
    }
};
}