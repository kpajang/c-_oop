/***********************************************************************
// Final project Milestone 1
// Module: Utils
// File: Utils.h
// Version 1.0
// Author  Fardad Soleimanloo
// Description
//
// Revision History
// -----------------------------------------------------------
// Name     kamelin pajang       186252219     Date            Reason
***********************************************************************/
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring> 

#include <ctime>
#include "Utils.h"
using namespace std;
namespace sdds
{
    Utils ut;
    void Utils::testMode(bool testmode) {
        m_testMode = testmode;
    }
    void Utils::getSystemDate(int* year, int* mon, int* day) {
        if (m_testMode)
        {
            if (day) *day = sdds_testDay;
            if (mon) *mon = sdds_testMon;
            if (year) *year = sdds_testYear;
        }
        else
        {
            time_t t = std::time(NULL);
            tm lt = *localtime(&t);
            if (day) *day = lt.tm_mday;
            if (mon) *mon = lt.tm_mon + 1;
            if (year) *year = lt.tm_year + 1900;
        }
    }
    int Utils::daysOfMon(int month, int year)const {
        int days[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1 };
        int mon = (month >= 1 && month <= 12 ? month : 13) - 1;
        return days[mon] + int((mon == 1) * ((year % 4 == 0) && (year % 100 != 0)) || (year % 400 == 0));
    }


    // allocate memory in destination and copies the source into it
    void Utils::alocpy(char*& destination, const char* source) {
        // Delete existing memory and set to null
        delete[] destination;
        destination = nullptr;

        // If source is not null, allocate new memory and copy the source into it
        if (source)
        {
            destination = new char[strlen(source) + 1];
            strcpy(destination, source);
        }
    }

    // get valid Integer
    int Utils::getint(const char* prompt) const {
        int var;
        bool isValid = false; // Flag to check if the input is valid

        if (prompt != nullptr)
        { // Display the prompt if not null
            cout << prompt;
        }

        while (!isValid)
        { // Continue looping until a valid input is received
            cin >> var; // Attempt to read an integer

            if (cin.fail())
            { // If input is not an integer
                cout << "Invalid Integer, retry: ";
                cin.clear(); // Clear error state
                cin.ignore(1000, '\n'); // Ignore incorrect input until the end of the current line
            }
            else
            {
                isValid = true; // Valid integer entered, set flag to true
            }
        }

        return var;
    }


    // get valid Integer within range
    int Utils::getint(int min, int max, const char* prompt, const char* errMes) const {
        int var;
        bool isInRange = false; // Flag to check if the input is within the range

        do
        {
            var = getint(prompt); // Reuse the previous getint()

            if (var >= min && var <= max)
            {
                isInRange = true; // Input is within range, set flag to true
            }
            else
            {
                // Display error message if the entered integer is not within the acceptable range
                if (errMes != nullptr)
                {
                    cout << errMes << ", retry: ";
                }
                else
                {
                    cout << "Value out of range [" << min << "<=" << var << "<=" << max << "]: ";
                }
            }
        } while (!isInRange); // Continue looping until a valid input within range is received

        cin.clear();
        cin.ignore(1000, '\n');
        return var;
    }

    
}