/**
 * 享元模式
 * - 定义
 * 运行共享技术有效地支持大量细粒度的对象
 */

#include <iostream>
#include <unordered_map>

class Product {
 private:
  std::string m_key;

 public:
  Product(const std::string& key) : m_key(key) {}
  ~Product() {}
  void show() { std::cout << "key" << std::endl; }
};

class Factory {
 private:
  std::unordered_map<std::string, Product*> pool;

 public:
  Product* Get(std::string key) {
    auto iter = pool.find(key);
    if (iter == pool.end()) {
      std::cout << "Add " << key << " into pool" << std::endl;
      pool[key] = new Product(key);
    }
    return pool[key];
  }
};

int main(int argc, char const* argv[]) {
  Factory factory;
  Product* p1 = factory.Get("A");
  Product* p2 = factory.Get("A");
  p1->show();
  p2->show();
  return 0;
}
