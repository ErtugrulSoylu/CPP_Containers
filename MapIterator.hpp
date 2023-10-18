#pragma once

#include "ft_pair.hpp"
namespace ft {
    // BNode
    template <class K, class T>
    struct BNode {
        BNode *left;
        BNode *right;
        BNode *parent;

        ft::pair<K, T> elem;

        BNode(const ft::pair<const K, T> &_elem) : left(NULL), right(NULL), parent(NULL), elem(_elem) {};
        BNode(ft::pair<K, T> &_elem) : left(NULL), right(NULL), parent(NULL), elem(_elem) {};
    };

    template <class K, class T>
    class MapIterator {
        
        public:
        typedef K                                           key_type;
        typedef T                                           mapped_type;
        typedef MapIterator<K, T>                           iterator;
        typedef ft::pair<K, T>                              value_type;
        typedef ft::pair<K, T>&                             reference;
        typedef BNode<K, T>*                                pointer;

        pointer     element_pointer;

        // Constructors and Destructor
        MapIterator() : element_pointer(NULL) {}
        MapIterator(const pointer it) : element_pointer(it) {}
        MapIterator(const iterator &copy) : element_pointer(copy.element_pointer) {}
        ~MapIterator() {}

        private:
        pointer get_next_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->right) {
                next = ptr;
                while (next->parent && next == next->parent->right)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->right;
                while (next->left)
                    next = next->left;
            }
            return (next);
        }

        pointer get_prev_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->left) {
                next = ptr;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->left;
                while (next->right)
                    next = next->right;
            }
            return (next);
        }

        public:
        // Operator Overloads
        // =
        iterator &operator=(const iterator &it) {
            this->element_pointer = it.element_pointer;
            return *this;
        }

        // ++
        iterator &operator++() {
            this->element_pointer = get_next_iterator(this->element_pointer);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // --
        iterator &operator--() {
            this->element_pointer = get_prev_iterator(this->element_pointer);
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        
        // ==
        friend bool operator==(const iterator &it1, const iterator &it) {
            return it1.element_pointer == it.element_pointer;
        }

        // !=
        friend bool operator!=(const iterator &it1, const iterator &it) {
            return it1.element_pointer != it.element_pointer;
        }
        
        // >
        friend bool operator>(const iterator &it1, const iterator &it) {
            return it1.element_pointer > it.element_pointer;
        }

        // <
        friend bool operator<(const iterator &it1, const iterator &it) {
            return it1.element_pointer < it.element_pointer;
        }
        
        // >=
        friend bool operator>=(const iterator &it1, const iterator &it) {
            return it1.element_pointer >= it.element_pointer;
        }
        
        // <=
        friend bool operator<=(const iterator &it1, const iterator &it) {
            return it1.element_pointer <= it.element_pointer;
        }

        // ->
        value_type *operator->() const { 
            return &(this->element_pointer->elem);
        }

        // *
        value_type &operator*() const {
            return this->element_pointer->elem;
        }
    };

    template <class K, class T>
    class ConstMapIterator {
        public:
        typedef K                                           key_type;
        typedef T                                           mapped_type;
        typedef ConstMapIterator<K, T>                      iterator;
        typedef ft::pair<K, T>                              value_type;
        typedef ft::pair<K, T>&                             reference;
        typedef BNode<K, T>*                                pointer;

        pointer     element_pointer;

        // Constructors and Destructor
        ConstMapIterator() : element_pointer(NULL) {}
        ConstMapIterator(const pointer it) : element_pointer(it) {}
        ConstMapIterator(const iterator &copy) : element_pointer(copy.element_pointer) {}
        ConstMapIterator(const MapIterator<K, T> &copy) : element_pointer(copy.element_pointer) {}
        ~ConstMapIterator() {}

        private:
        pointer get_next_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->right) {
                next = ptr;
                while (next->parent && next == next->parent->right)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->right;
                while (next->left)
                    next = next->left;
            }
            return (next);
        }

        pointer get_prev_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->left) {
                next = ptr;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->left;
                while (next->right)
                    next = next->right;
            }
            return (next);
        }

        public:
        // Operator Overloads
        // =
        iterator &operator=(const iterator &it) {
            this->element_pointer = it.element_pointer;
            return *this;
        }

        // ++
        iterator &operator++() {
            this->element_pointer = get_next_iterator(this->element_pointer);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // --
        iterator &operator--() {
            this->element_pointer = get_prev_iterator(this->element_pointer);
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        
        // ==
        friend bool operator==(const iterator &it1, const iterator &it) {
            return it1.element_pointer == it.element_pointer;
        }

        // !=
        friend bool operator!=(const iterator &it1, const iterator &it) {
            return it1.element_pointer != it.element_pointer;
        }
        
        // >
        friend bool operator>(const iterator &it1, const iterator &it) {
            return it1.element_pointer > it.element_pointer;
        }

        // <
        friend bool operator<(const iterator &it1, const iterator &it) {
            return it1.element_pointer < it.element_pointer;
        }
        
        // >=
        friend bool operator>=(const iterator &it1, const iterator &it) {
            return it1.element_pointer >= it.element_pointer;
        }
        
        // <=
        friend bool operator<=(const iterator &it1, const iterator &it) {
            return it1.element_pointer <= it.element_pointer;
        }

        // ->
        const value_type *operator->() const {
            return &(this->element_pointer->elem);
        }

        // *
        const value_type &operator*() const {
            return this->element_pointer->elem;
        }
    };

    template <class K, class T>
    class ReverseMapIterator {
        
        public:
        typedef K                                           key_type;
        typedef T                                           mapped_type;
        typedef ReverseMapIterator<K, T>                    iterator;
        typedef ft::pair<K, T>                              value_type;
        typedef ft::pair<K, T>&                             reference;
        typedef BNode<K, T>*                                pointer;

        pointer     element_pointer;

        // Constructors and Destructor
        ReverseMapIterator() : element_pointer(NULL) {}
        ReverseMapIterator(const pointer it) : element_pointer(it) {}
        ReverseMapIterator(const iterator &copy) : element_pointer(copy.element_pointer) {}
        ReverseMapIterator(const MapIterator<K, T> &copy) : element_pointer(get_next_iterator(copy.element_pointer)) {}
        ~ReverseMapIterator() {}

        private:
        pointer get_prev_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->right) {
                next = ptr;
                while (next->parent && next == next->parent->right)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->right;
                while (next->left)
                    next = next->left;
            }
            return (next);
        }

        pointer get_next_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->left) {
                next = ptr;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->left;
                while (next->right)
                    next = next->right;
            }
            return (next);
        }

        public:
        MapIterator<K, T> base() {
            return MapIterator<K, T>(get_prev_iterator(this->element_pointer));
        }

        // Operator Overloads
        // =
        iterator &operator=(const iterator &it) {
            this->element_pointer = it.element_pointer;
            return *this;
        }

        // ++
        iterator &operator++() {
            this->element_pointer = get_next_iterator(this->element_pointer);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // --
        iterator &operator--() {
            this->element_pointer = get_prev_iterator(this->element_pointer);
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        
        // ==
        friend bool operator==(const iterator &it1, const iterator &it) {
            return it1.element_pointer == it.element_pointer;
        }

        // !=
        friend bool operator!=(const iterator &it1, const iterator &it) {
            return it1.element_pointer != it.element_pointer;
        }
        
        // >
        friend bool operator>(const iterator &it1, const iterator &it) {
            return it1.element_pointer > it.element_pointer;
        }

        // <
        friend bool operator<(const iterator &it1, const iterator &it) {
            return it1.element_pointer < it.element_pointer;
        }
        
        // >=
        friend bool operator>=(const iterator &it1, const iterator &it) {
            return it1.element_pointer >= it.element_pointer;
        }
        
        // <=
        friend bool operator<=(const iterator &it1, const iterator &it) {
            return it1.element_pointer <= it.element_pointer;
        }

        // ->
        value_type *operator->() const { 
            return &(this->element_pointer->elem);
        }

        // *
        value_type &operator*() const {
            return this->element_pointer->elem;
        }
    };

    template <class K, class T>
    class ConstReverseMapIterator {
        
        public:
        typedef K                                           key_type;
        typedef T                                           mapped_type;
        typedef ConstReverseMapIterator<K, T>               iterator;
        typedef ft::pair<K, T>                              value_type;
        typedef ft::pair<K, T>&                             reference;
        typedef BNode<K, T>*                                pointer;

        pointer     element_pointer;

        // Constructors and Destructor
        ConstReverseMapIterator() : element_pointer(NULL) {}
        ConstReverseMapIterator(const pointer it) : element_pointer(it) {}
        ConstReverseMapIterator(const iterator &copy) : element_pointer(copy.element_pointer) {}
        ConstReverseMapIterator(const ReverseMapIterator<K, T> &copy) : element_pointer(copy.element_pointer) {}
        ConstReverseMapIterator(const MapIterator<K, T> &copy) : element_pointer(get_next_iterator(copy.element_pointer)) {}
        ConstReverseMapIterator(const ConstMapIterator<K, T> &copy) : element_pointer(get_next_iterator(copy.element_pointer)) {}
        ~ConstReverseMapIterator() {}

        private:
        pointer get_prev_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->right) {
                next = ptr;
                while (next->parent && next == next->parent->right)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->right;
                while (next->left)
                    next = next->left;
            }
            return (next);
        }

        pointer get_next_iterator(pointer ptr) {
            pointer next;

            if (!ptr)
                return ptr;
            if (!ptr->left) {
                next = ptr;
                while (next->parent && next == next->parent->left)
                    next = next->parent;
                next = next->parent;
            }
            else {
                next = ptr->left;
                while (next->right)
                    next = next->right;
            }
            return (next);
        }
        
        ConstMapIterator<K, T> base() {
            return ConstMapIterator<K, T>(get_next_iterator(this->element_pointer));
        }

        public:
        // Operator Overloads
        // =
        iterator &operator=(const iterator &it) {
            this->element_pointer = it.element_pointer;
            return *this;
        }

        // ++
        iterator &operator++() {
            this->element_pointer = get_next_iterator(this->element_pointer);
            return *this;
        }

        iterator operator++(int) {
            iterator tmp = *this;
            ++(*this);
            return tmp;
        }

        // --
        iterator &operator--() {
            this->element_pointer = get_prev_iterator(this->element_pointer);
            return *this;
        }

        iterator operator--(int) {
            iterator tmp = *this;
            --(*this);
            return tmp;
        }
        
        // ==
        friend bool operator==(const iterator &it1, const iterator &it) {
            return it1.element_pointer == it.element_pointer;
        }

        // !=
        friend bool operator!=(const iterator &it1, const iterator &it) {
            return it1.element_pointer != it.element_pointer;
        }
        
        // >
        friend bool operator>(const iterator &it1, const iterator &it) {
            return it1.element_pointer > it.element_pointer;
        }

        // <
        friend bool operator<(const iterator &it1, const iterator &it) {
            return it1.element_pointer < it.element_pointer;
        }
        
        // >=
        friend bool operator>=(const iterator &it1, const iterator &it) {
            return it1.element_pointer >= it.element_pointer;
        }
        
        // <=
        friend bool operator<=(const iterator &it1, const iterator &it) {
            return it1.element_pointer <= it.element_pointer;
        }

        // ->
        const value_type *operator->() const { 
            return &(this->element_pointer->elem);
        }

        // *
        const value_type &operator*() const {
            return this->element_pointer->elem;
        }
    };
};