//
// Created by dingrui on 2022/7/5.
//

// 责任链是一种行为设计模式 允许将请求沿着处理者链进行发送 直至其中一个处理者对其进行处理
// 该模式允许多个对象对请求进行处理 而无需让发送者类与具体接收者相耦合 链可在运行时遵循标准处理者接口的任意处理者动态生成

#include <string>
#include <vector>
#include <iostream>

namespace CHAIN
{
    class Handler
    {
    public:
        virtual Handler *set_next(Handler *handler) = 0;

        virtual std::string op(std::string request) = 0;
    };

    class AbstractHandler : public Handler
    {
    private:
        Handler *next_handler_;

    public:
        AbstractHandler() : next_handler_(nullptr)
        {}

        Handler *set_next(Handler *handler) override
        {
            this->next_handler_ = handler;
            return handler;
        }

        std::string op(std::string request) override
        {
            if (this->next_handler_) return this->next_handler_->op(request);
            return {};
        }
    };

    class MonkeyHandler : public AbstractHandler
    {
    public:
        std::string op(std::string request) override
        {
            if (request == "banana") return "monkey: i'll eat the " + request;
            else return AbstractHandler::op(request);
        }
    };

    class DogHandler : public AbstractHandler
    {
    public:
        std::string op(std::string request) override
        {
            if (request == "meat") return "dog: i'll eat the " + request;
            else return AbstractHandler::op(request);
        }
    };

    class SquirrelHandler : public AbstractHandler
    {
    public:
        std::string op(std::string request) override
        {
            if (request == "nut") return "squirrel: i'll eat the " + request;
            else return AbstractHandler::op(request);
        }
    };

    void client_code(Handler &handler)
    {
        std::vector<std::string> food = {"nut", "banana", "coffee"};
        for (const std::string &f: food)
        {
            std::cout << "client: who wants a " << f << std::endl;
            const std::string ret = handler.op(f);
            if (!ret.empty()) std::cout << ret << std::endl;
            else std::cout << f << " was left untouched" << std::endl;
        }
    }
}