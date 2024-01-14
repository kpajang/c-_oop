#ifndef SDDS_DATE_H
#define SDDS_DATE_H

#include "Utils.h"
#include "Status.h"
#include <string>
#include <iomanip>

namespace sdds
{
    class Date
    {
        int m_year;
        int m_month;
        int m_day;
        Status m_state;
        bool m_formatted;
        bool validate();
        int uniqueDateValue() const;
    public:
        Date();
        Date(int year, int month, int day);
        bool operator==(const Date& rhs) const;
        bool operator!=(const Date& rhs) const;
        bool operator<(const Date& rhs) const;
        bool operator>(const Date& rhs) const;
        bool operator<=(const Date& rhs) const;
        bool operator>=(const Date& rhs) const;
        const Status& state() const;
        Date& formatted(bool value); // Add const here
        operator bool() const;
        std::ostream& write(std::ostream& ostr) const;
        std::istream& read(std::istream& istr);
    };
    std::ostream& operator<<(std::ostream& ostr, const Date& rhs);
    std::istream& operator>>(std::istream& istr, Date& rhs);
}

#endif // SDDS_DATE_H
