//
// Created by fantomasm on 10/07/24.
//

#include "Client.h"

Client::Client(const Client &other){
    input=other.input;
    output=other.output;
    Email=other.Email;
}
Client & Client::operator =(const Client & other){
    if(&other== this){
        return *this;
    }
    input=other.input;
    output=other.output;
    Email=other.Email;
    return *this;
}
void Client::add_input(const CMail & mail){

    input.push_back(mail);

}
void Client::add_output(const CMail & mail){

    output.push_back(mail);

}
void Client::print_input() const{
    for(size_t i=0;i<input.size();i++){
        cout << input[i] << endl;
    }
}
void Client::print_output() const {
    for(size_t i=0;i<output.size();i++){
        cout << output[i] << endl;
    }
}
str Client::email() const {
    return Email;
}