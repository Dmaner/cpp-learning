/**
 * 单例模式
 * - 定义
 * 保证一个类仅有一个实例，并提供一个该实例的全局访问点
 */

#include <atomic>
#include <mutex>
class Singleton {
 private:
  Singleton();
  Singleton(const Singleton& other);

 public:
  static Singleton* getInstance();
  static Singleton* m_instance;
};

/* 单线程版 */
Singleton* Singleton::getInstance() {
  if (m_instance == nullptr) {
    m_instance = new Singleton();
  }
  return m_instance;
}