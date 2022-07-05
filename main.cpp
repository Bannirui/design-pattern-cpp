#include <iostream>
#include "template_method.h" // 模板方法
#include "strategy.h" // 策略
#include "observer.h" // 观察者
#include "decorator.cpp" // 装饰器
#include "abstract_factory.cpp" // 抽象工厂
#include "builder.cpp" // 生成器
#include "factory_method.cpp" // 工厂方法
#include "prototype.cpp" // 原型
#include "singleton.cpp" // 单例
#include "adapter.cpp" // 适配器
#include "bridge.cpp" // 桥接

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

    // 工厂模式
    std::cout << "App: Launched with the ConcreteCreator1" << std::endl;
    Creator *creator1 = new ConcreteCreator1;
    client_code(*creator1);
    delete creator1;
    std::cout << "App: Launched with the ConcreteCreator2" << std::endl;
    Creator *creator2 = new ConcreteCreator2;
    client_code(*creator2);
    delete creator2;

    // 原型
    PrototypeFactory *prototype_factory = new PrototypeFactory;
    client(*prototype_factory);
    delete prototype_factory;

    // 单例
    std::cout << "singleton" << std::endl;
    std::thread t1(thread_foo);
    std::thread t2(thread_bar);
    t1.join();
    t2.join();

    // 适配器
    std::cout << "client: i can work just fine with the target objects" << std::endl;
    Target *target = new Target;
    client_code(target);
    delete target;
    Adaptee *adaptee = new Adaptee;
    Adapter *adapter = new Adapter(adaptee);
    client_code(adapter);
    delete adaptee;
    delete adapter;

    // 桥接
    Implementation *implementationA = new ConcreteImplementationA;
    Abstraction *abstraction = new Abstraction(implementationA);
    client_code(*abstraction);
    delete implementationA;
    delete abstraction;

    Implementation *implementationB = new ConcreteImplementationB;
    abstraction = new ExtendAbstraction(implementationB);
    client_code(*abstraction);
    delete implementationB;
    delete abstraction;

    return 0;
}