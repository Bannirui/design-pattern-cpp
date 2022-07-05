//
// Created by dingrui on 2022/7/5.
//

// 访问者是一种行为设计模式 允许你在不修改已有代码的情况下向已有类层次结构中增加新的行为

#include <string>
#include <iostream>
#include <array>

namespace VISITOR
{
    class ConcreteComponentA;

    class ConcreteComponentB;

    class Visitor
    {
    public:
        virtual void visit_concrete_component_a(const ConcreteComponentA *element) const = 0;

        virtual void visit_concrete_component_b(const ConcreteComponentB *element) const = 0;
    };

    class Component
    {
    public:
        virtual ~Component() = default;

        virtual void accept(Visitor *visitor) const = 0;
    };

    class ConcreteComponentA : public Component
    {
    public:
        void accept(Visitor *visitor) const override
        {
            visitor->visit_concrete_component_a(this);
        }

        std::string exclusive_method_of_component_a() const
        {
            return "A";
        }
    };

    class ConcreteComponentB : public Component
    {
    public:
        void accept(Visitor *visitor) const override
        {
            visitor->visit_concrete_component_b(this);
        }

        std::string exclusive_method_of_component_b() const
        {
            return "B";
        }
    };

    class ConcreteVisitor1 : public Visitor
    {
    public:
        void visit_concrete_component_a(const ConcreteComponentA *element) const override
        {
            std::cout << element->exclusive_method_of_component_a() << " + ConcreteVisitor1" << std::endl;
        }

        void visit_concrete_component_b(const ConcreteComponentB *element) const override
        {
            std::cout << element->exclusive_method_of_component_b() << " + ConcreteVisitor1" << std::endl;
        }
    };

    class ConcreteVisitor2 : public Visitor
    {
    public:
        void visit_concrete_component_a(const ConcreteComponentA *element) const override
        {
            std::cout << element->exclusive_method_of_component_a() << " + ConcreteVisitor2" << std::endl;
        }

        void visit_concrete_component_b(const ConcreteComponentB *element) const override
        {
            std::cout << element->exclusive_method_of_component_b() << " + ConcreteVisitor2" << std::endl;
        }
    };

    void client_code(std::array<const Component *, 2> components, Visitor *visitor)
    {
        for (const Component *comp: components) comp->accept(visitor);
    }
}