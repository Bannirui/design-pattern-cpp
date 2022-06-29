#pragma once

// 策略基类
class Strategy
{
public:
    // 基类的析构函数声明为虚函数
    virtual ~Strategy() {}

    // 抽象函数 子类实现
    virtual void exec() = 0;
};

class StrategyFactory
{
public:
    StrategyFactory() = default;
    ~StrategyFactory() = default;
    Strategy *newStrategy();
};

// 开放给客户端使用策略模式
class Context
{
public:
    Context(StrategyFactory *strategyFactory);
    ~Context();

    void exec() const;

private:
    // 多态变量 使用指针或者引用
    Strategy *strategy;
};

// 策略实现
class ConcreteStrategyA : public Strategy
{
public:
    virtual void exec();
};

// 策略实现
class ConcreteStrategyB : public Strategy
{
public:
    virtual void exec();
};
