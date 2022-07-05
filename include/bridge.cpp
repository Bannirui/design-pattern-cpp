//
// Created by dingrui on 2022/7/5.
//

// 桥接是一种结构型设计模式 可将业务逻辑或一个大类拆分为不同的层次结构 从而能独立地进行开发
// 层次结构中的第一层(通常成为抽象部分) 将包含对第二层(实现部分)对象的引用 抽象部分能将一些对自己的调用委托给实现部分的对象 所有的实现部分都有一个通用接口 因此它们能在抽象部分内部相互替换

// 桥接模式在处理跨平台应用 支持多种类型的数据库服务与多个特定种类的API供应商协作时会特别有用
// 桥接可以通过一些控制实体及其所依赖的多个不同平台之间的明确区别来进行识别

#include <iostream>
#include <string>

class Implementation
{
public:
    virtual ~Implementation() = default;

    virtual std::string op() const = 0;
};

class ConcreteImplementationA : public Implementation
{
public:
    std::string op() const override
    {
        return "ConcreteImplementationA";
    }
};

class ConcreteImplementationB : public Implementation
{
public:
    std::string op() const override
    {
        return "ConcreteImplementationB";
    }
};

class Abstraction
{
protected:
    Implementation *implementation_;
public:
    Abstraction(Implementation *implementation) : implementation_(implementation)
    {}

    virtual ~Abstraction() = default;

    virtual std::string operation() const
    {
        return "Abstraction: base operation with: " + this->implementation_->op();
    }
};

class ExtendAbstraction : public Abstraction
{
public:
    ExtendAbstraction(Implementation *implementation) : Abstraction(implementation)
    {}

    std::string operation() const override
    {
        return "ExtendAbstraction: extend operator with: " + this->implementation_->op();
    }
};

void client_code(const Abstraction &abstraction)
{
    std::cout << abstraction.operation() << std::endl;
}