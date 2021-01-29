/**
 * 迭代器模式
 * - 定义
 * 提供一种方法顺序访问一个聚合对象中的各个元素，而又不暴露(稳定)该对象的内部表示
 */

#include <iostream>

class Iterator;
class Collection;

/* 一个集合 */
class Collection {
 public:
  virtual ~Collection() {}
  virtual Iterator* CreateIterator() = 0;
};

/* 集合实现类 */
class ConcreteCollection : public Collection {
 private:
  int* list;
  int m_size;

 public:
  ConcreteCollection(int size) {
    m_size = size;
    list = new int[m_size]();
    for (int i = 0; i < m_size; i++)
    {
      list[i] = i;
    }
  }
  ~ConcreteCollection() { delete list; }
  int size() { return m_size; }
  int at(int index) { return list[index]; }
  Iterator* CreateIterator() override;
};

/* 迭代器抽象类 */
class Iterator {
 public:
  virtual ~Iterator() {}
  virtual void begin() = 0;
  virtual void next() = 0;
  virtual bool done() = 0;
  virtual int current() = 0;
};


/* 迭代器实现类 */
class ConcreteIterator : public Iterator {
 private:
  ConcreteCollection* m_collection;
  int index;

 public:
  ConcreteIterator(ConcreteCollection* collection)
      : m_collection(collection), index(0) {}
  ~ConcreteIterator() {
    delete m_collection;
  }
  void begin() override {
    index = 0;
  }
  void next() override {
    index ++;
  }
  bool done() override {
    return index < m_collection->size();
  }
  int current() override {
    return m_collection->at(index);
  }
};

Iterator* ConcreteCollection::CreateIterator() {
  return new ConcreteIterator(this);
}

int main(int argc, char const *argv[])
{
  Collection* collection = new ConcreteCollection(6);
  Iterator* it = collection->CreateIterator();
  for (it->begin(); it->done(); it->next())
  {
    std::cout << "Item: " << it->current() << std::endl;
  }
  return 0;
}
