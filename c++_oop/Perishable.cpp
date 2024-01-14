#include "Perishable.h"
#include <cstring>
#include <iostream>
#include <limits>

namespace sdds
{

    Perishable::Perishable() : Item(), handlingInstructions(nullptr), expiryDate() {}

    Perishable::Perishable(const Perishable& other) : Item(other), expiryDate(other.expiryDate) {
        if (other.handlingInstructions)
        {
            handlingInstructions = new char[std::strlen(other.handlingInstructions) + 1];
            std::strcpy(handlingInstructions, other.handlingInstructions);
        }
        else
        {
            handlingInstructions = nullptr;
        }
    }

    Perishable& Perishable::operator=(const Perishable& other) {
        if (this != &other)
        {
            Item::operator=(other);
            expiryDate = other.expiryDate;
            delete[] handlingInstructions;
            if (other.handlingInstructions)
            {
                handlingInstructions = new char[std::strlen(other.handlingInstructions) + 1];
                std::strcpy(handlingInstructions, other.handlingInstructions);
            }
            else
            {
                handlingInstructions = nullptr;
            }
        }
        return *this;
    }
    // In Item class


    Perishable::~Perishable() {
        delete[] handlingInstructions;
    }

    // Constant query for expiry date
    const Date& Perishable::expiry() const {
        return expiryDate;
    }

    // Virtual Overrides

    // Override readSku function
    int Perishable::readSku(std::istream& istr) {
        int tempSku;
        std::cout << "SKU: ";
        istr >> tempSku;
        while (istr.fail() || tempSku < 10000 || tempSku > 39999)
        {
            istr.clear();
            istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Value out of range [10000<=val<=39999]: ";
            istr >> tempSku;
        }
        sku = tempSku; // Set the valid SKU
        return sku;
    }

    // Override save function
    std::ofstream& Perishable::save(std::ofstream& ofstr) const {
        Item::save(ofstr);
        ofstr << '\t' << (handlingInstructions ? handlingInstructions : "") << '\t';
        Date tempExpiryDate = expiryDate;
        tempExpiryDate.formatted(false); // Set to formatted for non-linear display
        ofstr << tempExpiryDate;        
        return ofstr;
    }
    std::ifstream& Perishable::load(std::ifstream& ifstr)
    {
        std::string handling;

        Item::load(ifstr); // Call the load function of the base class

        delete[] handlingInstructions;
        handlingInstructions = nullptr;

        if (ifstr.peek() != '\t') // Check if the very first character is not a tab
        {
            std::getline(ifstr, handling, '\t');
            ut.alocpy(handlingInstructions, handling.c_str());
        }

        if (ifstr.peek() == '\t')
            ifstr.ignore();

        ifstr >> expiryDate;

        if (ifstr.peek() == '\n') // Ignore the newline
            ifstr.ignore();

        if (ifstr.fail()) // If the ifstream object has failed
        {
            // Handle the failure if needed
        }

        return ifstr;
    }






    // Override display function
   // Override display function
    std::ostream& Perishable::display(std::ostream& ostr) const {
        if (linear())
        {

            // Call to base class display function. Make sure Item::display properly formats the output.
            Item::display(ostr);

            // Handling instructions: Display an asterisk or a space
            ostr << (handlingInstructions && handlingInstructions[0] != '\0' ? '*' : ' ');


            // Display the expiry date in formatted form as per example (YYYY/MM/DD)
            Date tempExpiryDate = expiryDate;
            tempExpiryDate.formatted(true); // Set to formatted
            ostr << tempExpiryDate;

        }
        else
        {
            // Non-linear mode display
            ostr << "Perishable ";
            Item::display(ostr); // Make sure this includes proper formatting and spacing

            ostr << "Expiry date: ";
            Date tempExpiryDate = expiryDate;
            tempExpiryDate.formatted(true); // Set to formatted for non-linear display
            ostr << tempExpiryDate;

            if (handlingInstructions && handlingInstructions[0] != '\0')
            {
                ostr << "\nHandling Instructions: " << handlingInstructions;
            }

            // Adjust the field width and fill for numerical values to avoid extra zeroes
            ostr << std::setw(1) << std::setfill(' ') << "\n";
        }
        return ostr;
    }



    // Override read function
    // Override read function
    // Override read function
    std::istream& Perishable::read(std::istream& istr) {
        Item::read(istr);
        delete[] handlingInstructions; // Clear previous handling instructions
        std::cout << "Expiry date (YYMMDD): ";

        // Temporarily set date formatting to unformatted
        expiryDate.formatted(false);

        istr >> expiryDate;
        istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        // Reset date formatting to default (with slashes)
        expiryDate.formatted(true);

        std::cout << "Handling Instructions, ENTER to skip: ";
        std::string tempInstructions;
        std::getline(istr, tempInstructions);
        if (!tempInstructions.empty())
        {
            // Remove leading zeros from handling instructions
            const char* instructions = tempInstructions.c_str();
            while (*instructions == '0' && *(instructions + 1) != '\0')
            {
                instructions++;
            }
            handlingInstructions = new char[strlen(instructions) + 1];
            std::strcpy(handlingInstructions, instructions);
        }
        else
        {
            handlingInstructions = nullptr;
        }
        return istr;
    }


    // Additional methods as needed...
}