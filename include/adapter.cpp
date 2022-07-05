//
// Created by dingrui on 2022/7/5.
//

// 适配器是一种结构型设计模式 它能使不兼容的对象能够互相合作
// 适配器可担任两个对象之间的封装器 它会接收对于一个对象的调用 并将其转换为另一个对象可识别的格式和接口
// 适配器模式在cpp代码中很常见 基于一些遗留代码的系统常常使用该模式
// 在这种情况下 适配器让遗留代码和现代的类得以相互合作
// 适配器可以通过不同的抽象或接口类实例为参数的构造函数来识别 当适配器的任何方法别调用时 它会将参数转换为合适的格式 然后将调用定向到其封装对象中的一个或多个方法

#include <iostream>
#include <string>

class Target
{
public:
    virtual ~Target() = default;

    virtual std::string request() const
    {
        return "target: the default target's behavior";
    };
};

class Adaptee
{
public:
    std::string specific_request() const
    {
        return "special behavior of the adaptee";
    }
};

class Adapter : public Target
{
private:
    Adaptee *adaptee_;
public:
    Adapter(Adaptee *adaptee) : adaptee_(adaptee)
    {}

    std::string request() const override
    {
        std::string specific = this->adaptee_->specific_request();
        return "Adapter: " + specific;
    }
};

void client_code(const Target *target)
{
    std::cout << target->request() << std::endl;
}