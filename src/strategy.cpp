#include "strategy.h"

#include <iostream>

Strategy *StrategyFactory::newStrategy()
{
    Strategy *ret = new ConcreteStrategyB();
    return ret;
}

Context::Context(StrategyFactory *strategyFactory)
{
    this->strategy = strategyFactory->newStrategy();
}

Context::~Context()
{
    delete this->strategy;
}

void Context::exec() const
{
    std::cout << "客户端调用" << std::endl;
    // 多态调用
    this->strategy->exec();
}

// 策略实现
void ConcreteStrategyA::exec()
{
    std::cout << "策略实现 A" << std::endl;
}

// 策略实现
void ConcreteStrategyB::exec()
{
    std::cout << "策略实现 B" << std::endl;
}
