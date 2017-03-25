#include <pthread.h>
#include <unistd.h>
#include "dsingleton.h" // 懒汉式-实现1
#include "nsingleton.h" // 懒汉式-栈
#include "singleton.h"     // 饿汉式
#include "dsingleton_sc.h" // 懒汉式-实现2

class Demo1: public DS::Singleton<Demo1> {
friend class DS::Singleton<Demo1>;
public:
    void print() { cout << "pid_t: " << pthread_self() << "\tsingleton: " << this << "\tuniq_val:" << ++uniq_val << endl; }       
protected:
    Demo1(): uniq_val(0) {}
private:
    int uniq_val;
};

class Demo2: public RS::Singleton<Demo2> {
friend class RS::Singleton<Demo2>;
public:
    void print() { cout << "pid_t: " << pthread_self() << "\tsingleton: " << this << "\tuniq_val:" << ++uniq_val << endl; }       
protected:
    Demo2(): uniq_val(0) {}
private:
    int uniq_val;
};

class Demo3: public SS::Singleton<Demo3> {
friend class SS::Singleton<Demo3>;
public:
    void print() { cout << "pid_t: " << pthread_self() << "\tsingleton: " << this << "\tuniq_val:" << ++uniq_val << endl; }       
protected:
    Demo3(): uniq_val(0) {}
private:
    int uniq_val;
};

class Demo4: public DS_SC::Singleton<Demo4> {
friend class DS_SC::Singleton<Demo4>;
public:
    void print() { cout << "pid_t: " << pthread_self() << "\tsingleton: " << this << "\tuniq_val:" << ++uniq_val << endl; }       
protected:
    Demo4(): uniq_val(0) {}
private:
    int uniq_val;
};

pthread_mutex_t g_mutex;


#define THREAD_FUN_IMPL(n)                       \
    void *thread ## n (void * arg) {             \
        for (int i = 0; i < 5; ++i) {            \
            pthread_mutex_lock(&g_mutex);        \
            Demo ## n::Instance()->print();      \
            pthread_mutex_unlock(&g_mutex);      \
            usleep(1);                           \
        }                                        \
    }

THREAD_FUN_IMPL(1)
THREAD_FUN_IMPL(2)
THREAD_FUN_IMPL(3)
THREAD_FUN_IMPL(4)

int main()
{
    pthread_t pid11, pid12, pid2, pid3, pid4;
    pthread_mutex_init(&g_mutex, NULL);
    cout << "TEST-lazy-1: (if multi-threads safe)---------------------- " << endl;
    pthread_create(&pid11, NULL, thread1, NULL);
    pthread_create(&pid12, NULL, thread1, NULL);
    pthread_join(pid11, NULL);
    pthread_join(pid12, NULL);

    cout << "TEST-lazy-stack, hungry, lazy-2 pattern---------------------- " << endl;
    pthread_create(&pid2, NULL, thread2, NULL);
    pthread_create(&pid3, NULL, thread3, NULL);
    pthread_create(&pid4, NULL, thread4, NULL);

    pthread_join(pid2, NULL);
    pthread_join(pid3, NULL);
    pthread_join(pid4, NULL);
    pthread_mutex_destroy(&g_mutex);
    return 0;
}
