//kamelin pajang 186252219
#include "Item.h"
#include <cstring>
#include <iomanip>
#include <limits>
#include <sstream>  // For std::stringstream
#include "Utils.h"




namespace sdds
{

    // Constructors
    Item::Item() : price(0.0), quantityOnHand(0), neededQuantity(0), description(nullptr), linearFormat(false), sku(0) {}
    Item::Item(const Item& other) : iProduct(other), state(other.state), sku(other.sku) {
        description = nullptr;
        *this = other; // Delegate to copy assignment operator
    }


    // Copy assignment operator
    Item& Item::operator=(const Item& other) {
        if (this != &other)
        {
            delete[] description; // Free existing resource
            if (other.description)
            {
                description = new char[std::strlen(other.description) + 1];
                std::strcpy(description, other.description);
            }
            else
            {
                description = nullptr;
            }
            // Copy other members...
            price = other.price;
            quantityOnHand = other.quantityOnHand;
            neededQuantity = other.neededQuantity;
            linearFormat = other.linearFormat;
            sku = other.sku;
            state = other.state;
        }
        return *this;
    }


    bool Item::linear() const {
        return linearFormat;
    }

    // Destructor
    Item::~Item() {
        delete[] description;
    }

    // Implementation of virtual methods from iProduct
    int Item::readSku(std::istream& istr) {
        int tempSku;
        std::cout << "SKU: ";
        while (true)
        {
            istr >> tempSku;
            if (istr.fail())
            {
                istr.clear();  // Clear the error flag
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore invalid input
                std::cout << "Invalid Integer, retry: ";
            }
            else if (tempSku < 40000 || tempSku > 99999)
            {
                std::cout << "Value out of range [40000<=val<=99999]: ";
            }
            else
            {
                sku = tempSku;  // Set the valid SKU
                break;
            }
        }
        return sku;
    }


    int Item::operator-=(int qty) {
        if (qty <= quantityOnHand)
        {
            quantityOnHand -= qty;
        }
        return quantityOnHand;
    }

    int Item::operator+=(int qty) {
        quantityOnHand += qty;
        return quantityOnHand;
    }

    Item::operator double() const {
        return price;
    }
    Item::operator bool() const {
        return state; //  calls Status::operator bool()
    }


    int Item::qtyNeeded() const {
        return neededQuantity;
    }

    int Item::qty() const {
        return quantityOnHand;
    }

    void Item::linear(bool isLinear) {
        linearFormat = isLinear;
    }

    std::ofstream& Item::save(std::ofstream& ofstr) const {
        if (static_cast<bool>(*this))
        { // Check if the item is in a good state
            ofstr << sku << '\t'
                << (description ? description : "") << '\t'
                << quantityOnHand << '\t'
                << neededQuantity << '\t'
                << std::fixed << std::setprecision(2) << price;
            // Note: No newline is added at the end
        }
        return ofstr;
    }


    std::ifstream& Item::load(std::ifstream& ifstr)
    {
        std::string tempDescription;

        delete[] description; // Free existing resource
        description = nullptr;

        ifstr >> sku;
        if (ifstr.peek() == '\t')
            ifstr.ignore();

        std::getline(ifstr, tempDescription, '\t');
        ut.alocpy(description, tempDescription.c_str()); // Allocate memory for m_description
        if (ifstr.peek() == '\t')
            ifstr.ignore();

        ifstr >> quantityOnHand;
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        ifstr >> neededQuantity;
        if (ifstr.peek() == '\t')
            ifstr.ignore();
        ifstr >> price;

        ifstr.ignore(1); // Discard a single character from the file

        if (ifstr.fail()) // If ifstream is in a bad state
            std::cout << "Input file stream read failed!" << std::endl;

        return ifstr;
    }


    std::ostream& Item::display(std::ostream& ostr) const {
        if (*this)
        { // Check if the item is in a good state
            if (linearFormat)
            {
                // Handling potential null pointers in description
                std::string descriptionString = description ? description : "";
                descriptionString = descriptionString.substr(0, 35); // Truncate to 35 characters

                // Pad with spaces if description is shorter than 35 characters

                if (descriptionString.length() < 35)
                {
                    descriptionString += std::string(35 - descriptionString.length(), ' ');
                }

                // Convert numeric fields to strings
                std::ostringstream qtyOnHandStream, neededQtyStream, priceStream;
                qtyOnHandStream << std::right << std::setw(4) << quantityOnHand;
                neededQtyStream << std::right << std::setw(4) << neededQuantity;
                priceStream << std::right << std::setw(7) << std::fixed << std::setprecision(2) << price;

                // Output the fields with SKU width calculated
                ostr << std::right << std::setw(4) << sku << " | "
                    << descriptionString << " | " // Description with spaces
                    << qtyOnHandStream.str() << " | "
                    << neededQtyStream.str() << " | "
                    << priceStream.str() << " |";
            }
            else
            {
                // Display in descriptive format
                ostr << "AMA Item:\n"
                    << sku << ": " << (description ? description : "") << "\n"
                    << "Quantity Needed: " << neededQuantity << "\n"
                    << "Quantity Available: " << quantityOnHand << "\n"
                    << "Unit Price: $" << std::fixed << std::setprecision(2) << price << "\n"
                    << "Needed Purchase Fund: $" << (neededQuantity - quantityOnHand) * price << "\n";
            }
        }
        else
        {
            // If the item is in a bad state, display the state
            ostr << state;
        }
        return ostr;
    }





    // Reads the remaining attributes of the item
    std::istream& Item::read(std::istream& istr) {
        delete[] description;  // Clear previous description
        description = nullptr;

        std::cout << "AMA Item:\n";

        // Read SKU (assuming it's done by the readSku method)
        std::cout << "SKU: " << sku << std::endl;

        // Read and set Description
        std::cout << "Description: ";
        std::string tempDescription;
        istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::getline(istr, tempDescription);
        if (!tempDescription.empty())
        {
            description = new char[tempDescription.length() + 1];
            std::strcpy(description, tempDescription.c_str());
        }

        // Read and validate Quantity Needed
        std::cout << "Quantity Needed: ";
        while (true)
        {
            if (!(istr >> neededQuantity))
            {
                istr.clear(); // clear the error flag
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the invalid input
                std::cout << "Invalid Integer, retry: ";
            }
            else if (neededQuantity < 1 || neededQuantity > 9999)
            {
                std::cout << "Value out of range [1<=val<=9999]: ";
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }

        // Read and validate Quantity On Hand
        std::cout << "Quantity On Hand: ";
        while (true)
        {
            if (!(istr >> quantityOnHand))
            {
                istr.clear(); // clear the error flag
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore the invalid input
                std::cout << "Invalid Integer, retry: ";
            }
            else if (quantityOnHand < 0 || quantityOnHand > neededQuantity)
            {
                std::cout << "Value out of range [0<=val<=" << neededQuantity << "]: ";
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }
        // Read and validate Price
        // Read and validate Unit Price
        std::cout << "Unit Price: $";
        while (true)
        {
            if (!(istr >> price))
            {
                istr.clear(); // Clear the error flag
                istr.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore the invalid input
                std::cout << "Invalid number, retry: ";
            }
            else if (price < 0.0 || price > 9999.00)
            {
                std::cout << "Value out of range [0.00<=val<=9999.00]: ";
            }
            else
            {
                break; // Valid input, exit the loop
            }
        }



        if (istr.fail())
        {
            state = "Console entry failed!";
        }

        return istr;
    }

    bool Item::operator==(int sku) const {
        return this->sku == sku;
    }

    bool Item::operator==(const char* description) const {
        return description && this->description && std::strstr(this->description, description);
    }

    void Item::clear() {
        delete[] description;
        description = nullptr;
        price = 0.0;
        quantityOnHand = 0;
        neededQuantity = 0;
        linearFormat = false;
        sku = 0;
        state.clear();
    }
}