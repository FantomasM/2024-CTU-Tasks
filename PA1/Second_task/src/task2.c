#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <inttypes.h>

typedef struct message{
    long long int end_time;
    long long int main_message;
}MESSAGE;

int read_entry(MESSAGE * mes){
    long long int end_time=0;
    long long int main_message=0;
    bool end_t=false;
    while (true)
    {
        char letter;
        
        if(scanf("%c",&letter)!=1){
            return EXIT_FAILURE;
        }
        
        if((letter <= 'z' && letter >='a') ){
            if(end_t){
                main_message+=pow(2,(letter-'a'));
            }
            else{
                end_time+=pow(2,(letter-'a'));
            }
        }
        else if(letter=='|'){
            if(end_t){
                return EXIT_FAILURE;

            }
            end_t=true;
            continue;
        }
        else if(letter=='\n'){
             if(!end_t || (main_message==end_time && main_message==0)){
                return EXIT_FAILURE;

            }
            mes->end_time=end_time;
            mes->main_message=main_message;
            return EXIT_SUCCESS;
        }
        else{
            return EXIT_FAILURE;
        }
        
    }
    




}
long long int gcd(__int128_t a,__int128_t b){
    if(a==b || b==0){
        return a;
    }
    if(a==0){
        return b;
    }
    if(a > b){
        return(gcd(a-b,b));
    }
    else{
        return(gcd(a,b-a));
    }
}
int Diophantine_equation(MESSAGE * mes_1,MESSAGE * mes_2){
    //diopantine equation looks like ax+by=c;
    long long int a,b,c,GCD;
    a=mes_1->main_message+mes_1->end_time;
    b=-1*(mes_2->main_message+mes_2->end_time);
    //control of limit values
    if((mes_1->main_message==mes_2->main_message && mes_1->main_message==0) ||(mes_1->main_message==mes_2->end_time && mes_2->end_time==0) ||
    (mes_2->main_message==mes_1->end_time && mes_1->end_time==0) ){
        printf("Synchronizace za: %d\n",0);
        return EXIT_SUCCESS;
    }
    c=(mes_2->end_time-mes_1->end_time);
    GCD=gcd(a,b*(-1));
   
    if(abs(c)%GCD!=0){
        return EXIT_FAILURE;
    }

    //Finding solution for alpha*x+beta*y=GCD;
    __int128_t alpha=0,beta=0;
    while (true)
    {
        if(a*alpha+b*beta>GCD){
            beta++;
        }
        else if(a*alpha+b*beta<GCD){
            alpha++;
        }
        else{
            break;
        }
    }
    
    long long int x,y;
    x=alpha*(c/GCD);
    y=beta*(c/GCD);
        //x and y cannot be negative due to our task, so we have to find positive solution
        // cause we now that all solutions look like alpha+(b/GCD)*k and beta-(a/GCD)*k
        //we can just add b/GCD and a/GCD untill we can find positive solution
     if(x <0 || y <0){
        while (true)
        {
            long long int next_x=x+abs(b/GCD);
            long long int next_y=y+abs(a/GCD);
            if(next_x > 0 && next_y > 0){
                x=next_x;
                y=next_y;
                 printf("Synchronizace za: %lld\n",x*a+mes_1->end_time);
                 return EXIT_SUCCESS;
                break;
            }
            else{
                x=next_x;
                y=next_y;
                continue;
            } 
            
        }
        
     }
     //Same for positive but not minimal solution
     if(x >0 && y >0){
        while (true)
        {
          
        
        
        long long int next_x=x-abs(b/GCD);
        long long int next_y=y-abs(a/GCD);
        if(next_x > 0 && next_y > 0){
                x=next_x;
                y=next_y;
                continue;
            }
            if(next_x <0 || next_y <0){
                printf("Synchronizace za: %lld\n",x*a+mes_1->end_time);
                 return EXIT_SUCCESS;
                break;
            }
        }
     }
     printf("Synchronizace za: %lld\n",x*a+mes_1->end_time);
    
    
    
    return EXIT_SUCCESS;

}


int main(void){
    MESSAGE * mes=(MESSAGE*)malloc(2*sizeof(MESSAGE));
    printf("Zpravy:\n");
    for(__int128_t i=0;i<2;i++){
        MESSAGE * ptr=&mes[i];
        if(read_entry(ptr)==1){
            printf("Nespravny vstup.\n");
            free(mes);
            return EXIT_FAILURE;
        }
        
    }
    MESSAGE * ptr_1=&mes[0];
    MESSAGE * ptr_2=&mes[1];
    if(Diophantine_equation(ptr_1,ptr_2)!=0){
        printf("Nelze dosahnout.\n");
            free(mes);
            return EXIT_SUCCESS;
    }


    free(mes);
    return EXIT_SUCCESS;
}