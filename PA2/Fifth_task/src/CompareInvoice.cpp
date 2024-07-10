//
// Created by fantomasm on 10/07/24.
//

#include "CompareInvoice.h"

bool CompareInvoice::operator () (const CInvoice& first, const CInvoice& second) {
        for (const auto &x: Sort_values.Sort_values) {
            switch (x) {
                case sorting::BY_DATE_HIGH:
                    //comparing by date if ascending is true

                    if (first.date().compare(second.date()) < 0) {
                        return true;
                    }


                        //if comparison says that values are equal, then go to next compare function/alternative compare function
                        if (first.date().compare(second.date()) == 0) {
                            continue;
                        }

                        break;
                        case sorting::BY_DATE_LOW:
                            //comparing by date in inverted order
                            if (second.date().compare(first.date()) < 0) {
                                return true;
                            }
                        if (first.date().compare(second.date()) == 0) {
                            continue;
                        }
                        break;
                        case sorting::BY_BUYER_HIGH: {
                            //copying names of buyers to strings and change them to lower because we sort case-insensitive
                            string first_buyer = first.buyer();
                            string second_buyer = second.buyer();
                            transform(first_buyer.begin(), first_buyer.end(), first_buyer.begin(), ::tolower);
                            transform(second_buyer.begin(), second_buyer.end(), second_buyer.begin(), ::tolower);
                            //comparing by buyer name if ascending is true

                            if (first_buyer < second_buyer) {
                                return true;
                            }
                            if (first_buyer == second_buyer) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_BUYER_LOW: {
                            //copying names of buyers to strings and change them to lower because we sort case-insensitive
                            string first_buyer = first.buyer();
                            string second_buyer = second.buyer();
                            transform(first_buyer.begin(), first_buyer.end(), first_buyer.begin(), ::tolower);
                            transform(second_buyer.begin(), second_buyer.end(), second_buyer.begin(), ::tolower);
                            //comparing by buyer name in inverted order

                            if (first_buyer > second_buyer) {
                                return true;
                            }


                            if (first_buyer == second_buyer) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_SELLER_HIGH: {
                            //copying names of sellers to strings and change them to lower because we sort case-insensitive
                            string first_seller = first.seller();
                            string second_seller = second.seller();
                            transform(first_seller.begin(), first_seller.end(), first_seller.begin(), ::tolower);
                            transform(second_seller.begin(), second_seller.end(), second_seller.begin(), ::tolower);
                            //comparing by seller name if ascending is true

                            if (first_seller < second_seller) {
                                return true;
                            }


                            if (first_seller == second_seller) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_SELLER_LOW: {
                            //copying names of sellers to strings and change them to lower because we sort case-insensitive
                            string first_seller = first.seller();
                            string second_seller = second.seller();
                            transform(first_seller.begin(), first_seller.end(), first_seller.begin(), ::tolower);
                            transform(second_seller.begin(), second_seller.end(), second_seller.begin(), ::tolower);
                            //comparing by seller in inverted order
                            if (first_seller > second_seller) {
                                return true;
                            }


                            if (first_seller == second_seller) {
                                continue;
                            }


                            break;
                        }
                        case sorting::BY_AMOUNT_HIGH:
                            //comparing by amount, if ascending is true

                            if (first.amount() < second.amount()) {
                                return true;
                            }


                        if (first.amount() == second.amount()) {
                            continue;
                        }

                        break;
                        case sorting::BY_AMOUNT_LOW:
                            //comparing by amount in inverted order
                            if (first.amount() > second.amount()) {
                                return true;
                            }
                        if (first.amount() == second.amount()) {
                            continue;
                        }
                        break;
                        case sorting::BY_VAT_HIGH:
                            //comparing by vat if ascending is true

                            if (first.vat() < second.vat()) {
                                return true;
                            }


                        if (first.vat() == second.vat()) {
                            continue;
                        }

                        break;
                        case sorting::BY_VAT_LOW:
                            //comparing by vat in inverted order

                            if (first.vat() > second.vat()) {
                                return true;
                            }


                        if (first.vat() == second.vat()) {
                            continue;
                        }

                        break;
                        case sorting::DEFAULT:
                            //wrong value, no sorting :(
                            break;
                    }

                    return false;
            }

            return first.number() < second.number();
        }