#ifndef SDDS_STATUS_H
#define SDDS_STATUS_H
#include <cstring>
#include <iostream>

namespace sdds
{
    class Status
    {
        char* description;
        int code;

    public:
        // Constructors
        Status(const char* desc = nullptr, int c = 0);
        Status(const Status& other);

        // Copy Assignment Operator
        Status& operator=(const Status& other);

        // Destructor
        ~Status();

        // Assignment to const char*
        Status& operator=(const char* desc);

        // Assignment to int
        Status& operator=(int c);

        // Cast to int
        operator int() const;

        // Cast to const char*
        operator const char* () const;

        // Cast to bool
        operator bool() const;

        // Clear method
        Status& clear();

        // Insertion Operator (Friend)
        friend std::ostream& operator<<(std::ostream& os, const Status& status);

    private:
        // Helper method to set the description
        void setDesc(const char* desc);
    };
} // namespace sdds

#endif 
