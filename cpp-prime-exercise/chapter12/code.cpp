#include <iostream>
#include <memory>
#include <cstring>
#include "Textquery.h"

// forward declare strBlobptr
class strBlobptr;

class strBlob {

public:
    friend class strBlobptr;
    using size_type = std::vector<std::string>::size_type;
    strBlob();
    strBlob(std::initializer_list<std::string> list);
    
    // access attributes
    size_type size() const {return data->size();}
    bool empty() const {return data->empty();}

    // add and delete elements
    void push_back(const std::string &s) {data->push_back(s);}
    void pop_back();
    
    // access elements
    std::string& front();
    std::string& back();
    const std::string& front() const;
    const std::string& back() const;

    //begin and end
    strBlobptr begin();
    strBlobptr end();

private:
    std::shared_ptr<std::vector<std::string>> data;
    void check(size_type i, const std::string &msg) const;
};

class strBlobptr{

public:
    strBlobptr(): curr(0) {}
    strBlobptr(strBlob &a, std::size_t sz = 0): wptr(a.data), curr(sz) {}
    bool operator!=(const strBlobptr& p) {return p.curr!= curr;}
    std::string& deref() const;
    strBlobptr& incr();
private:
    std::shared_ptr<std::vector<std::string>> 
        check(std::size_t, const std::string& ) const;
    std::weak_ptr<std::vector<std::string>> wptr;
    std::size_t curr;
};

// strBlob class function

strBlob::strBlob(): data(std::make_shared<std::vector<std::string>>()) {}
strBlob::strBlob(std::initializer_list<std::string> list) :
    data(std::make_shared<std::vector<std::string>>(list)) {}

void strBlob::check(size_type pos, const std::string & err_msg) const {
    if (pos >= data->size())
        throw std::out_of_range(err_msg);
}

std::string& strBlob::front(){
    check(0, "Empty string!");
    return data->front();
}

std::string& strBlob::back(){
    check(0, "Empty string!");
    return data->back();
}

const std::string& strBlob::front() const {
    check(0, "Empty string!");
    return data->front();
}

const std::string& strBlob::back() const {
    check(0, "Empty string!");
    return data->back();
}

void strBlob::pop_back(){
    check(0, "Empty string!");
    data->pop_back();
}

strBlobptr strBlob::begin() {
    return strBlobptr(*this);
}

strBlobptr strBlob::end() {
    auto ret = strBlobptr(*this, data->size());
    return ret;
}

// strBlobptr class function

std::shared_ptr<std::vector<std::string>>
strBlobptr::check(std::size_t sz, const std::string& msg) const{
    std::shared_ptr<std::vector<std::string>> ret = wptr.lock();
    if (!ret) 
        throw std::runtime_error("No pointer point to data");
    if (sz >= ret->size())
        throw std::out_of_range(msg);
    return ret;
}

std::string& strBlobptr::deref() const {
    auto p = check(curr, "Deference past end");
    return (*p)[curr];
}

strBlobptr& strBlobptr::incr(){
    check(curr, "Increment past end of strblob");
    ++curr;
    return *this;
}


void exc_12_6(){
    std::cout << "Exercise 12.6" << std::endl;
    std::vector<int> *p = new std::vector<int>();
    int temp;
    while (std::cin >> temp){
        p->push_back(temp);
    }
    for (int item: *p){
        std::cout << item << " ";
    }
    std::cout << std::endl;
    delete p;
}

void exc_12_7(){
    std::cout << "Exercise 12.7" << std::endl;
    std::shared_ptr<std::vector<int>> p = std::make_shared<std::vector<int>>();
    int temp;
    while (std::cin >> temp){
        p->push_back(temp);
    }
    for (int item: *p){
        std::cout << item << " ";
    }
    std::cout << std::endl;
}

std::string connect(std::string& msg){
    std::cout << "Begin connection with " << msg << std::endl;

    return msg + " connection";
}

void disconnect(std::string connection){
    std::cout << connection << " end." << std::endl;
}

void end_connection(std::string * connection){
    disconnect(*connection);
}

void exc_12_14(){
    std::cout << "Exercise 12.14" << std::endl;
    std::string msg = "test";
    std::string connection = connect(msg);
    std::shared_ptr<std::string> p(&connection, end_connection);
    std::cout << "Doing something ..." << std::endl;
}


void exc_12_15(){
    std::cout << "Exercise 12.15" << std::endl;
    std::string msg = "second test";
    std::string connection = connect(msg);
    std::shared_ptr<std::string> p(&connection, [](std::string* c) {disconnect(*c);});
    std::cout << "Doing something ..." << std::endl;
}

void exc_12_20(){
    std::cout << "Exercise 12.20" << std::endl;
    std::ifstream ifs("./test.txt");
    std::string line;
    strBlob sb;
    while (std::getline(ifs, line)){
        std::istringstream words(line);
        std::string word;
        while (words >> word){
            sb.push_back(word);
        }
    }
    for (strBlobptr beg = sb.begin(); beg != sb.end(); beg.incr())
        std::cout << beg.deref() << " ";
    std::cout << std::endl;
}

void exc_12_23(){
    std::cout << "Exercise 12.23" << std::endl;
    const char* p1 = "test";
    const char* p2 = " 12.23";
    int length = strlen(p1) + strlen(p2) + 1;
    char* p3 = new char[20];
    strcpy(p3, p1);
    strcat(p3, p2);
    for (int i = 0; i < length; ++i)
        std::cout << *(p3+i);
    delete [] p3;
}

void exc_12_27(){
    std::cout << "Exercise 12.27" << std::endl;
    std::ifstream ifs("./test.txt");
    TeXtQuery tx(ifs);
    while (true){
        std::cout << "Enter word to search or q to quit" << std::endl;
        std::string s;
        if (!(std::cin>> s) || s == "q") break;
        std::cout << tx.query(s) << std::endl; 
    }
}

int main(int argc, char const *argv[])
{
    // exc_12_6();
    // exc_12_7();
    // exc_12_14();
    // exc_12_15();
    // exc_12_20();
    // exc_12_23();
    exc_12_27();
    return 0;
}
