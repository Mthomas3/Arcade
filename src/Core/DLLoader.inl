//
// Created by styvaether on 3/8/16.
//

#include <iostream>
#include "../../include/Core/Exceptions.hh"

template <typename T>
Loader::DLLoader<T>::DLLoader(const std::string &filename, const std::string &functionName) : _filename(filename), _isOpen(false), _funcName(functionName)
{
}

template <typename T>
Loader::DLLoader<T>::~DLLoader()
{
    if (_isOpen)
        Close();
}

template <typename T>
bool Loader::DLLoader<T>::Open(int flags)
{
    if (!(_handle = dlopen(_filename.c_str(), flags)))
    {
        std::cerr << dlerror() << std::endl;
        throw exception::DLError(std::string("Failed to load the library : ").append(_filename));
    }
    _isOpen = true;
    return true;
}

template <typename T>
bool Loader::DLLoader<T>::Close()
{
    if (!_isOpen)
        return false;
    if (dlclose(_handle) != 0)
        throw exception::DLError(std::string("Failed to close the library : ").append(_filename));
    return true;
}

template  <typename T>
T *Loader::DLLoader<T>::GetInstance() const
{
    T *(*func)();
    T* ret;

    if (!(func = (T *(*)())(dlsym(_handle, _funcName.c_str()))))
        return nullptr;
    ret = func();
    if (!ret)
        return nullptr;
    return (ret);
}
