//
// Created by dingrui on 2022/7/4.
//

// 工厂方法模式
// 当需要在代码中提供高层次的灵活性时 该模式会非常实用
// 工厂方法通过构建方法来识别 它会创建具体类的对象 但以抽象类型或接口的形式返回这些对象

#include <iostream>
#include <string>

// the Product interface declares the options that all concrete products must implement
class Product
{
public:
    virtual ~Product() = default;

    virtual std::string operation() const = 0;
};

// concrete Products provide various implementations of the Product interface
class ConcreteProduct1 : public Product
{
public:
    ~ConcreteProduct1() override = default;

    std::string operation() const override
    {
        return "result of the concrete product1";
    }
};

class ConcreteProduct2 : public Product
{
public:
    ~ConcreteProduct2() override = default;

    std::string operation() const override
    {
        return "result of the concrete product2";
    }
};

// the Creator class declares the factory method that is supposed to return an object of a Product class
// the Creator's subclasses usually provide the implementation of this method
class Creator
{
public:
    virtual ~Creator() = default;

    virtual Product *factory_method() const = 0;

    std::string some_operation() const
    {
        Product *product = this->factory_method();
        std::string ret = "Creator: the same creator's code has just worked with " + product->operation();
        delete product;
        return ret;
    }
};

// concrete Creators override the factory method in order to change the resulting product's type
class ConcreteCreator1 : public Creator
{
public:
    Product *factory_method() const override
    {
        return new ConcreteProduct1;
    };
};

class ConcreteCreator2 : public Creator
{
public:
    Product *factory_method() const override
    {
        return new ConcreteProduct2;
    };
};

// the client code works with an instance of a concrete creator
// albeit through its base interface
// as long as the client keeps working with the creator via the base interface
// u can pass it any creator's subclass
void client_code(const Creator &creator)
{
    std::cout << "client: i'm aware of the creator's class, but it still works" << std::endl
              << creator.factory_method()->operation()
              << std::endl;
}