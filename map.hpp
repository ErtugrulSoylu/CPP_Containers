#pragma once

#include <iostream>
#include <limits>
#include "MapIterator.hpp"
#include "ft_pair.hpp"
#include <queue>
#include <map>      

namespace ft {

   
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
    class map {

    public:
        typedef Key 										    key_type;
        typedef T 											    mapped_type;
        typedef ft::pair<const key_type, mapped_type> 		    value_type;
        typedef Compare 									    key_compare;
        typedef Alloc 										    allocator_type;
        typedef T& 											    reference;
        typedef const T& 									    const_reference;
        typedef T* 											    pointer;
        typedef const T* 									    const_pointer;
        typedef size_t 										    size_type;
        typedef std::ptrdiff_t                                  difference_type;
        typedef BNode<Key, T>*                                  node;
        typedef MapIterator<key_type, mapped_type>              iterator;
        typedef ConstMapIterator<key_type, mapped_type>         const_iterator;
        typedef ReverseMapIterator<key_type, mapped_type>       reverse_iterator;
        typedef ConstReverseMapIterator<key_type, mapped_type>  const_reverse_iterator;
        class value_compare : public std::binary_function<value_type, value_type, bool> {
            friend class map;
            protected:
                Compare comp;
                value_compare (Compare c) : comp(c) {} // constructed with map's comparison object
            public:
                typedef bool result_type;
                typedef value_type first_argument_type;
                typedef value_type second_argument_type;
                bool operator() (const value_type& x, const value_type& y) const {
                    return comp(x.first, y.first);
                }
        };
    
    private:
        allocator_type  _allocator;
        std::allocator<BNode<key_type, mapped_type> > _tree_allocator;
        key_compare     _comp;
        node            _rend;
        node            _root;
        size_type       _length;
        node            _end;

        void _clear(node n) {
            if (!n || n == _end)
                return ;
            _clear(n->left);
            _clear(n->right);
            _tree_allocator.destroy(n);
            _tree_allocator.deallocate(n, 1);
        }

        std::map<node, int> m;
        void calc_dist(node cur, int dist) {
            if (!cur)
                return;
            m[cur] = dist;
            calc_dist(cur->left, dist - 1);
            calc_dist(cur->right, dist + 1);
        }
        unsigned int GetNumberOfDigits (unsigned int i)
        {
            return i > 0 ? (int) log10 ((double) i) + 1 : 1;
        }
        int count_digit(int number) {
            int count = 0;
            while(number != 0) {
                number = number / 10;
                count++;
            }
            return count;
        }
        void print_map()
        {
            int least = 0;
            calc_dist(_root, 0);
            for (auto element : m) {
                if (element.second < least)
                    least = element.second;
            }
            for (auto it = m.begin(); it != m.end(); it++) {
                it->second -= least;
                it->second *= 2;
            }
            node cur = _root;
            std::queue<node> q;
            q.push(cur);
            while (!q.empty()) {
                int size = q.size();
                int spaces = 0;
                for (int i = 0; i < size; i++) {
                    cur = q.front();
                    int k = (m[cur] - spaces) * 3 - count_digit(cur->elem.first) + 1;
                    std::cout << std::string(k >= 0 ? k : 0, ' ') << cur->elem.first;
                    spaces += m[cur] - spaces + 1;
                    if (cur->left)
                        q.push(cur->left);
                    if (cur->right)
                        q.push(cur->right);
                    q.pop();
                }
                std::cout << "\n";
            }
        }

    public:

        // Constructors
        explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
            _length = 0;
            _allocator = alloc;
            _comp = comp;
            _end = _tree_allocator.allocate(1);
            _tree_allocator.construct(_end, BNode<key_type, mapped_type>(ft::make_pair(key_type(), mapped_type())));
            _rend = _tree_allocator.allocate(1);
            _tree_allocator.construct(_end, BNode<key_type, mapped_type>(ft::make_pair(key_type(), mapped_type())));
            _root = _end;
            _rend->right = _end;
            _end->parent = _rend;
        }
        
        template <class InputIterator>map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) {
            _length = 0;
            _allocator = alloc;
            _comp = comp;
            _end = _tree_allocator.allocate(1);
            _tree_allocator.construct(_end, BNode<key_type, mapped_type>(ft::make_pair(key_type(), mapped_type())));
            _rend = _tree_allocator.allocate(1);
            _tree_allocator.construct(_end, BNode<key_type, mapped_type>(ft::make_pair(key_type(), mapped_type())));
            _root = _end;
            _rend->right = _end;
            _end->parent = _rend;
            insert(first, last);
        }

        map (const map& x) {
            *this = x;
        }

        // Destructors
        ~map() {
            clear();

            _tree_allocator.destroy(_end);
            _tree_allocator.deallocate(_end, 1);

            _tree_allocator.destroy(_rend);
            _tree_allocator.deallocate(_rend, 1);
        }

        // Operator Overloads
        map& operator= (const map& x) {
            _length = 0;
            _end = _tree_allocator.allocate(1);
            _tree_allocator.construct(_end, BNode<key_type, mapped_type>(ft::make_pair(key_type(), mapped_type())));
            _rend = _tree_allocator.allocate(1);
            _tree_allocator.construct(_end, BNode<key_type, mapped_type>(ft::make_pair(key_type(), mapped_type())));
            _root = _end;
            _rend->right = _end;
            _end->parent = _rend;
            insert(x.begin(), x.end());
            this->_length = x._length;
            return *this;
        }

        mapped_type& operator[](const key_type& k) {
            iterator tmp = find(k);
            if (tmp != end())
                return tmp->second;
            ft::pair<iterator, bool> p = insert(ft::make_pair(k, mapped_type()));
            return p.first->second;
        }

        iterator find(const key_type& k) {
            iterator it = begin();
            while (it != end() && it->first != k)
                it++;
            return it;
        }

        const_iterator find (const key_type& k) const {
            const_iterator it = begin();
            while (it != end() && it->first != k)
                it++;
            return it;
        }

        size_type count (const key_type& k) const {
            size_type counter = 0;
            for (const_iterator it = begin(); it != end(); it++) {
                if (it->first == k)
                    counter++;
            }
            return counter;
        }

        iterator lower_bound(const key_type& k) {
            for (iterator it = begin(); it != end(); ++it)
                if (!_comp(it->first, k))
                    return it;
            return end();
        }

        const_iterator lower_bound(const key_type& k) const {
            for (const_iterator it = begin(); it != end(); ++it)
                if (!_comp(it->first, k))
                    return it;
            return end();
        }
        
        iterator upper_bound(const key_type& k) {
            for (iterator it = begin(); it != end(); ++it)
                if (_comp(k, it->first))
                    return it;
            return end();
        }
        
        const_iterator upper_bound(const key_type& k) const {
            for (const_iterator it = begin(); it != end(); ++it)
                if (_comp(k, it->first))
                    return it;
            return end();
        }
        
        pair<iterator,iterator> equal_range(const key_type& k) {
            iterator it1 = lower_bound(k);
            iterator it2 = upper_bound(k);
            
            return make_pair<iterator, iterator>(it1, it2);
        }
        
        pair<const_iterator,const_iterator> equal_range(const key_type& k) const {
            const_iterator it1 = lower_bound(k);
            const_iterator it2 = upper_bound(k);
            
            return make_pair<const_iterator, const_iterator>(it1, it2);
        }

        // Iterators
        iterator begin() {
            node cur = _root;
            while (cur->left)
                cur = cur->left;
            return iterator(cur);
        }

        const_iterator begin() const {
            node cur = _root;
            while (cur->left)
                cur = cur->left;
            return const_iterator(cur);
        }

        iterator end() {
            return iterator(_end);
        }

        const_iterator end() const {
            return const_iterator(_end);
        }

        reverse_iterator rbegin() {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend() {
            return reverse_iterator(_rend);
        }

        const_reverse_iterator rend() const {
            return const_reverse_iterator(_rend);
        }

        //Capacity
        bool empty() const {
            return size() == 0;
        }

        size_type size() const {
            return _length;
        }
        size_type max_size() const {
            return  _tree_allocator.max_size();
        }

        // Modifiers
        ft::pair<iterator,bool> insert (const value_type& val) {
            if (_root == _end) {
                node tmp = _tree_allocator.allocate(1);
                _tree_allocator.construct(tmp, BNode<key_type, mapped_type>(val));
                tmp->right = _end;
                _end->parent = tmp;
                tmp->parent = _rend;
                _rend->right = tmp;
                _root = tmp;
                _length++;
                return ft::make_pair(iterator(_root), true);
            }
            node cur = _root;
            while (true) {
                if (cur->elem.first == val.first)
                    return ft::make_pair(iterator(cur), false);
                else if (_comp(val.first, cur->elem.first)) {
                    if (!cur->left) {
                        node tmp = _tree_allocator.allocate(1);
                        _tree_allocator.construct(tmp, BNode<key_type, mapped_type>(val));
                        cur->left = tmp;
                        tmp->parent = cur;
                        _length++;
                        return ft::make_pair(iterator(cur->left), true);
                    }
                    cur = cur->left;
                }
                else {
                    if (!cur->right) {
                        node tmp = _tree_allocator.allocate(1);
                        _tree_allocator.construct(tmp, BNode<key_type, mapped_type>(val));
                        cur->right = tmp;
                        tmp->parent = cur;
                        _length++;
                        return ft::make_pair(iterator(cur->right), true);
                    }
                    else if (cur->right == _end) {
                        node tmp = _tree_allocator.allocate(1);
                        _tree_allocator.construct(tmp, BNode<key_type, mapped_type>(val));
                        cur->right = tmp;
                        tmp->parent = cur;
                        tmp->right = _end;
                        _end->parent = tmp;
                        _length++;
                        return ft::make_pair(iterator(cur->right), true);
                    }
                    cur = cur->right;
                }
            }
            return ft::make_pair(iterator(), false);
        }

        iterator insert (iterator position, const value_type& val) {
            iterator tmp = find(val.first);
            if (tmp != end())
                return (tmp);
            ft::pair<iterator, bool> p = insert(val);
            (void)position;
            return p.first;
        }

        template <class InputIterator>
        void insert (InputIterator first, InputIterator last) {
            while (first != last) {
                insert(NULL, *first);
                first++;
            }
        }

        void erase (iterator position) {
            if (position == end())
                return ;
            node n = position.element_pointer;
            if (n->left) {
                node rightmost = n->left;
                while (rightmost->right)
                    rightmost = rightmost->right;
                std::swap(n->elem, rightmost->elem);
                if (rightmost->parent && rightmost->parent->right == rightmost)
                    rightmost->parent->right = rightmost->left;
                else if (rightmost->parent && rightmost->parent->left == rightmost)
                    rightmost->parent->left = rightmost->left;
                if (rightmost->left)
                    rightmost->left->parent = rightmost->parent;
                _length--;
                _tree_allocator.destroy(rightmost);
                _tree_allocator.deallocate(rightmost, 1);
            }
            else if (n->right) {
                if (n->right == _end) {
                    std::swap(n->elem, _end->elem);
                    n->left = NULL;
                    n->right = NULL;
                    _length--;
                    _tree_allocator.destroy(_end);
                    _tree_allocator.deallocate(_end, 1);
                    _end = n;
                    return ;
                }
                node tmp = n->right;
                tmp->parent = n->parent;
                if (n->parent && n->parent->left == n)
                    n->parent->left = tmp;
                if (n->parent && n->parent->right == n)
                    n->parent->right = tmp;
                _length--;
                if (_root == n)
                    _root = tmp;
                _tree_allocator.destroy(n);
                _tree_allocator.deallocate(n, 1);
            }
            else {
                if (n->parent && n->parent->left == n)
                    n->parent->left = NULL;
                if (n->parent && n->parent->right == n)
                    n->parent->right = NULL;
                _length--;
                _tree_allocator.destroy(n);
                _tree_allocator.deallocate(n, 1);
            }
        }

        size_type erase (const key_type& k) {
            size_type counter = 0;
            iterator it;
            while ((it = find(k)) != end()) {
                erase(it);
                counter++;
            }
            return counter;
        }

        void erase (iterator first, iterator last) {
            while (first != last)
                erase(first++);
        }

        void swap (map& x) {
            std::swap(_length, x._length);
            std::swap(_root, x._root);
            std::swap(_end, x._end);
        }

        void clear() {
            _clear(_root);
            _length = 0;
            _root = _end;
            _end->parent = _rend;
            _rend->right = _end;
        }


        // Observers
        key_compare key_comp() const {
            return _comp;
        }

        value_compare value_comp() const {
            return value_compare(_comp);
        }

        friend bool operator== (const map<key_type ,mapped_type>& lhs, const map<key_type ,mapped_type>& rhs) {
            if (lhs.size() != rhs.size())
			return (false);
            typename ft::map<key_type ,mapped_type>::const_iterator it = rhs.begin();
            typename ft::map<key_type ,mapped_type>::const_iterator it2 = lhs.begin();
            while (it != rhs.end())
            {
                if (*it != *it2)
                    return (false);
                ++it2;
                ++it;
            }
            return (true);
        }

        friend bool operator!=(const map<key_type ,mapped_type>& lhs, const map<key_type ,mapped_type>& rhs) {
            return !(lhs == rhs);
        }

        friend bool operator<(const map<key_type ,mapped_type>& lhs, const map<key_type ,mapped_type>& rhs) {
            const_iterator first1 = lhs.begin();
            const_iterator last1 = lhs.end();
            const_iterator first2 = rhs.begin();
            const_iterator last2 = rhs.end();

            for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 ) {
                if (*first1 < *first2)
                    return true;
                if (*first2 < *first1)
                    return false;
            }
            
            return (first1 == last1) && (first2 != last2);
        }
        
        friend bool operator<= (const map<key_type ,mapped_type>& lhs, const map<key_type ,mapped_type>& rhs) {
            return !(rhs < lhs);
        }

        friend bool operator>  (const map<key_type ,mapped_type>& lhs, const map<key_type ,mapped_type>& rhs) {
            return rhs < lhs;
        }
        
        friend bool operator>= (const map<key_type ,mapped_type>& lhs, const map<key_type ,mapped_type>& rhs) {
            return !(lhs < rhs);
        }
    }; // End of class
}; // End of namespace