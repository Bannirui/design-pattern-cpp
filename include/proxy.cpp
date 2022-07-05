//
// Created by dingrui on 2022/7/5.
//

// 代理是一种结构型设计模式 能提供真实服务对象的替代品给客户端使用 代理接收客户端的请求并进行一些处理(访问控制和缓存等) 然后再将请求传递给服务对象
// 代理对象拥有和服务对象相同的接口 这使得当其被传递给客户端时可与真实对象互换

#include <iostream>

namespace PROXY
{
    class Subject
    {
    public:
        virtual void request() const = 0;
    };

    class RealSubject : public Subject
    {
    public:
        void request() const override
        {
            std::cout << "RealSubject: handling request" << std::endl;
        }
    };

    class Proxy : public Subject
    {
    private:
        RealSubject *real_subject_;

        bool check_access() const
        {
            std::cout << "Proxy: checking access prior to firing a real request" << std::endl;
            return true;
        }

        void log_access() const
        {
            std::cout << "Proxy: logging the time of request" << std::endl;
        }

    public:
        Proxy(RealSubject *real_subject)
                : real_subject_(new RealSubject(*real_subject))
        {}

        ~Proxy()
        {
            delete real_subject_;
        }

        void request() const override
        {
            if (this->check_access())
            {
                this->real_subject_->request();
                this->log_access();
            }
        }
    };

    void client_code(const Subject &subject)
    {
        subject.request();
    }
}