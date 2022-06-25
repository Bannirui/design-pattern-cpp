#include <iostream>

#include "./src/templatemothod/template_method.cpp"

int main(int, char **)
{
    AbstractClass *obj = new ConcreteClass();
    obj->template_method();

    return 0;
}
