#ifndef PERSON_H
#define PERSON_H

#include<string>
#include<iostream>
using std::string;

class Person
{
    friend std::istream& read(std::istream&,  Person&);
    friend std::ostream& print(std::ostream&, const Person&);
public:
    Person() = default;
    Person(const string &s, const string& a): name(s), addr(a) {};
    Person(std::istream& );
    std::string get_name() const {return name;};
    std::string get_addr() const {return addr;};
private:
    std::string name;
    std::string addr;
};

Person::Person(std::istream&is){

}

std::istream& read(std::istream &is,  Person &a){
    is >> a.name>> a.addr;
    return is;
}

std::ostream& print(std::ostream &os, const Person &a){
    os << "Name: "<<a.name << " Address: "<<a.addr;
    return os;
}

#endif