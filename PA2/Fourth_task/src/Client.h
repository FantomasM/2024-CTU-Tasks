//
// Created by fantomasm on 10/07/24.
//

#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>
#include "CMailIterator.h"

class Client{
public:
    inline Client()=default;
    inline Client( const char*  email) : Email(email){}
    inline Client( const str & email) : Email(email){}
    Client(const Client &other);
    Client & operator =(const Client & other);
    void add_input(const CMail & mail);
    void add_output(const CMail & mail);
    void print_input() const;
    void print_output() const;
    str email() const ;
    vector<CMail> input;
    vector<CMail> output;

private:
    str Email;

};
#endif //CLIENT_H
