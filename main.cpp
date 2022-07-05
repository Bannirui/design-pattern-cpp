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
#include "composite.cpp" // 组合
#include "facade.cpp" // 外观
#include "share.cpp" // 享元
#include "proxy.cpp" // 代理

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

    // 组合
    COMPOSITE::Component *leaf = new COMPOSITE::Leaf;
    std::cout << "client: i've got a simple component" << std::endl;
    COMPOSITE::client_code_1(leaf);

    COMPOSITE::Component *tree = new COMPOSITE::Composite;
    COMPOSITE::Component *branch1 = new COMPOSITE::Composite;
    COMPOSITE::Component *leaf_1 = new COMPOSITE::Leaf;
    COMPOSITE::Component *leaf_2 = new COMPOSITE::Leaf;
    COMPOSITE::Component *leaf_3 = new COMPOSITE::Leaf;
    branch1->add(leaf_1);
    branch1->add(leaf_2);
    COMPOSITE::Component *branch2 = new COMPOSITE::Composite;
    branch2->add(leaf_3);
    tree->add(branch1);
    tree->add(branch2);
    std::cout << "client: now i've got a composite tree" << std::endl;
    COMPOSITE::client_code_1(tree);

    std::cout << "client: i don't need to check the components classes even when managing the tree" << std::endl;
    COMPOSITE::client_code_2(tree, leaf);

    delete leaf;
    delete tree;
    delete branch1;
    delete branch2;
    delete leaf_1;
    delete leaf_2;
    delete leaf_3;

    // 外观
    FACADE::Subsystem1 *subsystem1 = new FACADE::Subsystem1;
    FACADE::Subsystem2 *subsystem2 = new FACADE::Subsystem2;
    FACADE::Facade *facade = new FACADE::Facade(subsystem1, subsystem2);
    FACADE::client_code(facade);
    delete facade;

    // 享元
    SHARE::FlyweightFactory *factory = new SHARE::FlyweightFactory({{"Chevrolet",     "Camaro2018", "pink"},
                                                                    {"Mercedes Benz", "C300",       "black"},
                                                                    {"Mercedes Benz", "C500",       "red"},
                                                                    {"BMW",           "M5",         "red"},
                                                                    {"BMW",           "x6",         "white"}});
    factory->list_flyweights();
    SHARE::add_car_to_police_database(*factory, "CL234", "James Doe", "BMW", "M5", "red");
    SHARE::add_car_to_police_database(*factory, "CL235", "James Doe", "BMW", "x1", "red");
    factory->list_flyweights();
    delete factory;

    // 代理
    std::cout << "client: executing the client code with a real subject" << std::endl;
    PROXY::RealSubject *real_subject = new PROXY::RealSubject;
    PROXY::client_code(*real_subject);

    std::cout << "client: executing the same client code with a proxy" << std::endl;
    PROXY::Proxy *proxy = new PROXY::Proxy(real_subject);
    PROXY::client_code(*proxy);
    delete real_subject;
    delete proxy;

    return 0;
}