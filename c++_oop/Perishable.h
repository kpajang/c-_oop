#ifndef SDDS_PERISHABLE_H
#define SDDS_PERISHABLE_H

#include "Item.h"
#include "Date.h"

namespace sdds
{

    class Perishable : public Item
    {
        char* handlingInstructions;
        Date expiryDate;


    public:
        // Constructors
        Perishable();
        Perishable(const Perishable& other);

        // Copy Assignment Operator
        Perishable& operator=(const Perishable& other);

        // Destructor
        virtual ~Perishable();

        // Virtual Function Overrides
        int readSku(std::istream& istr) override;
        std::ofstream& save(std::ofstream& ofstr) const override;
        std::ifstream& load(std::ifstream& ifstr) override;
        std::ostream& display(std::ostream& ostr) const override;
        std::istream& read(std::istream& istr) override;
        const Date& expiry() const;

        // Additional methods...
    };

} // namespace sdds

#endif // SDDS_PERISHABLE_H