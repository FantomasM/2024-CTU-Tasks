#ifndef __PROGTEST__
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h> //smazat pred nahranim na protgtest
#include <time.h>
typedef struct TCell
{
  struct TCell             * m_Right;
  struct TCell             * m_Down;
  int                        m_Row;
  int                        m_Col;
  int                        m_Data;
} TCELL;

typedef struct TRowCol
{
  struct TRowCol           * m_Next;
  TCELL                    * m_Cells;
  int                        m_Idx;
} TROWCOL;

typedef struct TSparseMatrix
{
  TROWCOL                  * m_Rows;
  TROWCOL                  * m_Cols;
} TSPARSEMATRIX;
#endif /* __PROGTEST__ */


typedef struct TRowCol_better{
    TROWCOL *row_col;
    TROWCOL *prev;
    TROWCOL *next;
}TRowCol_better_t;

typedef struct TCELL_better{
    TCELL * cell;
    TCELL * next;
    TCELL *prev;
}TCELL_better_t;
#define nullptr NULL
void initMatrix   ( TSPARSEMATRIX   * m )
{
  m->m_Cols=nullptr;
  m->m_Rows=nullptr;
}
//------------------------------------------------------------------------------------------------------------
//Function expects right(N with 0) value of index
TROWCOL * create_row(int index, TROWCOL * next){
    TROWCOL * new_row=(TROWCOL*)malloc(sizeof(TROWCOL));
    new_row->m_Cells=nullptr;
    new_row->m_Idx=index;
    new_row->m_Next=next;
    return new_row;
}
//------------------------------------------------------------------------------------------------------------
//function create new cell and  give it links to next cell in row and in column
TCELL * create_cell(int data, TROWCOL * col, TROWCOL * row, TCELL * next,TCELL * down){
    TCELL * cell=(TCELL*)malloc(sizeof(TCELL));
    cell->m_Data=data;
    cell->m_Col=col->m_Idx;
    cell->m_Row=row->m_Idx;
    cell->m_Right=next;
    cell->m_Down=down;
    return cell;

    

}
//------------------------------------------------------------------------------------------------------------
//Finds new row or create it and links to right position and returns new row
TROWCOL * Find_row(int index,TSPARSEMATRIX * matrix){
    TROWCOL * init_row=matrix->m_Rows;
    TROWCOL * prev=init_row;
  //Finding row with right index or row with first bigger index
    while(init_row!=nullptr){
        
        if(init_row->m_Idx>=index){
            break;
        }
        prev=init_row;
        init_row=init_row->m_Next;
    }   
    //Handling case when we found right row
        if(init_row!=nullptr && init_row->m_Idx==index){

            return init_row;
        }
        //Handling case when we found bigger row ,and it's not a 0. element in row structure
        //or last row was lesser than our index
        if(init_row!=prev){
        prev->m_Next=create_row(index,init_row);
        return prev->m_Next;
        }
        //Handling case when we found bigger row ,and it's a 0. element in row structure
        else{
            matrix->m_Rows=create_row(index,init_row);
            return matrix->m_Rows;
        }
    
    
}
//------------------------------------------------------------------------------------------------------------
//Finds new column or create it and links to right position and returns new column
TROWCOL * Find_column(int index,TSPARSEMATRIX * matrix){
    TROWCOL * init_col=matrix->m_Cols;
    TROWCOL * prev=init_col;
    //Finding column with right index or row with first bigger index
    while(init_col!=nullptr){
        
        if(init_col->m_Idx>=index){
            break;
        }
        prev=init_col;
        init_col=init_col->m_Next;
    }   
    //Handling case when we found right row
        if(init_col!=nullptr && init_col->m_Idx==index){
            
            return init_col;
        }
        //Handling case we found bigger row ,and it's not a 0. element in row structure
        //or last column was lesser than our index
        if(init_col!=prev){
        prev->m_Next=create_row(index,init_col);
        return prev->m_Next;
        }
        //Handling case we found bigger row ,and it's a 0. element in row structure
        else{
            matrix->m_Cols=create_row(index,init_col);
            return matrix->m_Cols;
        }
    
    
}


//------------------------------------------------------------------------------------------------------------
//Function to insert new cell with data or to change already existed cell
TCELL * Insert_cell(TROWCOL * row, TROWCOL * col, int data){

    TCELL * init_col=col->m_Cells;
    TCELL * prev_col=col->m_Cells;
    //Finding the closest cell looking from up to down in column
    while(init_col!=nullptr){
        if(init_col->m_Row >= row->m_Idx){
            break;
        }
        prev_col=init_col;
        init_col=init_col->m_Down;
    }
    //No such row we have to add element
    if(row->m_Cells==nullptr){
        
        row->m_Cells=create_cell(data,col,row,nullptr,nullptr);
        //3 cases possible

        //1: column dont have elements
            if(col->m_Cells==nullptr){
                col->m_Cells=row->m_Cells;
                return col->m_Cells;
            }
        //2: prev col is less than our index
            if(prev_col!=init_col){ //prev_col is equal to init_col only in case when we ended on the start of loop ,and we have to insert on 0. place
                prev_col->m_Down=row->m_Cells;
                row->m_Cells->m_Down=init_col;
                return row->m_Cells;
            }
        //3: prev col is the first element in col ,and it's going after our cell
        else{

            col->m_Cells=row->m_Cells;
            col->m_Cells->m_Down=prev_col;
            return col->m_Cells;
        }

    }
    
    //row have cells
    else{
        TCELL * init_row=row->m_Cells;
        TCELL * prev_row=row->m_Cells;
        //Finding right cell with same index or with first bigger index
        while(init_row!=nullptr){
        if(init_row->m_Col >= col->m_Idx){
            break;
        }
        prev_row=init_row;
        init_row=init_row->m_Right;
    }
      //Case when column doesn't have cells
      if(col->m_Cells==nullptr){
        col->m_Cells=create_cell(data,col,row,nullptr,nullptr);

        //2 cases possible

        
        //1: prev row is less than our index
            if(prev_row!=init_row){ //prev_row is equal to init_row only in case when we ended on the start of loop ,and we have to insert on 0. place
                prev_row->m_Right=col->m_Cells;
                col->m_Cells->m_Right=init_row;
                return col->m_Cells;
            }
        //2: prev row is the last element in row ,and it's going after our cell
        else{
            row->m_Cells=col->m_Cells;
            row->m_Cells->m_Right=prev_row;
            return col->m_Cells;
        }




      }
      //Case when column and row have some cells
      else{

      //Such element is already in linked list
      if(init_col!=nullptr && init_row!=nullptr && init_col->m_Row==row->m_Idx && init_row->m_Col==col->m_Idx){
        init_col->m_Data=data;
        return init_col;
      }
      //no such element in linked list but indexes exist
      else{
        TCELL * new_cell=nullptr;
        //Insert into row
        //2 cases
        //1: we have to insert after prev row
         if(prev_row!=init_row){ //prev_row is equal to init_row only in case when we ended on the start of loop ,and we have to insert on 0. place
                prev_row->m_Right=create_cell(data,col,row,nullptr,nullptr);
                new_cell=prev_row->m_Right;
                new_cell->m_Right=init_row;

            }
        //2: we have to insert on the start
        else{
            row->m_Cells=create_cell(data,col,row,nullptr,nullptr);
            row->m_Cells->m_Right=init_row;
            new_cell=row->m_Cells;
           
        }
           
         //Insert into column system;

         //2 cases
        //1: we have to insert after prev col
        if(prev_col!=init_col){ //prev_col is equal to init_col only in case when we ended on the start of loop ,and we have to insert on 0. place
           
            prev_col->m_Down=new_cell;

            new_cell->m_Down=init_col;

        }
        //2: we have to insert on the start
        else{
            col->m_Cells=new_cell;
            new_cell->m_Down=init_col;

        }





      }

      return init_col;
      

      }
    }
}
//------------------------------------------------------------------------------------------------------------
void addSetCell   ( TSPARSEMATRIX   * m,
                    int               rowIdx,
                    int               colIdx,
                    int               data )
{
    //situation when we insert first element

  if(m->m_Cols==nullptr){
    m->m_Cols=create_row(colIdx,nullptr);
    m->m_Rows=create_row(rowIdx,nullptr);
    TCELL * cell=create_cell(data,m->m_Cols,m->m_Rows,nullptr,nullptr);
    m->m_Cols->m_Cells=cell;
    m->m_Rows->m_Cells=cell;
    return;
  }
  //not first element
  //Function Find row create or finds and return right row, same for Find column
   TROWCOL *row_to_ins=Find_row(rowIdx,m);
   TROWCOL *col_to_ins=Find_column(colIdx,m);

    Insert_cell(row_to_ins, col_to_ins, data);


}
//------------------------------------------------------------------------------------------------------------
//Debugging feature for printing one row
void Print_row(TROWCOL * row){
    TCELL * first=row->m_Cells;
    while (first!=nullptr)
    {
        printf("[%d,%d] value:%d  \n",first->m_Row,first->m_Col,first->m_Data);
        first=first->m_Right;
    }
    printf("\n");
    
}
//------------------------------------------------------------------------------------------------------------
//Debugging feature for printing matrix
void Print_Matrix(TSPARSEMATRIX * m){
    TROWCOL * row=m->m_Rows;
    if(row==nullptr){
        printf("Matrix is empty\n");
        return;
    }
    while(row!=nullptr){
        Print_row(row);
        row=row->m_Next;
    }
    TROWCOL * col=m->m_Cols;
    while (col!=nullptr)
    {
        printf("%d ",col->m_Idx);
        col=col->m_Next;
    }
    
}
//------------------------------------------------------------------------------------------------------------
void del_row(TROWCOL * prev, TROWCOL * row, TROWCOL * next, TSPARSEMATRIX * m){
    //Deleting first element
    if(row==prev){

        free(row);
        row=nullptr;
        m->m_Rows=next;
        return;
    }
    //Deleting not first element
    prev->m_Next=next;
    free(row);
    row=nullptr;


}
//------------------------------------------------------------------------------------------------------------

void del_col(TROWCOL * prev, TROWCOL * col, TROWCOL * next, TSPARSEMATRIX * m){
    //Deleting first element
    if(col==prev){

        free(col);
        col=nullptr;
        m->m_Cols=next;
        return;
    }
    //Deleting not first element
    prev->m_Next=next;
    free(col);
    col=nullptr;


}
//------------------------------------------------------------------------------------------------------------
bool removeCell   ( TSPARSEMATRIX   * m,
                    int               rowIdx,
                    int               colIdx )
{
        //Matrix is empty
     if(m->m_Cols==nullptr && m->m_Rows==nullptr){
    return false;
  }
  //Creating pointers for prev , current and next row in row system
    TRowCol_better_t *row=(TRowCol_better_t*)malloc(sizeof (TRowCol_better_t));
     row->row_col=m->m_Rows;
     row->prev=m->m_Rows;
     row->next=nullptr;
     if(row->row_col!=nullptr){
         row->next=row->row_col->m_Next;
     }



    //Creating pointers for prev , current and next col in col system
    TRowCol_better_t *col=(TRowCol_better_t*) malloc(sizeof (TRowCol_better_t));
     col->row_col=m->m_Cols;
     col->prev=m->m_Cols;
     col->next=nullptr;
     if(col->row_col!=nullptr){
         col->next=col->row_col->m_Next;
     }


  //Finding such row
  while(row->row_col!=nullptr){
    if(row->row_col->m_Idx==rowIdx){
        break;
    }
      row->prev=row->row_col;
    row->row_col=row->row_col->m_Next;
    if(row->row_col!=nullptr){
        row->next=row->row_col->m_Next;
  }
  }
  //Finding such col
  while(col->row_col!=nullptr){
    if(col->row_col->m_Idx==colIdx){
        break;
    }
    col->prev=col->row_col;
    col->row_col=col->row_col->m_Next;
    if(col->row_col!=nullptr){
    col->next=col->row_col->m_Next;
  }
  }
  //No such column or no such row, element cant exist
  if(col->row_col==nullptr || row->row_col==nullptr){
      free(col);
      free(row);
    return false;
  }

    TCELL_better_t * elem_in_row=(TCELL_better_t*) malloc(sizeof (TCELL_better_t));
  elem_in_row->cell=row->row_col->m_Cells;
  elem_in_row->prev=elem_in_row->cell;
  elem_in_row->next=nullptr;
  if(elem_in_row->cell!=nullptr){
      elem_in_row->next=elem_in_row->cell->m_Right;
  }

    //Finding position in row
  while(elem_in_row->cell!=nullptr){
    if(elem_in_row->cell->m_Col==colIdx){
        break;
    }

      elem_in_row->prev=elem_in_row->cell;
    elem_in_row->cell=elem_in_row->cell->m_Right;
     if(elem_in_row->cell!=nullptr){

    elem_in_row->next=elem_in_row->cell->m_Right;
  }
  }

  //-----------------------------

    TCELL_better_t * elem_in_col=(TCELL_better_t*) malloc(sizeof (TCELL_better_t));
  elem_in_col->cell=col->row_col->m_Cells;
  elem_in_col->prev=col->row_col->m_Cells;
  elem_in_col->next=nullptr;
  if(elem_in_col->cell!=nullptr){
      elem_in_col->next=elem_in_col->cell->m_Down;
  }


//Finding position in col
    while(elem_in_col->cell!=nullptr){
        if(elem_in_col->cell->m_Row==rowIdx){
            break;
        }
        elem_in_col->prev=elem_in_col->cell;
        elem_in_col->cell=elem_in_col->cell->m_Down;
        if(elem_in_col->cell!=nullptr){
        elem_in_col->next=elem_in_col->cell->m_Down;
        }
    }

  //--------------------------------
//We havent found such elements
if(elem_in_col->cell!=elem_in_row->cell || elem_in_col->cell==nullptr){
    free(col);
    free(row);
    free(elem_in_col);
    free(elem_in_row);
    return false;
}
//Row

//1: elem is only one, so we have to delete row
if(elem_in_row->cell==  elem_in_row->prev && elem_in_row->cell->m_Right==nullptr){

elem_in_row->cell=nullptr;

del_row(row->prev,row->row_col,row->next,m);
}

//2: there are more elements in row but elem to delete is the first
else if(elem_in_row->cell==  elem_in_row->prev && elem_in_row->cell->m_Right!=nullptr){

elem_in_row->cell=nullptr;

row->row_col->m_Cells=elem_in_row->next;
}
//3: there are more elements in row but elem isn't first
else if(elem_in_row->cell!=  elem_in_row->prev){
   
elem_in_row->cell=nullptr;

  elem_in_row->prev->m_Right=elem_in_row->next;
}

//Col

//1: elem is only one, so we have to delete col
if(elem_in_col->cell==elem_in_col->prev && elem_in_col->cell->m_Down==nullptr){
    free(elem_in_col->cell);
    elem_in_col->cell=nullptr;
   ;
    del_col(col->prev,col->row_col,col->next,m);
}


//2: there are more elements in col but elem is first
else if(elem_in_col->cell==elem_in_col->prev && elem_in_col->cell->m_Down!=nullptr){
    free(elem_in_col->cell);

    elem_in_col->cell=nullptr;
    col->row_col->m_Cells=elem_in_col->next;

}

//3: there are more elements in col and elem isn't first
else if(elem_in_col->cell!=elem_in_col->prev){
    free(elem_in_col->cell);
    elem_in_col->cell=nullptr;
    elem_in_col->prev->m_Down=elem_in_col->next;
}
    free(col);
    free(row);
    free(elem_in_col);
    free(elem_in_row);
return true;
}
//------------------------------------------------------------------------------------------------------------
void free_col(TROWCOL * col){
    if(col==nullptr){
        return;
    }
    TROWCOL * next=col->m_Next;
    free(col);
    free_col(next);
}
//------------------------------------------------------------------------------------------------------------
void free_cell_in_row(TCELL * cell){
    if(cell==nullptr){
        return;
    }
    TCELL * next=cell->m_Right;
    free(cell);
    free_cell_in_row(next);
}
//------------------------------------------------------------------------------------------------------------
int size_of_row(TROWCOL * row){ //Debugging feature
    int size=0;
    TCELL * start=row->m_Cells;
    while (start!=nullptr){
        size++;

        start=start->m_Right;
    }
    return size;
}
//------------------------------------------------------------------------------------------------------------
int size_of_col(TROWCOL * col){ //Debugging feature
    int size=0;
    TCELL * start=col->m_Cells;
    while (start!=nullptr){
        size++;

        start=start->m_Down;
    }
    return size;
}
//------------------------------------------------------------------------------------------------------------
void free_row(TROWCOL * row){
    if(row==nullptr){
        return;
    }
    free_cell_in_row(row->m_Cells);
    TROWCOL * next=row->m_Next;
    free(row);
    free_row(next);
}
//------------------------------------------------------------------------------------------------------------
void freeMatrix   ( TSPARSEMATRIX   * m ) //Recursive free function
{
  free_col(m->m_Cols); //Deleting cols without their cells
  free_row(m->m_Rows); //Deleting rows with their cells
  m->m_Cols=nullptr;
  m->m_Rows=nullptr;
  
}
//------------------------------------------------------------------------------------------------------------
TCELL * find_element(TSPARSEMATRIX * m, int row_id, int col_id) {
    TROWCOL *row = m->m_Rows;
    while (row != nullptr) {
        if (row->m_Idx >= row_id) {
            break;
        }
        row = row->m_Next;
    }
    if (row==nullptr || row->m_Idx!=row_id){
        return nullptr;
    }
    TCELL  * cell=row->m_Cells;
    while(cell!=nullptr){
        if(cell->m_Col==col_id){
            return cell;
        }
        if(cell->m_Col> col_id){
            return nullptr;
        }
        cell=cell->m_Right;

    }
    return nullptr;


}

#define size_max 20
//------------------------------------------------------------------------------------------------------------
bool Check_all_el_in_row(TROWCOL * row,const int array_2d[size_max][size_max],int size){ //Debugging function to check if elements in row have correct values
    TCELL * start=row->m_Cells;
    while (start!=nullptr){
        if(start->m_Col>size || start->m_Row>size){

            return false;
        }
        if(start->m_Data!=array_2d[start->m_Row][start->m_Col]){
            return false;
        }
        start=start->m_Right;
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------
                                                                                                    //Working only for wrong values, don't check situation when value isn't in matrix
bool Check_all_rows(TSPARSEMATRIX * m,const int array_2d[size_max][size_max],int size){ //Debugging function to check if all elements in matrix have correct values

    TROWCOL *start=m->m_Rows;
    while(start!=nullptr){
        if(Check_all_el_in_row(start,array_2d,size)!=true){
            return false;
        }
        start=start->m_Next;
    }
    return true;
}
//------------------------------------------------------------------------------------------------------------
bool Check_all_sizes(TSPARSEMATRIX *m,const int counter[],int size){ //Debugging function to check if sizes of rows are the right one
    TROWCOL *start=m->m_Rows;
    while (start!=nullptr){
        if(start->m_Idx>size){

            return false;
        }
        if(size_of_row(start)!=counter[start->m_Idx]){


            return false;
        }
        start=start->m_Next;
    }

    return true;
}

//------------------------------------------------------------------------------------------------------------
void big_random_test(TSPARSEMATRIX *m){ //Low level AG1 style testing function
    int array_2d[size_max][size_max]; //Array to track element's values
    int row_sizes[size_max]; //Array to track sizes of rows
    //Initialization of arrays
    for(int i=0;i<size_max;i++){
        for(int z=0;z<size_max;z++){
            array_2d[i][z]=-1;

        }
        row_sizes[i]=0;
    }
    time_t time1;
    srand((unsigned )time(&time1));

    for(int z=0;z<8*size_max;z++) {


        for (int i = 0; i < 10*size_max; i++) {

            int operation=rand()%2; //Randomizing operation to do
            if(i<=2*size_max){ //first i*2 operations will be inserts
                operation=1;
            }


            int value_row=rand()%size_max; //Creating value of row to insert

            int value_col=rand()%size_max; //Creating value of col to insert


            int value_to_ins=rand()%1000; //Creating random value to insert

            //Insert case
            if(operation==1){
                //Changing value in array with correct values of elements
                array_2d[value_row][value_col]=value_to_ins;
                //if it's a new element, we have to increase size of row in array with row sizes
                if(find_element(m,value_row,value_col)==nullptr){

                    row_sizes[value_row]++;
                }
                //Adding cell
                addSetCell(m,value_row,value_col,value_to_ins);

                //Finding this cell and checking if value is right
                assert(find_element(m,value_row,value_col)->m_Data==value_to_ins);
                //Checking sizes of all rows after insert
                assert(Check_all_sizes(m,row_sizes,size_max));
                //Checking all elements and their values
                assert(Check_all_rows(m,array_2d,size_max));

            }
            //Deletion case
            else{
                //If element is found, then we do same test as before
                if(find_element(m,value_row,value_col)!=nullptr){

                    row_sizes[value_row]--;
                    array_2d[value_row][value_col]=-1;
                    //Also adding test to check if removing was successful (it should be, because element was there)
                    assert(removeCell(m,value_row,value_col)==true);
                    assert(Check_all_sizes(m,row_sizes,size_max));
                    assert(Check_all_rows(m,array_2d,size_max));

                }
                else{
                    continue;
                }
            }

        }
    }
}
//------------------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int main ( int argc, char * argv [] )
{



    TSPARSEMATRIX big_matrix;
    initMatrix(&big_matrix);
    big_random_test(&big_matrix);
    freeMatrix(&big_matrix);


   
  TSPARSEMATRIX  m;
  initMatrix ( &m );
  addSetCell ( &m, 0, 1, 10 );
  addSetCell ( &m, 1, 0, 20 );
  addSetCell ( &m, 1, 5, 30 );
  addSetCell ( &m, 2, 1, 40 );
  assert ( m . m_Rows
           && m . m_Rows -> m_Idx == 0
           && m . m_Rows -> m_Cells
           && m . m_Rows -> m_Cells -> m_Row == 0
           && m . m_Rows -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Cells -> m_Data == 10
           && m . m_Rows -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next
           && m . m_Rows -> m_Next -> m_Idx == 1
           && m . m_Rows -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Col == 0
           && m . m_Rows -> m_Next -> m_Cells -> m_Data == 20
           && m . m_Rows -> m_Next -> m_Cells -> m_Right
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Col == 5
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Data == 30
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Right == nullptr );
           
  assert ( m . m_Rows -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Idx == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next == nullptr );
  
  assert(m . m_Cols -> m_Cells);
  assert ( m . m_Cols
           && m . m_Cols -> m_Idx == 0
           && m . m_Cols -> m_Cells
           && m . m_Cols -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Cells -> m_Col == 0
           && m . m_Cols -> m_Cells -> m_Data == 20
           && m . m_Cols -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next
           && m . m_Cols -> m_Next -> m_Idx == 1
           && m . m_Cols -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Cells -> m_Row == 0
           && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Data == 10
           && m . m_Cols -> m_Next -> m_Cells -> m_Down
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Row == 2
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Data == 40
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells -> m_Down );
  addSetCell ( &m, 230, 190, 50 );
  assert ( m . m_Rows
           && m . m_Rows -> m_Idx == 0
           && m . m_Rows -> m_Cells
           && m . m_Rows -> m_Cells -> m_Row == 0
           && m . m_Rows -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Cells -> m_Data == 10
           && m . m_Rows -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next
           && m . m_Rows -> m_Next -> m_Idx == 1
           && m . m_Rows -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Col == 0
           && m . m_Rows -> m_Next -> m_Cells -> m_Data == 20
           && m . m_Rows -> m_Next -> m_Cells -> m_Right
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Row == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Col == 5
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Data == 30
           && m . m_Rows -> m_Next -> m_Cells -> m_Right -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Idx == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr);
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Idx == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Next == nullptr);
  assert ( m . m_Cols
           && m . m_Cols -> m_Idx == 0
           && m . m_Cols -> m_Cells
           && m . m_Cols -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Cells -> m_Col == 0
           && m . m_Cols -> m_Cells -> m_Data == 20
           && m . m_Cols -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next
           && m . m_Cols -> m_Next -> m_Idx == 1
           && m . m_Cols -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Cells -> m_Row == 0
           && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Data == 10
           && m . m_Cols -> m_Next -> m_Cells -> m_Down
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Row == 2
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Data == 40
           && m . m_Cols -> m_Next -> m_Cells -> m_Down -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Idx == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells -> m_Down );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells );
  
  assert ( removeCell ( &m, 0, 1 ) );
  assert ( !removeCell ( &m, 0, 1 ) );
  assert ( !removeCell ( &m, 1, 2 ) );
  assert ( m . m_Rows
           && m . m_Rows -> m_Idx == 1
           && m . m_Rows -> m_Cells
           && m . m_Rows -> m_Cells -> m_Row == 1
           && m . m_Rows -> m_Cells -> m_Col == 0
           && m . m_Rows -> m_Cells -> m_Data == 20
           && m . m_Rows -> m_Cells -> m_Right
           && m . m_Rows -> m_Cells -> m_Right -> m_Row == 1
           && m . m_Rows -> m_Cells -> m_Right -> m_Col == 5
           && m . m_Rows -> m_Cells -> m_Right -> m_Data == 30
           && m . m_Rows -> m_Cells -> m_Right -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next
           && m . m_Rows -> m_Next -> m_Idx == 2
           && m . m_Rows -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Rows -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Rows -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Rows -> m_Next -> m_Cells -> m_Right == nullptr);
  assert ( m . m_Rows -> m_Next -> m_Next
           && m . m_Rows -> m_Next -> m_Next -> m_Idx == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Cells
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Rows -> m_Next -> m_Next -> m_Cells -> m_Right == nullptr );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Next == nullptr );
  assert ( m . m_Cols
           && m . m_Cols -> m_Idx == 0
           && m . m_Cols -> m_Cells
           && m . m_Cols -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Cells -> m_Col == 0
           && m . m_Cols -> m_Cells -> m_Data == 20
           && m . m_Cols -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next
           && m . m_Cols -> m_Next -> m_Idx == 1
           && m . m_Cols -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Cells -> m_Row == 2
           && m . m_Cols -> m_Next -> m_Cells -> m_Col == 1
           && m . m_Cols -> m_Next -> m_Cells -> m_Data == 40
           && m . m_Cols -> m_Next -> m_Cells -> m_Down == nullptr);
  assert ( m . m_Cols -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Idx == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Row == 1
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Col == 5
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Data == 30
           && m . m_Cols -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Idx == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Row == 230
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Col == 190
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Data == 50
           && m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells -> m_Down == nullptr );
  assert ( m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Next == nullptr);
  assert ( m . m_Rows -> m_Cells == m . m_Cols -> m_Cells );
  assert ( m . m_Rows -> m_Cells -> m_Right == m . m_Cols -> m_Next -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Cells );
  assert ( m . m_Rows -> m_Next -> m_Next -> m_Cells == m . m_Cols -> m_Next -> m_Next -> m_Next -> m_Cells );
  
  freeMatrix ( &m );

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */