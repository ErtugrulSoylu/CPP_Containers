#include <type_traits>

namespace ft {

    //integer variable types
    //bool, char, signed char
    //unsigned char, short
    //unsigned short, int
    //unsigned int, long
    //unsigned long

    //integral_constant definition
    //integral_constant default and mandatory struct!!!

    template <typename _Tp, _Tp __v>
    struct integral_constant
    {
        static const _Tp                    value       = __v;
        typedef _Tp                         value_type;
        typedef integral_constant<_Tp, __v> type;
    };

    //true and false types comes from integral_constant
    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    // if coming type is non-integral types, __is_integral_helper definitaion inherit false_type
    template <typename>
    struct __is_integral_helper : public false_type {};


    // if coming type is integral type then, __is_integral_helper which point whether integral type or not, will inherit from true_type
    template <> //there is no definition because we look at just certain types
    struct __is_integral_helper<bool> : public true_type {};

    template <>
    struct __is_integral_helper<char> : public true_type {};

    template <>
    struct __is_integral_helper<signed char> : public true_type {};

    template <>
    struct __is_integral_helper<unsigned char> : public true_type {};

    template <>
    struct __is_integral_helper<short> : public true_type {};

    template <>
    struct __is_integral_helper<unsigned short> : public true_type {};

    template <>
    struct __is_integral_helper<int> : public true_type {};

    template <>
    struct __is_integral_helper<unsigned int> : public true_type {};

    template <>
    struct __is_integral_helper<long> : public true_type {};

    template <>
    struct __is_integral_helper<unsigned long> : public true_type {};

    // is_integral main struct
    template <typename T>
    struct is_integral : public __is_integral_helper<T> {};
}