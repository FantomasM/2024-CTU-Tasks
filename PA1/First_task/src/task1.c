#include<stdio.h>
#include<stdlib.h>
#include <stdbool.h>
#include <time.h>
#define ARRIVAL 0
#define DEPARTURE 1

#define Trains_count 3 //Should be >=2

#define min_time 5 //minutes

#define max_time 180 //minutes

static char Train_name[Trains_count]={'A','B','C'};


//Structure to hold train's departures and arrivals
typedef struct Time_dep_arr{
    int hours;
    int minutes;
    int minutes_all;
    
    
}TIME_DEP_ARR;

typedef struct Time_pair{
    TIME_DEP_ARR * arr;
    TIME_DEP_ARR * dep;
}TIME_PAIR;


bool Read_input(int arr_or_dep,TIME_DEP_ARR *train,char sign){
    if(arr_or_dep==ARRIVAL){
        printf("Cas prijezdu vlaku %c:\n",sign);
    }
    else if(arr_or_dep==DEPARTURE){
        printf("Cas odjezdu vlaku %c:\n",sign);
        }
    else{
        return false;
    }
    int hours,minutes;
    //Time of dep/arr should be in format <0-23>:<0-59>
    if(scanf("%d:%d",&hours,&minutes)!=2 
    || hours > 23 || hours < 0 || minutes > 59 || minutes < 0 ){
        return false;
    }
    
    
    train->hours=hours;
    train->minutes=minutes;
    
    train->minutes_all=hours*60+minutes;
    
  
    return true;


}

bool is_transfer_from_first_to_second_possible(int First_arr,int Second_arr, int Second_dep){

    
    if((abs(Second_dep-First_arr)>=min_time && ( (First_arr > Second_dep && abs(First_arr-Second_dep) > 24*60-abs(First_arr-Second_dep))||( // First has Problems with midnight
        First_arr < Second_dep && abs(First_arr-Second_dep) < 24*60-abs(First_arr-Second_dep) // NO problems with midnight
    ))) && ((abs(First_arr-Second_arr)<=max_time || max_time >=60*24-abs(First_arr-Second_arr)) ||
    (Second_arr>Second_dep &&(First_arr>Second_arr || First_arr < Second_arr)) || //3 hours control
    (Second_arr < Second_dep && Second_arr < First_arr && First_arr < Second_dep))){ // or diff is negative
        return true;
    }
    return false;


}
//Finding first element in bool array , which is true
int Find_positive_index(bool * Transfers_bool, int elements_count){
    if(Transfers_bool==NULL){
        return -1;
    }
    for(int i=0;i<elements_count;i++){
        if(Transfers_bool[i]){
            return i;
        }
    }
    return -1;
    
}
void Print_possible_transfers(bool * transfers,int current_index){
    if(transfers==NULL){
        return;
    }
    
    for(int i=0;i<Trains_count;i++){
        int transfers_count=0;
        bool Transfers_bool[Trains_count];
        for(int z=0;z<Trains_count;z++){
            if(i==z){ //We cannot establish transfer to the same train
                Transfers_bool[z]=false;
                continue;
            }
            if(transfers[current_index]){
                transfers_count++;
                Transfers_bool[z]=true;
            }
            else{
                Transfers_bool[z]=false;
            }
            current_index++;
        }
        //No possible transfers
        if(transfers_count==0){
            printf("Z vlaku %c nelze prestupovat.\n",Train_name[i]);
        }
        //One possible transfer can be established
        else if(transfers_count==1){
            //Getting index of this Train to transfer
            int first_pos_index=Find_positive_index(Transfers_bool,Trains_count);

            if(first_pos_index<0 || first_pos_index >=Trains_count || first_pos_index==i){
                printf("Failure occured in transfers evaluation.\n");
                return;
            }

            printf("Z vlaku %c lze prestoupit na vlak %c.\n",Train_name[i],Train_name[first_pos_index]);
        }
        else{
            printf("Z vlaku %c lze prestoupit na vlaky",Train_name[i]);
            int count_of_transfers_printed=0;
            for(int y=0;y<Trains_count;y++){
                if(Transfers_bool[y]){
                    if(count_of_transfers_printed==0){
                        printf(" %c",Train_name[y]);
                        count_of_transfers_printed++;
                    }
                    else{
                        printf(" a %c",Train_name[y]);
                    }

                }
                else{
                    continue;
                }
            }
            printf(".\n");
        }
    }

}



void Find_possible_transfers(TIME_DEP_ARR * time){
    
   //Array with indicators, if transfer from one train to another is possible. For 3 Trains it will have structure like so:
   // 0 - Transfer from First to Second
   // 1 - Transfer from First to Third
   // 2 - Transfer from Second to First
   // 3 - Transfer from Second to Third
   // 4 - Transfer from Third to First
   // 5 - Transfer from Third to Second
   // and so on for another amount of trains
    bool transfers[Trains_count*(Trains_count-1)];

    //Structure with Train arrival and departure
    TIME_PAIR trains_info[Trains_count];

    int counter=0;

    for(int i=0;i<Trains_count*2;i+=2){
        trains_info[counter].arr=&time[i];
        trains_info[counter].dep=&time[i+1];
        counter++;
    }
    
    int current_index=0;

    //Evaluating possible transfers
    for(int i=0;i<Trains_count;i++){
        for(int z=0;z<Trains_count;z++){
            //Transfer to the same train isn't an option
            if(i==z){
                continue;
            }
            //If possible transfer can be established, we indicate it in bool array.
            if(is_transfer_from_first_to_second_possible(trains_info[i].arr->minutes_all,trains_info[z].arr->minutes_all,trains_info[z].dep->minutes_all)){
                transfers[current_index]=true;
            }
            
            else{
                transfers[current_index]=false;
            }
            current_index++;
        }
    }
    current_index=0;
    Print_possible_transfers(transfers,current_index);
    
   
   

}
int main(void){
    TIME_DEP_ARR * time=(TIME_DEP_ARR*)malloc(6*sizeof(TIME_DEP_ARR));
    if(time==NULL){
        printf("Malloc failrue occured.\n");
        return EXIT_FAILURE;
    }
    //1 A arrival 
    //2 A departure 
    //3 B arrival and so on
     for(int i=0;i<Trains_count*2;i++){
        TIME_DEP_ARR * ptr=&time[i];
        char sign;
        sign=Train_name[i/2];
        
        if((!Read_input(i%2,ptr,sign))){
            printf("Nespravny vstup.\n");
            free(time);
            return EXIT_FAILURE;
        }

    }
   Find_possible_transfers(time);
   
   
    



    free(time);
    return EXIT_SUCCESS;
}