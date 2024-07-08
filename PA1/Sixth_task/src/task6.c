#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

typedef struct mapping
{
    char digit;
    char letters[5];
}Key_mapping;
//--------------------------------------------------------------------------
static Key_mapping key_map[]={
    {'1'," "},{'2',"abc"},{'3',"def"},{'4',"ghi"},
    {'5',"jkl"},{'6',"mno"},{'7',"pqrs"},{'8',"tuv"},{'9',"wxyz"}
};
//--------------------------------------------------------------------------
typedef struct Contact{
    char * number;
    int number_length;
    int allocated_number_length;
    char * contact_name;
    int name_length;
    int allocated_name_length;
}Contact_t;
//--------------------------------------------------------------------------
typedef struct List_of_contacts
{   
    //Array of pointers to contacts sorted by name
    Contact_t ** contacts_by_name;
    int size;
    int allocated_size;
    //Array of same pointers but ordered by number
    Contact_t ** contacts_by_number;
    
    
    bool sorted;
}List_of_contacts_t;
//--------------------------------------------------------------------------
void init_contact(Contact_t * ptr){
    ptr->allocated_name_length=2;
    ptr->name_length=0;
    ptr->allocated_number_length=2;
    ptr->number_length=0;
    ptr->contact_name=(char*)malloc(ptr->allocated_name_length*sizeof(char));
    ptr->number=(char*)malloc(ptr->allocated_number_length*sizeof(char));
    
}
//--------------------------------------------------------------------------
void free_contact(Contact_t * ptr){
    free(ptr->contact_name);
    free(ptr->number);
    free(ptr);
}
//--------------------------------------------------------------------------

void init (List_of_contacts_t * ptr){
    ptr->allocated_size=2;
    ptr->size=0;
    ptr->contacts_by_name=(Contact_t**)malloc(ptr->allocated_size * sizeof(Contact_t*));
   
    
    ptr->contacts_by_number=(Contact_t**)malloc(ptr->allocated_size * sizeof(Contact_t*));

    ptr->sorted=false;


}
//--------------------------------------------------------------------------
void free_list(List_of_contacts_t * ptr){
    
    for(int i=0;i<ptr->size;i++){
        free_contact(ptr->contacts_by_name[i]);
    }
    free(ptr->contacts_by_name);
    free(ptr->contacts_by_number); 




}
//--------------------------------------------------------------------------
void realoc_name(Contact_t * ptr){
    ptr->allocated_name_length=ptr->allocated_name_length*2;
    ptr->contact_name=(char*)realloc(ptr->contact_name,ptr->allocated_name_length*sizeof(char));
}
//--------------------------------------------------------------------------
void realoc_number(Contact_t * ptr){
    ptr->allocated_number_length=ptr->allocated_number_length*2;
    ptr->number=(char*)realloc(ptr->number,ptr->allocated_number_length*sizeof(char));
}
//--------------------------------------------------------------------------
void realoc_contacts(List_of_contacts_t * ptr){
    ptr->allocated_size=ptr->allocated_size*2;
    ptr->contacts_by_name=(Contact_t**)realloc(ptr->contacts_by_name,ptr->allocated_size*sizeof(Contact_t*));
    ptr->contacts_by_number=(Contact_t**)realloc(ptr->contacts_by_number,ptr->allocated_size*sizeof(Contact_t*));

}
//--------------------------------------------------------------------------
int cmp_by_name(const void * a, const void * b){
    const Contact_t * a_deref=*(const Contact_t**)a;
    const Contact_t * b_deref=*(const Contact_t**)b;

    int min;
    if(a_deref->name_length < b_deref->name_length){
        min=a_deref->name_length;
    }
    else{
        min=b_deref->name_length;
    }
    for(int i=0;i<min;i++){
        
        if(( tolower(a_deref->contact_name[i]) < tolower(b_deref->contact_name[i]))){
            return -1;
        }
        else if(tolower(a_deref->contact_name[i]) > tolower(b_deref->contact_name[i])){
            return 1;
        }
        
    }
    return 0;
}
//--------------------------------------------------------------------------
int cmp_by_number(const void * a, const void * b){
    const Contact_t * a_deref=*(const Contact_t**)a;
    const Contact_t * b_deref=*(const Contact_t**)b;
   
    int min;
    if(a_deref->number_length < b_deref->number_length){
        min=a_deref->number_length;
    }
    else{
        min=b_deref->number_length;
    }
    for(int i=0;i<min;i++){
       
         if(( tolower(a_deref->number[i]) < tolower(b_deref->number[i]))){
            return -1;
        }
        else if(tolower(a_deref->number[i]) > tolower(b_deref->number[i])){
            return 1;
        }
        
        
    }
    return 0;
}
//--------------------------------------------------------------------------

bool Check_name(Contact_t * ptr){
if(ptr->name_length==0){
    return false;
}

    //Additional spaces on the start or on the end of name
    if(isspace(ptr->contact_name[0]) || (ptr->name_length>=2 && isspace(ptr->contact_name[ptr->name_length-2]) )){
        return false;
    }
    bool first_space=true;
    for(int i=0;i<ptr->name_length-1;i++){
        if(!isalpha(ptr->contact_name[i])){
            if(isspace(ptr->contact_name[i])){
                if(first_space){
                    first_space=false;
                    continue;
                }
                //More then one space between words
                else{
                    return false;
                }
            }
            //Encountered forbidden symbol
            else{
                return false;
            }
        }
        first_space=true;
    }
    return true;

}
//--------------------------------------------------------------------------
bool Check_number(Contact_t * ptr){
    //Basic controls for number
    if(ptr->number_length==0 || (ptr->number_length==1 && !isdigit(ptr->number[0]))){
        return false;
    }
    for(int i=0;i<ptr->number_length-1;i++){
        if(!isdigit(ptr->number[i])){
            return false;
        }
    }
    return true;



}
//--------------------------------------------------------------------------
Contact_t * Parse_line_contact(char * line, size_t size,bool * indicator){ //Smazat debbuging features pred uploadem
    Contact_t * new_contact=(Contact_t*)malloc(sizeof(Contact_t));
    init_contact(new_contact);
    *indicator=true;
   
    char * line_ptr=line;
   
    line_ptr++; //Setting line_ptr after first symbol +
  
    
    char *token = strtok(line_ptr, " "); //Parsing number
    
    //Basic controls of number length           situation when strtok jumped over more then 1 space    situation when there is no space between number and +
    if(strlen(token)>20 || strlen(token)==0 || (size >=2 && *token!=line[2])                       || ( size>=2 && !isspace(line[1]))){
        
       
        free_contact(new_contact);
        *indicator=false;
        return NULL;
    }
    char * ptr_token=token;
    size_t pos=1;
    //Rewriting number to temporary contact
    for(;*ptr_token!='\0';ptr_token++){
        if(pos >=size){
         
         
        free_contact(new_contact);
        *indicator=false;
        return NULL;
        }
        if(new_contact->allocated_number_length==new_contact->number_length){
            realoc_number(new_contact);
        }
        new_contact->number[new_contact->number_length++]=*ptr_token;
        pos++;
    }
    if(new_contact->allocated_number_length==new_contact->number_length){
            realoc_number(new_contact);
        }
    new_contact->number[new_contact->number_length]='\0';
    //Checks for number, if it contains only digit and etc
    if(!Check_number(new_contact)){
        
         
        free_contact(new_contact);
        *indicator=false;
        return NULL;
    }
    
    ptr_token++;
    //Rewriting name to temporary contact
    for(;*ptr_token!='\0';ptr_token++){
        if(new_contact->allocated_name_length==new_contact->name_length){
            realoc_name(new_contact);
        }
        new_contact->contact_name[new_contact->name_length++]=*ptr_token;
    }
    if(new_contact->allocated_name_length ==new_contact->name_length){
            realoc_name(new_contact);
        }
    new_contact->contact_name[new_contact->name_length-1]='\0';
    
    //Same checks for name as for number
    if(!Check_name(new_contact)){
        
        
        free_contact(new_contact);
        *indicator=false;
        return NULL;
    }
   
   
    return new_contact;
    
    

    
    
}
//--------------------------------------------------------------------------
char * Parse_line_question(char * line, size_t size, bool * indicator){
  
    char * line_ptr=line;
    
    line_ptr++;
    size--;
    //Avoiding situation when there is no number in question
    if(size <=1 || (size>=2 && !isspace(*line_ptr))  ){
       
        *indicator=false;
        return NULL;
    }
    line_ptr++;
    char * ptr=line_ptr;
    //Checking if number contains of number only
    for(;*ptr!='\0';ptr++){
        if(!isdigit(*ptr) &&   !(*ptr=='\n' && (*(ptr+1)=='\0'))){
          
            *indicator=false;
            return NULL;
        }
    }
    ptr--;
    *ptr='\0';
    *indicator=true;
    return line_ptr;
    
}
//--------------------------------------------------------------------------
bool find_dup(List_of_contacts_t * ptr,Contact_t * contact){
        //Finding duplicates
        for(int i=0;i<ptr->size;i++){
           
            if(contact->name_length==(ptr->contacts_by_number[i])->name_length &&
            strncmp(contact->contact_name,(ptr->contacts_by_number[i])->contact_name,contact->name_length)==0 &&
            contact->number_length==(ptr->contacts_by_number[i])->number_length &&
            strncmp(contact->number,(ptr->contacts_by_number[i])->number,contact->number_length)==0
            ){
                return true;
            }
        
            
        }
        return false;
    
}
//--------------------------------------------------------------------------
bool Add_contact(List_of_contacts_t * ptr, char * str, size_t size){
    bool indicator;
    //Parsing data for new contact
 Contact_t * new_contact=Parse_line_contact(str,size,&indicator);
 
 if(indicator==false){
    printf("Nespravny vstup.\n");
    return false;
 }
//Finding possible duplicates
if(find_dup(ptr,new_contact)){
    free_contact(new_contact);
    printf("Kontakt jiz existuje.\n");
    return false;
}
if(ptr->allocated_size==ptr->size){
    realoc_contacts(ptr);
}
ptr->contacts_by_name[ptr->size]=new_contact;
ptr->contacts_by_number[ptr->size++]=new_contact;
//We are sorting our array only before question, therefore every adding is crashing our sorted array
ptr->sorted=false;
printf("OK\n");
return true;

}
//--------------------------------------------------------------------------
void Print_all(List_of_contacts_t * ptr){ //Debugging feature
    for(int i=0;i<ptr->size;i++){
        printf("Name: %s, Number: %s \n",(ptr->contacts_by_name[i])->contact_name, (ptr->contacts_by_name[i])->number);
    }
    printf("---------------------\n");
    for(int i=0;i<ptr->size;i++){
        printf("Name: %s, Number: %s \n",(ptr->contacts_by_number[i])->contact_name, (ptr->contacts_by_number[i])->number);
    }
}
//--------------------------------------------------------------------------
Contact_t ** T9_search(List_of_contacts_t * ptr,char * line,size_t * size){
   
    size_t len=strlen(line);
    int int_len=strlen(line);
    Key_mapping * key_array=(Key_mapping *)malloc(len* sizeof(Key_mapping));
    for(size_t i=0;i<len;i++){
        key_array[i]=(key_map[line[i]-'0'-1]);
    }
   
    Contact_t ** container_of_contacts_to_ret=(Contact_t**)malloc(ptr->size*sizeof(Contact_t *));
    size_t pos=0;
    for(int i=0;i<ptr->size;i++){
        //First optimalization ,no sense to compare name that contains less letters than search parameter 
        if(ptr->contacts_by_name[i]->name_length < int_len){
          
            continue;
        }
        // Second optimalization , our array is sorted, so when we meet a contact, whose name is starting after t9 symbols, for example first t9 symbol is 2 'ABC' and contact name is starting from d, there is no sense to check next contacts
        if( tolower((ptr->contacts_by_name[i])->contact_name[0]) > tolower(key_array[0].letters[strlen(key_array[0].letters)-1])){
           
            break;
        }
       //Main T9 loop, at first we try to find contacts which contact name starts from letters on first number of line, for example for 2 we are finding contacts which names starts from a or b or c
        for(char * z=&key_array[0].letters[0];*z!='\0';z++){
         
        if(tolower((ptr->contacts_by_name[i])->contact_name[0])==*z){
            	//then we go to second loop, where we control if other letters in contact's name
            	// are matching
            for(size_t f=1; f<len;f++){
                bool at_least_one_true=false;
                //Comparing with letters for current number
                 for(char * key_z=&key_array[f].letters[0];*key_z!='\0';key_z++){
                   ;
                   //If we found match, we can end cycle
                    if(tolower((ptr->contacts_by_name[i])->contact_name[f])==*key_z){
                        at_least_one_true=true;
                        break;
                    }
                 }
                 //Match was not found
                 if(!at_least_one_true){
                    break;
                 }
                 //If it is cycle and name is matching, adding it to return struct array
                 if(f+1==len){
                    container_of_contacts_to_ret[pos++]=ptr->contacts_by_name[i];
                 }
            }
            //Fixing situation, when there is only one symbol in question
            if(len==1){
                container_of_contacts_to_ret[pos++]=ptr->contacts_by_name[i];
            }

            
            
        }
        }

    }   
    free(key_array);
    
     *size=pos;
    return container_of_contacts_to_ret;
    
    
}
//--------------------------------------------------------------------------
void add_number_occ(List_of_contacts_t * ptr, char * line,Contact_t ** contacts, size_t* size){
    //Adding number that starts with prefix in question
    
    size_t pos=*size;
    Contact_t tmp[1];
    tmp->number=line;
    tmp->number_length=strlen(line);
    
    for(int i=0;i<ptr->size;i++){
        //Same optimalization as in T9
        if(ptr->contacts_by_number[i]->number[0] > line[0]){
            break;
        }



        if(ptr->contacts_by_number[i]->number[0]==line[0] && ptr->contacts_by_number[i]->number_length >=tmp->number_length){
            if(strncmp(ptr->contacts_by_number[i]->number,line,tmp->number_length)==0){
                bool dup=false;
               
                pos=*size;
                //We already have some contacts from T9, so we hav to avoid adding duplicates
                for(size_t z=0;z<pos;z++){
                    if(contacts[z]== ptr->contacts_by_number[i]){
                        dup=true;
                        break;
                    }
                }
                if(!dup){
                    contacts[*size]=ptr->contacts_by_number[i];
                    (*size)++;
                }
            }
        }
    }
   
    


}

//--------------------------------------------------------------------------
void Find_occurences(List_of_contacts_t * ptr, char * line, size_t size){
    bool indicator;
    char * res=Parse_line_question(line,size,&indicator);
   
    if(indicator==false){
         printf("Nespravny vstup.\n");
         return;
    }
    if(!ptr->sorted){
    qsort(ptr->contacts_by_name,ptr->size,sizeof(Contact_t*),cmp_by_name);
    qsort(ptr->contacts_by_number,ptr->size,sizeof(Contact_t *),cmp_by_number);
    ptr->sorted=true;
    }
    size_t size_search=0;
    Contact_t ** contacts=NULL;
    contacts= T9_search(ptr,res,&size_search);
    
    add_number_occ(ptr,res,contacts,&size_search);
    if(contacts!=NULL){
        if(size_search <=10){
        for(size_t i=0;i<size_search;i++){
            printf("%s %s\n", (contacts[i])->number,(contacts[i])->contact_name);
        }
        }
        printf("Celkem: %lu\n",size_search);
        free(contacts);
    }
}
//--------------------------------------------------------------------------
void Read_Input(List_of_contacts_t * ptr){
    char * line_to_read=NULL;
    size_t size_of_line=0;
    int real_size_of_line=0;
    while ((real_size_of_line=getline(&line_to_read,&size_of_line,stdin)) >=0)
    {   
        switch (line_to_read[0])
        {
        case '+':
            Add_contact(ptr,line_to_read,real_size_of_line);
            free(line_to_read);
            line_to_read=NULL;
            size_of_line=0;
            break;
        case '?':
            Find_occurences( ptr,line_to_read,real_size_of_line);
            free(line_to_read);
            line_to_read=NULL;
            size_of_line=0;
            break;
        default:
        
        printf("Nespravny vstup.\n");
            free(line_to_read);
            line_to_read=NULL;
            size_of_line=0;
            break;
        }
    }
    if(line_to_read!=NULL){
    free(line_to_read);
            line_to_read=NULL;
            size_of_line=0;
    }



}





int main(void){
    List_of_contacts_t Contact_list[1];
    init(&Contact_list[0]);
    Read_Input(&Contact_list[0]);
 

    free_list(&Contact_list[0]);
    return EXIT_SUCCESS;
}
