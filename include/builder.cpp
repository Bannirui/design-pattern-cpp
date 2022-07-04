//
// Created by dingrui on 2022/7/3.
//

// 生成器是一种创建型设计模式 分步创建复杂对象
// 与其他创建型模式不同 生成器不要求产品拥有通用接口 使得相同的创建过程生成不同的产品成为可能
// 当需要创建一个可能有许多配置选项的对象时 该模式会特别有用
// 生成器模式可以通过类别来识别 它拥有一个构建方法和多个配置结果对象的方法 生成器方法通常支持方法链
// someBuilder->setValueA(1)->setValueB(2)->create()

#include <vector>
#include <string>
#include <iostream>

class Product1
{
public:
    std::vector<std::string> parts_;

    void list_parts() const
    {
        std::cout << "product parts" << std::endl;
        for (size_t i = 0; i < parts_.size(); i++)
        {
            if (parts_[i] == parts_.back())
                std::cout << parts_[i];
            else
                std::cout << parts_[i] << ", ";
        }
        std::cout << std::endl;
    }
};

class Builder
{
public:
    virtual ~Builder() = default;

    virtual void product_part_A() const = 0;

    virtual void product_part_B() const = 0;

    virtual void product_part_C() const = 0;
};

class ConcreteBuilder1 : public Builder
{
private:
    Product1 *product;

public:
    ConcreteBuilder1()
    {
        this->Reset();
    }

    ~ConcreteBuilder1()
    {
        delete this->product;
    }

    void Reset()
    {
        this->product = new Product1();
    }

    void product_part_A() const override
    {
        this->product->parts_.push_back("partA1");
    }

    void product_part_B() const override
    {
        this->product->parts_.push_back("partB1");
    }

    void product_part_C() const override
    {
        this->product->parts_.push_back("partC1");
    }

    Product1 *get_product()
    {
        Product1 *ret = this->product;
        this->Reset();
        return ret;
    }
};

class Director
{
private:
    Builder *builder;

public:
    void set_builder(Builder *builder)
    {
        this->builder = builder;
    }

    void build_minimal_viable_product()
    {
        this->builder->product_part_A();
    }

    void build_full_featured_product()
    {
        this->builder->product_part_A();
        this->builder->product_part_B();
        this->builder->product_part_C();
    }
};

void client_code(Director &director)
{
    ConcreteBuilder1 *builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "standard basic product" << std::endl;
    director.build_minimal_viable_product();

    Product1 *p = builder->get_product();
    p->list_parts();
    delete p;

    std::cout << "standard full feature product" << std::endl;
    director.build_full_featured_product();

    p = builder->get_product();
    p->list_parts();
    delete p;

    std::cout << "custom product" << std::endl;
    builder->product_part_A();
    builder->product_part_C();
    p = builder->get_product();
    p->list_parts();
    delete p;
}