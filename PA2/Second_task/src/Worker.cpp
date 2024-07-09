//
// Created by fantomasm on 09/07/24.
//

#include "Worker.h"

bool Worker::cmp_name_and_surname(const string &Name,
                             const string &Surname) const {

    if (name != Name || surname != Surname) {

        return false;
    }
    return true;

}
string Worker::getEmail() const {
    return email;
}

string Worker::getName() const {
    return name;
}

string Worker::getSurname() const {
    return surname;
}

unsigned int Worker::getSalary() const {
    return salary;
}

void Worker::setName(string NewName) {
    name = NewName;
}

void Worker::setSurname(string NewSurname) {
    surname = NewSurname;
}

void Worker::setEmail(string NewEmail) {
    email = NewEmail;
}

void Worker::setSalary(unsigned int NewSalary) {
    salary = NewSalary;
}

bool Worker::operator!=(const Worker &rhs) const {
    if (name != rhs.name ||
        surname != rhs.surname ||
        email != rhs.email ||
        salary != rhs.salary) {
        return true;
        }
    return false;
}