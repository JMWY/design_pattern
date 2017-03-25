#include <iostream>

using namespace std;

#define DISALLOW_COPY_AND_ASSIGN(TypeName) \
        TypeName (const TypeName&);        \
        TypeName& operator= (const TypeName&)

namespace RS {

template<typename T>
class Singleton{
public:
    static T* Instance(){
        static T instance;
        return &instance;
    }
protected:
    Singleton() {}
    virtual ~Singleton() { cout << "RS: call ~Singleton()" << endl; }

private:
    DISALLOW_COPY_AND_ASSIGN(Singleton);
};

}
