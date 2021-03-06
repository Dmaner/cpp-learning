# c++ 实现设计23种设计模式

### 六大原则

单一职责原则
- 不要让一个类承担过多的职责
- 避免职责耦合在一起，避免一个职责的变化影响到其他职责

开放封闭职责
- 对扩展开放，对更改封闭
- 类模块应该是可扩展的，但是不可修改

Liskov（里氏）替换原则
- 子类必须能够替换它们的基类

依赖倒置原则
- 接口或抽象类不依赖于实现类，而实现类依赖接口或抽象类

迪米特原则
- 一个对象应该对其他对象有最少的了解，当其中某一个类发生修改时，就会尽量少地影响其他模块
- 降低系统的耦合度，使类与类之间保持松散的耦合关系

接口隔离原则
- 建立单一接口而不是建立庞大臃肿的接口，尽量细化接口，接口中的方法尽量少

### 代码实现

#### 行为型模式
- [模板模式](TemplateMethod.cpp)
- [策略模式](Strategy.cpp) 
- [观察者模式](Observer.cpp)
- [中介者模式](Mediator.cpp)
- [状态模式](State.cpp)
- [备忘录模式](Memento.cpp)
- [迭代器模式](Iterator.cpp)
- [责任链模式](ChainOfResponsibility.cpp)
- [命令模式](Command.cpp)
- [访问者模式](Visitor.cpp)
- [解析器模式](Interperter.cpp)


#### 结构型模式
- [装饰模式](Decorator.cpp)
- [桥模式](Bridge.cpp)
- [享元模式](Flyweight.cpp)
- [门面模式](Facade.cpp)
- [代理模式](Proxy.cpp)
- [适配器模式](Adapter.cpp)
- [组合模式](Composite.cpp)


#### 创建型模式
- [工厂模式](FactoryMethod.cpp)
- [抽象工厂模式](AbstractFactory.cpp)
- [原型模式](Prototype.cpp)
- [建造者模式](Build.cpp)
- [单例模式](Singleton.cpp)