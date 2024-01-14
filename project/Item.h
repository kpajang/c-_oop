//kamelin pajang 186252219
#ifndef SDDS_ITEM_H
#define SDDS_ITEM_H

#include "iProduct.h"
#include "Status.h"

namespace sdds
{
    class Item : public iProduct
    {
    private:
        double price;
        int quantityOnHand;
        int neededQuantity;
        char* description;
        bool linearFormat;

    protected:
        Status state;
        int sku;
        bool linear() const;  // Protected query method to return the linear flag


    public:
        Item();
        Item(const Item& other);
        Item& operator=(const Item& other);
        virtual ~Item();

        // Overridden methods from iProduct

        virtual int readSku(std::istream& istr) override;
        virtual int operator-=(int qty) override;
        virtual int operator+=(int qty) override;
        virtual operator double() const override;
        virtual operator bool() const override;
        virtual int qtyNeeded() const override;
        virtual int qty() const override;
        virtual void linear(bool isLinear) override;
        virtual std::ofstream& save(std::ofstream& ofstr) const override;
        virtual std::ifstream& load(std::ifstream& ifstr) override;
        virtual std::ostream& display(std::ostream& ostr) const override;
        virtual std::istream& read(std::istream& istr) override;
        virtual bool operator==(int sku) const override;
        virtual bool operator==(const char* description) const override;

        void clear(); // Additional helper function
    };
}

#endif // SDDS_ITEM_H