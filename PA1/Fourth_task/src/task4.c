#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//--------------------------------------------------------------
typedef struct array{
    int * array;
    int size;
    int size_max;
}array_t;
//--------------------------------------------------------------
typedef struct max_interval{
    int size;
    int from;
    int to;
    
}max_interval_t;
//--------------------------------------------------------------
void array_init(array_t * ptr){
    ptr->array=(int*)malloc(2*sizeof(int));
    ptr->size_max=2;
    ptr->size=0;
    

}
//--------------------------------------------------------------
void Realoc_c_plus_plus(array_t * ptr){
    int * tmp=(int*)malloc(ptr->size_max*2*sizeof(int));
    ptr->size_max*=2;
    for(int i=0;i<ptr->size;i++){
        tmp[i]=ptr->array[i];
    }
    free(ptr->array);
    ptr->array=tmp;
}
//--------------------------------------------------------------
bool Read_Input(array_t * ptr){
    printf("Hodnoty:\n");
    int num_to_read=0,count_of_signs;
    while(true){
        (count_of_signs=scanf("%d",&num_to_read));
       
        if(count_of_signs==EOF){
            break;
        }
        if(count_of_signs!=1){
          
            return false;
        }
        
        if(ptr->size==ptr->size_max){
            Realoc_c_plus_plus(ptr);
        }
        ptr->array[ptr->size++]=num_to_read;
        if(ptr->size >250000){
        return false;
    }
        
    }
    //EOF encountered, but fewer than two numbers were read.
    if(ptr->size < 2){
        return false;
    }
    return true;
}
//--------------------------------------------------------------
//O(n^2) solution for finding longest sequence of numbers
void Find_max(array_t * ptr){
    int max_length=0,cur_length=0;
    int size_of_max_int=0,max_size_of_max_int=2;
    max_interval_t * max_int=(max_interval_t*)malloc(2*sizeof(max_interval_t));
    if(max_int == NULL){ //Allocation wasn't successful 
        return;
    }
    bool new_int=true;
    for(int i=0;i<ptr->size;i++){
     
        for(int z=ptr->size-1;z>i;z--){
             if(z-i < max_length){
            break;
        }
            if(ptr->array[z] >=ptr->array[i]){
            cur_length=z-i;


            if(cur_length>max_length){
                max_length=cur_length;
                
                if(new_int){
                    new_int=false;
                    max_int[0].from=i;
                    max_int[0].to=z;
                    max_int[0].size=cur_length;
                }
                else{
                    //Delete_and_create_new(max_int);
                    max_interval_t * tmp=(max_interval_t*)malloc(2*sizeof(max_interval_t));
                    free(max_int);
                    max_int=tmp;

                    max_size_of_max_int=2;
                    max_int[0].from=i;
                    max_int[0].to=z;
                    max_int[0].size=cur_length;
                }
                size_of_max_int=1;
                continue;
            }
            if(cur_length==max_length){
                if(size_of_max_int==max_size_of_max_int){
                    max_interval_t * tmp=(max_interval_t*)malloc(max_size_of_max_int*2*sizeof(max_interval_t));
    
                    for(int i=0;i<max_size_of_max_int;i++){
                           tmp[i]=max_int[i];
                             }
                         free(max_int);
                     max_int=tmp;
                    max_size_of_max_int*=2;
                }
                max_int[size_of_max_int].from=i;
                    max_int[size_of_max_int].to=z;
                    max_int[size_of_max_int].size=cur_length;
                    size_of_max_int++;

            }
        }

        }
        
        
       
    }
    

    if(max_length==0){
        printf("Nelze najit.\n");
    }
    else{
        for(int i=0;i<size_of_max_int;i++){
            printf("%d: %d - %d\n",max_int[i].size+1,max_int[i].from,max_int[i].to);
        }
        printf("Moznosti: %d\n",size_of_max_int);
    }



   free(max_int);
}
//--------------------------------------------------------------
int main (void){
array_t * ptr=(array_t*)malloc(sizeof(array_t));
if(ptr==NULL){
    return EXIT_FAILURE;
}
array_init(ptr);
if(!Read_Input(ptr)){
    printf("Nespravny vstup.\n");
    free(ptr->array);
    free(ptr);
    return EXIT_FAILURE;
}
Find_max(ptr);


free(ptr->array);
free(ptr);
return EXIT_SUCCESS;
}