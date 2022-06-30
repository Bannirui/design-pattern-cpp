#pragma once

#include <string>
#include <list>

// 抽象接口 观察者
class IObserver
{
public:
    virtual ~IObserver() = default;;

    virtual void Update(const std::string &message_from_subject) = 0;
};

// 抽象接口
// 管理观察者
// 通知观察者
class ISubject
{
public:
    virtual ~ISubject() = default;;

    virtual void Attach(IObserver *observer) = 0;

    virtual void Detach(IObserver *observer) = 0;

    virtual void Notify() = 0;
};

// 主题实现
class Subject : public ISubject
{
public:
    Subject() = default;

    ~Subject() override;

    void Attach(IObserver *observer) override;

    void Detach(IObserver *observer) override;

    void Notify() override;

    void CreateMessage(std::string message = "Empty");

    void HowManyObserver();

    void SomeBussinessLogic();

private:
    std::list<IObserver *> list_observer_;
    std::string message_;
};

// 观察者实现
class Observer : public IObserver
{
public:
    explicit Observer(Subject &subject);

    ~Observer() override;

    void Update(const std::string &message_from_subject) override;

    void RemoveMeFromTheList();

private:
    void PrintInfo();

private:
    std::string message_from_subject_;
    Subject &subject_;
    static int static_number_;
    int number_;
};
