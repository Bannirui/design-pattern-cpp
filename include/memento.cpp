//
// Created by dingrui on 2022/7/5.
//

// 备忘录是一种行为设计模式 允许生成对象状态的快照并在以后将其还原
// 备忘录不会影响它所处理的对象的内部结构 也不会影响快照中保存的数据

#include <string>
#include <iostream>
#include <vector>

namespace MEMENTO
{
    class Memento
    {
    public:
        virtual std::string get_name() const = 0;

        virtual std::string date() const = 0;

        virtual std::string state() const = 0;
    };

    class ConcreteMemento : public Memento
    {
    private:
        std::string state_;
        std::string date_;

    public:
        ConcreteMemento(std::string state)
                : state_(state)
        {
            std::time_t now = std::time(0);
            this->date_ = std::ctime(&now);
        }

        std::string state() const override
        {
            return this->state_;
        }

        std::string get_name() const override
        {
            return this->date_ + " / (" + this->state_.substr(0, 9) + "...)";
        }

        std::string date() const override
        {
            return this->date_;
        }
    };

    class Originator
    {
    private:
        std::string state_;

        std::string generate_random_string(int length = 10)
        {
            const char alphanum[] = "012334"
                                    "sdf"
                                    "abd";
            int string_length = sizeof(alphanum) - 1;
            std::string random_string;
            for (int i = 0; i < length; i++) random_string += alphanum[std::rand() % string_length];
            return random_string;
        }

    public:
        Originator(std::string state) : state_(state)
        {
            std::cout << "originator: my init state is: " << this->state_ << std::endl;
        }

        void do_sth()
        {
            std::cout << "originator: i'm doing sth import" << std::endl;
            this->state_ = this->generate_random_string(30);
            std::cout << "originator: and my state has changed to: " << this->state_ << std::endl;
        }

        Memento *save()
        {
            return new ConcreteMemento(this->state_);
        }

        void restore(Memento *memento)
        {
            this->state_ = memento->state();
            std::cout << "originator: my state has changed to: " << this->state_ << std::endl;
        }
    };

    class Caretaker
    {
    private:
        std::vector<Memento *> mementors_;

        Originator *originator_;

    public:
        Caretaker(Originator *originator) : originator_(originator)
        {
        }

        void backup()
        {
            std::cout << "cartaker: saving originator's state..." << std::endl;
            this->mementors_.push_back(this->originator_->save());
        }

        void undo()
        {
            if (!this->mementors_.size()) return;
            Memento *memento = this->mementors_.back();
            this->mementors_.pop_back();
            std::cout << "cartaker: restoring state to: " << memento->get_name() << std::endl;
            try
            {
                this->originator_->restore(memento);
            } catch (...)
            { this->undo(); }
        }

        void show_history() const
        {
            std::cout << "cartaker: here's the list of mementors" << std::endl;
            for (Memento *memento: this->mementors_) std::cout << memento->get_name() << std::endl;
        }
    };

    void client_code()
    {
        Originator *originator = new Originator("super-duper-super-puper-super");
        Caretaker *caretaker = new Caretaker(originator);
        caretaker->backup();
        originator->do_sth();
        caretaker->backup();
        originator->do_sth();
        caretaker->backup();
        originator->do_sth();
        caretaker->show_history();
        std::cout << "client: let's roll back" << std::endl;
        caretaker->undo();
        std::cout << "client: once again" << std::endl;
        caretaker->undo();

        delete originator;
        delete caretaker;
    }
}