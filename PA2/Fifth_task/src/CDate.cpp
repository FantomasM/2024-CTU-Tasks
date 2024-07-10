//
// Created by fantomasm on 10/07/24.
//

#include "CDate.h"
#include <iostream>

int                      CDate::compare                       ( const CDate     & x ) const
{
    if ( m_Year != x . m_Year )
        return m_Year - x . m_Year;
    if ( m_Month != x . m_Month )
        return m_Month - x . m_Month;
    return m_Day - x . m_Day;
}
//---------------------------------------------------------------------------------------------
int                      CDate::year                          ( void ) const
{
    return m_Year;
}
//---------------------------------------------------------------------------------------------
int                      CDate::month                         ( void ) const
{
    return m_Month;
}
//---------------------------------------------------------------------------------------------
int                      CDate::day                           ( void ) const
{
    return m_Day;
}
//---------------------------------------------------------------------------------------------
ostream         & operator <<                   ( ostream         & os,
                                                         const CDate     & x )
{
    char oldFill = os . fill ();
    return os << setfill ( '0' ) << setw ( 4 ) << x . m_Year << "-"
              << setw ( 2 ) << static_cast<int> ( x . m_Month ) << "-"
              << setw ( 2 ) << static_cast<int> ( x . m_Day )
              << setfill ( oldFill );
}
//---------------------------------------------------------------------------------------------
bool operator < (const CDate & x, const CDate &y) {
    if(x.compare(y) > 0){
        return false;
    }
    else{
        return true;
    }
}
bool operator > (const CDate & x, const CDate &y){
    if(y.compare(x) > 0){
        return false;
    }
    else{
        return true;
    }
}
//creating canonical name by changing all leters to lower and then separating words by one space and also one space will be in the end
//For example canonical name for "CaT GarFielD" will be "cat garfield "
string change_to_canonical( string  old){
    std::transform(old.begin(),old.end(),old.begin(),[](unsigned char c){return std::tolower(c);});
    istringstream iss(old);
    vector<string> words;
    copy(istream_iterator<string> (iss),istream_iterator<string>(), back_inserter(words));
    ostringstream oss;
    copy(words.begin(),words.end(), ostream_iterator<string>(oss," "));


    return oss.str();
}
