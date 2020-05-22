#include<iostream>
#include<string>

class Screen{
public:
    using pos = std::string::size_type;
    Screen() = default;
    Screen(pos h, pos w): height(h), width(w), content(h*w, " ") {};
    Screen(pos h, pos w, char c): height(h), width(w), content(h*w, c) {};
    char get() const {return content[cursor];};
    inline char get(pos, pos) const;
    Screen& move(pos, pos);
private:
    int height = 0, width = 0;
    int cursor = 0;
    std::string content;
};

inline
Screen& Screen::move(pos h, pos w){
    cursor = h * width + w;
    return *this;
}

char Screen::get(pos h, pos w) const {
    return cursor[h*width + w];
}

int main(int argc, char const *argv[])
{
    const Screen a;

    return 0;
}
