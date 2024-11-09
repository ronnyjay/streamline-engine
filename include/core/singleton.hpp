#pragma once

template <typename T>
class Singleton {
public:
    static T& GetInstance() {
        static T instance;
        return instance;
    }

    virtual void Init() = 0;
    virtual void DeInit() = 0;

    virtual ~Singleton() {}

private:
    Singleton() {} // Private constructor to prevent direct instantiation
    Singleton(const Singleton&) = delete; // Prevent copy construction
    Singleton& operator=(const Singleton&) = delete; // Prevent assignment
};
