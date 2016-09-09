#include <iostream>
#include <Core/Core.hh>

using namespace std;

int main(int ac, char **av) {
    if (ac != 2)
        return (-1);
    try
    {
        Core::Core core(av[1]);
        core.loop();
    } catch (exception::ArcadeError &e) {
        std::cerr << "Exception " << e.GetComponent() << ": " << e.what() << std::endl;
    }
    return 0;
}