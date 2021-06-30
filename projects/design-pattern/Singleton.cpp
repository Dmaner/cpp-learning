/**
 * 单例模式
 * - 定义
 * 保证一个类仅有一个实例，并提供一个该实例的全局访问点
 */

#include <atomic>
#include <mutex>

class Singleton
{
private:
	Singleton() { };
	~Singleton() { };
	Singleton(const Singleton&);
	Singleton& operator=(const Singleton&);
public:
	static Singleton& getInstance() 
        {
		static Singleton instance;
		return instance;
	}
};


