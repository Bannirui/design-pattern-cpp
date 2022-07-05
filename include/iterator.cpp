//
// Created by dingrui on 2022/7/5.
//

// 迭代器是一种行为模式 让你能在不暴露复杂数据结构内部细节的情况下遍历其中所有的元素
// 在迭代器的帮助下 客户端可以用一个迭代器接口以相似的方式遍历不同集合中的元素

#include <iostream>
#include <string>
#include <vector>

namespace ITERATOR
{
    template<typename T, typename U>
    class Iterator
    {
    public:
        typedef typename std::vector<T>::iterator iter_type;

        Iterator(U *p_data, bool reverse = false)
                : m_p_data_(p_data)
        {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void first()
        {
            m_it_ = m_p_data_->m_data_.begin();
        }

        void next()
        {
            m_it_++;
        }

        bool is_done()
        {
            return (m_it_ == m_p_data_->m_data_.end());
        }

        iter_type cur()
        {
            return m_it_;
        }

    private:
        U *m_p_data_;
        iter_type m_it_;
    };

    template<class T>
    class Container
    {
        friend class Iterator<T, Container>;

    public:
        void add(T a)
        {
            m_data_.push_back(a);
        }

        Iterator<T, Container> *create_iterator()
        {
            return new Iterator<T, Container>(this);
        }

    private:
        std::vector<T> m_data_;
    };

    class Data
    {
    public:
        Data(int a = 0)
                : m_data_(a)
        {}

        void set_data(int a)
        { m_data_ = a; }

        int data()
        {
            return m_data_;
        }

    private:
        int m_data_;
    };

    void client_code()
    {
        std::cout << "iterator with int" << std::endl;
        Container<int> cont1;
        for (int i = 0; i < 10; i++) cont1.add(i);
        Iterator<int, Container<int>> *it1 = cont1.create_iterator();
        for (it1->first(); !it1->is_done(); it1->next()) std::cout << *it1->cur() << std::endl;

        Container<Data> cont2;
        Data a(100), b(200), c(300);
        cont2.add(a);
        cont2.add(b);
        cont2.add(c);

        std::cout << "iterator with custom class" << std::endl;
        Iterator<Data, Container<Data>> *it2 = cont2.create_iterator();
        for (it2->first(); !it2->is_done(); it2->next()) std::cout << it2->cur()->data() << std::endl;

        delete it1;
        delete it2;
    }
}