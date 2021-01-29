/** 
 * 备忘录模式
 * - 定义
 * 在不破坏封装性的前提下，捕获一个对象的内部状态，并在该对象之外保存这个状态。这样以后就可以将该对象恢复到原先保存的状态
 */
class Memento{
    private:
    int m_state;
    public:
    Memento(int state) : m_state(state) {}
    int GetState() const {return m_state;}
};

class Originator {
    private:
    int m_state;
    public:
    Originator() : m_state(0) {}
    Memento CreateMemento(){
        Memento m(m_state);
        return m;
    }
    void SetMemento(const Memento& m){
        m_state = m.GetState();
    }
};

int main(int argc, char const *argv[])
{
    Originator originator;
    Memento memento = originator.CreateMemento();
    /* changing state */
    originator.SetMemento(memento);
    return 0;
}
