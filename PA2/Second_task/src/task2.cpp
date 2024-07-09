#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>

using namespace std;
#endif /* __PROGTEST__ */

//constants for temporary Worker
#define basic_name "Error 404"
#define basic_surname "Error 505"
#define basic_salary 666666
#define basic_email  "who_cares@yahoo.com"

class Worker {
public:

    Worker() = default;

    Worker(string Name, string Surname, string Email, unsigned int Salary) : name(std::move(Name)),
                                                                             surname(std::move(Surname)),
                                                                             email(std::move(Email)), salary(Salary) {};

    Worker(const Worker &second) : name(second.name), surname(second.surname), email(second.email),
                                   salary(second.salary) {}

    bool cmp_name_and_surname(const string &Name,
                              const string &Surname) const {

        if (name != Name || surname != Surname) {

            return false;
        }
        return true;

    }

    string getEmail() const {
        return email;
    }

    string getName() const {
        return name;
    }

    string getSurname() const {
        return surname;
    }

    unsigned int getSalary() const {
        return salary;
    }

    void setName(string NewName) {
        name = NewName;
    }

    void setSurname(string NewSurname) {
        surname = NewSurname;
    }

    void setEmail(string NewEmail) {
        email = NewEmail;
    }

    void setSalary(unsigned int NewSalary) {
        salary = NewSalary;
    }

    bool operator!=(const Worker &rhs) const {
        if (name != rhs.name ||
            surname != rhs.surname ||
            email != rhs.email ||
            salary != rhs.salary) {
            return true;
        }
        return false;
    }

private:
    string name;
    string surname;
    string email;
    unsigned int salary = 0;

};
//main compare functions for lower/upper_bound
bool cmpfunc_email(const Worker &lhs,
                   const Worker &rhs) {


    return lhs.getEmail() < rhs.getEmail();

}

bool cmpfunc_surname(const Worker &lhs,
                     const Worker &rhs) {
    if (lhs.getSurname() != rhs.getSurname()) {
        return lhs.getSurname() < rhs.getSurname();
    }
    return lhs.getName() < rhs.getName();

}
//------------------------------------------
class CPersonalAgenda {
public:
    CPersonalAgenda(void);

    ~CPersonalAgenda(void);

    bool add(const string &name,
             const string &surname,
             const string &email,
             unsigned int salary);

    bool del(const string &name,
             const string &surname);

    bool del(const string &email);

    bool changeName(const string &email,
                    const string &newName,
                    const string &newSurname);

    bool changeEmail(const string &name,
                     const string &surname,
                     const string &newEmail);

    bool setSalary(const string &name,
                   const string &surname,
                   unsigned int salary);

    bool setSalary(const string &email,
                   unsigned int salary);

    unsigned int getSalary(const string &name,
                           const string &surname) const;

    unsigned int getSalary(const string &email) const;

    bool getRank(const string &name,
                 const string &surname,
                 int &rankMin,
                 int &rankMax) const;

    bool getRank(const string &email,
                 int &rankMin,
                 int &rankMax) const;

    bool getFirst(string &outName,
                  string &outSurname) const;

    bool getNext(const string &name,
                 const string &surname,
                 string &outName,
                 string &outSurname) const;


    //Printing method for testing
    void Print() {
        cout << "List by surname :" << endl;
        for (size_t i = 0; i < List_by_surname.size(); i++) {
            cout << List_by_surname[i].getName() << " " << List_by_surname[i].getSurname() << " "
                 << List_by_surname[i].getEmail() << " " << List_by_surname[i].getSalary() << endl;
        }
        cout << "List by email :" << endl;
        for (size_t i = 0; i < List_by_email.size(); i++) {
            cout << List_by_email[i].getName() << " " << List_by_email[i].getSurname() << " "
                 << List_by_email[i].getEmail() << " " << List_by_email[i].getSalary() << endl;
        }
    }

private:
    //methods for adding worker into vector, after founding his future position by lower_bound
    void add_to_Surname_sort(const Worker &New_Worker,
                             __gnu_cxx::__normal_iterator<Worker *, vector<Worker>> it) {
        if (it == List_by_surname.end()) {
            List_by_surname.push_back(New_Worker);

        } else {
            List_by_surname.insert(it, New_Worker);

        }
    }

    void add_to_email_sort(const Worker &New_Worker,
                           __gnu_cxx::__normal_iterator<Worker *, vector<Worker>> it) {
        if (it == List_by_email.end()) {
            List_by_email.push_back(New_Worker);

        } else {
            List_by_email.insert(it, New_Worker);

        }
    }
    //------------------------------------------------------------------------
    //methods for checking if user with this name,surname/email isn't already in vectors
    bool check_for_similarity(const string &name,
                              const string &surname) const {
        Worker tmp(name, surname, basic_email, basic_salary);

        auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);


        if ((lower_surname != List_by_surname.end() && lower_surname->cmp_name_and_surname(name, surname))

                ) {
            return false;
        }
        return true;
    }

    bool check_for_similarity(const string &email) const {
        Worker tmp("name", "surname", email, 1234);

        auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);
        if ((lower_email != List_by_email.end() && lower_email->getEmail() == email)) {
            return false;
        }
        return true;
    }
    //-------------------------------------------------------------

    //iterators are pointing to possible location of user in vector found by lower_bound
    bool check_if_worker_exists(const Worker &find,
                                const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> surname_it,
                                const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> email_it) const {
        if ((surname_it != List_by_surname.end() &&
             surname_it->cmp_name_and_surname(find.getName(), find.getSurname())) ||
            (email_it != List_by_email.end() && email_it->getEmail() == find.getEmail())) {
            return true;
        }
        return false;
    }

    bool check_if_worker_exists_surname(const Worker &find,
                                        const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> surname_it) const {
        if ((surname_it != List_by_surname.end() &&
             surname_it->cmp_name_and_surname(find.getName(), find.getSurname()))) {
            return true;
        }
        return false;
    }

    bool check_if_worker_exists_email(const Worker &find,
                                      const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> email_it) const {
        if (email_it != List_by_email.end() && email_it->getEmail() == find.getEmail()) {
            return true;
        }
        return false;
    }
    //-------------------------------------------------------------
    vector<Worker> List_by_surname;
    vector<Worker> List_by_email;
};

CPersonalAgenda::CPersonalAgenda() =default;



CPersonalAgenda::~CPersonalAgenda() =default;



bool CPersonalAgenda::add(const string &name, const string &surname, const string &email, unsigned int salary) {
    //Creating temporary worker to find possible location of worker we want to add
    Worker tmp(name, surname, email, salary);

    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);

    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);

    if (check_if_worker_exists(tmp, lower_surname, lower_email)) {
        return false;
    }

    add_to_Surname_sort(tmp, lower_surname);
    add_to_email_sort(tmp, lower_email);

    return true;

}


bool CPersonalAgenda::del(const string &name, const string &surname) {
    //Creating a temporary worker with default basic email and salary to find possible location of worker we want to delete
    //compare function is using only surname and name, so that's ok
    Worker tmp(name, surname, basic_email, basic_salary);

    //Finding possible location of user in vector sorted by surname/name
    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);

    if (!check_if_worker_exists_surname(tmp, lower_surname)) {
        return false;
    }

    //Finding possible location of user in vector sorted by email and checking  if it really exists for sure
    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), *lower_surname, cmpfunc_email);

    if (!check_if_worker_exists_email(*lower_surname, lower_email)) {
        return false;
    }

    List_by_surname.erase(lower_surname);
    List_by_email.erase(lower_email);
    return true;
}

bool CPersonalAgenda::del(const string &email) {
    //same as in previous del but in inverted order
    Worker tmp(basic_name, basic_surname, email, basic_salary);


    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);
    if (!check_if_worker_exists_email(tmp, lower_email)) {
        return false;
    }


    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), *lower_email, cmpfunc_surname);
    if (!check_if_worker_exists_surname(*lower_email, lower_surname)) {
        return false;
    }

    List_by_surname.erase(lower_surname);
    List_by_email.erase(lower_email);
    return true;
}

bool CPersonalAgenda::changeName(const string &email, const string &newName, const string &newSurname) {

    Worker tmp(basic_name, basic_surname, email, basic_salary);


    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);

    //in this method also we want to check if worker with new name and surname isn't already in our vectors
    if (!check_if_worker_exists_email(tmp, lower_email) ||
        !check_for_similarity(newName, newSurname)) {
        return false;
    }

    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), *lower_email, cmpfunc_surname);

    //checking if worker really exists in both vectors and checking if founded workers in both vectors are the same
    if (!check_if_worker_exists_surname(*lower_email, lower_surname) || *lower_email != *lower_surname) {
        return false;
    }
    //in vector sorted by emails we can just change name and surname for worker, but in vector sorted by surname/name we should change his position
    //by deleting current and inserting new Worker with correct name and surname
    List_by_surname.erase(lower_surname);
    lower_email->setName(newName);
    lower_email->setSurname(newSurname);


    auto lower_surname_change_name = lower_bound(List_by_surname.begin(), List_by_surname.end(), *lower_email,
                                                 cmpfunc_surname);
    add_to_Surname_sort(*lower_email, lower_surname_change_name);

    return true;
}

bool CPersonalAgenda::changeEmail(const string &name, const string &surname, const string &newEmail) {
    //Same as in changeName but again in inverted order
    Worker tmp(name, surname, basic_email, basic_salary);


    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);

    if (!check_if_worker_exists_surname(tmp, lower_surname) || !check_for_similarity(newEmail)) {
        return false;
    }


    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), *lower_surname, cmpfunc_email);

    if (!check_if_worker_exists_email(*lower_surname, lower_email) || *lower_email != *lower_surname) {


        return false;


    }


    lower_surname->setEmail(newEmail);

    List_by_email.erase(lower_email);


    auto lower_surname_change_email = lower_bound(List_by_email.begin(), List_by_email.end(), *lower_surname,
                                                  cmpfunc_email);
    add_to_email_sort(*lower_surname, lower_surname_change_email);

    return true;

}

bool CPersonalAgenda::setSalary(const string &name, const string &surname, unsigned int salary) {
    //Founding worker in both sorted vectors by lower_bound and then changing his salary
    Worker tmp(name, surname, basic_email, salary);

    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);

    if (!check_if_worker_exists_surname(tmp, lower_surname)) {
        return false;
    }


    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), *lower_surname, cmpfunc_email);

    if (!check_if_worker_exists_email(*lower_surname, lower_email) || *lower_surname != *lower_email) {
        return false;
    }


    lower_email->setSalary(salary);
    lower_surname->setSalary(salary);

    return true;
}

bool CPersonalAgenda::setSalary(const string &email, unsigned int salary) {
    //Same as before
    Worker tmp(basic_name, basic_surname, email, salary);


    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);

    if (!check_if_worker_exists_email(tmp, lower_email)) {
        return false;
    }

    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), *lower_email, cmpfunc_surname);

    if (!check_if_worker_exists_surname(*lower_email, lower_surname) || *lower_email != *lower_surname) {
        return false;
    }

    lower_email->setSalary(salary);
    lower_surname->setSalary(salary);
    return true;
}

unsigned int CPersonalAgenda::getSalary(const string &name, const string &surname) const {

    Worker tmp(name, surname, basic_email, basic_salary);

    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);

    if (!check_if_worker_exists_surname(tmp, lower_surname)) {
        return 0;
    }

    return lower_surname->getSalary();
}

unsigned int CPersonalAgenda::getSalary(const string &email) const {
    Worker tmp(basic_name, basic_surname, email, basic_salary);

    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);

    if (!check_if_worker_exists_email(tmp, lower_email)) {
        return 0;
    }
    return lower_email->getSalary();
}

bool CPersonalAgenda::getRank(const string &name, const string &surname, int &rankMin, int &rankMax) const {
    Worker tmp(name, surname, basic_email, basic_salary);

    rankMin = 0;
    rankMax = 0;
    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);

    if (!check_if_worker_exists_surname(tmp, lower_surname)) {
        return false;
    }
    //looking for workers with same salary or with better sallary
    //Rankmin is amount of workers with worse salary
    //Rankmax is amount of workers with same salary or worse
    for (size_t i = 0; i < List_by_surname.size(); i++) {
        if (List_by_surname[i].getSalary() == lower_surname->getSalary()) {
            rankMax++;
            continue;
        }
        if (List_by_surname[i].getSalary() < lower_surname->getSalary()) {
            rankMin++;
            continue;
        }

    }
    //deincrementing rankmax because we count current worker too
    rankMax--;
    rankMax += rankMin;

    return true;
}

bool CPersonalAgenda::getRank(const string &email, int &rankMin, int &rankMax) const {
    //same as in previous version
    Worker tmp(basic_name, basic_surname, email, basic_salary);

    rankMin = 0;
    rankMax = 0;
    auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);

    if (!check_if_worker_exists_email(tmp, lower_email)) {
        return false;
    }

    for (size_t i = 0; i < List_by_surname.size(); i++) {
        if (List_by_surname[i].getSalary() == lower_email->getSalary()) {
            rankMax++;
            continue;
        }
        if (List_by_surname[i].getSalary() < lower_email->getSalary()) {
            rankMin++;
            continue;
        }

    }
    rankMax--;
    rankMax += rankMin;

    return true;
}

bool CPersonalAgenda::getFirst(string &outName, string &outSurname) const {
    //returning first Worker in a sorted vector
    if (!List_by_surname.empty()) {
        outName = List_by_surname[0].getName();
        outSurname = List_by_surname[0].getSurname();
        return true;
    }
    return false;

}

bool CPersonalAgenda::getNext(const string &name, const string &surname, string &outName, string &outSurname) const {

    Worker tmp(name, surname, basic_email, basic_salary);
    //Checking if worker is really exists and checking if previous worker is not the last
    auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);
    if (!check_if_worker_exists_surname(tmp, lower_surname)
        || !(*lower_surname != List_by_surname[List_by_surname.size() - 1])
            ) {
        return false;


    }
    auto higher_surname = upper_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);
    if (higher_surname == List_by_surname.end()) {
        return false;
    }
    outName = higher_surname->getName();
    outSurname = higher_surname->getSurname();
    return true;

}

#ifndef __PROGTEST__

int main(void) {
    string outName, outSurname;
    int lo, hi;
    CPersonalAgenda b3;
    assert (b3.add("!!!", "!", "john", 30000));
    assert (b3.add("!", "!!!", "johnm", 35000));
    assert(b3.getFirst(outName,outSurname) &&
    outName=="!!!" &&
    outSurname=="!");
    CPersonalAgenda b1;
    assert (b1.add("John", "Smith", "john", 30000));
    assert (b1.add("John", "Miller", "johnm", 35000));
    assert (b1.add("Peter", "Smith", "peter", 23000));

    assert (b1.getFirst(outName, outSurname)
            && outName == "John"
            && outSurname == "Miller");
    assert (b1.getNext("John", "Miller", outName, outSurname)
            && outName == "John"
            && outSurname == "Smith");
    assert (b1.getNext("John", "Smith", outName, outSurname)
            && outName == "Peter"
            && outSurname == "Smith");
    assert (!b1.getNext("Peter", "Smith", outName, outSurname));
    assert (b1.setSalary("john", 32000));
    assert (b1.getSalary("john") == 32000);
    assert (b1.getSalary("John", "Smith") == 32000);
    assert (b1.getRank("John", "Smith", lo, hi)
            && lo == 1
            && hi == 1);
    assert (b1.getRank("john", lo, hi)
            && lo == 1
            && hi == 1);
    assert (b1.getRank("peter", lo, hi)
            && lo == 0
            && hi == 0);
    assert (b1.getRank("johnm", lo, hi)
            && lo == 2
            && hi == 2);
    assert (b1.setSalary("John", "Smith", 35000));
    assert (b1.getSalary("John", "Smith") == 35000);
    assert (b1.getSalary("john") == 35000);
    assert (b1.getRank("John", "Smith", lo, hi)
            && lo == 1
            && hi == 2);
    assert (b1.getRank("john", lo, hi)
            && lo == 1
            && hi == 2);
    assert (b1.getRank("peter", lo, hi)
            && lo == 0
            && hi == 0);
    assert (b1.getRank("johnm", lo, hi)
            && lo == 1
            && hi == 2);
    assert (b1.changeName("peter", "James", "Bond"));
    assert (b1.getSalary("peter") == 23000);
    assert (b1.getSalary("James", "Bond") == 23000);
    assert (b1.getSalary("Peter", "Smith") == 0);
    assert (b1.getFirst(outName, outSurname)
            && outName == "James"
            && outSurname == "Bond");
    assert (b1.getNext("James", "Bond", outName, outSurname)
            && outName == "John"
            && outSurname == "Miller");
    assert (b1.getNext("John", "Miller", outName, outSurname)
            && outName == "John"
            && outSurname == "Smith");
    assert (!b1.getNext("John", "Smith", outName, outSurname));
    assert (b1.changeEmail("James", "Bond", "james"));
    assert (b1.getSalary("James", "Bond") == 23000);
    assert (b1.getSalary("james") == 23000);
    assert (b1.getSalary("peter") == 0);
    assert (b1.del("james"));
    assert (b1.getRank("john", lo, hi)
            && lo == 0
            && hi == 1);
    assert (b1.del("John", "Miller"));
    assert (b1.getRank("john", lo, hi)
            && lo == 0
            && hi == 0);
    assert (b1.getFirst(outName, outSurname)
            && outName == "John"
            && outSurname == "Smith");
    assert (!b1.getNext("John", "Smith", outName, outSurname));
    assert (b1.del("john"));
    assert (!b1.getFirst(outName, outSurname));
    assert (b1.add("John", "Smith", "john", 31000));
    assert (b1.add("john", "Smith", "joHn", 31000));
    assert (b1.add("John", "smith", "jOhn", 31000));

    CPersonalAgenda b2;
    assert (!b2.getFirst(outName, outSurname));
    assert (b2.add("James", "Bond", "james", 70000));
    assert (b2.add("James", "Smith", "james2", 30000));
    assert (b2.add("Peter", "Smith", "peter", 40000));
    assert (!b2.add("James", "Bond", "james3", 60000));
    assert (!b2.add("Peter", "Bond", "peter", 50000));
    assert (!b2.changeName("joe", "Joe", "Black"));
    assert (!b2.changeEmail("Joe", "Black", "joe"));
    assert (!b2.setSalary("Joe", "Black", 90000));
    assert (!b2.setSalary("joe", 90000));
    assert (b2.getSalary("Joe", "Black") == 0);
    assert (b2.getSalary("joe") == 0);
    assert (!b2.getRank("Joe", "Black", lo, hi));
    assert (!b2.getRank("joe", lo, hi));
    assert (!b2.changeName("joe", "Joe", "Black"));
    assert (!b2.changeEmail("Joe", "Black", "joe"));
    assert (!b2.del("Joe", "Black"));
    assert (!b2.del("joe"));

    assert (!b2.changeName("james2", "James", "Bond"));
    assert (!b2.changeEmail("Peter", "Smith", "james"));

    assert (!b2.changeName("peter", "Peter", "Smith"));
    assert (!b2.changeEmail("Peter", "Smith", "peter"));
    assert (b2.del("Peter", "Smith"));
    assert (!b2.changeEmail("Peter", "Smith", "peter2"));
    assert (!b2.setSalary("Peter", "Smith", 35000));
    assert (b2.getSalary("Peter", "Smith") == 0);
    assert (!b2.getRank("Peter", "Smith", lo, hi));
    assert (!b2.changeName("peter", "Peter", "Falcon"));
    assert (!b2.setSalary("peter", 37000));
    assert (b2.getSalary("peter") == 0);
    assert (!b2.getRank("peter", lo, hi));
    assert (!b2.del("Peter", "Smith"));
    assert (!b2.del("peter"));
    assert (b2.add("Peter", "Smith", "peter", 40000));
    assert (b2.getSalary("peter") == 40000);

    return EXIT_SUCCESS;
}

#endif /* __PROGTEST__ */
