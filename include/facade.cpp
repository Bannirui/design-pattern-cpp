//
// Created by dingrui on 2022/7/5.
//

// 外观是一种结构型设计模式 能为复杂系统、程序库或框架提供一个简单的接口
// 尽管外观模式降低了程序的整体复杂度 但它同时也有助于将不需要的依赖移动到同一个位置

// 使用cpp开发的程序中会经常使用外观模式 它在与复杂程序库和API协作时特别有用
// 外观可以通过使用简单接口 但将绝大部分工作委派给其他类来识别 通常情况下 外观管理所使用的对象的完整声明周期

#include <iostream>
#include <string>

namespace FACADE
{
    class Subsystem1
    {
    public:
        std::string op1() const
        {
            return "subsystem1: ready";
        }

        std::string opN() const
        {
            return "subsystem1: go";
        }
    };

    class Subsystem2
    {
    public:
        std::string op1() const
        {
            return "subsystem2: get ready";
        }

        std::string opZ() const
        {
            return "subsystem2: fire";
        }
    };

    class Facade
    {
    protected:
        Subsystem1 *subsystem1_;
        Subsystem2 *subsystem2_;

    public:
        Facade(Subsystem1 *subsystem1 = nullptr, Subsystem2 *subsystem2 = nullptr)
        {
            this->subsystem1_ = subsystem1 ?: new Subsystem1;
            this->subsystem2_ = subsystem2 ?: new Subsystem2;
        }

        ~Facade()
        {
            delete this->subsystem1_;
            delete this->subsystem2_;
        }

        std::string op()
        {
            std::string ret = "facade init subsystems\n";
            ret += this->subsystem1_->op1();
            ret += this->subsystem2_->op1();
            ret += "facade orders subsystems to perform the action\n";
            ret += this->subsystem1_->opN();
            ret += this->subsystem2_->opZ();
            return ret;
        }
    };

    void client_code(Facade *facade)
    {
        std::cout << facade->op() << std::endl;
    }
}