//
// Created by fantomasm on 10/07/24.
//

#ifndef COMPAREINVOICE_H
#define COMPAREINVOICE_H
#include <iostream>
#include "CSortOpt.h"
struct CompareInvoice {
public:
    inline CompareInvoice (const CSortOpt& sortBy) : Sort_values(sortBy) {}

    bool operator () (const CInvoice& first, const CInvoice& second);

private:
    CSortOpt Sort_values;

};
#endif //COMPAREINVOICE_H
