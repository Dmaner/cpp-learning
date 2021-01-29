/**
 * 组合模式
 * - 定义
 * 将对象组合成树形结构以表示”部分-整体“的层次结构。Composite使得用户对单个对象和组合对象的使用具有一致性(稳定)
 */

#include <vector>
#include <iostream>

class Component {
 public:
  virtual ~Component() {}
  virtual void AddChild(Component*) {}
  virtual void Run() = 0;
};

/* 树节点 */
class Composite : public Component {
 private:
 std::vector<Component*> children;
 std::string m_name;
 public:
 Composite(const std::string& name) : m_name(name) {}
 ~Composite() {
     for (auto& child : children)
     {
         delete child;
     }
 }
 void AddChild(Component* p) override{
     children.push_back(p);
 }
 void Run() override {
     std::cout << m_name << std::endl;
     for (auto&child : children) {
         child->Run();
     }
 }
};

class Leaf : public Component {
    private:
    std::string leafname;
    public:
    Leaf(const std::string& name) : leafname(name) {}
    void Run() override {
        std::cout << "Leaf" << std::endl;
    }
};

int main(int argc, char const *argv[])
{
    Component* level1 = new Composite("tree node 1");
    Component* level2 = new Composite("tree node 2");
    Component* level3 = new Leaf("Leaf 1");
    level2->AddChild(level3);
    level1->AddChild(level2);
    level1->Run();
    return 0;
}
