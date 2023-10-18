#pragma once

template <typename T, typename Pointer, typename Reference>
class InputIterator {
    
    public:
    typedef Pointer                                     pointer;
    typedef Reference                                   reference;
    typedef size_t								        size_type;
    typedef InputIterator<T, Pointer, Reference>        iterator_class;
    typedef InputIterator<T, T*, T&>                    iterator;

    pointer element_pointer;

    // Constructors and Destructor
    InputIterator() : element_pointer(NULL) {};
    InputIterator(const pointer it) : element_pointer(it) {};
    InputIterator(const iterator &copy) {*this = copy;};
    ~InputIterator() {}

    // Operator Overloads

    // =
    iterator_class &operator=(const iterator &it) {
        this->element_pointer = it.element_pointer;
        return *this;    
    }

    // ++
    iterator_class &operator++() {
        this->element_pointer++;
        return *this;
    }

    iterator_class operator++(int) {
        iterator_class tmp = *this;
        ++this->element_pointer;
        return tmp;
    }

    // --
    iterator_class &operator--() {
        this->element_pointer--;
        return *this;
    }

    iterator_class operator--(int) {
        iterator_class tmp = *this;
        --this->element_pointer;
        return tmp;
    }

    // +=
    iterator_class &operator+=(size_type n) {
        this->element_pointer += n;
        return *this;
    }
    
    // -=
    iterator_class &operator-=(size_type n) {
        this->element_pointer -= n;
        return *this;
    }
    
    // +
    size_type operator+(const iterator_class &it) const {
        return this->element_pointer + it.element_pointer;
    }

    iterator_class operator+(size_type n) const {
        iterator_class tmp = *this;
        tmp.element_pointer += n;
        return tmp;
    }
    
    friend iterator_class operator+(size_type n, const iterator_class &it) {
        return it + n;
    }
    
    // -
    int operator-(const iterator_class &it) const {
        return this->element_pointer - it.element_pointer;
    }

    iterator_class operator-(size_type n) const {
        iterator_class tmp = *this;
        tmp.element_pointer -= n;
        return tmp;
    }

    friend iterator_class operator-(size_type n, const iterator_class &it) {
        return -(it - n);
    }
    
    // ==
    friend bool operator==(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer == it.element_pointer;
    }

    // !=
    friend bool operator!=(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer != it.element_pointer;
    }
    
    // >
    friend bool operator>(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer > it.element_pointer;
    }

    // <
    friend bool operator<(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer < it.element_pointer;
    }
    
    // >=
    friend bool operator>=(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer >= it.element_pointer;
    }
    
    // <=
    friend bool operator<=(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer <= it.element_pointer;
    }
    
    // ->
    pointer operator->() { 
        return *(&(this->element_pointer));
    }
    
    // *
    reference operator*() {
        return *this->element_pointer;
    }
    
    // []
    reference operator[](size_type n) {
        return *(this->element_pointer + n);
    }

};

template <typename T, typename Pointer, typename Reference>
class RevInputIterator {
    
    public:
    typedef Pointer                                     pointer;
    typedef Reference                                   reference;
    typedef size_t								        size_type;
    typedef RevInputIterator<T, Pointer, Reference>     iterator_class;
    typedef RevInputIterator<T, T*, T&>                 iterator;
    
    pointer element_pointer;

    public:
    // Constructors and Destructor
    RevInputIterator() : element_pointer(NULL) {};
    RevInputIterator(const pointer it) : element_pointer(it) {};
    RevInputIterator(const iterator &copy) {*this = copy;};
    RevInputIterator(const InputIterator<T, T*, T&> &it) {
        this->element_pointer = it.element_pointer - 1;
    }
    RevInputIterator(const InputIterator<T, const T*, const T&> &it) {
        this->element_pointer = it.element_pointer - 1;
    }
    ~RevInputIterator() {}

    InputIterator<T, Pointer, Reference> base() { return InputIterator<T, Pointer, Reference>(this->element_pointer + 1); }

    // Operator Overloads
    
    // =
    iterator_class &operator=(const iterator &it) {
        this->element_pointer = it.element_pointer;
        return *this;    
    }

    // ++
    iterator_class &operator++() {
        this->element_pointer--;
        return *this;
    }

    iterator_class operator++(int) {
        iterator_class tmp = *this;
        --this->element_pointer;
        return tmp;
    }

    // --
    iterator_class &operator--() {
        this->element_pointer++;
        return *this;
    }

    iterator_class operator--(int) {
        iterator_class tmp = *this;
        ++this->element_pointer;
        return tmp;
    }

    // +=
    iterator_class &operator+=(size_type n) {
        this->element_pointer -= n;
        return *this;
    }
    
    // -=
    iterator_class &operator-=(size_type n) {
        this->element_pointer += n;
        return *this;
    }
    
    // +
    size_type operator+(const iterator_class &it) const {
        return this->element_pointer - it.element_pointer;
    }

    iterator_class operator+(size_type n) const {
        iterator_class tmp = *this;
        tmp.element_pointer -= n;
        return tmp;
    }
    
    friend iterator_class operator+(size_type n, const iterator_class &it) {
        iterator_class tmp = it;
        tmp.element_pointer -= n;
        return tmp;
    }
    
    // -
    int operator-(const iterator_class &it) const {
        return it.element_pointer - this->element_pointer;
    }

    iterator_class operator-(size_type n) const {
        iterator_class tmp = *this;
        tmp.element_pointer += n;
        return tmp;
    }

    friend iterator_class operator-(size_type n, const iterator_class &it) {
        iterator_class tmp = it;
        tmp.element_pointer += n;
        return tmp;
    }
    
    // ==
    friend bool operator==(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer == it.element_pointer;
    }

    // !=
    friend bool operator!=(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer != it.element_pointer;
    }
    
    // >
    friend bool operator>(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer < it.element_pointer;
    }

    // <
    friend bool operator<(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer > it.element_pointer;
    }
    
    // >=
    friend bool operator>=(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer <= it.element_pointer;
    }
    
    // <=
    friend bool operator<=(const iterator_class &it1, const iterator_class &it) {
        return it1.element_pointer >= it.element_pointer;
    }
    
    // ->
    pointer operator->() { 
        return *(&(this->element_pointer));
    }
    
    // *
    reference operator*() {
        return *this->element_pointer;
    }
    
    // []
    reference operator[](size_type n) {
        return *(this->element_pointer - n);
    }

};