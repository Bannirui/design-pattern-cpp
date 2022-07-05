//
// Created by dingrui on 2022/7/5.
//

// 组合是一种结构型设计模式 可以使用它将对象组合成树状结构 并且能够像使用独立对象一样使用它们
// 对于绝大多数需要生成树状结构的问题来说 组合都是非常受欢迎的解决方案 组合主要的功能是在整个树状结构上递归调用方法并对结果进行汇总
// 组合模式在cpp代码中很常见 常用于表示与图形打交道的用户界面组件或代码层次结构
// 组合可以通过将同一抽象或接口类型的实例放入树状结构的行为方法来轻松识别

#include <algorithm>
#include <iostream>
#include <list>
#include <string>

namespace COMPOSITE
{
    class Component
    {
    protected:
        Component *parent_;
    public:
        virtual ~Component() = default;

        void set_parent(Component *parent)
        {
            this->parent_ = parent;
        }

        Component *get_parent() const
        {
            return this->parent_;
        }

        virtual void add(Component *component)
        {}

        virtual void remove(Component *component)
        {}

        virtual bool is_composite() const
        {
            return false;
        }

        virtual std::string op() const = 0;
    };

    class Leaf : public Component
    {
    public:
        std::string op() const override
        {
            return "leaf";
        }
    };

    class Composite : public Component
    {
    protected:
        std::list<Component *> children_;
    public:
        void add(Component *component) override
        {
            this->children_.push_back(component);
            component->set_parent(this);
        }

        void remove(Component *component) override
        {
            this->children_.remove(component);
            component->set_parent(nullptr);
        }

        bool is_composite() const override
        {
            return true;
        }

        std::string op() const override
        {
            std::string ret;
            for (const Component *c: this->children_)
            {
                if (c == this->children_.back()) ret += c->op();
                else ret += c->op() + "+";
            }
            return "Branch(" + ret + ")";
        }
    };

    void client_code_1(Component *component)
    {
        std::cout << "result: " << component->op() << std::endl;
    }

    void client_code_2(Component *component1, Component *component2)
    {
        if (component1->is_composite()) component1->add(component2);
        std::cout << "result: " << component1->op() << std::endl;
    }
}