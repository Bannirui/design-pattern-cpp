//
// Created by dingrui on 2022/7/5.
//

// 享元是一种结构型设计模式 它允许你在消耗少量内存的情况下支持大量对象
// 模式通过共享多个对象的部分状态来实现上述功能 享元会将不同对象的相同数据进行缓存以节省内存

// 享元模式只有一个目的 将内存消耗最小化
// 享元可以通过构建方法来识别 它会返回缓存对象而不是创建新的对象

#include <string>
#include <iostream>
#include <unordered_map>

namespace SHARE
{
    struct SharedState
    {
        std::string brand_;
        std::string model_;
        std::string color_;

        SharedState(const std::string &brand, const std::string &model, const std::string &color)
                : brand_(brand), model_(model), color_(color)
        {
        }

        friend std::ostream &operator<<(std::ostream &os, const SharedState &ss)
        {
            return os << "[ " << ss.brand_ << ", " << ss.model_ << ", " << ss.color_ << " ]";
        }
    };

    struct UniqueState
    {
        std::string owner_;
        std::string plates_;

        UniqueState(const std::string &owner, const std::string &plates)
                : owner_(owner), plates_(plates)
        {}

        friend std::ostream &operator<<(std::ostream &os, const UniqueState &us)
        {
            return os << "[ " << us.owner_ << ", " << us.plates_ << " ]";
        }
    };

    class Flyweight
    {
    private:
        SharedState *shared_state_;

    public:
        Flyweight(const SharedState *shared_state)
                : shared_state_(new SharedState(*shared_state))
        {}

        Flyweight(const Flyweight &other)
                : shared_state_(new SharedState(*other.shared_state_))
        {}

        ~Flyweight()
        {
            delete shared_state_;
        }

        SharedState *shared_state() const
        {
            return shared_state_;
        }

        void op(const UniqueState &unique_state) const
        {
            std::cout << "Flyweight: display shared (" << *shared_state_ << " ) and unique (" << unique_state
                      << " ) state" << std::endl;
        }
    };

    class FlyweightFactory
    {
    private:
        std::unordered_map<std::string, Flyweight> flyweights_;

        std::string get_key(const SharedState &ss) const
        {
            return ss.brand_ + "_" + ss.model_ + "_" + ss.color_;
        }

    public:
        FlyweightFactory(std::initializer_list<SharedState> share_states)
        {
            for (const SharedState &ss: share_states)
                this->flyweights_.insert(std::make_pair<std::string, Flyweight>(this->get_key(ss), Flyweight(&ss)));
        }

        Flyweight get_flyweight(const SharedState &shared_state)
        {
            std::string key = this->get_key(shared_state);
            if (this->flyweights_.find(key) == this->flyweights_.end())
            {
                std::cout << "FlyweightFactory: can't find a flyweight, create a new one" << std::endl;
                this->flyweights_.insert(std::make_pair(key, Flyweight(&shared_state)));
            } else
            {
                std::cout << "FlyweightFactory: reusing existing flyweight" << std::endl;
            }
            return this->flyweights_.at(key);
        }

        void list_flyweights() const
        {
            size_t count = this->flyweights_.size();
            std::cout << "FlyweightFactory: i have " << count << " flyweights" << std::endl;
            for (std::pair<std::string, Flyweight> pair: this->flyweights_) std::cout << pair.first << std::endl;
        }
    };

    void add_car_to_police_database(
            FlyweightFactory &ff,
            const std::string &plates,
            const std::string &owner,
            const std::string &brand,
            const std::string &model,
            const std::string &color
    )
    {
        std::cout << "Client: adding a car to database" << std::endl;
        const Flyweight &flyweight = ff.get_flyweight({brand, model, color});
        flyweight.op({owner, plates});
    }
}