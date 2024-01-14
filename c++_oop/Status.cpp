// Include the header file where the definition of the Status class is declared.
#include "Status.h"

namespace sdds
{

    // Constructor with parameters for description and code.
    // Initializes the description to nullptr and sets the code.
    Status::Status(const char* desc, int c) : description(nullptr), code(c) {
        setDesc(desc); // Set the description using the private member function.
    }

    // Copy constructor: initializes the description to nullptr and copies the code from the other Status object.
    // Then it sets the description using the copied object's description.
    Status::Status(const Status& other) : description(nullptr), code(other.code) {
        setDesc(other.description);
    }

    // Copy assignment operator: checks for self-assignment, then sets the description and code from the other object.
    Status& Status::operator=(const Status& other) {
        if (this != &other) // Self-assignment check.
        {
            setDesc(other.description); // Copy the description.
            code = other.code; // Copy the code.
        }
        return *this; // Return the current object.
    }

    // Destructor: deallocates the dynamically allocated description to prevent memory leaks.
    Status::~Status() {
        delete[] description; // Deallocate the description array.
    }

    // Assignment operator that takes a C-style string (const char*).
    // Sets the current object's description to the provided string.
    Status& Status::operator=(const char* desc) {
        if (desc != description) // Self-assignment check.
        {
            delete[] description; // Deallocate current description.
            if (desc) // If desc is not null,
            {
                description = new char[strlen(desc) + 1]; // Allocate memory for the new description.
                strcpy(description, desc); // Copy the string into the new memory location.
            }
            else
            {
                description = nullptr; // Set description to nullptr if desc is null.
            }
        }
        return *this; // Return the current object.
    }

    // Assignment operator that takes an integer.
    // Sets the status code and clears the description if the code is zero.
    Status& Status::operator=(int c) {
        if (c == 0 && description != nullptr) // If code is zero and description is not null,
        {
            delete[] description; // Deallocate description.
            description = nullptr; // Set description to nullptr.
        }
        code = c; // Set the code.
        return *this; // Return the current object.
    }

    // Conversion operator to int. Allows the Status object to be used where an int is expected.
    // Returns the status code.
    Status::operator int() const {
        return code;
    }

    // Conversion operator to const char*. Allows the Status object to be used where a C-style string is expected.
    // Returns the description.
    Status::operator const char* () const {
        return description;
    }

    // Conversion operator to bool. Returns true if the description is nullptr.
    // This is usually used to check if the Status object is in a 'good' state.
    Status::operator bool() const {
        return description == nullptr;
    }

    // Clears the status, deleting the description and setting the code to 0.
    Status& Status::clear() {
        delete[] description; // Deallocate the description.
        description = nullptr; // Set description to nullptr.
        code = 0; // Reset the code to 0.
        return *this; // Return the current object.
    }

    // Overloaded insertion operator for outputting the Status object to an output stream.
    std::ostream& operator<<(std::ostream& os, const Status& status) {
        if (!status) // If the status conversion to bool returns false (i.e., description is not nullptr),
        {
            if (status.code != 0) // If the code is not zero,
            {
                os << "ERR#" << status.code << ": "; // Output the error code.
            }
            os << (status.description ? status.description : ""); // Output the description or an empty string if null.
        }
        return os; // Return the output stream.
    }

    // Private member function that sets the description of the status.
    // It is used internally by the constructors and assignment operators.
    void Status::setDesc(const char* desc) {
        delete[] description; // Deallocate the current description.
        if (desc && desc[0] != '\0') // If the input string is not null and not empty,
        {
            description = new char[std::strlen(desc) + 1]; // Allocate memory for the new description.
            std::strcpy(description, desc); // Copy the input string into the new memory location.
        }
        else
        {
            description = nullptr; // Set description to nullptr if input string is null or empty.
        }
    }

}