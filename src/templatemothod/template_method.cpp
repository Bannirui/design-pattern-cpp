#include <iostream>

class AbstractClass
{
public:
    AbstractClass() = default;
    virtual ~AbstractClass() {}

    void template_method()
    {
        method1();
        method2();
    }

protected:
    virtual void method1() = 0;

private:
    void method2()
    {
        std::cout << "Super Class::here is method2" << std::endl;
    }
};

class ConcreteClass : public AbstractClass
{
public:
    ConcreteClass() = default;
    ~ConcreteClass() = default;

protected:
    void method1()
    {
        std::cout << "Sub Class::here is method1" << std::endl;
    }
};