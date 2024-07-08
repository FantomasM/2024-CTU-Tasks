#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct convertor
{
    long long int from;
    long long int to;
    
}convertor_t;
///------------------------------------------------------------------------------
typedef struct List_of_convertors{
    convertor_t * convertors;
    int count;
    int allocated_size;


}List_of_convertors_t;
///------------------------------------------------------------------------------
void init(List_of_convertors_t * ptr){
    ptr->count=0;
    ptr->allocated_size=2;
    ptr->convertors=(convertor_t*)malloc(ptr->allocated_size*sizeof(convertor_t));
}
///------------------------------------------------------------------------------
void free_all(List_of_convertors_t * ptr){
    free(ptr->convertors);
}
///------------------------------------------------------------------------------
void realoc(List_of_convertors_t * ptr){
    
    ptr->allocated_size=ptr->allocated_size*4;
    ptr->convertors=(convertor_t*)realloc(ptr->convertors,ptr->allocated_size*sizeof(convertor_t));


}
//-------------------------------------------------------------------------------
//Helping function for simplifying
long long int gcd(long long int a, long long int b){
    if (b == 0) {
        return a;
    } 
    else{
        return gcd(b, a % b);
    }
}
//-------------------------------------------------------------------------------
//Simplifying of  fraction
void simplify(long long int * a, long long int * b){
    long long int div=gcd(*a,*b);
    *a/=div;
    *b/=div;
}

//-------------------------------------------------------------------------------
//Comparing potential new best coeficient with current best coef according to rules
bool Set_best_conv(double * ptr,double to_compare,long int to, long int from){
    double dbl_from=from, dbl_to=to;
    double x=dbl_from/dbl_to;
    double new_comp=to_compare/x;
    if(new_comp <1){
        new_comp=x/to_compare;
    }
    double best=*ptr;
    
    double div=best/x;
    if(div<1){
        div=x/best;
    }
    
    if(new_comp < div){
        *ptr=to_compare;
        return true;
    }
    return false;


}
//-------------------------------------------------------------------------------
void recursive_all_possiblities_try(List_of_convertors_t * ptr,convertor_t * array,convertor_t * best_array,bool * visited,int n,
 double cur_conv,long int from, long int to,int i,int max_len,double * best_conv,
 int start,int end,int index,int end_r){
    //Ending branch 
        if(index==end_r){
            //Comparing potential coeficient with current best
            if(Set_best_conv(best_conv,cur_conv,to,from)){
                //Rewriting interval of convertors in case of better option
                for(int f=0;f<end_r;f++){
                 best_array[f].from=array[f].from;
                 best_array[f].to=array[f].to;
            }
            }        
            
            

           

            return;
        }
    //Generating all possible combinations of convertors of length i
    for (int i = start; i <= end && end - i + 1 >= end_r - index; i++) {
        visited[i] = true; //Special array to indicate, if we used this element or not

        //Adding convertor in normal orientation
        array[index] = ptr->convertors[i];
        double dbl_from=array[n].from, dbl_to=array[n].to;
       double new_cur_conv=cur_conv*(dbl_from/dbl_to);
       recursive_all_possiblities_try(ptr,array,best_array,visited,n+1,new_cur_conv,from,to,i+1,max_len,best_conv,i+1,end,index+1,end_r);
       
        //Adding inverted convertor 
        array[index].from=ptr->convertors[i].to;
        array[index].to=ptr->convertors[i].from;
         dbl_from=array[n].from, dbl_to=array[n].to;
        new_cur_conv=cur_conv*(dbl_from/dbl_to);


        recursive_all_possiblities_try(ptr,array,best_array,visited,n+1,new_cur_conv,from,to,i+1,max_len,best_conv,i+1,end,index+1,end_r);
        
        
        visited[i] = false;
    }



}


///------------------------------------------------------------------------------
void find_convertion(List_of_convertors_t * ptr,long long int from,long long int to){
    
    double best[1]; //pointer with best coef
    *best=1;    //Its set on 1, and in case when we cannot find better option, we just print 1:1
   
   //Creating temp arrays for recursion function
    convertor_t * array=(convertor_t*)malloc((ptr->count+1)*sizeof(convertor_t));
    convertor_t * best_array=(convertor_t*)malloc((ptr->count+1)*sizeof(convertor_t));
    bool * visited=(bool*)malloc(ptr->count*sizeof(bool)); //Array with indication if we have this elem in our combination
    for(int i=0;i<ptr->count;i++){ //Setting some default values in arrays
        
        visited[i]=false;
    }
   
    int len=0;
    //Main recursion loop, in every step it generates all combinations of convertors of length i
    for(int i=1;i<=ptr->count;i++){
        //Saving current best value
        double ptr_value=*best;
     
    recursive_all_possiblities_try(ptr,array,best_array,visited,0,1,from,to,0,i,&best[0],0,ptr->count-1,0,i);
    //Checking if best value is changed after generating new combinations
    if(*best!=ptr_value){ //if so, change length of best interval of convertors
        len=i;
    }
    }
   
    long long int from_new=1;
    long long int to_new=1;
    //Getting fraction of our founded koef
     for(int i=0;i<len;i++){
         from_new*=best_array[i].from;
         to_new*=best_array[i].to;
    }
    //And then simplifying it
    simplify(&from_new,&to_new);
    if(len!=0){
    printf("%lld:%lld =",from_new,to_new);
    }
    else{
        printf("%lld:%lld",from_new,to_new);
    }
    for(int i=0;i<len;i++){
        if(i+1!=len){
        printf(" [%lld:%lld] *",best_array[i].from,best_array[i].to);
        }
        else{
            printf(" [%lld:%lld]",best_array[i].from,best_array[i].to);
        }
    }
    printf("\n");
    free(array);
    free(best_array);
    free(visited);

}

///------------------------------------------------------------------------------
bool Read_Input(List_of_convertors_t * ptr){
    printf("Prevody:\n");
    bool question_encountered=false; 

    int scanf_ret_value=0;
   
    int real_size=0;
    char * buffer=NULL;
        size_t size=0;
    while ((real_size=getline(&buffer,&size,stdin))>=0)
    {   
        char sign;
        long long int from, to;
        
       
        //Putting end of string symbol to avoid problems with newline
        buffer[real_size-1]='\0';
        //Parsing line
        scanf_ret_value=sscanf(buffer,"%c %lld:%lld",&sign,&from,&to);
        //Basic input check
        if(scanf_ret_value!=-1 && scanf_ret_value!=3){
            free(buffer);
            return false;
        }
        //Check for right symbol on the start of line
        if(sign!='?' && sign!='+'){
            free(buffer);
            return false;
        }
        //Checking if values in question make sense
        if(sign=='?' && ( from <= 0 || to <= 0 )){
            free(buffer);
            return false;
        }
        //Checking if added convertor doesnt have wrong values
        if( sign=='+' && (from < 10 || from > 1000 || to >1000 || to < 10)){
            free(buffer);
            return false;
        }
        if(sign=='?'){
            find_convertion(ptr,from,to);
            question_encountered=true;


        }
        if(sign=='+'){
            //If adding is encountered after first question, program will end
            if(question_encountered){
                free(buffer);
                return false;
            }
            //Increasing size
            if(ptr->allocated_size==ptr->count){
                realoc(ptr);
            }
            //Adding convertor 
            ptr->convertors[ptr->count].from=from;
            ptr->convertors[ptr->count].to=to;
            ptr->count++;
        }
        //Deleting garbage after getline
        size=0;
     free(buffer);
     buffer=NULL;
    }
    if(buffer!=NULL){
    free(buffer);
    }
    
    return true;



}
///------------------------------------------------------------------------------
//Debugging feature
void Print_all(List_of_convertors_t * ptr){
    for(int i=0;i<ptr->count;i++){
        printf("Prevodovka %lld:%lld\n",ptr->convertors[i].from,ptr->convertors[i].to);
    }
}
///------------------------------------------------------------------------------
int main(void){
    List_of_convertors_t list[1];
    init(&list[0]);
    if(!Read_Input(&list[0])){
        printf("Nespravny vstup.\n");
        
        free_all(&list[0]);
        return EXIT_FAILURE;
    }
    

    free_all(&list[0]);
    return EXIT_SUCCESS;
}