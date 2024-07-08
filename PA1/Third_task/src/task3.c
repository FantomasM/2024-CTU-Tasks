#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
typedef struct
{
  int m_TotalDays;
  int m_WorkDays;
} TResult;
#endif /* __PROGTEST__ */
bool is_leap(int year){
  if( (year%4==0 && year%100!=0) || (year%4==0 && year%100==0 && year%400==0)){
    return true;
  }
  return false;
}


int Days_in_month(int year, int month){
 switch (month)
 {
 case 1:return 31;break;
  case 2:
  if(is_leap(year))return 29;
  return 28;break;
  case 3:return 31;break;
  case 4:return 30;break;
  case 5:return 31;break;
  case 6:return 30;break;
  case 7:return 31;break;
  case 8:return 31;break;
  case 9:return 30;break;
  case 10:return 31;break;
  case 11:return 30;break;
  case 12:return 31;break;
  default:return 666; // hell's number, can't occur after validating input
 
 }
}


// 1.1.2000 is saturday 7.1.2000 is friday 
//if year is leap then 1.1.2001 will be monday, if no, then sunday
//0 saturday, 1 sunday and so on
int shift_count(int year,int month , int day){
  int shift=0;
  
  for(int i=2000;i<year;i++){
    if(is_leap(i)){
      shift+=2;
    }
    else{
      shift+=1;
    }
  }
  return shift%7;


}
//difference between two dates in one year , second date is starting sooner
int diff_between_dates(int year,int month,int day,int sec_month, int sec_day){
int cur_sum=0;
for(int i=sec_month+1;i<month;i++){
  cur_sum+=Days_in_month(year,i);
}
if(sec_month!=month){
cur_sum+=(Days_in_month(year,sec_month)-sec_day);
}
else{
  cur_sum-=sec_day;
}
cur_sum+=day;

return cur_sum;
}

int cur_weekday(int y, int m, int d ){
  int shift=shift_count(y,m,d); // if 1.1.2000 was monday then our current year has shift for 1.1.year...
  int days_from_years_beg=diff_between_dates(y,m,d,1,1);
  
  days_from_years_beg=days_from_years_beg%7;
  
  return ((days_from_years_beg+shift)%7);
}




//holidays     1.1,  1.5,  8.5,  5.7,  6.7, 28.9,  28.10,  17.11,  24.12, 25.12 a 26.12
bool isWorkDay ( int y, int m, int d )
{
  
  //wrong input
  if((Days_in_month(y,m)<d) || y <2000 || m > 12 || m <1 || d <1){
    
    return false;
  }
  //holidays dates
  if((d==1 && m==1) || (d==1 && m==5) || (d==8 && m==5) || (d==5 && m==7) || (d==6 && m==7) || (d==28 && m==9) || (d==28 && m==10) 
  || (d==17 && m==11) || (d==24 && m==12) || (d==25 && m==12) || (d==26 && m==12)  ){
    return false;
  }
  
  
  
  //0 saturday, 1 sunday,2 monday and so on
  if((cur_weekday(y,m,d))>1){
    return true;
  }
  return false;

}
int Working_days_on_week (int weekday,int year,int month,int day,bool reverse){ //Only for week of one month
  //0 saturday, 1 sunday,2 monday and so on
  int working_days=0;
  
  if(!reverse){
  while (weekday!=2)
  {
    if(cur_weekday(year,month,day)>1){
      working_days++;
    }
    if(weekday==6){
      weekday=0;
      day++;
      continue;
    }
    else{
      weekday++;
    }
    day++;
    
  }
  }
  
  

  else{
  while (weekday!=1)
  {
    if(cur_weekday(year,month,day)>1){
      working_days++;
    }
    if(weekday==0){
      weekday=6;
      day--;
      continue;
    }
    else{
      weekday--;
    }
    day--;
    
  }
  }
  
  return working_days;
 
  
}
//reverse false = count of days from this day to end of week, reverse true= count of days from this day to start of week 
int count_of_days_to_end_of_week(int weekday, bool reverse){
  switch (reverse)
  {
  case false:
    switch (weekday)
  {
  case 2:return 7;break;
  case 3:return 6;break;
    case 4:return 5;break;
    case 5:return 4;break;
    case 6:return 3;break;
    case 0:return 2;break;
    case 1:return 1;break;
  
  }
    break;
  default:  
   switch (weekday)
  {
  case 2:return 1;break;
  case 3:return 2;break;
    case 4:return 3;break;
    case 5:return 4;break;
    case 6:return 5;break;
    case 0:return 6;break;
    case 1:return 7;break;
  
  }
  
    break;
  }
  return 7;
  
}

//good holiday is a holiday on a working day
int count_of_good_holidays(int year){
    int count=0;
    //0 saturday, 1 sunday ,2 monday and so on
    if(cur_weekday(year,1,1)>1){
      count++;
    }
    if(cur_weekday(year,5,1)>1){
      count++;
    }
    if(cur_weekday(year,5,8)>1){
      count++;
    }
    if(cur_weekday(year,7,5)>1){
      count++;
    }
    if(cur_weekday(year,7,6)>1){
      count++;
    }
    if(cur_weekday(year,9,28)>1){
      count++;
    }
    if(cur_weekday(year,10,28)>1){
      count++;
    }
    if(cur_weekday(year,11,17)>1){
      count++;
    }
    if(cur_weekday(year,12,24)>1){
      count++;
    }
    if(cur_weekday(year,12,25)>1){
      count++;
    }
    if(cur_weekday(year,12,26)>1){
      count++;
    }
    
    return count;
}
TResult countDaysPerOneYear(int year){
  TResult tmp_res[1];
  if(is_leap(year)){
    tmp_res[0].m_TotalDays=366;
  }
  else{
    tmp_res[0].m_TotalDays=365;
  }
  
  int tmp_total_days_count=tmp_res[0].m_TotalDays;

  int tmp_Working_days=0;

 
  int count_of_weeks;
  //0 saturday, 1 sunday ,2 monday and so on
  int start_week_day=cur_weekday(year,1,1);
  if(start_week_day!=2){
    tmp_Working_days+=Working_days_on_week(start_week_day,year,1,1,false);
    tmp_total_days_count-=count_of_days_to_end_of_week(start_week_day,false);
  }
  

  int end_week_day=cur_weekday(year,12,31);
  if(end_week_day!=1){
    tmp_Working_days+=Working_days_on_week(end_week_day,year,12,31,true);
    tmp_total_days_count-=count_of_days_to_end_of_week(end_week_day,true);
  }
  
  count_of_weeks=tmp_total_days_count/7;
  tmp_Working_days+=(count_of_weeks*5);
 
  tmp_Working_days-=count_of_good_holidays(year);

  tmp_res[0].m_WorkDays=tmp_Working_days;
  return tmp_res[0];
  
  
}
//workdays count <first,second> 
int workdays_count(int year, int month, int day, int sec_month, int sec_day){
  int workdays=0;
  for(int i=month;i<=sec_month;i++){
    int z=1,lim=Days_in_month(year,i);
    if(i==month){
      z=day;
    }
    if(i==sec_month){
      lim=sec_day;
    }
    
    for(;z<=lim;z++){
      if(isWorkDay(year,i,z)){
        workdays++;
      }
    }
  }
  
  return workdays;


}

TResult countDays ( int y1, int m1, int d1,
                    int y2, int m2, int d2 )
{
  TResult res[1];
  //Validating Input
  if(y2<y1 || (y2==y1 && m2<m1 ) || (y2==y1 && m2==m1 && d2 <d1) || y1 < 2000 || y2 <2000 || m1 < 1 || m1 >12 || d1 < 1 
  || d1 > Days_in_month(y1,m1) || d2 < 1 || d2 > Days_in_month(y2,m2) || m2<1 || m2 >12 ){
    res[0].m_TotalDays=-1;
    res[0].m_WorkDays=-1;
    return res[0];
  }
  
  if(y2-y1 >0){
    int year1_a_d=diff_between_dates(y1,12,31,m1,d1)+1;
    int year1_w_d=workdays_count(y1,m1,d1,12,31);
    int year_mid_a_d=0; //all days between two years without counting y1 and y2
    int year_mid_w_d=0; //same for workdays;
    TResult tmp;
    for(int i=y1+1;i<y2;i++){
      tmp=countDaysPerOneYear(i);
      year_mid_a_d+=tmp.m_TotalDays;
      year_mid_w_d+=tmp.m_WorkDays;
    }
    int year2_a_d=diff_between_dates(y2,m2,d2,1,1)+1;
    int year2_w_d=workdays_count(y2,1,1,m2,d2);
    res[0].m_TotalDays=year1_a_d+year_mid_a_d+year2_a_d;
    res[0].m_WorkDays=year1_w_d+year_mid_w_d+year2_w_d;
    return res[0];

  }
  if(y2==y1){
    res[0].m_TotalDays=diff_between_dates(y1,m2,d2,m1,d1)+1;
    res[0].m_WorkDays=workdays_count(y1,m1,d1,m2,d2);
    return res[0];
  }
  else{
     int year1_a_d=diff_between_dates(y1,12,31,m1,d1)+1;
    int year1_w_d=workdays_count(y1,m1,d1,12,31);
     int year2_a_d=diff_between_dates(y2,m2,d2,1,1)+1;
    int year2_w_d=workdays_count(y2,1,1,m2,d2);
    res[0].m_TotalDays=year1_a_d+year2_a_d;
    res[0].m_WorkDays=year1_w_d+year2_w_d;
    return res[0];

  }



}


#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{
  TResult r;

  assert ( isWorkDay ( 2023, 10, 10 ) );

  assert ( ! isWorkDay ( 2023, 11, 11 ) );

  assert ( ! isWorkDay ( 2023, 11, 17 ) );

  assert ( ! isWorkDay ( 2023, 11, 31 ) );

  assert ( ! isWorkDay ( 2023,  2, 29 ) );

  assert ( ! isWorkDay ( 2004,  2, 29 ) );

  assert ( isWorkDay ( 2008,  2, 29 ) );

  assert ( ! isWorkDay ( 2001,  2, 29 ) );

  assert ( ! isWorkDay ( 1996,  1,  2 ) );

  r = countDays ( 2023, 11,  1,
                  2023, 11, 30 );
  assert ( r . m_TotalDays == 30 );
  assert ( r . m_WorkDays == 21 );

  r = countDays ( 2023, 11,  1,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 17 );
  assert ( r . m_WorkDays == 12 );

  r = countDays ( 2023, 11,  1,
                  2023, 11,  1 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 1 );

  r = countDays ( 2023, 11, 17,
                  2023, 11, 17 );
  assert ( r . m_TotalDays == 1 );
  assert ( r . m_WorkDays == 0 );

  r = countDays ( 2023,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 365 );
  assert ( r . m_WorkDays == 252 );

  r = countDays ( 2024,  1,  1,
                  2024, 12, 31 );
  assert ( r . m_TotalDays == 366 );
  assert ( r . m_WorkDays == 254 );

  r = countDays ( 2000,  1,  1,
                  2023, 12, 31 );
  assert ( r . m_TotalDays == 8766 );
  assert ( r . m_WorkDays == 6072 );

  r = countDays ( 2001,  2,  3,
                  2023,  7, 18 );
  assert ( r . m_TotalDays == 8201 );
  assert ( r . m_WorkDays == 5682 );

  r = countDays ( 2021,  3, 31,
                  2023, 11, 12 );
  assert ( r . m_TotalDays == 957 );
  assert ( r . m_WorkDays == 666 );

  r = countDays ( 2001,  1,  1,
                  2000,  1,  1 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );

  r = countDays ( 2001,  1,  1,
                  2023,  2, 29 );
  assert ( r . m_TotalDays == -1 );
  assert ( r . m_WorkDays == -1 );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
