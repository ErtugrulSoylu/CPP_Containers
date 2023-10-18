#include <type_traits>

namespace ft{

    //this function return whether two container completely equal as integer or no
    //funcion takes 2 container and these container should has able to bidirectional iteration
    template <class U, class X>
    bool equal(U left_it, U left_end, X right_it, X right_end){
        while (left_it != left_end) {
            if (right_it == right_end || *right_it != *left_it)
                return (false);
            ++left_it;
            ++right_it;
        }
        return (true);
    }

    //lexicographical_compare
    //this function return whether two container completely equal as string or no
    template<class T, class U>
    bool lexicographical_compare(T first1, T last1, U first2, U last2) {
        while (first1 != last1) {
            if (first2 = last2 || *first2 < *first1) return false;
            else if (*first1 < *first2) return true;
        
            ++first1;
            ++first2;

        }
    return first2 != last2;
    }
}