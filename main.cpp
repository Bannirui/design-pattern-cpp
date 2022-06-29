#include <iostream>
#include "template_method.h"
#include "strategy.h"

int main()
{
    // 模板方法
    AbstractClass *con = new ConcreteClass();
    con->template_method();

    // 策略模式
    Context *ctx = new Context(new StrategyFactory());
    ctx->exec();
    return 0;
}