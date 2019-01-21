#ifndef _SINGLETON_H_
#define _SINGLETON_H_

template <class T> class Singleton {

public:
    static T* getInstance();

protected:
    Singleton() = default;
    ~Singleton() = default;

private:
    static T* m_pInstance;
};
 
template <class T>
T* Singleton<T>::m_pInstance=nullptr;

template <class T>
T* Singleton<T>::getInstance(){
    if(!m_pInstance) m_pInstance = new T();
    return m_pInstance;
}

#endif