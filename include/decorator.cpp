//
// Created by dingrui on 2022/6/30.
//

# pragma once

#include <iostream>
#include <string>

// 接口
class Component
{
public:
    virtual ~Component() = default;;

    virtual std::string op() const = 0;
};

class ConcreteComponent : public Component
{
public:
    ConcreteComponent() = default;

    ~ConcreteComponent() override = default;

    std::string op() const override
    {
        return "ConcreteComponent";
    };
};

// 中间层 组合一个多态接口的实现
class Decorator : public Component
{
protected:
    Component *cmp;

public:
    explicit Decorator(Component *component) : cmp(component)
    {

    };

    ~Decorator() override = default;

    std::string op() const override
    {
        return this->cmp->op();
    };
};

class ConcreteDecoratorA : public Decorator
{
public:
    explicit ConcreteDecoratorA(Component *component) : Decorator(component)
    {

    };

    ~ConcreteDecoratorA() override = default;

    std::string op() const override
    {
        return "ConcreteDecoratorA(" + Decorator::op() + ")";
    };
};

class ConcreteDecoratorB : public Decorator
{
public:
    explicit ConcreteDecoratorB(Component *component) : Decorator(component)
    {

    };

    ~ConcreteDecoratorB() override = default;

    std::string op() const override
    {
        return "ConcreteDecoratorB(" + Decorator::op() + ")";
    };
};


// // 客户端api
inline static void decoratorClient(Component *component)
{
    std::cout << "Result=" << component->op() << std::endl;
}