#ifndef PRINT_STRING_H
#define PRINT_STRING_H

#include <iostream>
#include <string>

class PrintString
{
public:
    PrintString(std::ostream &o = std::cout, std::string s = "\n") : out(o), end(s) {}
    void operator()(const std::string &s) { out << s << end; }

private:
    std::ostream &out;
    std::string end;
};

#endif