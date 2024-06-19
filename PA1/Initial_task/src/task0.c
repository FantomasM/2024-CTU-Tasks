#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool Read_input(int * number_to_scan){
    if(scanf("%d",number_to_scan)!=1){
    printf("Neh mi'\n");
        return false;
}
return true;
}



int main(void){
    
    int number_to_scan =0;
    char sign;
    printf("ml' nob:\n");
    
    if(!Read_input(&number_to_scan)){
        return EXIT_FAILURE;
    }

  int result=scanf("%c",&sign);

if(sign!='\n' && sign!=' ' && sign!='	' && result!=EOF){
    printf("bIjatlh 'e' yImev\n");
    return 1;
}

switch (number_to_scan)
    {
    case 0:
    printf("Qapla'\nnoH QapmeH wo' Qaw'lu'chugh yay chavbe'lu' 'ej wo' choqmeH may' DoHlu'chugh lujbe'lu'.\n");
    break;
    case 1:
    printf("Qapla'\nbortaS bIr jablu'DI' reH QaQqu' nay'.\n");
    break;
    case 2:
    printf("Qapla'\nQu' buSHa'chugh SuvwI', batlhHa' vangchugh, qoj matlhHa'chugh, pagh ghaH SuvwI''e'.\n");
    break;
    case 3:
    printf("Qapla'\nbISeH'eghlaH'be'chugh latlh Dara'laH'be'.\n");
    break;
    case 4:
    printf("Qapla'\nqaStaHvIS wa' ram loS SaD Hugh SIjlaH qetbogh loD.\n");
    break;
    case 5:
    printf("Qapla'\nSuvlu'taHvIS yapbe' HoS neH.\n");
    break;
    case 6:
    printf("Qapla'\nHa'DIbaH DaSop 'e' DaHechbe'chugh yIHoHQo'.\n");
    break;
    case 7:
    printf("Qapla'\nHeghlu'meH QaQ jajvam.\n");
    break;
    case 8:
    printf("Qapla'\nleghlaHchu'be'chugh mIn lo'laHbe' taj jej.\n");
    break;
    default:
    printf("Qih mi' %d\n",number_to_scan);
        return 1;
        break;
    }

    return 0;
}
