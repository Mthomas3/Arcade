//
// Created by styvaether on 3/8/16.
//

#ifndef ARCADE_DLLOADER_HH
#define ARCADE_DLLOADER_HH

#include <dlfcn.h>

namespace Loader
{
    template<typename T>
    class DLLoader
    {
    public:
        DLLoader(const std::string &filename, const std::string &functionName);
        virtual ~DLLoader();

        bool Open(int flags = RTLD_LAZY);
        bool Close();

        T *GetInstance() const;

    private:
        std::string _filename;
        std::string _funcName;
        bool _isOpen;
        void *_handle;
    };
}

# include "../../src/Core/DLLoader.inl"

#endif //ARCADE_DLLOADER_HH
