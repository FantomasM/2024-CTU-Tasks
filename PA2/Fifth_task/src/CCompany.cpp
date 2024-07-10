//
// Created by fantomasm on 10/07/24.
//

#include "CCompany.h"

void CCompany::pair_invoices(){
    count_of_paired_invoices++;
    count_of_unpaired_invoices--;
}
void CCompany::unpair_invoices(){
    count_of_paired_invoices--;
    count_of_unpaired_invoices++;
}