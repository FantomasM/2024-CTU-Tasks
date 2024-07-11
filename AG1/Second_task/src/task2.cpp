#ifndef __PROGTEST__
#include <cassert>
#include <iomanip>
#include <cstdint>
#include <iostream>
#include <memory>
#include <limits>
#include <optional>
#include <algorithm>
#include <bitset>
#include <list>
#include <array>
#include <vector>
#include <deque>
#include <unordered_set>
#include <unordered_map>
#include <stack>
#include <queue>
#include <random>
#include <type_traits>

#endif

struct TextEditorBackend {
    typedef struct My_Node{
        char  value;
        My_Node * parent= nullptr;
        My_Node * left= nullptr;
        My_Node * right=nullptr;
        size_t count_of_newlines=0;
        int height=1;
        size_t count_of_el_under=0;
    }My_Node_t;
  TextEditorBackend(const std::string& text){
      size_t size=size_tree;
      for(const char a : text){
          insert(size++,a);
      }
  }

  size_t size() const{
      return size_tree;
  }
  size_t lines() const{
      return number_of_lines;
  }
  size_t count_of_newl(My_Node * ptr) const {
      if(ptr== nullptr){
          return 0;
      }

      size_t size_of=0;
      if(ptr->value=='\n'){
          size_of++;
      }
      if(ptr->left!= nullptr){
          size_of+=ptr->left->count_of_newlines;
      }
      if(ptr->right!= nullptr){
          size_of+=ptr->right->count_of_newlines;
      }
      return size_of;

  }
  char at(size_t i) const{
        ///Again works on interval from 0 to size_tree-1 in case of not empty tree
      if(i >size_tree-1 ){
          throw  std::out_of_range("Miss\n");

      }
      My_Node * ptr= k_least_const(i,root);
      return ptr->value;
  }
  void edit(size_t i, char c){
      /// We can edit only on positions in interval <0,size_tree-1>
      ///But we have to consider situations when we have empty string
      if(i >size_tree-1 || size_tree==0){
          throw  std::out_of_range("Miss\n");
      }
        if(i==65){
            std::cout <<"stop";
        }
      My_Node * ptr= k_least_const(i,root);
      if(c==ptr->value){
          return;
      }
      My_Node * ptr_new= create_new(c);
      if(c=='\n' && ptr->value!='\n'){
          number_of_lines++;
      }
      if(c!='\n' && ptr->value=='\n'){
          number_of_lines--;
      }
      if(ptr->parent!= nullptr){
          ptr_new->parent=ptr->parent;
          if(ptr->parent->left!= nullptr && ptr->parent->left==ptr){
              ptr->parent->left=ptr_new;
          }
          else{
              ptr->parent->right=ptr_new;
          }
      }
      else{
          root=ptr_new;
      }

      if(ptr->left!= nullptr){
          ptr->left->parent=ptr_new;
      }
      ptr_new->left=ptr->left;
      if(ptr->right!= nullptr){
          ptr->right->parent=ptr_new;
      }
      ptr_new->right=ptr->right;
      delete ptr;
      ptr= nullptr;
      iterative_rotations(ptr_new);

  }
  ///Something like k_least but for newlines
  ///////////////////////Dark magic//////////////////////////
    My_Node * new_lines_least_const(size_t k,My_Node * ptr){
      if(ptr== nullptr){
          return nullptr;
      }

      if(k== count_of_newl(ptr->left) && ptr->value=='\n'){
          return ptr;
      }


      else if(k < count_of_newl(ptr->left) ){
          return new_lines_least_const(k,ptr->left);
      }

      else if(k+1> count_of_newl(ptr->left) && count_of_newl(ptr->left)!=0 && ptr->value=='\n'){
          return new_lines_least_const(k-(count_of_newl(ptr->left)+1),ptr->right);
      }
      else if(k+1> count_of_newl(ptr->left) && count_of_newl(ptr->left)!=0 && ptr->value!='\n'){
          return new_lines_least_const(k-(count_of_newl(ptr->left)),ptr->right);
      }

      else if(count_of_newl(ptr->left)==0 && ptr->value!='\n'){
          return new_lines_least_const(k,ptr->right);
      }
      else if(count_of_newl(ptr->left)==0 && ptr->value=='\n'){
          return new_lines_least_const(k-1,ptr->right);
      }
      else if(count_of_newl(ptr->right)==0 && ptr->value!='\n'){
          return new_lines_least_const(k,ptr->left);
      }
      else if(count_of_newl(ptr->right)==0 && ptr->value=='\n'){
          return new_lines_least_const(k,ptr->left);
      }



      return nullptr;



    }
    My_Node * k_least_const(size_t k,My_Node * ptr) const{ ///Working 100 % tested in miniprogtest

        if(ptr== nullptr){
            return nullptr;
        }
        if(k== count_of_el(ptr->left)){
            return ptr;
        }
        else if(k < count_of_el(ptr->left)){
            return k_least_const(k,ptr->left);
        }
        else if(k> count_of_el(ptr->left)){
            return k_least_const(k-(count_of_el(ptr->left))-1,ptr->right);
        }

        return ptr;
    }
    My_Node * min_node(My_Node * node){
        while(node->left!= nullptr){
            node=node->left;
        }
        return node;
    }
    void push_back(char value){
        My_Node * ptr= k_least_const(size_tree-1,root);
        ptr->right= create_new(value);
        ptr->right->parent=ptr;
        if(value=='\n'){
            number_of_lines++;
            ptr->right->count_of_newlines= count_of_newl(ptr->right);
        }
        iterative_rotations(ptr->right);

    }

  void insert(size_t i, char c){
      /// We can insert on positions in interval <0,size_tree>

      if(i>size_tree){
          throw std::out_of_range("Miss\n");
      }
      /// size_tree is a specific situation, when we have to call push_back or create root
      if(i==size_tree && root!= nullptr){
          push_back(c);
          size_tree++;
          return;
      }
      ///Consider situation when insert works like push_back
      My_Node * ptr;
      ///If tree is empty just push elem on root's place
      if(root== nullptr){
          root= create_new(c);
          if(c=='\n') {
              number_of_lines++;
          root->count_of_newlines=1;
          }
          size_tree++;
          return;
      }

      ///Handling case when index is 0
      if(i==0){
          ptr= k_least_const(i,root);
          ptr->left= create_new(c);
          ptr->left->parent=ptr;
          if(c=='\n'){
              number_of_lines++;
              ptr->left->count_of_newlines=1;
          }
          iterative_rotations(ptr->left);
          size_tree++;
          return;
      }
      ///Finding place to insert elem
      ptr=k_least_const(i-1,root);
      if(ptr==root){
          My_Node * to_ins= min_node(ptr->right);
          to_ins->left= create_new(c);
          to_ins->left->parent=to_ins;
          size_tree++;
          if(c=='\n'){
              number_of_lines++;
              to_ins->left->count_of_newlines=1;
          }
          iterative_rotations(to_ins->left);
          return;


      }

      ///Continue here--------------------------------------------

      ///Approach when we try to insert our elem on right side of prev elem
      if(ptr->right!= nullptr) {
          My_Node *to_ins = min_node(ptr->right);
          to_ins->left = create_new(c);
          to_ins->left->parent = to_ins;
          if(c=='\n'){
              number_of_lines++;
              to_ins->left->count_of_newlines=1;
          }
          size_tree++;
          iterative_rotations(to_ins->left);
          return;
      }
      else{
          ptr->right= create_new(c);
          ptr->right->parent=ptr;
          if(c=='\n'){
              number_of_lines++;
              ptr->right->count_of_newlines=1;
          }
          size_tree++;
          iterative_rotations(ptr->right);
          return;


      }




      


  }
    ~TextEditorBackend(){
        My_Node * ptr=root;
        deallocate(ptr);

    }
    void deallocate( My_Node * ptr){
        if(ptr== nullptr){
            return;
        }

        deallocate(ptr->left);
        deallocate(ptr->right);
        delete ptr;

    }

    int height(My_Node * t) const{
        if(t== nullptr){
            return 0;

        } else{
            return t->height;
        }
    }

    size_t count_of_el(My_Node * t)const{
        size_t count=0;
        if(t== nullptr){
            return 0;
        }
        count++;
        if(t->left!= nullptr){
            count=count+t->left->count_of_el_under;

        }
        if(t->right!= nullptr){
            count=count+t->right->count_of_el_under;
        }
        return count;
    }

    My_Node * Left_rotation(My_Node * x){
        My_Node * y=x->right;
        x->right=y->left;
        y->left=x;
        if(x->right!= nullptr){
            x->right->parent=x;
        }
        if(x->parent!= nullptr) {
            if (x->parent->left == x) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
        }
        y->parent=x->parent;
        x->parent=y;
        x->height=std::max(height(x->left),height(x->right))+1;
        y->height=std::max(height(y->right), height(x))+1;

        x->count_of_el_under= count_of_el(x);
        y->count_of_el_under= count_of_el(y);

        x->count_of_newlines= count_of_newl(x);
        y->count_of_newlines= count_of_newl(y);

        if(root==x){
            root=y;
        }


        return y;
    }

    My_Node * Right_rotation(My_Node * x){
        My_Node * y=x->left;
        x->left=y->right;
        y->right=x;
        if(x->left!= nullptr){
            x->left->parent=x;
        }
        if(x->parent!= nullptr) {
            if (x->parent->left == x) {
                x->parent->left = y;
            } else {
                x->parent->right = y;
            }
        }
        y->parent=x->parent;
        x->parent=y;
        x->height=std::max(height(x->left), height(x->right))+1;
        y->height=std::max(height(y->left), height(x))+1;

        x->count_of_el_under= count_of_el(x);
        y->count_of_el_under= count_of_el(y);

        x->count_of_newlines= count_of_newl(x);
        y->count_of_newlines= count_of_newl(y);

        if(root==x){
            root=y;
        }

        return y;

    }

    My_Node * create_new(char value){
        My_Node * new_node=new My_Node;
        new_node->value=value;
        new_node->left= nullptr;
        new_node->right= nullptr;
        new_node->parent= nullptr;
        new_node->height=1;
        new_node->count_of_el_under=1;
        new_node->count_of_newlines=0;
        return new_node;
    }
    void iterative_rotations(My_Node * ptr){
        while(ptr!= nullptr){
            ptr->height=1+std::max(height(ptr->left), height(ptr->right));
            ptr->count_of_el_under= count_of_el(ptr);
            ptr->count_of_newlines= count_of_newl(ptr);
            int balance= height(ptr->left)- height(ptr->right);
            if(balance >1 ){

                if(height(ptr->left->left)-height(ptr->left->right) <0){
                    ptr->left=Left_rotation(ptr->left);
                }
                ptr=Right_rotation(ptr);
                continue;
            }
            if(balance < -1){

                if(height(ptr->right->left)-height(ptr->right->right) >0){
                    ptr->right=Right_rotation(ptr->right);
                }
                ptr=Left_rotation(ptr);
                continue;
            }

            ptr=ptr->parent;
        }



    }
    ///We can delete only in interval <0,size_tree-1> and if tree is empty, then we cant delete anything
  void erase(size_t i){
      if(i>size_tree-1){
          throw std::out_of_range("Miss\n");
      }

      My_Node * ptr= k_least_const(i,root);

      /// Deleting node and changing pointers
      My_Node * father=ptr->parent; ///Creating father pointer for better orientation
      bool left= false;
      if(father!= nullptr) {
          if (father->left != nullptr && father->left == ptr) {
              left = true;
          }
      }
      /// Dividing situation into three cases
      char ret=ptr->value;

      ///1: No children

      if(ptr->right== nullptr && ptr->left== nullptr){
          ///Disconect ptr from father and change height of father plus delete node
          if(father!= nullptr){
              if(left){
                  father->left= nullptr;
              }
              else{
                  father->right= nullptr;
              }
              ///Bubble up with rotations
              iterative_rotations(father);

          }
              ///If father is nullptr then ptr is root or we messed things up :)
          else{
              root= nullptr;
          }
          delete ptr;
          ptr= nullptr;



      }

          ///2: One child right/left

      else if((ptr->right== nullptr || ptr->left== nullptr) && !(ptr->right== nullptr && ptr->left== nullptr)){

          ///Right son case
          if(ptr->right!= nullptr){
              ///Root case / we have to change parent and delete node
              if(root==ptr){
                  root=ptr->right;
                  root->parent= nullptr;
                  delete ptr;
                  ptr= nullptr;


              }
                  ///Standard case
              else{
                  if(left){
                      father->left=ptr->right;
                      ptr->right->parent=father;
                  }
                  else{
                      father->right=ptr->right;
                      ptr->right->parent=father;
                  }
                  iterative_rotations(father);
                  delete ptr;
                  ptr= nullptr;
              }




          }
              ///Left son case
          else if(ptr->left!= nullptr){
              ///Root case / we have to change parent and delete node
              if(root==ptr){
                  root=ptr->left;
                  root->parent= nullptr;
                  delete ptr;
                  ptr= nullptr;


              }
                  ///Standard case
              else{
                  if(left){
                      father->left=ptr->left;
                      ptr->left->parent=father;
                  }
                  else{
                      father->right=ptr->left;
                      ptr->left->parent=father;
                  }
                  iterative_rotations(father);
                  delete ptr;
                  ptr= nullptr;
              }


          }



      }
      ///3: two children worst case scenario
      if(ptr!= nullptr && ptr->right!= nullptr && ptr->left!= nullptr){ /// clang tidy was upset about me adding else if branch, dont know why, so i've added not null test

          ///Finding successor of cur node to replace
          My_Node * Min_node=min_node(ptr->right);
          if(root==ptr){
              root=Min_node;
          }
          ///Consider two cases min_node is ptr->right or no

          ///Min node is right elem of ptr
          if(Min_node==ptr->right){
              Min_node->parent=ptr->parent;
              if(ptr->parent!= nullptr) {
                  if (left) {
                      ptr->parent->left=Min_node;
                  } else {
                      ptr->parent->right=Min_node;
                  }
              }
              Min_node->left=ptr->left;
              ptr->left->parent= Min_node;
              delete ptr;
              ptr= nullptr;
              iterative_rotations(Min_node);
          }
              ///Min node is not a right son of ptr
          else if(Min_node!=ptr->right){
              ///Min node doest have any sons
              if(Min_node->right== nullptr) {
                  father = Min_node->parent;
                  father->left = nullptr;
                  Min_node->parent = ptr->parent;
                  if (ptr->parent != nullptr) {
                      if (left) {
                          ptr->parent->left = Min_node;
                      } else {
                          ptr->parent->right = Min_node;
                      }
                  }
                  Min_node->left = ptr->left;
                  Min_node->right = ptr->right;
                  ptr->left->parent = Min_node;
                  ptr->right->parent = Min_node;
                  delete ptr;
                  ptr = nullptr;
                  iterative_rotations(father);
              }
                  ///Min node have one right son
              else{
                  father = Min_node->parent;
                  father->left = Min_node->right;
                  Min_node->right->parent=father;
                  Min_node->parent = ptr->parent;
                  if (ptr->parent != nullptr) {
                      if (left) {
                          ptr->parent->left = Min_node;
                      } else {
                          ptr->parent->right = Min_node;
                      }
                  }
                  Min_node->left = ptr->left;
                  Min_node->right = ptr->right;
                  ptr->left->parent = Min_node;
                  ptr->right->parent = Min_node;
                  delete ptr;
                  ptr = nullptr;
                  iterative_rotations(father);
              }
          }




      }




        if(ret=='\n'){
            number_of_lines--;
        }
      size_tree--;
  }

    size_t rank(My_Node * ptr)const {

        My_Node * tmp=ptr;
        if (ptr == root) {
            return count_of_el(ptr->left);
        }


        std::vector<bool> bin; ///Reverse k-least route

        while (ptr != root) {
            if (ptr->parent->right != nullptr && ptr->parent->right == ptr) {
                bin.push_back(true);

                ptr = ptr->parent;
                continue;
            }
            if (ptr->parent->left!= nullptr && ptr->parent->left==ptr) {
                bin.push_back(false);
                ptr = ptr->parent;
                continue;
            }
        }
        size_t k= count_of_el(tmp->left);
        My_Node * new_node=tmp;
        for(auto boll : bin){

            if(boll){
                k+= count_of_el(new_node->parent->left)+1;


            }

            new_node=new_node->parent;

        }

        return k;


    }
    size_t line_rank(My_Node * ptr) const{
        My_Node * tmp=ptr;
        if (ptr == root) {
            return count_of_newl(ptr->left);
        }


        std::vector<std::pair<bool,bool>> bin; ///Reverse k-least route

        while (ptr != root) {
            if (ptr->parent->right != nullptr && ptr->parent->right == ptr) {

                if(count_of_newl(ptr->parent->left)!=0 && ptr->parent->value!='\n'){
                    bin.push_back(std::make_pair(true,true));
                }
                else if(count_of_newl(ptr->parent->left)!=0 && ptr->parent->value=='\n'){
                    bin.push_back(std::make_pair(true,false));
                }
                else if(count_of_newl(ptr->parent->left)==0 && ptr->parent->value=='\n'){
                    bin.push_back(std::make_pair(false,true));
                }
                else{
                    bin.push_back(std::make_pair(false, false));
                }
                ptr = ptr->parent;
                continue;
            }
            if (ptr->parent->left!= nullptr && ptr->parent->left==ptr) {
                bin.push_back(std::make_pair(false, false));
                ptr = ptr->parent;
                continue;
            }
        }
        size_t k= count_of_newl(tmp->left);
        My_Node * new_node=tmp;
        for(auto boll : bin){

            if(boll.first && boll.second){
                k+= count_of_newl(new_node->parent->left);


            }
            else if(boll.first && !boll.second){
                k+= count_of_newl(new_node->parent->left)+1;
            }
            else if(!boll.first && boll.second){
                k+=1;
            }

            new_node=new_node->parent;

        }

        return k;
  }
        My_Node * new_lines_least(size_t k,My_Node * ptr) const{
             if(ptr== nullptr){
                return nullptr;
            }
            if(k== count_of_newl(ptr->left) && ptr->value=='\n'){
                return ptr;
            }


            else if(k < count_of_newl(ptr->left) ){
                return new_lines_least(k,ptr->left);
            }

            else if(k+1> count_of_newl(ptr->left) && count_of_newl(ptr->left)!=0 && ptr->value=='\n'){
                return new_lines_least(k-(count_of_newl(ptr->left)+1),ptr->right);
            }
            else if(k+1> count_of_newl(ptr->left) && count_of_newl(ptr->left)!=0 && ptr->value!='\n'){
                return new_lines_least(k-(count_of_newl(ptr->left)),ptr->right);
            }

            else if(count_of_newl(ptr->left)==0 && ptr->value!='\n'){
                return new_lines_least(k,ptr->right);
            }
            else if(count_of_newl(ptr->left)==0 && ptr->value=='\n'){

                return new_lines_least(k-1,ptr->right);
            }
            else if(count_of_newl(ptr->right)==0 && ptr->value!='\n'){
                return new_lines_least(k,ptr->left);
            }
            else if(count_of_newl(ptr->right)==0 && ptr->value=='\n'){
                return new_lines_least(k,ptr->left);
            }
            return nullptr;
  }
    ///Working for lines in interval <0,number_of_lines-1>,
    /// we always have at least one line,
    /// in case of just one line its enough to return size value of tree
  size_t line_start(size_t r) {
      if(r>number_of_lines-1 ){
          throw std::out_of_range("Miss\n");
      }
      if(r==0){
          return 0;
      }
      My_Node * ptr= new_lines_least_const(r-1,root); /// Yes, this method with const in name isn't const
      return rank(ptr)+1;
  }
  ///Working for lines in interval <0,number_of_lines-1>,
  /// we always have at least one line,
  /// in case of just one line its enough to return size value of tree
  size_t line_length(size_t r) const{
      if(r>number_of_lines-1){
          throw std::out_of_range("Miss\n");
      }

      if(r==0){
          if(number_of_lines==1){
              return size_tree;

          }
          else {
              return rank(new_lines_least(0,root))+1;
          }
      }
      if(r==number_of_lines-1){
          return size_tree-1- rank(new_lines_least(r-1,root));
      }

      My_Node * ptr= new_lines_least(r-1,root); ///And this one is const
      My_Node * sec_ptr= new_lines_least(r,root);

      return rank(sec_ptr)- rank(ptr);
  }
    ///Working for interval <0,size_tree-1> or if size_tree is 0, then not working at all
  size_t char_to_line(size_t i) const{
      if(i>size_tree-1){
          throw std::out_of_range("Miss");
      }
      return line_rank(k_least_const(i,root));
  }
  size_t size_tree=0;
  size_t number_of_lines=1;
  My_Node * root= nullptr;
};

#ifndef __PROGTEST__

////////////////// Dark magic, ignore ////////////////////////

template < typename T >
auto quote(const T& t) { return t; }

std::string quote(const std::string& s) {
  std::string ret = "\"";
  for (char c : s) if (c != '\n') ret += c; else ret += "\\n";
  return ret + "\"";
}

#define STR_(a) #a
#define STR(a) STR_(a)

#define CHECK_(a, b, a_str, b_str) do { \
    auto _a = (a); \
    decltype(a) _b = (b); \
    if (_a != _b) { \
      std::cout << "Line " << __LINE__ << ": Assertion " \
        << a_str << " == " << b_str << " failed!" \
        << " (lhs: " << quote(_a) << ")" << std::endl; \
      fail++; \
    } else ok++; \
  } while (0)

#define CHECK(a, b) CHECK_(a, b, #a, #b)

#define CHECK_ALL(expr, ...) do { \
    std::array _arr = { __VA_ARGS__ }; \
    for (size_t _i = 0; _i < _arr.size(); _i++) \
      CHECK_((expr)(_i), _arr[_i], STR(expr) "(" << _i << ")", _arr[_i]); \
  } while (0)

#define CHECK_EX(expr, ex) do { \
    try { \
      (expr); \
      fail++; \
      std::cout << "Line " << __LINE__ << ": Expected " STR(expr) \
        " to throw " #ex " but no exception was raised." << std::endl; \
    } catch (const ex&) { ok++; \
    } catch (...) { \
      fail++; \
      std::cout << "Line " << __LINE__ << ": Expected " STR(expr) \
        " to throw " #ex " but got different exception." << std::endl; \
    } \
  } while (0)
 
////////////////// End of dark magic ////////////////////////


std::string text(const TextEditorBackend& t) {
  std::string ret;
  for (size_t i = 0; i < t.size(); i++) ret.push_back(t.at(i));
  return ret;
}

void test1(int& ok, int& fail) {
	TextEditorBackend s("123\n456\n789");
  CHECK(s.size(), 11);
	CHECK(text(s), "123\n456\n789");
  CHECK(s.lines(), 3);
  CHECK_ALL(s.char_to_line, 0,0,0,0, 1,1,1,1, 2,2,2);
  CHECK_ALL(s.line_start, 0, 4, 8);
  CHECK_ALL(s.line_length, 4, 4, 3);
}

void test2(int& ok, int& fail) {
	TextEditorBackend t("123\n456\n789\n");
  CHECK(t.size(), 12);
	CHECK(text(t), "123\n456\n789\n");
  CHECK(t.lines(), 4);
  CHECK_ALL(t.char_to_line, 0,0,0,0, 1,1,1,1, 2,2,2,2);
  CHECK_ALL(t.line_start, 0, 4, 8, 12);
  CHECK_ALL(t.line_length, 4, 4, 4, 0);
}

void test3(int& ok, int& fail) {
	TextEditorBackend t("asdfasdfasdf");

  CHECK(t.size(), 12);
  CHECK(text(t), "asdfasdfasdf");
	CHECK(t.lines(), 1);
  CHECK_ALL(t.char_to_line, 0,0,0,0, 0,0,0,0, 0,0,0,0);
	CHECK(t.line_start(0), 0);
	CHECK(t.line_length(0), 12);
	
	t.insert(0, '\n');
  CHECK(t.size(), 13);
  CHECK(text(t), "\nasdfasdfasdf");
	CHECK(t.lines(), 2);
  CHECK_ALL(t.line_start, 0, 1);
	
  t.insert(4, '\n');
  CHECK(t.size(), 14);
  CHECK(text(t), "\nasd\nfasdfasdf");
	CHECK(t.lines(), 3);
  CHECK_ALL(t.line_start, 0, 1, 5);
	
  t.insert(t.size(), '\n');
  CHECK(t.size(), 15);
  CHECK(text(t), "\nasd\nfasdfasdf\n");
	CHECK(t.lines(), 4);
  CHECK_ALL(t.line_start, 0, 1, 5, 15);
	
	t.edit(t.size() - 1, 'H');
  CHECK(t.size(), 15);
  CHECK(text(t), "\nasd\nfasdfasdfH");
	CHECK(t.lines(), 3);
  CHECK_ALL(t.line_start, 0, 1, 5);

	t.erase(8);
  CHECK(t.size(), 14);
  CHECK(text(t), "\nasd\nfasfasdfH");
	CHECK(t.lines(), 3);
  CHECK_ALL(t.line_start, 0, 1, 5);

  t.erase(4);
  CHECK(t.size(), 13);
  CHECK(text(t), "\nasdfasfasdfH");
	CHECK(t.lines(), 2);
  CHECK_ALL(t.line_start, 0, 1);
}

void test_ex(int& ok, int& fail) {
	TextEditorBackend t("123\n456\n789\n");
  CHECK_EX(t.at(12), std::out_of_range);

  CHECK_EX(t.insert(13, 'a'), std::out_of_range);
  CHECK_EX(t.edit(12, 'x'), std::out_of_range);
  CHECK_EX(t.erase(12), std::out_of_range);

  CHECK_EX(t.line_start(4), std::out_of_range);
  CHECK_EX(t.line_start(40), std::out_of_range);
  CHECK_EX(t.line_length(4), std::out_of_range);
  CHECK_EX(t.line_length(6), std::out_of_range);
  CHECK_EX(t.char_to_line(12), std::out_of_range);
  CHECK_EX(t.char_to_line(25), std::out_of_range);
}
void test_custom1(int& ok, int & fail){
    TextEditorBackend t("123\nabc\n789\ncde\n");
    CHECK(t.size(),16);
    CHECK(t.lines(), 5);
    t.erase(3);
    CHECK(t.size(),15);
    CHECK(t.lines(), 4);
    t.erase(6);
    CHECK(t.size(),14);
    CHECK(t.lines(), 3);
    t.erase(9);
    CHECK(t.size(),13);
    CHECK(t.lines(), 2);
    for(int i=12;i>=0;i--){
        t.erase(0);
        CHECK(t.size(),i);
    }

    CHECK(t.lines(),1);
    CHECK_EX(t.char_to_line(0),std::out_of_range);
    CHECK_EX(t.line_length(1),std::out_of_range);
    CHECK_EX(t.line_start(1),std::out_of_range);
    CHECK_EX(t.edit(0,'c'),std::out_of_range);
    CHECK_EX(t.erase(0),std::out_of_range);
    CHECK_EX(t.insert(1,'\n'),std::out_of_range);
    CHECK(t.lines(),1);
    TextEditorBackend y("");
    CHECK_EX(y.char_to_line(0),std::out_of_range);
    CHECK_EX(y.line_length(1),std::out_of_range);
    CHECK_EX(y.line_start(1),std::out_of_range);
    CHECK_EX(y.edit(0,'c'),std::out_of_range);
    CHECK_EX(y.erase(0),std::out_of_range);
    CHECK_EX(y.insert(1,'\n'),std::out_of_range);
    CHECK(y.lines(),1);
    y.insert(0,'\n');
    CHECK(y.lines(),2);
    for(int i=0;i<100;i++){
        y.insert(0,'\n');
        CHECK(y.lines(),3+i);
    }
    for(int i=102;i>1;i--){
        size_t size=y.size_tree;
        y.erase(size-1);
        CHECK(y.lines(),i-1);
        CHECK(y.size(),size-1);
    }
    TextEditorBackend f("1234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890");
    for(int i=0;i<100;i++){
        std::cout <<i <<" \n";
        f.edit(i,'\n');
        CHECK(f.lines(),i+2);
    }


}
void test_custom(int& ok, int & fail){
    TextEditorBackend t("asddasasdasd\nasdsdaasdcasdasdasd\nasddasdasasdasdasd\nasdasdasddasasd\nasdsdasdassdaasdasdasddasadsasdasdasdasdsadasdasdasdasdad\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                        "\n\n\n\n\n\n\n\n\n\n\nsdffsdsdfmsd\nsd\nsd\nffg\ng\nhg\nh\nh\nh\nh\nh\nh\nh\nh\nh");
    std::string s="asddasasdasd\nasdsdaasdcasdasdasd\nasddasdasasdasdasd\nasdasdasddasasd\nasdsdasdassdaasdasdasddasadsasdasdasdasdsadasdasdasdasdad\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"
                  "\n\n\n\n\n\n\n\n\n\n\nsdffsdsdfmsd\nsd\nsd\nffg\ng\nhg\nh\nh\nh\nh\nh\nh\nh\nh\nh";
    ///Testing method new_lines_least
    std::vector<size_t> visited;
    for(size_t i=0;i<t.lines()-1;i++){
        ///Testing if new_lines_least returns right position with '/n'
        if((t.new_lines_least(i,t.root)->value!='\n' && s[t.rank(t.new_lines_least(i,t.root))]=='\n')
        || (t.new_lines_least(i,t.root)->value=='\n' && s[t.rank(t.new_lines_least(i,t.root))]!='\n')){
            fail++;
        }


        else{
            ///Testing if given position hasn't encountered before
            size_t k=t.rank(t.new_lines_least(i,t.root));
            bool failed=false;
            for(auto elem : visited){
                if(k==elem){
                    failed= true;
                    fail++;
                    break;
                }

            }
            if(!failed) {
                ok++;
            }
        }
        visited.push_back(t.rank(t.new_lines_least(i,t.root)));
    }
}

int main() {
  int ok = 0, fail = 0;




  if (!fail) test1(ok, fail);
  if (!fail) test2(ok, fail);
  if (!fail) test3(ok, fail);
  if (!fail) test_ex(ok, fail);
  if(!fail) test_custom(ok,fail);
  if(!fail) test_custom1(ok,fail);
  
  if (!fail) std::cout << "Passed all " << ok << " tests!" << std::endl;
  else std::cout << "Failed " << fail << " of " << (ok + fail) << " tests." << std::endl;


}


#endif


