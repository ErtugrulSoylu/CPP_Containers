#include "map.hpp"
#include "vector.hpp"
#include <vector>
#include <map>
#include <iostream>

void map() {
    ft::map<int, int> m1;
    std::map<int, int> m2;

    m1[5] = 2;
    m1[3] = 4;

    m2[5] = 2;
    m2[3] = 4;

    m1.insert(ft::make_pair(4, 4));
    m1.insert(ft::make_pair(6, 4));
    m1.insert(ft::make_pair(2, 4));

    m2.insert(std::make_pair(4, 4));
    m2.insert(std::make_pair(6, 4));
    m2.insert(std::make_pair(2, 4));

    ft::map<int, int>::iterator it1 = m1.begin();
    std::map<int, int>::iterator it2 = m2.begin();

    ft::map<int, int>::reverse_iterator ite1 = m1.rbegin();
    std::map<int, int>::reverse_iterator ite2 = m2.rbegin();
    
    while (it1 != m1.end() || it2 != m2.end()) {
        if (it1->first != it2->first)
            std::cout << "error!\n";
        if (it1->second != it2->second)
            std::cout << "error!\n";
        it1++;
        it2++;
    }

    while (ite1 != m1.rend() || ite2 != m2.rend()) {
        if (ite1->first != ite2->first)
            std::cout << "error!\n";
        if (ite1->second != ite2->second)
            std::cout << "error!\n";
        ite1++;
        ite2++;
    }

    // m1.print_map();
    m1.clear();
    // m1.print_map();

    m2.clear();
}

void vec() {
    ft::vector<int> v1;
    std::vector<int> v2;

    for (int i = 0; i < 1000; i++) {
        v1.push_back(i);
        v2.push_back(i);
    }

    for (int i =0 ; i < 100; i++) {
        v1.pop_back();
        v2.pop_back();
    }

    for (int i = 0; i < 900; i++) {
        if (v1[i] != v2[i])
            std::cout << "error!\n";
    }

    ft::vector<int> tmp1 = v1;
    std::vector<int> tmp2 = v2;
}

int main() {
    vec();
    map();
    return 0;
}