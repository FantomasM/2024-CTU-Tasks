//
// Created by fantomasm on 09/07/24.
//
#pragma once
#ifndef WORKER_H
#define WORKER_H

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
class Worker {
public:

    inline Worker() = default;

    inline Worker(string Name, string Surname, string Email, unsigned int Salary) : name(std::move(Name)),
                                                                             surname(std::move(Surname)),
                                                                             email(std::move(Email)), salary(Salary) {};

    inline Worker(const Worker &second) : name(second.name), surname(second.surname), email(second.email),
                                   salary(second.salary) {}

    bool cmp_name_and_surname(const string &Name,
                              const string &Surname) const ;

    string getEmail() const;

    string getName() const;

    string getSurname() const;

    unsigned int getSalary() const;

    void setName(string NewName);

    void setSurname(string NewSurname);

    void setEmail(string NewEmail);

    void setSalary(unsigned int NewSalary);

    bool operator!=(const Worker &rhs) const;

private:
    string name;
    string surname;
    string email;
    unsigned int salary = 0;

};
#endif //WORKER_H
