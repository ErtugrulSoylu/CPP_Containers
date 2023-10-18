#pragma once

#include "vector.hpp"

namespace ft {

    template<class T, class Container = ft::vector<T> >
    class stack {
    public:
        typedef Container                                   container_type;
        typedef typename container_type::value_type         value_type;
        typedef typename container_type::size_type          size_type;
        typedef typename container_type::reference          reference;
        typedef typename container_type::const_reference    const_reference;
        container_type container;
        
        explicit stack (const container_type& ctnr = container_type()) : container(ctnr) {}
        ~stack() {};

        stack &operator=(const stack &other) {
            container = other.container;
            return *this;
        }

        reference top() {
            return container.back(); //access last element
        }

        const_reference top() const {
            return container.back(); //access last element
        }

        bool empty() const {
            return container.empty(); // test whether vector is empty
        }

        size_type size() const {
            return container.size(); // return size
        }

        void push(const value_type& value) {
            container.push_back(value); // add element at the end
        }

        void pop() {
            container.pop_back(); // delete last element
        }

    }; //end of class

    template <class T, class Container>
    bool operator==(const stack<T, Container> &value1, const stack<T, Container> &value2) {
        return value1.container == value2.container;
    }

    template <class T, class Container>
    bool operator!=(const stack<T, Container> &value1, const stack<T, Container> &value2) {
        return value1.container != value2.container;
    }

    template <class T, class Container>
    bool operator<(const stack<T, Container> &value1, const stack<T, Container> &value2) {
        return value1.container < value2.container;
    }

    template <class T, class Container>
    bool operator>(const stack<T, Container> &value1, const stack<T, Container> &value2) {
        return value1.container > value2.container;
    }

    template <class T, class Container>
    bool operator<=(const stack<T, Container> &value1, const stack<T, Container> &value2) {
        return value1.container <= value2.container;
    }

    template <class T, class Container>
    bool operator>=(const stack<T, Container> &value1, const stack<T, Container> &value2) {
        return value1.container >= value2.container;
    }

}