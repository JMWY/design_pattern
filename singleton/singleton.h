#include <iostream>
#include <stdio.h>

namespace SS {

template<typename T>
class Singleton {
public:
    static T *Instance() { return _ins; }

protected:
    Singleton() { garbo;}
    virtual ~Singleton() { }

private:
    class Garbo {
    public:
        ~Garbo() {
            if (Singleton<T>::_ins) {
                cout << "SS: ~Garbo(): delete Singleton::_ins" << endl;
                delete Singleton<T>::_ins;
                Singleton<T>::_ins = NULL;
            }
        }    
    };
    static T*  _ins;
    static Garbo garbo;
};
template<typename T> T *Singleton<T>::_ins = new T();
template<typename T> typename Singleton<T>::Garbo Singleton<T>::garbo;

}
