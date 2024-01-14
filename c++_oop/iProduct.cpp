//kamelin pajang 186252219
#include "iProduct.h"

namespace sdds
{

    std::istream& operator>>(std::istream& istr, iProduct& product) {
        return product.read(istr);
    }

    std::ostream& operator<<(std::ostream& ostr, const iProduct& product) {
        return product.display(ostr);
    }

} // namespace sdds
