//
// Created by styvaether on 12/29/15.
//

#ifndef PULSE_ENGINE_SINGLETON_H
#define PULSE_ENGINE_SINGLETON_H

#include <iostream>

namespace Pulse
{
    namespace Utils
    {
        template <typename T>
        class Singleton
        {
        protected:
            Singleton() { }
            ~Singleton() { }

        public:
            static T *GetInstance() {
                if (_singleton == nullptr)
                {
                    std::cout << "Creating singleton." << std::endl;
                    _singleton = new T;
                }
                return (static_cast<T *>(_singleton));
            }

            static void Destroy()
            {
                if (_singleton != nullptr)
                {
                    delete (_singleton);
                    _singleton = nullptr;
                }
            }

        private:
            static T *_singleton;
        };

        template <typename T>
        T *Singleton<T>::_singleton = nullptr;
    }
}

#endif //PULSE_ENGINE_SINGLETON_H
