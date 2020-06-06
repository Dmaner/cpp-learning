#ifndef STRVEC_H
#define STRVEC_H

#include <memory>
#include <string>
#include <iostream>
#include <utility>
#include <algorithm>


class StrVec
{
public:
    StrVec() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
    StrVec(std::initializer_list<std::string> args){
        size_t counts = args.size();
        auto data = alloc.allocate(counts);
        auto begin = data;
        for (auto iter = args.begin(); iter != args.end(); iter++){
            alloc.construct(begin++, *iter);
        }
        elements = data;
        first_free = cap = begin;
    }

    // exercise 13.49
    StrVec(StrVec &&) noexcept;
    StrVec& operator=(StrVec &&) noexcept;

    // copy function
    StrVec(const StrVec &);
    StrVec &operator=(const StrVec &);
    ~StrVec();

    void push_back(const std::string&);

    // size
    std::size_t size() const { return first_free - elements; }
    std::size_t capacity() const { return cap - elements; }
    std::string *begin() const { return elements; }
    std::string *end() const { return first_free; }
    // allocate memory
    void reserve(size_t);
    void resize(size_t);
    void resize(size_t, std::string);

private:
    std::allocator<std::string> alloc;
    void ck_n_alloc()
    {
        if (size() == capacity())
            reallocate();
    }
    std::pair<std::string *, std::string *> alloc_n_copy(const std::string *, const std::string*);

    void free();
    void reallocate();
    void alloc_n_move(size_t);

    // header point
    std::string *elements;

    // tail point
    std::string *first_free;

    // capacity
    std::string *cap;
};


void StrVec::push_back(const std::string &s)
{
    // check if out of memory
    ck_n_alloc();
    alloc.construct(first_free, s);
    ++first_free;
} 

std::pair<std::string *, std::string *>
StrVec::alloc_n_copy(const std::string *beg, const std::string *end)
{
    std::string *data = alloc.allocate(end - beg);
    // return begin and end after copying
    return {data, std::uninitialized_copy(beg, end, data)};
}

void StrVec::free()
{
    if (elements) // check if elements is nullptr
    {
        // exersize 13.43
        auto iter = first_free;
        std::for_each(elements, first_free, [this](std::string&rhs){alloc.destroy(&rhs);});
        std::cout << "Free StrVec" << std::endl;
        alloc.deallocate(elements, cap-elements);
    }
}

StrVec::StrVec(const StrVec& rhs){
    std::cout << "Using copy construct" << std::endl;
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    elements = data.first;
    first_free = cap = data.second;
}

StrVec::~StrVec(){
    free();
}

StrVec& StrVec::operator=(const StrVec& rhs){
    auto data = alloc_n_copy(rhs.begin(), rhs.end());
    free();
    elements = data.first;
    first_free = cap = data.second;
    return *this;
}

void StrVec::alloc_n_move(size_t capacity){
    auto data = alloc.allocate(capacity);
    auto begin = data;
    auto origin = elements;
    for (size_t i = 0; i != size(); ++i, ++ begin, ++origin)
        alloc.construct(begin, std::move(*origin));
    free();
    elements = data;
    first_free = begin;
    cap = elements + capacity;
}

void StrVec::reallocate(){
    size_t capacity = size() ? 2 * size() : 1;
    alloc_n_move(capacity);
}

void StrVec::reserve(size_t counts){
    if (counts > size())
        alloc_n_move(counts);
}

void StrVec::resize(size_t counts, std::string s){
    if (counts > size()){
        if (counts > capacity()) reserve(2*counts);
        for (size_t i = 0; i < counts-size(); i++, first_free++)
            alloc.construct(first_free, s);
    }
    else if (counts < size()){
        for (size_t i = 0; i < counts; i++)
            alloc.destroy(--first_free);
    }
}

void StrVec::resize(size_t counts){
    if (counts > size())
        resize(counts, std::string());
}

// exercise 13.49
StrVec::StrVec(StrVec &&rhs) noexcept {
    elements = rhs.elements;
    first_free = rhs.first_free;
    cap = rhs.cap;
    rhs.elements = rhs.first_free = rhs.cap = nullptr;
}

StrVec& StrVec::operator=(StrVec &&rhs) noexcept{
    if (&rhs != this){
        free();
        elements = rhs.elements;
        first_free = rhs.first_free;
        cap = rhs.cap;
        rhs.elements = rhs.first_free = rhs.cap = nullptr;
    }
    return *this;
}

#endif