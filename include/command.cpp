//
// Created by dingrui on 2022/7/5.
//

// 命令是一种行为设计模式 它可以将请求或简单操作转换为一个对象
// 此类转换让你能够延迟进行或远程执行请求 还可以将其放入队列中

#include <iostream>
#include <string>

namespace COMMAND
{
    class Command
    {
    public:
        virtual ~Command() = default;

        virtual void execute() const = 0;
    };

    class SimpleCommand : public Command
    {
    private:
        std::string pay_load_;

    public:
        explicit SimpleCommand(std::string pay_load) : pay_load_(pay_load)
        {}

        void execute() const override
        {
            std::cout << "SimpleCommand: i can do simple things (" << this->pay_load_ << std::endl;
        }
    };

    class Receiver
    {
    public:
        void do_sth(const std::string &a)
        {
            std::cout << "Receiver: work on " << a << std::endl;
        }

        void do_sth_else(const std::string &b)
        {
            std::cout << "Receiver: also work on " << b << std::endl;
        }
    };

    class ComplexCommand : public Command
    {
    private:
        Receiver *receiver_;
        std::string a_;
        std::string b_;

    public:
        ComplexCommand(Receiver *receiver, std::string a, std::string b)
                : receiver_(receiver), a_(a), b_(b)
        {}

        void execute() const override
        {
            std::cout << "ComplexCommand: complex stuff should be done by a receiver object" << std::endl;
            this->receiver_->do_sth(this->a_);
            this->receiver_->do_sth_else(this->b_);
        }
    };

    class Invoker
    {
    private:
        Command *on_start_;
        Command *on_finish_;

    public:
        ~Invoker()
        {
            delete this->on_start_;
            delete this->on_finish_;
        }

        void set_on_start(Command *command)
        {
            this->on_start_ = command;
        }

        void set_on_finish(Command *command)
        {
            this->on_finish_ = command;
        }

        void do_sth_important()
        {
            std::cout << "Invoker: does anybody want sth done before i begin" << std::endl;
            if (this->on_start_) this->on_start_->execute();
            std::cout << "Invoker: doing sth really important" << std::endl;
            std::cout << "Invoker: does anybody want sth done after i finish" << std::endl;
            if (this->on_finish_) this->on_finish_->execute();
        }
    };
}