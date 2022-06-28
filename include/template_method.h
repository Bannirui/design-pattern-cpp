#include <iostream>

// 基类
class AbstractClass
{
public:
    AbstractClass() = default;
    virtual ~AbstractClass() = default;

    // 开发给客户端使用的api
    // 定义了算法族的流程
    void template_method();

protected:
    // 纯虚函数 留给子类去实现
    virtual void method1() = 0;

private:
    void method2();
};

// 实现类
class ConcreteClass : public AbstractClass
{
public:
    ConcreteClass() = default;
    ~ConcreteClass() = default;

protected:
    // 父类的纯虚函数
    void method1();
};