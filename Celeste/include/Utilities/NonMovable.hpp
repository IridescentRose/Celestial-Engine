/**
 * Generic superclass for NonMovable classes
 */
#pragma once

class NonMovable {
public:
    NonMovable(NonMovable &&) = delete;
    NonMovable &operator=(NonMovable &&) = delete;

protected:
    NonMovable () = default;
    ~NonMovable () = default;
};