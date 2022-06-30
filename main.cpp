#include <iostream>
#include "template_method.h"
#include "strategy.h"
#include "observer.h"

int main()
{
    // 模板方法
    AbstractClass *con = new ConcreteClass();
    con->template_method();

    // 策略模式
    Context *ctx = new Context(new StrategyFactory());
    ctx->exec();

    // 观察者模式
    Subject *subject = new Subject();
    Observer *observer1 = new Observer(*subject);
    Observer *observer2 = new Observer(*subject);
    Observer *observer3 = new Observer(*subject);
    Observer *observer4;
    Observer *observer5;
    subject->CreateMessage("Helle World");
    observer3->RemoveMeFromTheList();
    subject->CreateMessage("The weather is hot");
    observer4 = new Observer(*subject);
    observer2->RemoveMeFromTheList();
    observer5 = new Observer(*subject);
    subject->CreateMessage("My new car is great");
    observer5->RemoveMeFromTheList();
    observer4->RemoveMeFromTheList();
    observer1->RemoveMeFromTheList();

    delete observer5;
    delete observer4;
    delete observer3;
    delete observer2;
    delete observer1;
    delete subject;

    return 0;
}