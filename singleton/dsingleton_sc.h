#include <iostream>
#include <pthread.h>

using namespace std;

namespace DS_SC{

template<typename T>
class Singleton {
public:
    static T *Instance();

protected:
    Singleton() {}
    ~Singleton() { cout << "DS_SC: call ~Singleton()" << endl; }
private:
    struct SingletonContainer {
        T *_ins;
        SingletonContainer(): _ins(NULL) {}
        ~SingletonContainer() { delete _ins; }
    };
    static pthread_mutex_t mutex;
    static SingletonContainer SC;
};

template<typename T> pthread_mutex_t Singleton<T>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<typename T> typename Singleton<T>::SingletonContainer Singleton<T>::SC;

template<typename T>
T* Singleton<T>::Instance()
{
    if (NULL == SC._ins) {
        pthread_mutex_lock(&mutex);
        if (NULL == SC._ins) {
            SC._ins = new T();
        }
        pthread_mutex_unlock(&mutex);
    }
    return SC._ins;
}

}
