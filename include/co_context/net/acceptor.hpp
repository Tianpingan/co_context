#pragma once
#include <co_context/net/socket.hpp>

#include <memory>

namespace co_context {

class inet_address;

class acceptor {
  public:
    explicit acceptor(const inet_address &listen_addr);

    ~acceptor() = default;
    acceptor(acceptor &&) = default;
    acceptor &operator=(acceptor &&) = default;

    [[CO_CONTEXT_AWAIT_HINT]]
    auto accept(sockaddr *addr, socklen_t *addrlen, int flags = 0) noexcept {
        return lazy::accept(listen_socket.fd(), addr, addrlen, flags);
    }

    [[nodiscard]]
    int listen_fd() const noexcept {
        return listen_socket.fd();
    }

    // socket acceptSocketOrDie();

  private:
    socket listen_socket;
};

inline acceptor::acceptor(const inet_address &listen_addr)
    : listen_socket(socket::create_tcp(listen_addr.family())) {
    listen_socket.set_reuse_addr(true).bind(listen_addr).listen();
}

} // namespace co_context
