//
// Created by dingrui on 2022/7/2.
//

// 抽象工厂是一种创建型设计模式 它能创建一系列相关的对象 而无需指定其具体类
// 抽象工厂定义了用于创建不同产品的接口 但实际的创建工作留给了具体工厂类 每个工厂类型都能对应一个特定的产品变体
// 在创建产品时 客户端代码调用的是工厂对象的构建方法 而不是直接调用构造函数(new操作符) 由于一个工厂对应一种产品变体 因此它创建的所有产品都可相互兼容
// 客户端代码紧通过其抽象接口与工厂和产品进行交互 该接口允许同一客户端代码与不同产品进行交互 只需创建一个具体工厂类并将其代码传递给客户端代码即可

#include <iostream>
#include <string>

class AbstractProductA
{
public:
    virtual ~AbstractProductA() = default;

    virtual std::string UsefulFunctionA() const = 0;
};

class ConcreteProductA1 : public AbstractProductA
{
public:
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A1";
    }
};

class ConcreteProductA2 : public AbstractProductA
{
    std::string UsefulFunctionA() const override
    {
        return "The result of the product A2";
    }
};

class AbstractProductB
{
public:
    virtual ~AbstractProductB() = default;

    virtual std::string UsefulFunctionB() const = 0;

    virtual std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const = 0;
};

class ConcreteProductB1 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B1";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
    {
        const std::string ret = collaborator.UsefulFunctionA();
        return "The result of the B1 collaborating with ( " + ret + " )";
    }
};

class ConcreteProductB2 : public AbstractProductB
{
public:
    std::string UsefulFunctionB() const override
    {
        return "The result of the product B2";
    }

    std::string AnotherUsefulFunctionB(const AbstractProductA &collaborator) const override
    {
        const std::string ret = collaborator.UsefulFunctionA();
        return "The result of the B2 collaborating with ( " + ret + " )";
    }
};

class AbstractFactory
{
public:
    virtual AbstractProductA *createProductA() const = 0;

    virtual AbstractProductB *createProductB() const = 0;
};

class ConcreteFactory1 : public AbstractFactory
{
public:
    AbstractProductA *createProductA() const override
    {
        return new ConcreteProductA1();
    }

    AbstractProductB *createProductB() const override
    {
        return new ConcreteProductB1();
    }
};

class ConcreteFactory2 : public AbstractFactory
{
public:
    AbstractProductA *createProductA() const override
    {
        return new ConcreteProductA2();
    }

    AbstractProductB *createProductB() const override
    {
        return new ConcreteProductB2();
    }
};

void clientCode(const AbstractFactory &factory)
{
    const AbstractProductA *productA = factory.createProductA();
    const AbstractProductB *productB = factory.createProductB();
    std::cout << productB->UsefulFunctionB() << std::endl;
    std::cout << productB->AnotherUsefulFunctionB(*productA) << std::endl;
    delete productA;
    delete productB;
}