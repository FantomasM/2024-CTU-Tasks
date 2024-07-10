//
// Created by fantomasm on 10/07/24.
//

#ifndef CDATE_H
#define CDATE_H
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <deque>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <iterator>
#include <functional>
using namespace std;
class CDate
{
public:
    //---------------------------------------------------------------------------------------------
    inline CDate                         ( int               y,
                                    int               m,
                                    int               d )
            : m_Year ( y ),
              m_Month ( m ),
              m_Day ( d )
    {
    }
    //---------------------------------------------------------------------------------------------
    int                      compare                       ( const CDate     & x ) const;
    //---------------------------------------------------------------------------------------------
    int                      year                          ( void ) const;
    //---------------------------------------------------------------------------------------------
    int                      month                         ( void ) const;
    //---------------------------------------------------------------------------------------------
    int                      day                           ( void ) const;
    //---------------------------------------------------------------------------------------------
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CDate     & x );
    //---------------------------------------------------------------------------------------------
private:
    int16_t                  m_Year;
    int8_t                   m_Month;
    int8_t                   m_Day;
};

string change_to_canonical(string name);
bool operator < (const CDate & x, const CDate &y);
bool operator > (const CDate & x, const CDate &y);
#endif //CDATE_H
