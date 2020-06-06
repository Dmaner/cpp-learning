#ifndef HASPTR_H
#define HASPTR_H

#include <string>
#include <iostream>

class Hasptr{
    public:
        friend void swap(Hasptr&, Hasptr&);
        friend bool operator<(const Hasptr&, const Hasptr&);
        Hasptr(const std::string &s = std::string()): ps(new std::string(s)), i(0) {}
        Hasptr(const Hasptr & ptr): 
            ps(new std::string(*(ptr.ps))), i(ptr.i) { 
                std::cout << "Using copy construct " << *ps <<std::endl;
            }

        ~ Hasptr(){
            std::cout << "Destruct " << *ps << " class" << std::endl;
            delete ps;
        }

        const std::string value() const {return *ps;}

        Hasptr& operator=(const Hasptr& );
    private:
        std::string* ps;
        int i;
};

class Hasptr_sec{
    public:
        Hasptr_sec(const std::string &s = std::string()): ps(new std::string(s)), i(0), use(new std::size_t(1)) {}
        
        // copy constructor
        Hasptr_sec(const Hasptr_sec &ptr): ps(ptr.ps), i(ptr.i), use(ptr.use) {++*use;}
        Hasptr_sec& operator=(const Hasptr_sec&);

        // destructor
        ~ Hasptr_sec();

        // test function 
        const std::size_t counts() const {return *use;}
        
    private:
        std::string* ps;
        int i;
        std::size_t* use;
};

Hasptr& Hasptr::operator=(const Hasptr& rhs){
    std::string *newps = new std::string(*(rhs.ps));
    delete ps;
    ps = newps;
    i = rhs.i;
    std::cout << "Using reload operator =" << std::endl;
    return *this;
}

bool operator<(const Hasptr& lhs, const Hasptr& rhs){
    return *lhs.ps < *rhs.ps;
}

void swap(Hasptr& left, Hasptr &right){
    using std::swap;
    std::cout << "Swap two Hashptr" << std::endl;
    swap(left.ps, right.ps);
    swap(left.i, right.i);
}

Hasptr_sec::~Hasptr_sec(){
    if (--*use == 0){
        delete ps;
        delete use;
    }
}

Hasptr_sec& Hasptr_sec::operator=(const Hasptr_sec &rhs){
    ++*rhs.use;
    if (--*use == 0){
        delete ps;
        delete use;
    }
    ps = rhs.ps;
    i = rhs.i;
    use = rhs.use;
    return *this;
}

#endif 