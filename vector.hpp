#pragma once

#include <iostream>
#include <limits>
#include "Iterator.hpp"

namespace ft {

    template <class T, class Alloc = std::allocator<T> >
    class vector {
    
    // Typedefs
    public:
        typedef T														        value_type;
        typedef	Alloc													        allocator_type;
        typedef value_type&												        reference;
        typedef const value_type&										        const_reference;
        typedef value_type*												        pointer;
        typedef const value_type*										        const_pointer;
        typedef size_t                                                          size_type;
        typedef InputIterator<value_type, pointer, reference>		            iterator;
        typedef InputIterator<value_type, const_pointer, const_reference>	    const_iterator;
        typedef RevInputIterator<value_type, pointer, reference>				reverse_iterator;
        typedef RevInputIterator<value_type, const_pointer, const_reference>	const_reverse_iterator;
    
    // Variables
    private:
        pointer			arr;
        allocator_type  alloc;
        size_type		length;
        size_type		cap;
        double			multiplier;
    
    public:
        // Constructors
        explicit vector (const allocator_type& alloc = allocator_type());
        explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type());
        vector (iterator first, iterator last, const allocator_type& alloc = allocator_type());
        vector (const vector& x);

        // Destructors
        ~vector();

        // Operator Overloads
        vector& operator=(const vector& x);

        // Iterators
        iterator begin() { return iterator(this->arr); }
        const_iterator begin() const { return const_iterator(this->arr); }
        iterator end() { return (iterator(&this->arr[this->length])); }
        const_iterator end() const { return const_iterator(&this->arr[this->length]); }
        reverse_iterator rbegin() { return reverse_iterator(&this->arr[this->length - 1]); }
        const_reverse_iterator rbegin() const { return const_iterator(&this->arr[this->length - 1]); }
        reverse_iterator rend() { return reverse_iterator(&this->arr[-1]); }
        const_reverse_iterator rend() const { return iterator(&this->arr[-1]); }
        
        //Capacity
        size_type size() const { return this->length; }
        size_type max_size() const { return alloc.max_size(); }
        size_type capacity() const { return this->cap; }
        bool empty() const { return !this->length; }

        void resize (size_type n, value_type val = value_type());
        void reserve (size_type n);

        // Access
        reference operator[] (size_type n) { return this->arr[n]; }
        reference front () { return this->arr[0]; }
        reference back () { return this->arr[this->length - 1]; }
        reference at (size_type n) {
            if (n >= this->length)
                throw (std::out_of_range("out of range"));
            return this->arr[n];
        }
        const_reference operator[] (size_type n) const { return this->arr[n]; }
        const_reference front() const { return this->arr[0]; }
        const_reference back() const { return this->arr[length - 1]; }
        const_reference at (size_type n) const {
            if (n >= this->length)
                throw (std::out_of_range("out of range"));
            return this->arr[n];
        }

        // Modifiers
        void assign (iterator first, iterator last);
        void assign (size_type n, const value_type& val);
        void push_back (const value_type& val);
        void pop_back();
        iterator insert (iterator position, const value_type& val);
        iterator insert (iterator position, size_type n, const value_type& val);
        iterator insert (iterator position, iterator first, iterator last);
        iterator erase (iterator position);
        iterator erase (iterator first, iterator last);
        void swap (vector& x);
        void clear();
        void swap (vector<T,Alloc>& x, vector<T,Alloc>& y);
    }; // End of class

    // Constructors
    template <typename T, typename Alloc>
    vector<T, Alloc>::vector (const allocator_type& _alloc) {
        this->alloc = _alloc;
        this->length = 0;
        this->cap = 8;
        this->multiplier = 2;
        this->arr = alloc.allocate(cap * sizeof(T));
            for (size_type i = 0; i < cap; i++)
                alloc.construct(arr + i, T());
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector (size_type n, const value_type& val, const allocator_type& _alloc) {
        this->alloc = _alloc;
        this->multiplier = 2;
        this->arr = alloc.allocate(int(n * this->multiplier) * sizeof(T));
            for (int i = 0; i < int(n * this->multiplier); i++)
                alloc.construct(arr + i, T());
        this->length = n;
        this->cap = n * this->multiplier;

        for (size_type i = 0; i < n; i++)
            this->arr[i] = val;
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector (iterator first, iterator last, const allocator_type& _alloc) {
        size_type n = last - first;
        this->alloc = _alloc;
        this->multiplier = 2;
        this->length = n;
        this->cap = n * this->multiplier;
        this->arr = alloc.allocate(cap * sizeof(T));
        for (size_t i = 0; i < cap; i++)
            alloc.construct(arr + i, T());

        for (size_type i = 0; i < n; i++)
            this->arr[i] = *(first + i);
    }

    template <typename T, typename Alloc>
    vector<T, Alloc>::vector (const vector& x) {
        this->alloc = alloc;
        this->multiplier = 2;
        this->arr = NULL;
        this->length = 0;
        this->cap = 0;
        *this = x;
    }

    // Destructors
    template <typename T, typename Alloc>
    vector<T, Alloc>::~vector() {
        if (this->arr) {
            alloc.deallocate(arr, cap);
            this->arr = NULL;
        }
    }

    // Operator Overloads
    template <typename T, typename Alloc>
    vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc>& x) {
        if (this->arr) {
            alloc.deallocate(arr, cap);
            this->arr = NULL;
        }

        this->arr = alloc.allocate(x.cap * sizeof(T));
        for (size_type i = 0; i < x.cap; i++)
            alloc.construct(arr + i, T());
        this->multiplier = x.multiplier;
        this->cap = x.cap;
        this->length = x.length;

        for (size_type i = 0; i < x.length; i++)
            this->arr[i] = x.arr[i];

        return *this;
    }

    template <typename T, typename Alloc>
    bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename vector<T, Alloc>::const_iterator lhs_cur = lhs.begin();
        typename vector<T, Alloc>::const_iterator rhs_cur = rhs.begin();
        
        while (lhs_cur != lhs.end() && rhs_cur != lhs.end())
            if (*lhs_cur++ != *rhs_cur++)
                return false;

        if (lhs_cur != lhs.end() || rhs_cur != rhs.end())
            return false;

        return true;
    }

    template <typename T, typename Alloc>
    bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs == rhs);
    }

    template <typename T, typename Alloc>
    bool operator<  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        typename vector<T, Alloc>::const_iterator first1 = lhs.begin();
        typename vector<T, Alloc>::const_iterator last1 = lhs.end();
        typename vector<T, Alloc>::const_iterator first2 = rhs.begin();
        typename vector<T, Alloc>::const_iterator last2 = rhs.end();

        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
            if (*first1 < *first2)
                return true;
            if (*first2 < *first1)
                return false;
        }
        
        return (first1 == last1) && (first2 != last2);
    }
    
    template <typename T, typename Alloc>
    bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(rhs < lhs);
    }

    template <typename T, typename Alloc>
    bool operator>  (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return rhs < lhs;
    }
    
    template <typename T, typename Alloc>
    bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs) {
        return !(lhs < rhs);
    }

    //Capacity
    template <typename T, typename Alloc>
    void vector<T, Alloc>::resize (size_type n, value_type val) {
        while (n < this->length)
            pop_back();
        while (n > this->length)
            push_back(val);
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::reserve (size_type n) {
        if (n > this->cap) {
            value_type *tmp = arr;
            this->arr = alloc.allocate(n * sizeof(T));
            for (size_type i = 0; i < n; i++)
                alloc.construct(arr + i, T());

            for (size_t i = 0; i < this->length; i++)
                arr[i] = tmp[i];
            
            if (tmp) {
                alloc.deallocate(tmp, cap);
                tmp = NULL;
            }
            this->cap = n;
        }
    }

    // Modifiers
    template <typename T, typename Alloc>
    void vector<T, Alloc>::assign (iterator first, iterator last) {
        if (this->arr) {
            alloc.deallocate(arr, cap);
            this->arr = NULL;
        }
        size_t i;
        iterator tmp = first;

        for (i = 0; tmp != last; i++, tmp++);
        
        this->cap = i;
        this->length = i;
        this->arr = alloc.allocate(i * sizeof(T));
        for (size_type j = 0; j < i; j++)
            alloc.construct(arr + j, T());
        
        for (i = 0; i < this->length; i++)
            arr[i] = *first++;
    }
    
    template <typename T, typename Alloc>
    void vector<T, Alloc>::assign (size_type n, const value_type& val) {
        if (this->arr) {
            alloc.deallocate(arr, cap);
            this->arr = NULL;
        }
        this->cap = n;
        this->length = n;
        this->arr = alloc.allocate(n * sizeof(T));
            for (size_type i = 0; i < n; i++)
                alloc.construct(arr + i, T());

        for (size_t i = 0; i < n; i++)
            arr[i] = val;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::push_back (const value_type& val) {
        if (this->length == this->cap) {
            int c = cap;
            this->cap *= multiplier;
            value_type *tmp = arr;
            this->arr = alloc.allocate(cap * sizeof(T));
            for (size_type i = 0; i < cap; i++)
                alloc.construct(arr + i, T());
        
            for (size_t i = 0; i < this->cap; i++)
                arr[i] = tmp[i];

            if (tmp) {
                alloc.deallocate(tmp, c);
                tmp = NULL;
            }
        }

        arr[this->length++] = val;
    }
    
    template <typename T, typename Alloc>
    void vector<T, Alloc>::pop_back() {
        if (this->length > 0)
            this->length--;
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::insert (iterator position, const value_type& val) {
        return insert(position, 1, val);
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::insert (iterator position, size_type n, const value_type& val) {
        iterator first = begin();
        iterator last = end();

        reserve(this->length + n);

        size_t i = this->length + n - 1;
        this->length += n;
        iterator it;

        for (it = end(); last - position != end() - it; it--, i--) {
            arr[i] = *(it - n - 1);
        }

        for (; n > 0; i--, n--)
            arr[i] = val;

        return iterator(&arr[size_type(position - first)]);
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::insert (iterator position, iterator first, iterator last) {
        iterator _first = begin();
        iterator _last = end();

        size_t n = last - first;

        reserve(this->length + n);

        size_t i = this->length + n - 1;
        this->length += n;
        iterator it;

        for (it = end(); _last - position != end() - it; it--, i--) {
            arr[i] = *(it - n - 1);
        }

        for (; n > 0; i--, n--)
            arr[i] = *(first + n - 1);

        return iterator(&arr[size_type(position - first)]);
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase (iterator position) {
        size_t i = 0;
        for (iterator it = begin(); it != position; it++, i++);
        for (iterator it = position + 1; it != end(); it++, i++)
            arr[i] = arr[i + 1];
        
        this->length -= 1;

        return iterator(&arr[size_type(position - begin())]);
    }

    template <typename T, typename Alloc>
    typename vector<T, Alloc>::iterator vector<T, Alloc>::erase (iterator first, iterator last) {
        size_type interval = last - first;
        
        size_t i = 0;
        for (iterator it = begin(); it != first; it++, i++);
        for (iterator it = last - 1; it != end(); it++, i++)
            arr[i] = arr[i + interval];
        
        this->length -= interval;

        return iterator(&arr[size_type(first - begin())]);
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::swap (vector& x) {
        std::swap(this->arr, x.arr);
        std::swap(this->length, x.length);
        std::swap(this->cap, x.cap);
        std::swap(this->multiplier, x.multiplier);
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::clear() {
        if (this->arr) {
            alloc.deallocate(arr, cap);
            this->arr = NULL;
        }
        this->arr = alloc.allocate(cap * sizeof(T));
        for (size_type i = 0; i < cap; i++)
            alloc.construct(arr + i, T());
        this->length = 0;
    }

    template <typename T, typename Alloc>
    void vector<T, Alloc>::swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
        std::swap(y.arr, x.arr);
        std::swap(y.length, x.length);
        std::swap(y.cap, x.cap);
        std::swap(y.multiplier, x.multiplier);
    }

} // End of namespace