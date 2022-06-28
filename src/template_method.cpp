#include "template_method.h"

void AbstractClass::template_method()
{
    method1();
    method2();
}

void AbstractClass::method2()
{
    std::cout << "Super Class::here is method2" << std::endl;
}

void ConcreteClass::method1()
{
    std::cout << "Sub Class::here is method1" << std::endl;
}