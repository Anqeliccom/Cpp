#ifndef SCOPED_POINTER_HPP
#define SCOPED_POINTER_HPP

template <typename T>
class ScopedPointerDeepCopy {
    T* pointer;

public:
    explicit ScopedPointerDeepCopy(T* raw) : pointer(raw) {}

    ScopedPointerDeepCopy(const ScopedPointerDeepCopy& other) {
        pointer = new T(*other.pointer);
    }

    ScopedPointerDeepCopy& operator=(const ScopedPointerDeepCopy& other) {
        if (this != &other) {
            delete pointer;
            pointer = new T(*other.pointer);
        }
        return *this;
    }

    ScopedPointerDeepCopy(ScopedPointerDeepCopy&& other) = delete;

    ScopedPointerDeepCopy& operator=(ScopedPointerDeepCopy&& other) = delete;

    T& operator*() { return *pointer; }
    const T& operator*() const { return *pointer; }

    T* operator->() { return pointer; }
    const T* operator->() const { return pointer; }

    ~ScopedPointerDeepCopy() {
        delete pointer;
    }
};

template <typename T>
class ScopedPointerMove {
    T* pointer;

public:
    explicit ScopedPointerMove(T* raw) : pointer(raw) {}

    ScopedPointerMove(const ScopedPointerMove& other) = delete;
    ScopedPointerMove& operator=(const ScopedPointerMove& other) = delete;

    ScopedPointerMove(ScopedPointerMove&& other) noexcept : pointer(other.pointer) {
        other.pointer = nullptr;
    }

    ScopedPointerMove& operator=(ScopedPointerMove&& other) noexcept {
        if (this != &other) {
            delete pointer;
            pointer = other.pointer;
            other.pointer = nullptr;
        }
        return *this;
    }

    T& operator*() { return *pointer; }
    const T& operator*() const { return *pointer; }

    T* operator->() { return pointer; }
    const T* operator->() const { return pointer; }

    ~ScopedPointerMove() {
        delete pointer;
    }
};

#endif // SCOPED_POINTER_HPP
