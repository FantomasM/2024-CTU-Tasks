//
// Created by fantomasm on 09/07/24.
//

#include "CPersonalAgenda.h"

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

void CPersonalAgenda::Print() {
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

void CPersonalAgenda::add_to_Surname_sort(const Worker &New_Worker,
                             __gnu_cxx::__normal_iterator<Worker *, vector<Worker>> it) {
        if (it == List_by_surname.end()) {
            List_by_surname.push_back(New_Worker);

        } else {
            List_by_surname.insert(it, New_Worker);

        }
    }

    void CPersonalAgenda::add_to_email_sort(const Worker &New_Worker,
                           __gnu_cxx::__normal_iterator<Worker *, vector<Worker>> it) {
        if (it == List_by_email.end()) {
            List_by_email.push_back(New_Worker);

        } else {
            List_by_email.insert(it, New_Worker);

        }
    }
    //------------------------------------------------------------------------
    //methods for checking if user with this name,surname/email isn't already in vectors
    bool CPersonalAgenda::check_for_similarity(const string &name,
                              const string &surname) const {
        Worker tmp(name, surname, basic_email, basic_salary);

        auto lower_surname = lower_bound(List_by_surname.begin(), List_by_surname.end(), tmp, cmpfunc_surname);


        if ((lower_surname != List_by_surname.end() && lower_surname->cmp_name_and_surname(name, surname))

                ) {
            return false;
        }
        return true;
    }

    bool CPersonalAgenda::check_for_similarity(const string &email) const {
        Worker tmp("name", "surname", email, 1234);

        auto lower_email = lower_bound(List_by_email.begin(), List_by_email.end(), tmp, cmpfunc_email);
        if ((lower_email != List_by_email.end() && lower_email->getEmail() == email)) {
            return false;
        }
        return true;
    }
    //-------------------------------------------------------------

    //iterators are pointing to possible location of user in vector found by lower_bound
    bool CPersonalAgenda::check_if_worker_exists(const Worker &find,
                                const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> surname_it,
                                const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> email_it) const {
        if ((surname_it != List_by_surname.end() &&
             surname_it->cmp_name_and_surname(find.getName(), find.getSurname())) ||
            (email_it != List_by_email.end() && email_it->getEmail() == find.getEmail())) {
            return true;
        }
        return false;
    }

    bool CPersonalAgenda::check_if_worker_exists_surname(const Worker &find,
                                        const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> surname_it) const {
        if ((surname_it != List_by_surname.end() &&
             surname_it->cmp_name_and_surname(find.getName(), find.getSurname()))) {
            return true;
        }
        return false;
    }

    bool CPersonalAgenda::check_if_worker_exists_email(const Worker &find,
                                      const __gnu_cxx::__normal_iterator<const Worker *, vector<Worker>> email_it) const {
        if (email_it != List_by_email.end() && email_it->getEmail() == find.getEmail()) {
            return true;
        }
        return false;
    }

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
