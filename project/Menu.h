//kamelin pajang186252219
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
using namespace std;
namespace sdds
{
    const int max = 15;

    class Menu
    {
        char* content = nullptr;
        unsigned int option;
        void clear();

    public:
        Menu(unsigned int option, const char* content);
      
        ~Menu();
        unsigned int run() const;
    };
}
#endif 