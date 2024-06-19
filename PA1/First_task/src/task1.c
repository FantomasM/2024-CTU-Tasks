#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ARRIVAL 0
#define DEPARTURE 1

#define min_time 5 //minutes

#define max_time 180 //minutes

typedef struct Time_dep_arr{
    int hours;
    int minutes;
    int minutes_all;
    
    
}TIME_DEP_ARR;

int read_entry(int arr_or_dep,TIME_DEP_ARR *train,char sign){
    if(arr_or_dep==ARRIVAL){
        printf("Cas prijezdu vlaku %c:\n",sign);
    }
    else if(arr_or_dep==DEPARTURE){
        printf("Cas odjezdu vlaku %c:\n",sign);
        }
    int hours,minutes;
    if(scanf("%d:%d",&hours,&minutes)!=2){
        return 1;
    }
    if(hours > 23 || hours < 0 ||
    minutes > 59 || minutes < 0){
        return 2;
    }
    train->hours=hours;
    train->minutes=minutes;
    
    train->minutes_all=hours*60+minutes;
    
  //  printf("Hours %d minutes %d minutesall %d \n",train->hours,train->minutes,train->minutes_all);
    return 3;


}
bool transfer_inside(int First_arr,int Second_arr, int Second_dep){


    if((abs(Second_dep-First_arr)>=min_time && ( (First_arr > Second_dep && abs(First_arr-Second_dep) > 24*60-abs(First_arr-Second_dep))||( // First has Problems with midnight
        First_arr < Second_dep && abs(First_arr-Second_dep) < 24*60-abs(First_arr-Second_dep) // NO problems with midnight
    ))) && ((abs(First_arr-Second_arr)<=max_time || max_time >=60*24-abs(First_arr-Second_arr)) ||
    (Second_arr>Second_dep &&(First_arr>Second_arr || First_arr < Second_arr)) || //3 hours control
    (Second_arr < Second_dep && Second_arr < First_arr && First_arr < Second_dep))){ // or diff is negative
        return true;
    }
    return false;


}


void transfer(TIME_DEP_ARR time[6]){
    bool A_B=false,A_C=false,B_A=false,B_C=false,C_A=false,C_B=false;
    TIME_DEP_ARR *A_arr_ptr=&time[0];
    TIME_DEP_ARR *A_dep_ptr=&time[1];
    TIME_DEP_ARR *B_arr_ptr=&time[2];
    TIME_DEP_ARR *B_dep_ptr=&time[3];
    TIME_DEP_ARR *C_arr_ptr=&time[4];
    TIME_DEP_ARR *C_dep_ptr=&time[5];
    if(transfer_inside(A_arr_ptr->minutes_all,B_arr_ptr->minutes_all,B_dep_ptr->minutes_all)){
        A_B=true;
    }
    if(transfer_inside(A_arr_ptr->minutes_all,C_arr_ptr->minutes_all,C_dep_ptr->minutes_all)){
        A_C=true;
    }
    if(transfer_inside(B_arr_ptr->minutes_all,A_arr_ptr->minutes_all,A_dep_ptr->minutes_all)){
        B_A=true;
    }
    if(transfer_inside(B_arr_ptr->minutes_all,C_arr_ptr->minutes_all,C_dep_ptr->minutes_all)){
        B_C=true;
    }
    if(transfer_inside(C_arr_ptr->minutes_all,A_arr_ptr->minutes_all,A_dep_ptr->minutes_all)){
        C_A=true;
    }
    if(transfer_inside(C_arr_ptr->minutes_all,B_arr_ptr->minutes_all,B_dep_ptr->minutes_all)){
        C_B=true;
    }

    if(A_B && A_C){
        printf("Z vlaku A lze prestoupit na vlaky B a C.\n");
    }
    else if(A_B && !A_C){
        printf("Z vlaku A lze prestoupit na vlak B.\n");

    }
    else if (!A_B && A_C)
    {
        printf("Z vlaku A lze prestoupit na vlak C.\n");
    }
    else{
        printf("Z vlaku A nelze prestupovat.\n");

    }

    if(B_A && B_C){
        printf("Z vlaku B lze prestoupit na vlaky A a C.\n");

    }
    else if(B_A && !B_C){
        printf("Z vlaku B lze prestoupit na vlak A.\n");

    }
    else if (!B_A && B_C)
    {
        printf("Z vlaku B lze prestoupit na vlak C.\n");
        
    }
    else{
        printf("Z vlaku B nelze prestupovat.\n");

    }

     if(C_A && C_B){
         printf("Z vlaku C lze prestoupit na vlaky A a B.\n");

    }
    else if(C_A && !C_B){
        printf("Z vlaku C lze prestoupit na vlak A.\n");

    }
    else if (!C_A && C_B)
    {
        printf("Z vlaku C lze prestoupit na vlak B.\n");
    }
    else{
        printf("Z vlaku C nelze prestupovat.\n");

    }

}
int main(void){
    TIME_DEP_ARR * time=(TIME_DEP_ARR*)malloc(6*sizeof(TIME_DEP_ARR));
    //1 A arrival 
    //2 A departure 
    //3 B arrival and so on
     for(int i=0;i<6;i++){
        TIME_DEP_ARR * ptr=&time[i];
        char sign;
        switch (i)
        {
        case 0:
        sign='A';
            break;
        case 1:
         sign='A';
            break;
        case 2:
         sign='B';
            break;
        case 3:
         sign='B';
            break;
        case 4:
         sign='C';
            break;
        case 5:
         sign='C';
            break;                
        
        }
        if((read_entry(i%2,ptr,sign)!=3)){
            printf("Nespravny vstup.\n");
            free(time);
            return EXIT_FAILURE;
        }

    }
    transfer(time);
   
   
    



    free(time);
    return EXIT_SUCCESS;
}