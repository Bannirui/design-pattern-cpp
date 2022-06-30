#include "observer.h"

#include <iostream>
#include <utility>

// Subject
Subject::~Subject()
{
    std::cout << "Goodbye, i was the subject" << std::endl;
}

void Subject::Attach(IObserver *observer)
{
    this->list_observer_.push_back(observer);
}

void Subject::Detach(IObserver *observer)
{
    this->list_observer_.remove(observer);
}

void Subject::Notify()
{
    std::list<IObserver *>::iterator it = this->list_observer_.begin();
    this->HowManyObserver();
    while (it != this->list_observer_.end())
    {
        (*it)->Update(this->message_);
        ++it;
    }
}

void Subject::CreateMessage(std::string message)
{
    this->message_ = std::move(message);
    this->Notify();
}

void Subject::HowManyObserver()
{
    std::cout << "There are " << this->list_observer_.size() << " observers in the list" << std::endl;
}

void Subject::SomeBussinessLogic()
{
    this->message_ = "change message";
    this->Notify();
    std::cout << "I'm about to doing sth import" << std::endl;
}

// Observer
int Observer::static_number_ = 0;

Observer::Observer(Subject &subject) : subject_(subject)
{
    this->subject_.Attach(this);
    std::cout << "Hi, i'm the Observer " << ++Observer::static_number_ << std::endl;
    this->number_ = Observer::static_number_;
}

Observer::~Observer()
{
    std::cout << "Goodbye, i was the Observer " << this->number_ << std::endl;
}

void Observer::Update(const std::string &message_from_subject)
{
    this->message_from_subject_ = message_from_subject;
    this->PrintInfo();
}

void Observer::RemoveMeFromTheList()
{
    this->subject_.Detach(this);
    std::cout << "Observer " << this->number_ << " removed from the list" << std::endl;
}

void Observer::PrintInfo()
{
    std::cout << "Observer " << this->number_ << ": a new message is available->" << this->message_from_subject_
              << std::endl;
}