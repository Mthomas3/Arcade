//
// Created by styvaether on 3/8/16.
//

#ifndef ARCADE_EXCEPTIONS_HH
#define ARCADE_EXCEPTIONS_HH

#include <string>
#include <exception>

namespace exception
{
    class ArcadeError : public std::exception
    {
    public:
        ArcadeError(const std::string &message, const std::string &component = "Unknown") : _message(message), _component(component) {}
        virtual ~ArcadeError() throw() {}

        const std::string &GetComponent() const { return _component; }
        const char *what() const throw() { return _message.c_str(); }

    private:
        std::string _message;
        std::string _component;
    };

    class DLError : public ArcadeError
    {
    public:
        DLError(const std::string &message) : ArcadeError(message, "Dynamic libraries") {}
    };

    class GraphicError : public ArcadeError
    {
    public:
        GraphicError(const std::string &message) : ArcadeError(message, "Graphic exception") {}
    };
}

#endif //ARCADE_EXCEPTIONS_HH
