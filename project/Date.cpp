#include "Date.h"
#include <sstream> // Include this at the top of Date.cpp

namespace sdds
{
    // Default constructor initializing members with 0 or appropriate default values and retrieving the system date
    Date::Date() : m_year(0), m_month(0), m_day(0), m_state(), m_formatted(true) {
        // ut.getSystemDate() sets the year, month, and day to the current system date.
        ut.getSystemDate(&m_year, &m_month, &m_day);
        validate(); // Validates the date set by the system date
    }

    // Parameterized constructor that takes year, month, and day and initializes the members with these values
    Date::Date(int year, int month, int day) : m_year(year), m_month(month), m_day(day), m_state(), m_formatted(true) {
        validate(); // Validates the date provided
    }

    // Validates the date and sets an error state if the date is not valid
    bool Date::validate() {
        const int MaxYear = 2030; // Defines the maximum acceptable year
        int currentYear;
        ut.getSystemDate(&currentYear); // Retrieves the current system year
        bool valid = true; // Flag to check the validity of the date

        // Conditions that check if the date provided is valid and set appropriate error states and codes
        if (m_year < currentYear || m_year > MaxYear)
        {
            m_state = "Invalid year in date"; // Error message
            m_state = 1; // Error code
            valid = false; // Validity flag set to false
        }
        else if (m_month < 1 || m_month > 12)
        {
            m_state = "Invalid month in date"; // Error message
            m_state = 2; // Error code
            valid = false; // Validity flag set to false
        }
        else if (m_day < 1 || m_day > ut.daysOfMon(m_month, m_year))
        {
            m_state = "Invalid day in date"; // Error message
            m_state = 3; // Error code
            valid = false; // Validity flag set to false
        }
        else
        {
            m_state.clear(); // Clears the state if date is valid
        }

        return valid; // Returns the validity of the date
    }

    // A function to calculate a unique value for the date for comparison purposes
    int Date::uniqueDateValue() const {
        return m_year * 372 + m_month * 31 + m_day; // Arbitrary calculation to get a unique number for the date
    }

    // Overloaded comparison operators to compare two Date objects based on their unique value
    bool Date::operator==(const Date& rhs) const {
        return uniqueDateValue() == rhs.uniqueDateValue(); // Equal if unique values are the same
    }

    bool Date::operator!=(const Date& rhs) const {
        return !(*this == rhs); // Not equal if unique values are not the same
    }

    bool Date::operator<(const Date& rhs) const {
        return uniqueDateValue() < rhs.uniqueDateValue(); // Less than if this unique value is less than rhs's
    }

    bool Date::operator>(const Date& rhs) const {
        return rhs < *this; // Greater than if rhs is less than this
    }

    bool Date::operator<=(const Date& rhs) const {
        return !(*this > rhs); // Less than or equal to if not greater than rhs
    }

    bool Date::operator>=(const Date& rhs) const {
        return !(*this < rhs); // Greater than or equal to if not less than rhs
    }

    // Returns the current error state of the Date object
    const Status& Date::state() const {
        return m_state;
    }

    // Sets the formatted flag of the Date object and returns a reference to the object
    Date& Date::formatted(bool value) {
        m_formatted = value;
        return *this;
    }

    // Type conversion operator to check if the Date object is in a valid state
    Date::operator bool() const {
        return !m_state; // Returns true if state is empty (no errors)
    }

    // Outputs the date to an ostream depending on whether it's formatted or not
    std::ostream& Date::write(std::ostream& ostr) const {
        if (m_formatted)
        {
            // Formatted output: YYYY/MM/DD
            ostr << m_year << '/'
                << std::setw(2) << std::setfill('0') << m_month << '/'
                << std::setw(2) << std::setfill('0') << m_day;
        }
        else
        {
            // Unformatted output: YYMMDD
            ostr << std::setw(2) << std::setfill('0') << (m_year % 100)
                << std::setw(2) << std::setfill('0') << m_month
                << std::setw(2) << std::setfill('0') << m_day;
        }
        return ostr;
    }


    // Reads the date from an istream and validates the input
    std::istream& Date::read(std::istream& istr) {
        std::string dateStr;
        istr >> dateStr; // Read the entire date as a string

        if (istr.fail())
        {
            m_state = "Invalid date input"; // Set error message
            m_state = 4; // Error code for invalid input
        }
        else
        {
            // Check if the date is in formatted style (contains '/')
            if (dateStr.find('/') != std::string::npos)
            {
                std::istringstream dateStream(dateStr);
                char delimiter;
                dateStream >> m_year >> delimiter >> m_month >> delimiter >> m_day;
                m_formatted = true; // Mark as formatted
            }
            else
            {
                // Handle unformatted style
                int dateValue = std::stoi(dateStr);
                int length = dateStr.length();

                // Parsing the integer value into year, month, and day based on its length
                if (length == 6)
                { // Format is YYMMDD
                    m_year = 2000 + (dateValue / 10000);
                    m_month = (dateValue / 100) % 100;
                    m_day = dateValue % 100;
                }
                else if (length == 8)
                { // Format is YYYYMMDD
                    m_year = dateValue / 10000;
                    m_month = (dateValue / 100) % 100;
                    m_day = dateValue % 100;
                }
                else
                {
                    m_state = "Invalid date format";
                    istr.setstate(std::ios::failbit); // Signal an error
                }
            }

            // Validate the date after parsing
            if (!validate())
            {
                istr.setstate(std::ios::failbit); // Set the failbit if the date is invalid
            }
        }

        return istr;
    }


    // Overloads the insertion operator to write a Date object to an ostream
    std::ostream& operator<<(std::ostream& ostr, const Date& rhs) {
        return rhs.write(ostr); // Calls the write method of the Date class
    }

    // Overloads the extraction operator to read a Date object from an istream
    std::istream& operator>>(std::istream& istr, Date& rhs) {
        return rhs.read(istr); // Calls the read method of the Date class
    }
}
