//
// Created by dingrui on 2022/7/5.
//

// 中介者是一种行为设计模式 让程序组件通过特殊的中介者对象进行间接沟通 达到减少组件之间依赖关系的目的
// 中介者能使得程序更易于修改和扩展 而且能够更方便对独立的组件进行复用 因为它们不再依赖于很多其他的类

#include <string>
#include <iostream>

namespace MEDIATOR
{
    class BaseComponent;

    class Mediator
    {
    public:
        virtual void notify(BaseComponent *sender, std::string event) const = 0;
    };

    class BaseComponent
    {
    protected:
        Mediator *mediator_;
    public:
        BaseComponent(Mediator *mediator = nullptr)
                : mediator_(mediator)
        {}

        void set_mediator(Mediator *mediator)
        {
            this->mediator_ = mediator;
        }
    };

    class Component1 : public BaseComponent
    {
    public:
        void do_a()
        {
            std::cout << "component 1 does a" << std::endl;
            this->mediator_->notify(this, "a");
        }

        void do_b()
        {
            std::cout << "component 1 does b" << std::endl;
            this->mediator_->notify(this, "b");
        }
    };

    class Component2 : public BaseComponent
    {
    public:
        void do_c()
        {
            std::cout << "component 2 does c" << std::endl;
            this->mediator_->notify(this, "c");
        }

        void do_d()
        {
            std::cout << "component 2 does d" << std::endl;
            this->mediator_->notify(this, "d");
        }
    };

    class ConcreteMediator : public Mediator
    {
    private:
        Component1 *component1_;
        Component2 *component2_;

    public:
        ConcreteMediator(Component1 *c1, Component2 *c2)
                : component1_(c1), component2_(c2)
        {
            this->component1_->set_mediator(this);
            this->component2_->set_mediator(this);
        }

        void notify(BaseComponent *sender, std::string event) const override
        {
            if (event == "a")
            {
                std::cout << "mediator reacts on a and triggers following operations" << std::endl;
                this->component2_->do_c();
            }
            if ("d" == event)
            {
                std::cout << "mediator reacts on d and triggers following operations" << std::endl;
                this->component1_->do_b();
                this->component2_->do_d();
            }
        }
    };

    void client_code()
    {
        Component1 *c1 = new Component1;
        Component2 *c2 = new Component2;
        ConcreteMediator *mediator = new ConcreteMediator(c1, c2);
        std::cout << "client triggers operation a" << std::endl;
        c1->do_a();
        std::cout << "client triggers operation d" << std::endl;
        c2->do_d();
        delete c1;
        delete c2;
        delete mediator;
    }
}