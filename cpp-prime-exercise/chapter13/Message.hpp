#ifndef MESSAGE_H
#define MESSAGE_H

#include <set>
#include <string>
#include <iostream>

class Folder;

class Message
{
public:
    friend void swap(Message &, Message &);

    explicit Message(const std::string &str = "") : contents(str) {}

    // copy function
    Message(const Message &);
    Message &operator=(const Message &);

    // destructor
    ~Message();

    // save and remove folders
    void save(Folder &);
    void remove(Folder &);

    // add folders
    void add_folder(Folder &);
    void remove_folder(Folder &);

    // test function
    void show();

private:
    std::string contents;
    std::set<Folder *> folders;

    void add_to_folders(const Message &);
    void remove_from_folders();
};

class Folder
{
public:
    friend void Message::show();
    Folder(const std::string &name) : folder_name(name) {}

    void add_mgs(const Message *m) { messages.insert(m); }
    void remove_mgs(const Message *m) { messages.erase(m); }


private:
    std::set<const Message *> messages;
    std::string folder_name;
};

void Message::remove(Folder &f)
{
    folders.erase(&f);
    f.add_mgs(this);
}

void Message::save(Folder &f)
{
    folders.insert(&f);
    f.remove_mgs(this);
}

void Message::add_to_folders(const Message &m)
{
    for (Folder *folder : m.folders)
        folder->add_mgs(&m);
}

void Message::remove_from_folders()
{
    for (Folder *folder : folders)
        folder->remove_mgs(this);
}

// copy function
Message::Message(const Message &m)
{
    contents = m.contents;
    folders = m.folders;
    add_to_folders(m);
}

Message &Message::operator=(const Message &rhs)
{
    // remove original folder record
    remove_from_folders();
    contents = rhs.contents;
    folders = rhs.folders;
    add_to_folders(rhs);
    return *this;
}

// destructor
Message::~Message()
{
    remove_from_folders();
}

void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    // first reomve message
    for (Folder *f : lhs.folders)
        f->remove_mgs(&lhs);
    for (Folder *f : rhs.folders)
        f->remove_mgs(&rhs);

    // swap
    swap(rhs.contents, lhs.contents);
    swap(rhs.folders, lhs.folders);

    // add folder
    for (Folder *f : lhs.folders)
        f->add_mgs(&lhs);
    for (Folder *f : rhs.folders)
        f->add_mgs(&rhs);
}

void Message::add_folder(Folder &f)
{
    folders.insert(&f);
    f.add_mgs(this);
}

void Message::remove_folder(Folder &f)
{
    folders.erase(&f);
    f.remove_mgs(this);
}

void Message::show()
{
    for (Folder* f: folders)
        std::cout<< "Folder: "<< f->folder_name << " ";
    std::cout << std::endl;
}


#endif