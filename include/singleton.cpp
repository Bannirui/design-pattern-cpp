//
// Created by dingrui on 2022/7/4.
//

// 单例是一种创建型设计模式 能够保证一个类只有一个实例 并提供一个访问该实例的全局节点
// 单例拥有与全局变量相同的优缺点 尽管他们非常有用 但却会破坏代码的模块化特性

#include <mutex>
#include <string>
#include <thread>
#include <iostream>

class Singleton
{
private:
    static Singleton *p_instance_;
    static std::mutex mutex_;

protected:
    Singleton(std::string value) : value_(value)
    {

    }

    ~Singleton() = default;

    std::string value_;

public:
    Singleton(Singleton &other) = delete;

    void operator=(const Singleton &) = delete;

    static Singleton *get_instance(const std::string &value)
    {
        std::lock_guard<std::mutex> lock(mutex_);
        if (p_instance_ == nullptr) p_instance_ = new Singleton(value);
        return p_instance_;
    };

    void some_business_logic()
    {}

    std::string value() const
    {
        return this->value_;
    }
};

Singleton *Singleton::p_instance_{nullptr};
std::mutex Singleton::mutex_;

void thread_foo()
{
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton *singleton = Singleton::get_instance("Foo");
    std::cout << singleton->value() << std::endl;
}

void thread_bar()
{
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton *singleton = Singleton::get_instance("Bar");
    std::cout << singleton->value() << std::endl;
}