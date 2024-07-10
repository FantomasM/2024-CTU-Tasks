#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */
/*
 They took my lower_bound , they left me without vector, they even took STRING. But can it stop me from implementing my own vector, lower_bound and string?

 */

template <typename T>
class vector{
public:
    vector() :M_Size(2), M_Capacity(0),m_Data(new T[2]){

    }
    vector(const vector& other) : M_Size(other.M_Size), M_Capacity(other.M_Capacity), m_Data(new T[other.M_Size]){

        for (size_t i = 0; i < other.M_Capacity; i++) {
            m_Data[i] = other.m_Data[i];
        }
    }
    ~vector(){


           delete [] m_Data;

    }
     [[nodiscard]] size_t size() const {
        return M_Capacity;
    }
    size_t count_of_members () const{
        return M_Capacity-1;
    }
    void push_back(const T& obj){

        if(M_Size<=M_Capacity){
            realloc();
        }
        m_Data[M_Capacity]=obj;
        M_Capacity++;

    }
    void insert(size_t position, const T & value){
        if(position > M_Size-1){
            push_back(value);

        }
        else{
            if(M_Size<=M_Capacity){
                realloc();
            }
            for(size_t i=M_Capacity;i>position;i--){
                m_Data[i]=m_Data[i-1];
            }
            m_Data[position]=value;
            M_Capacity++;
        }
    }
    T & operator[](size_t index) const {
        return m_Data[index];
    }
    bool empty() const{
        if(M_Capacity==0){
        return true;
                }
        else{
            return false;
        }
    }
    void clear(){
        delete []m_Data;
        m_Data=new T[2];
        M_Size=2;
        M_Capacity=0;
    }
    vector & operator =(const vector & src){
        if(&src==this ){
            return *this;
        }
        clear();
        realloc(src.M_Size);
        for(size_t i=0;i<src.M_Capacity;i++){
           m_Data[i]=src.m_Data[i];
        }
        M_Capacity=src.M_Capacity;
        return *this;

    }
    void realloc(size_t new_size){

       while(M_Size < new_size){
           M_Size*=1.5;
       }

        T * tmp=new T[M_Size];
        for(size_t i=0;i<M_Capacity;i++){
            tmp[i]=m_Data[i];
        }
        delete[] m_Data;
        m_Data=tmp;
    }
    bool operator ==(const vector & src) const {
        if(M_Capacity!=src.M_Capacity){
            return false;
        }
        for(size_t i=0;i<M_Capacity;i++){
            if(m_Data[i]!=src.m_Data[i]){
                return false;
            }
        }
        return true;
    }
    void realloc(){
        M_Size*=1.5;
        //cout << M_Size << endl;
        T * tmp=new T[M_Size];
        for(size_t i=0;i<M_Capacity;i++){
            tmp[i]=m_Data[i];
        }
        delete[] m_Data;
        m_Data=tmp;
    }
    void Print_vector() const{
        for(size_t i=0;i<M_Capacity;i++){
            cout << m_Data[i] << endl;
        }
    }
private:
    size_t M_Size=2;
    size_t M_Capacity=0;
    T * m_Data;

};
class str{
public:
     str()=default ;

    str(const str & copy){

        delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
        max=2;
        size_t tmpmax=max;
        while(copy.size+size+1>tmpmax){
            tmpmax*=1.5;
        }
        if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars,copy.array_of_chars,copy.size);
        size=copy.size;


    }
    str(const char * char_array) {
         size_t arraysize= strlen(char_array);
         size_t tmpmax=max;
         while(arraysize+size+1>tmpmax){
             tmpmax*=1.5;
         }
         if(tmpmax!=max) {
             Realloc(tmpmax);
         }


        for(size_t i=0;i< arraysize;i++){
            array_of_chars[i]=char_array[i];
            size++;
        }
    }


    ~str(){
        delete [] array_of_chars;
    }
    void Realloc(size_t num){
        while (num >= max){
            max*=1.5;
        }
        char * tmp=new char[max];
        memcpy(tmp,array_of_chars,size);

        delete [] array_of_chars;
        array_of_chars=tmp;



    }

    void Realloc(){

            max*=1.5;

            char * tmp=new char[max];
       memcpy(tmp,array_of_chars,size);

            delete [] array_of_chars;
            array_of_chars=tmp;



    }
    str & operator + (const char* src){
        str source(src);
       size_t tmpmax=max;
        while(source.size+size+1>tmpmax){
            tmpmax*=1.5;
        }if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars+size,src,source.size);

        size+=source.size;
        array_of_chars[size]='\0';

        return *this;
    }

    str & operator +=(const char * src){
        return *this+src;
    }
     bool operator ==(const char * second) const{
        str sec(second);
         if(sec.size!= size){
             return false;
         }
        int switch_ride=strncmp(array_of_chars,second,size);
         if (switch_ride == 0) {

             return true;
         }
         else{
             return false;


         }
    }
    bool operator ==(const str & second)const {

       if(second.size!= size ){
           return false;
       }


          int strcm = strncmp(array_of_chars, second.array_of_chars,size);

        if (strcm == 0) {

            return true;
        }
        else{
                return false;


        }
    }
    bool operator !=(const str &second)const{
        return !(second==array_of_chars);
    }
    bool operator !=(const char* second)const{
        return second != array_of_chars;
    }

    friend ostream & operator << (ostream & os , const str &stri){
        for(size_t i=0;i< stri.size;i++){
            os <<stri.array_of_chars[i];
        }

        return os;
    }
    char operator [](size_t index) const{
        return array_of_chars[index];

    }
    str & operator =(  const str & sec ) {
         if(&sec== this){
             return *this;
         }
        delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
        max=2;
        size_t tmpmax=max;
        while(sec.size+size+1>tmpmax){
            tmpmax*=1.5;
        }
        if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars,sec.array_of_chars,sec.size);
        size=sec.size;
        return *this;
   }

    str & operator =(  const char * sec ) {
        if(sec== this->array_of_chars){
            return *this;
        }
        delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
        max=2;
        size_t secsize= strlen(sec);
        size_t tmpmax=max;
        while(secsize+size+1>tmpmax){
            tmpmax*=1.5;
        }
        if(tmpmax!=max) {
            Realloc(tmpmax);
        }
        memcpy(array_of_chars,sec,secsize);
        size=secsize;
        return *this;
    }
   void clear(){
         delete []array_of_chars;
        size=0;
        array_of_chars=new char [2];
        max=2;
    }

    int compare(const str & second) const {
        const size_t length1 = size;
        const size_t length2 = second.size;
        const size_t commonLength = (length1 < length2 ? length1 : length2);
        const int cmp = memcmp(array_of_chars, second.array_of_chars, commonLength);
        if (cmp != 0) {
            return cmp < 0 ? -1 : 1;
        }
        return (length1 == length2) ? 0 : (length1 < length2) ? -1 : 1;

    }
    size_t size=0;
    char * array_of_chars=new char[2];
private:

    size_t max=2;

};



bool operator<(const str& lhs, const str& rhs)  {
    return lhs.compare(rhs) < 0;
}
bool operator <=(const str& lhs , const str &rhs){
    return lhs < rhs || lhs==rhs;
}
class CMail
{
  public:
    CMail(){


    };
                             CMail                         ( const char      * from,
                                                             const char      * to,
                                                             const char      * body );
    bool                     operator ==                   ( const CMail     & x ) const{
        if(Source==x.Source &&  Destination==x.Destination && Body==x.Body){

            return true;
        }
        return false;
    }
    CMail  reverse(const CMail & y){
        CMail newcmail=y;
        str tmp=y.Source;
        newcmail.Source=Destination;
        newcmail.Destination=tmp;
        return newcmail;
    }
    friend ostream         & operator <<                   ( ostream         & os,
                                                              const CMail     & m ){

        os << "From: " << m.Source << ", To: " << m.Destination << ", Body: " << m.Body;
        return os;
    }

    bool from_comparsion(const str & from2) const{
        if(from2==Source){
            return true;
        }
        return false;
    }
    bool to_comparsion(const str & from2) const{
        if(from2==Destination){
            return true;
        }
        return false;
    }
    CMail(const CMail & other) : Source(other.Source) , Destination(other.Destination),Body(other.Body){}
    CMail & operator=(const CMail & other){
        if(this==&other){
            return *this;
        }
        Source=other.Source;
        Destination=other.Destination;
        Body=other.Body;
        return *this;
    }

    str Source;
    str Destination;
    str Body;
private:


};



CMail::CMail(const char *from, const char *to, const char *body)  : Source(from) , Destination(to), Body(body){}




class CMailIterator 
{


  public:
    explicit                 operator bool                 ( void ) const{


           if (index<=base.count_of_members() && ok== true && base.size()!= 0){
               return true;
           }
        return false;


    }
    bool                     operator !                    ( void ) const{


       if(  base.size()==0 || index > base.count_of_members()) {
           return true;
       }

        return false;

    }
    const CMail            & operator *                    ( void ) const{
        return base[index];
    }
    CMailIterator          & operator ++                   ( void ){

        index++;

        return *this;

    }
    CMailIterator(vector<CMail>& vec) : base(vec){

    }
    CMailIterator() : ok(false),index(0){}

    vector<CMail> base;

    bool ok= true;
  private:


    size_t index=0;


};

class Client{
public:
    Client()=default;
    Client( const char*  email) : Email(email){

    }
    Client( const str & email) : Email(email){

    }
    Client(const Client &other){
        input=other.input;
        output=other.output;
        Email=other.Email;
    }
    Client & operator =(const Client & other){
        if(&other== this){
            return *this;
        }
        input=other.input;
        output=other.output;
        Email=other.Email;
        return *this;
    }
    void add_input(const CMail & mail){

        input.push_back(mail);

    }
    void add_output(const CMail & mail){

        output.push_back(mail);

    }
    void print_input() const{
        for(size_t i=0;i<input.size();i++){
            cout << input[i] << endl;
        }
    }
    void print_output() const {
        for(size_t i=0;i<output.size();i++){
            cout << output[i] << endl;
        }
    }
    str email() const {
        return Email;
    }
    vector<CMail> input;
    vector<CMail> output;

private:
    str Email;

};
class CMailServer 
{
  public:
                             CMailServer                   ( void );
                             CMailServer                   ( const CMailServer & src );
    CMailServer            & operator =                    ( const CMailServer & src );
                             ~CMailServer                  ( void );
    void                     sendMail                      ( const CMail     & m );
    CMailIterator            outbox                        ( const char      * email ) const ;

    CMailIterator            inbox                         ( const char      * email ) const;
    void Print(){
        for(size_t i=0;i<base.size();i++){
            cout << "email: " <<base[i].email() <<endl << "input: -----------------------------------------------------------" <<endl;
            base[i].print_input();
            cout << "output: ---------------------------------------------------------------------" << endl;
            base[i].print_output();
            cout << "///////////////////////////////////////////////////////" << endl;
        }
    }

    vector<Client> base;
  private:


};
CMailServer::~CMailServer()=default;


size_t Lower_bound(const vector<Client> & base, str array) {
   size_t mid;
   size_t low=0;
   size_t high=base.size();
   while(low  <high){
       mid=low+(high-low)/2;
       if(base[mid].email() < array){
           low=mid+1;
       }

       else{
           high=mid;
       }
   }
   if(low < base.size() && base[low].email() < array ){
       low++;
   }
    return low;
}

CMailServer::CMailServer()=default;




CMailIterator CMailServer::outbox(const char *email) const {

    str em(email);
    size_t position= Lower_bound(base,em);


        if( position <=base.count_of_members() &&base[position].email()==email){

                return CMailIterator{base[position].output};




        }
        else{
            return CMailIterator{};
        }



}

CMailServer::CMailServer(const CMailServer & src) : base(src.base) {}






CMailIterator CMailServer::inbox(const char *email) const {


    str em(email);
    size_t position= Lower_bound(base,em);
        if( position <=base.count_of_members() && base[position].email()==email){

                return CMailIterator{base[position].input};




        }
        else{
            return CMailIterator{};
        }



}


CMailServer &CMailServer::operator=(const CMailServer &src)  {
    if(&src==this){
        return *this;
    }
    base=src.base;

    return *this;
}

void CMailServer::sendMail(const CMail &m) {




    size_t position= Lower_bound(base,m.Source);


        if(position <=base.count_of_members() && m.from_comparsion(base[position].email())){
            base[position].add_output(m);

        }
        else{
            Client Lilychad(m.Source);
            base.insert(position,Lilychad);
            base[position].add_output(m);
        }

    size_t position2= Lower_bound(base,m.Destination);





        if(position2 <=base.count_of_members() && m.to_comparsion(base[position2].email())){
            base[position2].add_input(m);


        }
        else{
            Client Lilychad(m.Destination);
            base.insert(position2,Lilychad);
            base[position2].add_input(m);
        }



   
}
#ifndef __PROGTEST__

bool                         matchOutput                   ( const CMail     & m,
                                                             const char      * str )
{
  ostringstream oss;
  oss << m;
  return oss . str () == str;
}

int main ( void )
{
  char from[100], to[100], body[1024];



  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );

  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  CMailServer s0;
  s0 . sendMail ( CMail ( "john", "peter", "some important mail" ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "thomas", sizeof ( to ) );
  strncpy ( body, "another important mail", sizeof ( body ) );
  s0 . sendMail ( CMail ( from, to, body ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "alice", sizeof ( to ) );
  strncpy ( body, "deadline notice", sizeof ( body ) );
  s0 . sendMail ( CMail ( from, to, body ) );
  s0 . sendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
  s0 . sendMail ( CMail ( "peter", "alice", "PR bullshit" ) );

  CMailIterator i0 = s0 . inbox ( "alice" );

  assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );

  assert ( matchOutput ( *i0,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i0,  "From: peter, To: alice, Body: PR bullshit" ) );

  assert ( ! ++i0 );

  CMailIterator i1 = s0 . inbox ( "john" );
  assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  assert ( matchOutput ( *i1,  "From: alice, To: john, Body: deadline confirmation" ) );
  assert ( ! ++i1 );

  CMailIterator i2 = s0 . outbox ( "john" );
  assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  assert ( matchOutput ( *i2,  "From: john, To: peter, Body: some important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  assert ( matchOutput ( *i2,  "From: john, To: thomas, Body: another important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i2,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ! ++i2 );

  CMailIterator i3 = s0 . outbox ( "thomas" );

  assert ( ! i3 );

  CMailIterator i4 = s0 . outbox ( "steve" );
  assert ( ! i4 );

  CMailIterator i5 = s0 . outbox ( "thomas" );

  s0 . sendMail ( CMail ( "thomas", "boss", "daily report" ) );

  assert ( ! i5 );

  CMailIterator i6 = s0 . outbox ( "thomas" );
  assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  assert ( matchOutput ( *i6,  "From: thomas, To: boss, Body: daily report" ) );
  assert ( ! ++i6 );

  CMailIterator i7 = s0 . inbox ( "alice" );
  s0 . sendMail ( CMail ( "thomas", "alice", "meeting details" ) );

  assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i7,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i7,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ! ++i7 );

  CMailIterator i8 = s0 . inbox ( "alice" );
  assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i8,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i8,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i8,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ! ++i8 );

  CMailServer s1 ( s0 );
  s0 . sendMail ( CMail ( "joe", "alice", "delivery details" ) );
  s1 . sendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  CMailIterator i9 = s0 . inbox ( "alice" );
  assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i9,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i9,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i9,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i9,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ! ++i9 );

  CMailIterator i10 = s1 . inbox ( "alice" );
  assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i10,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i10,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i10,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  assert ( matchOutput ( *i10,  "From: sam, To: alice, Body: order confirmation" ) );
  assert ( ! ++i10 );

  CMailServer s2;
  s2 . sendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  CMailIterator i11 = s2 . inbox ( "alice" );
  assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  assert ( matchOutput ( *i11,  "From: alice, To: alice, Body: mailbox test" ) );
  assert ( ! ++i11 );

  s2 = s0;
  s0 . sendMail ( CMail ( "steve", "alice", "newsletter" ) );
  s2 . sendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  CMailIterator i12 = s0 . inbox ( "alice" );
  assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i12,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i12,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i12,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i12,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  assert ( matchOutput ( *i12,  "From: steve, To: alice, Body: newsletter" ) );
  assert ( ! ++i12 );

  CMailIterator i13 = s2 . inbox ( "alice" );
  assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( matchOutput ( *i13,  "From: john, To: alice, Body: deadline notice" ) );
  assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( matchOutput ( *i13,  "From: peter, To: alice, Body: PR bullshit" ) );
  assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( matchOutput ( *i13,  "From: thomas, To: alice, Body: meeting details" ) );
  assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( matchOutput ( *i13,  "From: joe, To: alice, Body: delivery details" ) );
  assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  assert ( matchOutput ( *i13,  "From: paul, To: alice, Body: invalid invoice" ) );
  assert ( ! ++i13 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
