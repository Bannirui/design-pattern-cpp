#include <iostream>
#include "template_method.h"

int main()
{
    AbstractClass *con = new ConcreteClass();
    con->template_method();
    std::cout << "hello world" << std::endl;
    return 0;
}