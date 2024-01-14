//kamelin pajang 186252219
#ifndef SDDS_AID_MAN_H
#define SDDS_AID_MAN_H
#include <iostream>
#include "Menu.h"
#include "iProduct.h"

using namespace std;
namespace sdds
{
    const int sdds_max_num_items = 100;

    class AidMan
    {
        char* m_fileName = nullptr;
        Menu mainMenu;
        iProduct* m_iProduct[sdds_max_num_items] = {};
        int numberofiproduct;
        unsigned int menu() ;
        void clear();
        void nameoffile(const char* fileName = nullptr);

        void save() const;
        void deallocate();

        int list(const char* sub_desc = nullptr); // Menu Item 1 (List Items)

        bool load();                              // Menu item 7 (New/Open Aid Database)
        void exit();                              // Menu Item 0 (Exit)

    public:
        AidMan();
       
        ~AidMan();
        void run();
    };
}
#endif 