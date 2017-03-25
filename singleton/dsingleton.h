#include <iostream>
#include <pthread.h>
#include <stdio.h>

using namespace std;

namespace DS{

template<typename T>
class Singleton {
public:
    static T *Instance();

protected:
    Singleton() { garbo; }

private:
    class Garbo {
    public:
        ~Garbo() {
            if (Singleton<T>::_ins) {
                cout << "DS: ~Garbo(): delete Singleton::_ins" << endl;
                delete Singleton<T>::_ins;
                Singleton<T>::_ins = NULL;
            }
        }    
    };
    static T *_ins;
    static pthread_mutex_t mutex;
    static Garbo garbo;
};
template<typename T> T* Singleton<T>::_ins = NULL;
template<typename T> pthread_mutex_t Singleton<T>::mutex = PTHREAD_MUTEX_INITIALIZER;
template<typename T> typename Singleton<T>::Garbo Singleton<T>::garbo;

template<typename T>
T* Singleton<T>::Instance()
{
    if (NULL == _ins) {
        pthread_mutex_lock(&mutex);
        if (NULL == _ins) {
            _ins = new T();
        }
        pthread_mutex_unlock(&mutex);
    }
    return _ins;
}

}
