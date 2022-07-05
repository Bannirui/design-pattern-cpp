//
// Created by dingrui on 2022/7/5.
//

// 状态是一种行为设计模式 让你能在一个对象的内部状态变化时改变其行为
// 该模式将与状态相关的行为抽取到独立的状态类中 让原对象将工作委派给这些类的实例 而不是自行进行处理

#include <iostream>
#include <typeinfo>

namespace STATE
{
    class Context;

    class State
    {
    protected:
        Context *context_;
    public:
        virtual ~State() = default;

        void set_context(Context *context)
        {
            this->context_ = context;
        }

        virtual void handle1() = 0;

        virtual void handle2() = 0;
    };

    class Context
    {
    private:
        State *state_;
    public:
        Context(State *state) : state_(nullptr)
        {
            this->transition_to(state);
        }

        ~Context()
        {
            delete this->state_;
        }

        void transition_to(State *state)
        {
            std::cout << "Context: transition to " << typeid(*state).name() << std::endl;
            if (this->state_ != nullptr) delete this->state_;
            this->state_ = state;
            this->state_->set_context(this);
        }

        void request1()
        {
            this->state_->handle1();
        }

        void request2()
        {
            this->state_->handle2();
        }
    };

    class ConcreteStateA : public State
    {
    public:
        void handle1() override;

        void handle2() override
        {
            std::cout << "ConcreteStateA handles request2" << std::endl;
        }
    };

    class ConcreteStateB : public State
    {
    public:
        void handle1() override
        {
            std::cout << "ConcreteStateB handles request1" << std::endl;
        }

        void handle2() override
        {
            std::cout << "ConcreteStateB handles request1" << std::endl;
            std::cout << "ConcreteStateB wants to change the state of the context" << std::endl;
            this->context_->transition_to(new ConcreteStateA);
        }
    };

    void ConcreteStateA::handle1()
    {
        std::cout << "ConcreteStateA handles request1" << std::endl;
        std::cout << "ConcreteStateA want to change the state of the context" << std::endl;
        this->context_->transition_to(new ConcreteStateB);
    }

    void client_code()
    {
        Context *context = new Context(new ConcreteStateA);
        context->request1();
        context->request2();
        delete context;
    }
}