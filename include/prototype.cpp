//
// Created by dingrui on 2022/7/4.
//

// 原型是一种创建型设计模式 能够复制对象 甚至是复杂对象 而又无需使代码依赖它们所属的类
// 所有的原型类都必须有一个通用的接口 使得即使在对象所属的具体类未知的情况下也能复制对象
// 原型对象可以生成自身的完整副本 因为相同的对象可以相互访问对方的私有成员变量

// 原型可以简单地通过识别clone或copy方法来识别

#include <iostream>
#include <string>
#include <unordered_map>

enum Type
{
    PROTOTYPE1 = 0,
    PROTOTYPE2
};

class Prototype
{
protected:
    std::string prototype_name_;
    float prototype_field_;

public:
    Prototype() = default;

    Prototype(std::string prototype_name)
            : prototype_name_(prototype_name)
    {

    }

    virtual ~Prototype() = default;

    virtual Prototype *clone() const = 0;

    virtual void method(float prototype_field)
    {
        this->prototype_field_ = prototype_field;
        std::cout << "call method from " << this->prototype_name_ << " with field: " << this->prototype_field_
                  << std::endl;
    }
};

class ConcretePrototype1 : public Prototype
{
private:
    float concrete_prototype_field_;

public:
    ConcretePrototype1(std::string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field_(concrete_prototype_field)
    {}

    Prototype *clone() const override
    {
        return new ConcretePrototype1(*this);
    }
};

class ConcretePrototype2 : public Prototype
{
private:
    float concrete_prototype_field_;

public:
    ConcretePrototype2(std::string prototype_name, float concrete_prototype_field)
            : Prototype(prototype_name), concrete_prototype_field_(concrete_prototype_field)
    {}

    Prototype *clone() const override
    {
        return new ConcretePrototype2(*this);
    }
};

class PrototypeFactory
{
private:
    std::unordered_map<Type, Prototype *, std::hash<int>> prototypes_;

public:
    PrototypeFactory()
    {
        this->prototypes_[Type::PROTOTYPE1] = new ConcretePrototype1("PROTOTYPE_1", 50.f);
        this->prototypes_[Type::PROTOTYPE2] = new ConcretePrototype1("PROTOTYPE_2", 60.f);
    }

    ~PrototypeFactory()
    {
        delete this->prototypes_[Type::PROTOTYPE1];
        delete this->prototypes_[Type::PROTOTYPE2];
    }

    Prototype *create_prototype(Type type)
    {
        return this->prototypes_[type]->clone();
    }
};

void client(PrototypeFactory &prototype_factory)
{
    std::cout << "let's create a prototype 1" << std::endl;
    Prototype *prototype1 = prototype_factory.create_prototype(Type::PROTOTYPE1);
    prototype1->method(90.0f);
    delete prototype1;

    std::cout << "let's create a prototype 2" << std::endl;
    Prototype *prototype2 = prototype_factory.create_prototype(Type::PROTOTYPE2);
    prototype2->method(80.0f);
    delete prototype2;
}