#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include "AidMan.h"
#include "Date.h"
#include "Utils.h"
#include "Perishable.h"
using namespace std;
namespace sdds
{
    // Shows the main menu and returns the user's choice.
    unsigned int AidMan::menu() {
        int year, month, day;
        sdds::ut.getSystemDate(&year, &month, &day); // Get the current system date

        // Display the header information including date and filename
        std::cout << "Aid Management System\n";
        std::cout << "Date: ";
        std::cout << year << "/";
        std::cout << (month < 10 ? "0" : "") << month << "/";
        std::cout << (day < 10 ? "0" : "") << day << "\n";
        std::cout << "Data file: " << (m_fileName ? m_fileName : "No file") << std::endl;
        cout << "---------------------------------\n";

        return mainMenu.run(); // Display the main menu and get the user's choice
    }
    void AidMan::clear()
    {
        delete[] m_fileName;
        m_fileName = nullptr;
    }

    void AidMan::nameoffile(const char* fileName)
    {
        if (fileName != nullptr)
            ut.alocpy(m_fileName, fileName);
        else
            clear();
    }

    AidMan::AidMan()
        : mainMenu(7, "1- List Items\n2- Add Item\n3- Remove Item\n4- Update Quantity\n5- Sort\n6- Ship Items\n7- New/Open Aid Database\n---------------------------------\n")
    {
        nameoffile();
    }



    AidMan::~AidMan() {
        clear();
    }

    void AidMan::save() const
    {
        if (m_fileName != nullptr)
        {
            ofstream ofstr(m_fileName, ios::out);
            for (int i = 0; i < numberofiproduct; i++)
                m_iProduct[i]->save(ofstr) << endl;
            ofstr.flush();
            ofstr.close();
        }
    }

    void AidMan::deallocate()
    {
        for (int i = 0; m_iProduct[i]; i++)
            delete m_iProduct[i];
        delete[] m_fileName;
        m_fileName = nullptr;
        numberofiproduct = 0;
    }
    bool AidMan::load() {
        save(); // Save current data
        deallocate(); // Prepare for new data

        cout << "\n****New/Open Aid Database****\n"
            << "Enter file name: ";
        string fileName;
        getline(cin, fileName);
        ut.alocpy(m_fileName, fileName.c_str());

        ifstream ifstr;
        if (m_fileName != nullptr)
        {
            ifstr.open(m_fileName);
        }

        if (!ifstr)
        {
            cout << (m_fileName != nullptr ? "Failed to open " : "File name is null. ")
                << (m_fileName != nullptr ? m_fileName : "") << " for reading!\n"
                << "Would you like to create a new data file?\n1- Yes!\n0- Exit\n> ";

            if (ut.getint(0, 1) == 1)
            {
                ofstream ofstr(m_fileName);
                if (ofstr)
                {
                    cout << "New file created: " << m_fileName << endl;
                }
                else
                {
                    cout << "Failed to create the file: " << m_fileName << endl;
                    return false;
                }
            }
            else
            {
                cout << "Aborted!\n";
                delete[] m_fileName;
                m_fileName = nullptr;
                return false;
            }
        }


        int loadedCount = 0;
        char type;
        while (loadedCount < sdds_max_num_items && (type = ifstr.peek()) != EOF)
        {
            iProduct* product = nullptr;

            // Streamlined logic for determining product type
            if ((type >= '1' && type <= '3') || (type >= '4' && type <= '9'))
            {
                product = (type >= '1' && type <= '3') ? new Perishable() : new Item();
            }
            else
            {
                ifstr.ignore(1000, '\n'); // Skip invalid record
                continue;
            }

            if (product && product->load(ifstr))
            {
                m_iProduct[loadedCount++] = product;
            }
            else
            {
                delete product; // Delete if load unsuccessful
            }
        }

        numberofiproduct = loadedCount;
        cout << (numberofiproduct > 0 ? numberofiproduct : 0) << " records loaded!\n\n";
        return numberofiproduct > 0;
    }



    int AidMan::list(const char* sub_desc) {
        int i = 0;

        // Print the header for the list only once
        cout << "\n****List Items****" << endl
            << " ROW |  SKU  | Description                         | Have | Need |  Price  | Expiry" << endl
            << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

        if (sub_desc == nullptr)
        { // list all items
            for (i = 0; i < numberofiproduct; i++)
            {
                cout.setf(ios::right);
                cout.width(4);

                cout << i + 1;
                cout << " | ";
                cout.unsetf(ios::right);

                m_iProduct[i]->linear(true);
                m_iProduct[i]->display(cout) << endl;
            }
        }
        else
        { // list only matched desc items
            for (i = 0; i < numberofiproduct; i++)
            {
                if (*m_iProduct[i] == sub_desc)
                {
                    cout.setf(ios::right); cout.width(4);    cout.fill(' ');  // Set the fill character to a space
                    cout << i + 1;
                    cout << " | ";
                    cout.unsetf(ios::right);

                    m_iProduct[i]->linear(true);
                    m_iProduct[i]->display(cout);
                    cout << endl;
                }
            }
        }

        cout << "-----+-------+-------------------------------------+------+------+---------+-----------" << endl;

        // Additional logic for user interaction
        if (numberofiproduct > 0)
        {
            cout << "Enter row number to display details or <ENTER> to continue:" << endl
                << "> ";
            if (cin.peek() != '\n')
            {
                int number = ut.getint(1, i) - 1;
                m_iProduct[number]->linear(false);
                m_iProduct[number]->display(cout);
                cout << endl;
            }
            else
            {
                cin.ignore();
            }
            cout << endl;
        }
        else
        {
            cout << "The list is empty!" << endl;
        }

        return i;
    }





    void AidMan::exit()
    {
        cout << "Exiting Program!" << endl;
        save();
        deallocate();
    }

    void AidMan::run() {
        const int ExitOption = 0;
        const int LoadDatabaseOption = 7;

        unsigned int option;
        do
        {
            option = menu(); // Display the menu and get user choice

            // If no file is loaded and the selected option requires a file, force load option
            if (option != ExitOption && option != LoadDatabaseOption && m_fileName == nullptr)
            {
                option = LoadDatabaseOption;
            }

            switch (option)
            {
            case ExitOption:
                exit();
                break;
            case 1:
                list();
                break;
            case 2:
                // add();
                std::cout << "Add Item";
                break;
            case 3:
                // remove();
                std::cout << "Remove Item";
                break;
            case 4:
                // update();
                std::cout << "Update Quantity";
                break;
            case 5:
                // sort();
                std::cout << "Sort";
                break;
            case 6:
                // ship();
                std::cout << "Ship Items";
                break;
            case LoadDatabaseOption:
                load();
                break;
            default:
                std::cout << "Invalid Option. Please try again.";
            }

        } while (option != ExitOption); // Loop until the user selects the exit option
    }

}