#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <float.h>
#include <cassert>

typedef struct date{
    int day;
    int month;
    int year;
}date_t;
///----------------------------------------------------------------------------------
typedef struct review
{
    char * review_text;
    int length_of_text;
    int allocated_space;
    int score;
}review_t;
///----------------------------------------------------------------------------------
typedef struct Day{
    date_t review_date[1];
    review_t * reviews;
    int reviews_count;
    int allocated_space;
    double avg;
}Day_t;
///----------------------------------------------------------------------------------
typedef struct list_of_days
{
    Day_t * reviews_day;
    int reviews_count;
    int days_count;
    int allocated_days;
    date_t last_date[1];
}list_of_days_t;
///----------------------------------------------------------------------------------
void init(list_of_days_t * ptr){
    ptr->allocated_days=2;
    ptr->reviews_day=(Day_t*)malloc(ptr->allocated_days*sizeof(Day_t));
    //Inicialization of days
    for(int i=0;i<ptr->allocated_days;i++){
        ptr->reviews_day[i].reviews=(review_t*)malloc(2*sizeof(review_t));
        ptr->reviews_day[i].allocated_space=2;
        ptr->reviews_day[i].reviews_count=0;
    }
    //Setting date to default wrong values to avoid situations with uninitialized values
    ptr->last_date->day=-1;
    ptr->last_date->month=-1;
    ptr->last_date->year=-1;

    ptr->days_count=0;
    ptr->reviews_count=0;



}
///----------------------------------------------------------------------------------
// Gregorian calendar version
bool is_leap(int year){
  if( (year%4==0 && year%100!=0) || (year%4==0 && year%100==0 && year%400==0)){
    return true;
  }
  return false;
}
///----------------------------------------------------------------------------------
int Days_in_month(int year, int month){ //Input is validates and there is no possibility for month to be not in interval <1,12>
 switch (month)
 {
 
  case 2:if(is_leap(year))return 29;
  return 28;
  case 4:return 30;
  case 6:return 30;
  case 9:return 30;
  case 11:return 30;
  default:return 31;
  
 
 }
}
///----------------------------------------------------------------------------------
void init_review(review_t * ptr){ //Inicialization of review
    ptr->allocated_space=2;
    ptr->length_of_text=0;
    ptr->review_text=(char *)malloc(ptr->allocated_space*sizeof(char));


}
///----------------------------------------------------------------------------------
void deallocate_review_t(review_t * ptr){ //Deallocation of review
    ptr->allocated_space=0;
    ptr->length_of_text=0;
    free(ptr->review_text);
}
///----------------------------------------------------------------------------------
void dealloc(list_of_days_t * ptr){ //Deallocation of structure
    for(int i=0;i<ptr->allocated_days;i++){
        for(int z=0;z<ptr->reviews_day[i].reviews_count;z++){
            free(ptr->reviews_day[i].reviews[z].review_text);
        }
        free(ptr->reviews_day[i].reviews);
    }
    free(ptr->reviews_day);
    free(ptr);



}
///----------------------------------------------------------------------------------
void review_text_realloc(review_t * ptr){ //Safe realloc function for review's text
    ptr->allocated_space=ptr->allocated_space*2;
    ptr->review_text=(char*)realloc(ptr->review_text,ptr->allocated_space*(sizeof(char)));
}
///----------------------------------------------------------------------------------
void reviews_day_realoc( Day_t * ptr){ //Safe realloc function for reviews
    ptr->allocated_space=ptr->allocated_space*2;
    ptr->reviews=(review_t*)realloc(ptr->reviews,ptr->allocated_space*(sizeof(review_t)));
}
///----------------------------------------------------------------------------------
void Day_t_realoc(list_of_days_t * ptr){ //Safe realloc function for days
    ptr->allocated_days=ptr->allocated_days*2;
    ptr->reviews_day=(Day_t*)realloc(ptr->reviews_day,ptr->allocated_days*(sizeof(Day_t)));
    //Inicialization of new days
    //Cycle is starting from first added day, which is allocated_days/2 
    for(int i=ptr->allocated_days/2;i<ptr->allocated_days;i++){
        ptr->reviews_day[i].reviews=(review_t*)malloc(2*sizeof(review_t));
        ptr->reviews_day[i].allocated_space=2;
        ptr->reviews_day[i].reviews_count=0;
    }
}
///----------------------------------------------------------------------------------
bool check_right_date(list_of_days_t * ptr, date_t * date){
    
    
    //No such date
    if(date->day <= 0 || date->day > Days_in_month(date->year,date->month) || date->month <= 0 || date->month > 12){
        return false;
    }
    //We cannot compare with last date if List is empty
    if(ptr->days_count==0){
        return true;
    }
    //Review date is starting after last review
    if(ptr->last_date->year > date->year || (ptr->last_date->year == date->year && ptr->last_date->month > date->month) || 
    (ptr->last_date->year == date->year && ptr->last_date->month == date->month && ptr->last_date->day > date->day) ){
        return false;
    }
    return true;
}
///----------------------------------------------------------------------------------
void review_assign(review_t * to_assign, review_t * assigning_review){
    to_assign->review_text=assigning_review->review_text;
    to_assign->allocated_space=assigning_review->allocated_space;
    to_assign->length_of_text=assigning_review->length_of_text;
    to_assign->score=assigning_review->score;
}
///----------------------------------------------------------------------------------
void new_day_create(list_of_days_t * ptr, date_t * date, review_t * review){
    //Assiging tmp date to date of new day
    ptr->reviews_day[ptr->days_count].review_date->year=date->year;
    ptr->reviews_day[ptr->days_count].review_date->month=date->month;
    ptr->reviews_day[ptr->days_count].review_date->day=date->day;

    //Assigning new review and increasing counter
    ptr->reviews_day[ptr->days_count].reviews[0]=*review;
    ptr->reviews_day[ptr->days_count].reviews_count=1;
    ptr->reviews_day[ptr->days_count].avg=review->score;



}
///----------------------------------------------------------------------------------
void add_review_to_list(list_of_days_t * ptr,date_t * date, review_t * review){
    ///Finding reviews with same date, according to our system same date is the last system or there is no such date

    //Setting last date to date of last object
    ptr->last_date[0]=date[0];

        
        //Adding cur review to list of reviews for this day if this day is already in list
         //We cant check if last date is the same as current for adding if days count is 0
        if(ptr->days_count!=0){
        int i=ptr->days_count-1; //Relict of old for cycle | last index in array with days
        //Checking if last date is the same as date on current review to add
        if(ptr->reviews_day[i].review_date->year==date->year && ptr->reviews_day[i].review_date->month ==date->month && ptr->reviews_day[i].review_date->day ==date->day){
            //Increasing size in case of little space
            if(ptr->reviews_day[i].allocated_space==ptr->reviews_day[i].reviews_count){
               
                reviews_day_realoc(&(ptr->reviews_day[i]));
            }
            //Adding new review for last day
            review_assign(&ptr->reviews_day[i].reviews[ptr->reviews_day[i].reviews_count],review);
          
            


            //Increasing count of reviews for last day and for global counter in List_of_days
            ptr->reviews_day[i].reviews_count++;
            ptr->reviews_count++;
            //Storing avg for every day
            double num_to_div=0;
            for(int z=0;z<ptr->reviews_day[i].reviews_count;z++){
                num_to_div+=ptr->reviews_day[i].reviews[z].score;
            }
            ptr->reviews_day[i].avg=num_to_div/ptr->reviews_day[i].reviews_count;
            return;

        }
        }
        //Increasing size in case of little space
    if(ptr->allocated_days==ptr->days_count){
        Day_t_realoc(ptr);
    }
    //Creating new day, when new date is encountered
    new_day_create(ptr,date,review);
   
   //Increasing global counter of days and reviews in list_of_days
    ptr->days_count++;
    ptr->reviews_count++;
   

}
///----------------------------------------------------------------------------------
//Return codes
// 0 for EOF ,  1 for problems with input, 2 is ok
int review_add(list_of_days_t * ptr){
    date_t tmp_date[1]={0,0,0}; //Temp values for reading input
    review_t tmp_review[1];
    init_review(&tmp_review[0]);
    bool first_space=true;
    
     //If reading of input failed then we have to deallocate tmp review and return indicator of problems with input
    if(scanf("%d-%d-%d %d",&tmp_date->year,&tmp_date->month,&tmp_date->day,&tmp_review->score)!=4){
        deallocate_review_t(tmp_review);
        return 1;
    }
    
    //Checking if date is right and score is a N+ value
    if(!check_right_date(ptr,&(tmp_date[0])) || tmp_review->score < 1){
        deallocate_review_t(tmp_review);
        return 1;
    }

    int length_of_text=0;
    //Reading input while text has length up to 4096 or newline symbol is encountered 
    while (length_of_text <= 4096)
    {
        char sign_to_read;
        int scanf_ret_value=scanf("%c",&sign_to_read);
        //Handling EOF
        if(scanf_ret_value==-1){
            if(length_of_text==0){
                deallocate_review_t(tmp_review);
                return 1;
            }
            //Increasing size of text
            if(length_of_text==tmp_review->allocated_space){
                review_text_realloc(&tmp_review[0]);
            }
            //Putting end of string symbol
            tmp_review->review_text[tmp_review->length_of_text]='\0';
            add_review_to_list(ptr,&tmp_date[0],&tmp_review[0]);

            
            return 0;
        }
        //Handling wrong input
        if(scanf_ret_value!=1){
            deallocate_review_t(tmp_review);
            return 1;
        }
        //After encountering white space character adding prepared review to list
        if(isspace(sign_to_read) && !first_space){
             if(length_of_text==tmp_review->allocated_space){
                review_text_realloc(&tmp_review[0]);
            }
            //Putting end of string symbol
            tmp_review->review_text[tmp_review->length_of_text]='\0';
            add_review_to_list(ptr,&tmp_date[0],&tmp_review[0]);
            return 2;
        }
        //Feature for skipping first newline after score value
        if(first_space){
            first_space=false;
            continue;
        }

        //Assigning value in case of right value
        if(length_of_text==tmp_review->allocated_space){
                review_text_realloc(&tmp_review[0]);
            }
            //Assigning new symbol to char array of review_text
        tmp_review->review_text[tmp_review->length_of_text]=sign_to_read;
         //Incresing counter for length of text inside review and in cycle
        tmp_review->length_of_text++;    
        length_of_text++;


    }
    //Max+1 length of text reached
    deallocate_review_t(tmp_review);
    return 1;
    



}
///----------------------------------------------------------------------------------
//Comparsion function for qsort
int cmp_func(const void * a, const void * b){
    int a_der =*(const int*)a;
    int b_der=*(const int*)b;

    return (a_der > b_der) - (a_der < b_der);


}
///----------------------------------------------------------------------------------
bool double_comparsion(double a, double b){
    return fabs(a - b) < DBL_EPSILON ;
}
///----------------------------------------------------------------------------------
//Finding median function
int find_med(list_of_days_t * ptr, int first_day,int last_day, int indexes,int * tmp_array){
    int index=0; //Index of possible median
    int first_possible_med,second_possible_med;
    bool one=true; //bool value to indicate if count of values in array is even /odd
    if(indexes%2==1){
        index=indexes/2;
    }
    else{
        index=indexes/2;
        one=false;
    }
    //Creating tmp array and sorting it for easier finding median
    int * tmp_tmp_array =(int*)malloc(indexes * sizeof(int));
    for(int i=0;i<indexes;i++){
        tmp_tmp_array[i]=tmp_array[i];
    }
    qsort(tmp_tmp_array,indexes,sizeof(int),cmp_func);
    first_possible_med=tmp_tmp_array[index];

    //If count of elements in array is even we have to find second median
    if(!one){
        
        
        second_possible_med=tmp_tmp_array[index-1];
        
        if(first_possible_med > second_possible_med){
            free(tmp_tmp_array);
            return second_possible_med;
        }
    }
    free(tmp_tmp_array);
    return first_possible_med;
    
   
}
///----------------------------------------------------------------------------------
//Return codes: 1 is for problems with input, 2 is for unexisted interval ,3 is ok
int interval_search(list_of_days_t * ptr, bool print_strings){
    date_t interval_start[1],interval_end[1];
    //Setting some default values to avoid situationg with uninitialized values
    interval_start->day=-1; interval_start->month=-1; interval_start->year=-1;
     interval_end->day=-1; interval_end->month=-1; interval_end->year=-1;
    int median=0; // best median
    double avg=0; // and best avg
    double best_diff=0; //and best diff
    int first_index=0; //index of first day for interval_start with reviews in our list
    int second_index=0; //index of last day for interval_end with reviews in our list
    bool found=false;
    int count_of_reviews=0; // count of reviews of best interval


    int min_num=0;
    int scanf_ret_value=scanf("%d",&min_num);
    // handling problems with scanf, question for empty list and situation when min. number of reviews is 0
    if((scanf_ret_value!=1 && scanf_ret_value!=-1) || ptr->days_count==0  || min_num==0){
        return 1;
    }
    //count of reviews is lesser then min number of reviews to return
    if( ptr->reviews_count < min_num){
       
        return 2;
    }
    //if there is only one review , we just print it's data, and median with avg as score of this review
    if(ptr->reviews_count==1){
        printf("%d-%.2d-%.2d - %d-%.2d-%.2d: %lf %d\n",ptr->last_date->year,ptr->last_date->month,ptr->last_date->day,ptr->last_date->year,ptr->last_date->month,ptr->last_date->day,ptr->reviews_day[0].avg,ptr->reviews_day[0].reviews[0].score);
        
                
            
        
        printf("  %d: %s\n",ptr->reviews_day[0].reviews[0].score,ptr->reviews_day[0].reviews[0].review_text);
        return 3;
    
    }
    
    // O(n^2) solution // O(n^3 * log(n)) cause we have to sort every possible found interval
    //We are trying all possible abilities with every possible interval 
    //Main loop, starting point 
    int max_reviews=ptr->reviews_count;
    for(int i=0;i < ptr->days_count;i++){
        int index=0; // count of current elements in interval
        double sum=0; //Sum of all elements in interval

        //temporary array with values from interval
        int * tmp_array=(int*)malloc(2*sizeof(int));
        int size=2;

        //Optimalization, when we starts to iterate over interavls which have not enough reviews, there is no sense to try next intervals which will have even less reviews
        if(max_reviews < min_num){
            free(tmp_array);
            break;
        }
        //Second loop ending point, can be sane as starting point
        for(int z=i;z<ptr->days_count;z++){
            //Loop with all reviews in that day, we have to add them all according to task
            for(int f=0;f<ptr->reviews_day[z].reviews_count;f++){
                index++; // Increasing count of elements in our array/interval

                sum+=ptr->reviews_day[z].reviews[f].score; // Adding new element to sum
                //Increasing size of array
                if((index-1)==size){
                    size=2*size;
                    tmp_array=(int*)realloc(tmp_array,size*sizeof(int));
                }
                //Assigning new element to array
                tmp_array[index-1]=ptr->reviews_day[z].reviews[f].score;
            }
            //If we have enough elements in array, we can try to find, if this interval is what we looking for
            if(index>=min_num){
                
            double new_avg=sum/index; //Average is just a sum of all elements in array divided by their count
            int new_tmp_med=find_med(ptr,i,z,index,tmp_array); 
            double new_med=new_tmp_med;
            double possible_diff=0;
             possible_diff=fabs(new_med-new_avg);

               //We found new interval and it has same diff of med - avg as curent best interval                                                             
            if((best_diff!=0 || found==true) && double_comparsion(possible_diff,best_diff) ){
                //Cur date is later then cur max date
                if(ptr->reviews_day[z].review_date->year > interval_end->year ||
                (ptr->reviews_day[z].review_date->year == interval_end->year && ptr->reviews_day[z].review_date->month > interval_end->month) ||
                (ptr->reviews_day[z].review_date->year == interval_end->year && ptr->reviews_day[z].review_date->month == interval_end->month && ptr->reviews_day[z].review_date->day > interval_end->day) ){
                   avg=new_avg;
                   median=new_med;
                   interval_end[0]=*ptr->reviews_day[z].review_date ;
                   interval_start[0]=*ptr->reviews_day[i].review_date;
                   count_of_reviews=index;
                   best_diff=possible_diff;
                   first_index=i; 
                   second_index=z;
                }
                //Cur interval ends on the same date, but cur interval has more reviews
                else if((ptr->reviews_day[z].review_date->year == interval_end->year && ptr->reviews_day[z].review_date->month == interval_end->month && ptr->reviews_day[z].review_date->day == interval_end->day)){
                    if(index > count_of_reviews){
                        avg=new_avg;
                        median=new_med;
                        interval_end[0]=*ptr->reviews_day[z].review_date ;
                        interval_start[0]=*ptr->reviews_day[i].review_date;
                        count_of_reviews=index;
                        first_index=i;
                        best_diff=possible_diff;
                   second_index=z;
                    }
                }
            
            }
            //Cur interval is bigger or its just a first interval
            else if(possible_diff> best_diff || (best_diff==0 && found==false) ){
                avg=new_avg;
                   median=new_tmp_med;
                   interval_end[0]=*ptr->reviews_day[z].review_date ;
                   interval_start[0]=*ptr->reviews_day[i].review_date;
                   count_of_reviews=index;
                   first_index=i;
                   second_index=z;
                   best_diff=possible_diff;
                   found=true;
            }
          
        }
        
    }
    //Deallocating temporary array
    max_reviews-=ptr->reviews_day[i].reviews_count;
    free(tmp_array);

}
if(found==true){
    
    
    printf("%d-%.2d-%.2d - %d-%.2d-%.2d: %lf %d\n",interval_start[0].year,interval_start[0].month,interval_start[0].day,
    
    interval_end[0].year,interval_end[0].month,interval_end[0].day,avg,median);
    if(print_strings){
        for(int i=first_index;i<=second_index;i++){
            for(int z=0;z<ptr->reviews_day[i].reviews_count;z++){
                printf("  %d: %s\n",ptr->reviews_day[i].reviews[z].score,ptr->reviews_day[i].reviews[z].review_text);
            }
        }
    }
}
return 3;


}

///----------------------------------------------------------------------------------
bool Read_Input(list_of_days_t * ptr){
    printf("Recenze:\n");
    bool EOF_reached=false;
    bool first_white_line=true;
    while(!EOF_reached){
        char sign_to_read;
        int scanf_ret_value=scanf("%c",&sign_to_read);
        
        if(scanf_ret_value!=1 && scanf_ret_value!=-1 ){
            return false;
        }
        //Handling EOF situation
        if(scanf_ret_value==-1){
            return true;
        }
        int value;
        switch (sign_to_read)
        {
        case '+':
        // 0 for EOF ,  1 for problems with input, 2 is ok
            value=review_add(ptr);
            if(value==1){
                return false;
            }
            if(value==0){
                EOF_reached=true;
            }
            
            break;
        case '?':
        // 0 for EOF ,  1 for problems with input, 2 is for unreachable interval, 3 is ok
            value=interval_search(ptr,true);
            if(value==1){
                return false;
            }
            if(value==2){
                printf("Neexistuje.\n");
            }
            if(value==0){
                EOF_reached=true;
            }
            first_white_line=true;
            break;
        case '#':
        value=interval_search(ptr,false);
            if(value==1){
                return false;
            }
            if(value==2){
                printf("Neexistuje.\n");
            }
            if(value==0){
                EOF_reached=true;
            }
            first_white_line=true;
            break;    
        default:
        //Handling situation with ? and # command, when we read only first symbol and number without whitespace after it
            if(first_white_line){
                first_white_line=false;
                continue;
            }
            return false;
            break;
        }



    }
    return true;
    




}
///----------------------------------------------------------------------------------
// Debugging feature
void Print_all(list_of_days_t * ptr){
    for(int i=0;i<ptr->days_count;i++){
        printf("Date: %d-%.2d-%.2d :\n",ptr->reviews_day[i].review_date->year,ptr->reviews_day[i].review_date->month,ptr->reviews_day[i].review_date->day);
        for(int z=0;z<ptr->reviews_day[i].reviews_count;z++){
            printf("%d: score: %d text: %s\n",z,ptr->reviews_day[i].reviews[z].score,ptr->reviews_day[i].reviews[z].review_text );

        }
    }

}

///----------------------------------------------------------------------------------
int main(void){
    list_of_days_t * list=(list_of_days_t *)malloc(sizeof(list_of_days_t));
    init(&list[0]);
    if(!Read_Input(&list[0])){
        printf("Nespravny vstup.\n");
        dealloc(&list[0]);
        return EXIT_FAILURE;
    }
   
    
    dealloc(&list[0]);
    return EXIT_SUCCESS;
}