//
// Created by fantomasm on 10/07/24.
//

#ifndef CCOMPANY_H
#define CCOMPANY_H
#include <iostream>
#include "CompareInvoice.h"
class CCompany{
public:
    inline CCompany(const string & name){
        real_name=name;
        canonical_name= change_to_canonical(name);

    }
    string real_name;
    string canonical_name;
    int count_of_paired_invoices=0;
    int count_of_unpaired_invoices=0;
    int obj_value_issued=1;
    void pair_invoices();
    void unpair_invoices();

    unordered_map<string ,CInvoice> CInvoices;
private:

};
#endif //CCOMPANY_H
