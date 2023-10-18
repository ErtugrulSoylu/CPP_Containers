#pragma once

#include <algorithm>

namespace ft{

    //Pair 
    //Pair is used to combine to two values that may be of different data types
    //Usage : ft::pair<type1, type2> pair_name
    template<class T1, class T2>
    struct pair {
        typedef T1 first_type; // get variable type
        typedef T2 second_type;

        T1 first; //get variable value
        T2 second;

        //constructors
        pair() : first(), second() {}
        pair(const T1& x, const T2& y) : first(x), second(y) {} //ft:pair<type1, type2> pair_name(val1, val2)
        template<class U1, class U2>
        pair(const pair<U1, U2> &p) : first(p.first), second(p.second) {}

        pair& operator =(const pair& other) {
            first = other.first;
            second = other.second;
            return *this;
        }
    };

    //Make pair
    //Usage : ft::pair<type1, type2> = ft::make_pair(val1, val2)
    template<class T1, class T2>
    ft::pair<T1,T2> make_pair(T1 t, T2 u){
        return pair<T1, T2>(t, u);
    }

    //Pair Operators
    
    template<class T1, class T2>
	bool operator==(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first == rhs.first;
	}

	template<class T1, class T2>
	bool operator!=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs == rhs);
	}

	template<class T1, class T2>
	bool operator<(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return lhs.first != rhs.first ? lhs.first < rhs.first : lhs.second < rhs.second;
	}

	template<class T1, class T2>
	bool operator<=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(rhs < lhs);
	}

	template<class T1, class T2>
	bool operator>(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return rhs < lhs;
	}

	template<class T1, class T2>
	bool operator>=(const ft::pair<T1,T2>& lhs, const ft::pair<T1,T2>& rhs) {
		return !(lhs < rhs);
	}
}