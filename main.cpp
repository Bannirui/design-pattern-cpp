#include <iostream>
#include "template_method.h"
#include "strategy.h"
#include "observer.h"
#include "decorator.cpp"
#include "abstract_factory.cpp"
#include "builder.cpp"

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

    // 装饰模式
    Component *simple = new ConcreteComponent();
    std::cout << "Client: i've got a simple component" << std::endl;
    decoratorClient(simple);
    Component *decorator1 = new ConcreteDecoratorA(simple);
    Component *decorator2 = new ConcreteDecoratorB(simple);
    std::cout << "Client: i've got a decorated component" << std::endl;
    decoratorClient(decorator1);
    std::cout << "Client: i've got a decorated component" << std::endl;
    decoratorClient(decorator2);
    delete simple;
    delete decorator1;
    delete decorator2;

    // 抽象工厂
    std::cout << "Client: Testing client code with the first factory type" << std::endl;
    ConcreteFactory1 *f1 = new ConcreteFactory1();
    clientCode(*f1);
    delete f1;
    std::cout << "Client: Testing client same client code with the second factory type" << std::endl;
    ConcreteFactory2 *f2 = new ConcreteFactory2();
    clientCode(*f2);
    delete f2;

    // 生成器模式
    Director *director = new Director;
    client_code(*director);
    delete director;

    return 0;
}