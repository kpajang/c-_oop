#include <iostream>
#include "Menu.h"
#include "Utils.h"
//kamelin pajang 186252219
using namespace std;

namespace sdds
{
    void Menu::clear() {
        if (content != nullptr)
        {
            delete[] content;
            content = nullptr;
        }
    }

    Menu::Menu(unsigned int numOpt, const char* text)
        : content(nullptr), option(numOpt) { // Initialize content and option using an initializer list
        if (numOpt <= max && text != nullptr)
        { // Check if valid and then allocate and copy text
            ut.alocpy(content, text);
        }
        else
        {
            clear(); // If invalid, ensure the object is in a valid state
        }
    }

    Menu::~Menu() {
        clear();
    }

    unsigned int Menu::run() const {
        if (content)
        {
            cout << content;
        }
        cout << "0- Exit" << endl << "> ";
        return ut.getint(0, option);
    }
}
