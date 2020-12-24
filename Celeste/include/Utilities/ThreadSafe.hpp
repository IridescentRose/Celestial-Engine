/**
 * Templated wrapper for ThreadSafe access to a class or struct.
 * Depends on the SINGLE_THREADED Compiler flag.
 */
#pragma once

#ifndef SINGLE_THREADED
#include <mutex>
#include <thread>
#endif

template <typename T>
/**
 * ThreadSafe wraps all parts of a class or struct with a mutex and lock_guard.
 * @tparam T - Class or Struct
 */
class ThreadSafe final {
    T data;
#ifndef SINGLE_THREADED
    std::mutex mut;
#endif

    class Proxy {
#ifndef SINGLE_THREADED
        std::unique_lock<std::mutex> lock;
#endif
        T& t;
    public:

#ifndef SINGLE_THREADED
        explicit Proxy(std::mutex& mx, T& t) : lock(mx), t(t) { }
#else
        explicit Proxy(T& t) : t(t) {}
#endif

#ifndef SINGLE_THREADED
        Proxy(Proxy&& src) : lock(std::move(src.lock)), t(src.t) { }
#else
        Proxy(Proxy&& src) : t(src.t) { }
#endif

        ~Proxy() { }
        T* operator -> () { return &t; }
    };

public:
    template <typename ...Args>
    explicit ThreadSafe(Args&&... args) : data(std::forward<Args>(args)...) { }

#ifndef SINGLE_THREADED
    Proxy operator -> () { return Proxy(mut, data); }
#else
    Proxy operator -> () { return Proxy(data); }
#endif
    template <typename Func, typename R = typename std::enable_if<!std::is_void<typename std::result_of<Func(T&)>::type>::value>::type>
    auto operator () (const Func& func) {

#ifndef SINGLE_THREADED
        std::lock_guard<std::mutex> lock(mut);
#endif
        return func(data);
    }

    template <typename Func, typename R = typename std::enable_if<std::is_void<typename std::result_of<Func(T&)>::type>::value>::type>
    void operator () (const Func& func) {
        func(*operator -> () . operator -> ());
    }
};