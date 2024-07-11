#ifndef __PROGTEST__
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdint>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <numeric>
#include <string>
#include <vector>
#include <array>
#include <iterator>
#include <set>
#include <list>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <compare>
#include <queue>
#include <stack>
#include <deque>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>
#include <atomic>
#include <chrono>
#include <stdexcept>
#include <condition_variable>
#include <pthread.h>
#include <semaphore.h>
#include "progtest_solver.h"
#include "sample_tester.h"
using namespace std;
#endif /* __PROGTEST__ */

enum problem_type{min_pr,cnt_pr};
enum solver_status{not_created,not_full,working};

class Buffer_class
{
  private:
  
   
  
  public:
  
  std::shared_ptr<std::mutex> mutex_ = std::make_shared<std::mutex>();
  std::shared_ptr<std::mutex> mutex_end_indicator=std::make_shared<std::mutex>();

  std::shared_ptr<condition_variable> cv_full=std::make_shared<std::condition_variable>();    
  std::shared_ptr<condition_variable> cv_empty=std::make_shared<std::condition_variable>();
  std::shared_ptr<condition_variable> not_ready=std::make_shared<std::condition_variable>();
  //deque of a problem pack, shared ptr on pair of count of problems in pack and count of solved problems 
  //, shared_ptr to mutex that control previous two numbers editing, 
  deque<std::pair<AProblemPack,std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,std::shared_ptr<condition_variable>>>>> problems; 
  public:
  Buffer_class(){
   // mutex_=std::make_shared<std::mutex>();
  };
  void notify_before_leaving(){
    std::lock_guard<std::mutex> lock(*mutex_);
    cv_empty->notify_all();
    std::lock_guard<std::mutex> lock_1(*mutex_end_indicator);
    not_ready->notify_all();
  }
  std::pair<AProblemPack,std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,std::shared_ptr<condition_variable>>>> & push_back_thread_safe(AProblemPack & pack){
    //Add checking if pack is on its end
    //critical section
    std::lock_guard<std::mutex> lock(*mutex_);
    
    size_t count=pack->m_ProblemsCnt.size()+pack->m_ProblemsMin.size();
    problems.push_back(make_pair(pack,make_pair(std::make_shared<std::pair<size_t,size_t>>(std::make_pair(count,0)),make_pair(mutex_end_indicator,not_ready))));

   (*cv_empty).notify_one();
   
    return  problems.back();
  }
  bool check_equal(atomic_bool & working){
   
    unique_lock<mutex> ul2(*mutex_end_indicator);
    
    if(problems.front().second.first->first==problems.front().second.first->second){
      
      return true;
    }
    if(!working && problems.empty()){
      throw std::logic_error("no work and problems empty");
    }
    return false;
  }
  
  bool remove_thread_safe(ACompany & company, atomic_bool & working,int tid){
    unique_lock<mutex> ul (*mutex_);
    
    if(problems.empty() && !working){
      return false;
    }
     (*cv_empty).wait(ul, [ this,&working ] () {return ( (!problems.empty() ||  !working) ); } );
     if(problems.empty() && !working){
      return false;
    }
   

     //working && last not ready || (!working && !problems.empty && last not ready) problems.front().second.first->first==problems.front().second.first->second
     
     
      //consider deinc of wokring int after stop
     (*not_ready).wait(ul,[this,&working](){    return  ( check_equal(working)) ;});
     
          
     if(problems.empty() && !working){
      return false;
    }
    
     AProblemPack ptr=problems.front().first;
     
     problems.pop_front();
     
     company->solvedPack(ptr);
     
     ul.unlock();
     return true;

  }

 



};


class Buffer_class_global{
  private:
  
  
  public:
  //deque of problems, problem_type , shared_ptr on pair of count of problems and count of solved problems,
  //shared ptr on mutex which is control editing of previous pair
  //and condition variable to wake up consumer when packet is finished
  deque<pair<APolygon,std::pair< problem_type,std::pair<std::shared_ptr<std::pair<size_t,size_t>>,
  std::pair<std::shared_ptr<std::mutex>,std::shared_ptr<condition_variable>>>>>> problems;
  std::mutex mut1; //mutex for working with problems vector
  std::mutex mut_cnt; //mutex for working with states of solvers inside cnt problems
  std::mutex mut_min; //mutex for working with states of solvers inside min problems
  std::condition_variable no_problems; //cond var 
  int solver_count=0; //same as count of work_threads
 
  
  
  std::vector<AProgtestSolver> solv_cnt;
  std::vector<solver_status> states_cnt;
  std::vector<std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>>>>> cnt_attributtes; //Attributtes of problems for updating theirs states in main deque

  std::vector<AProgtestSolver> solv_min;
  std::vector<solver_status> states_min;
  std::vector<std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>>>>> min_attributtes; //Attributtes of problems for updating theirs states in main deque
  
  //Creating 2 solvers and their states indication for each thread, one thread for cnt computations, another for min comp.
  void initialize_solvers(int number_of_threads){
      solver_count=number_of_threads;
    for(int i=0;i<solver_count;i++){ 
      solv_cnt.push_back(AProgtestSolver());
      solv_min.push_back(AProgtestSolver());
      states_cnt.push_back(solver_status(not_created));
      states_min.push_back(solver_status(not_created));
      cnt_attributtes.push_back(std::make_shared<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>>>>());
  min_attributtes.push_back(std::make_shared<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>>>>());
    }
  }
  void push_back_thread_safe(APolygon & pol,std::shared_ptr<std::pair<size_t,size_t>> & ptr,problem_type type,
  std::shared_ptr<std::mutex> & end_indicator , std::shared_ptr<std::condition_variable> & not_ready){
   
    //critical section
     std::lock_guard<std::mutex> lock(mut1);
    problems.push_back(make_pair(pol,make_pair(type,make_pair(ptr,make_pair(end_indicator,not_ready)))));
    no_problems.notify_one();
  }
  
  void Process_polygons(std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>>>> & polygons_vector ){
    
    
    for(auto & elem : *polygons_vector){
      //critical section for indicators of proceeded problems
      unique_lock<mutex> ul (*elem.second.first);
      
        elem.first->second=elem.first->second+1;
       
        //if count of proceeded problems is equal to count of all problems in packet, then notify consumer
        if(elem.first->first==elem.first->second){
         
          (*elem.second.second).notify_all();
        }
    }
    polygons_vector->clear();
  }

  void min_problem_solve(APolygon & problem, std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>> & additional_param){ 
      std::unique_lock<std::mutex> lock(mut_min);
     
      std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
      std::shared_ptr<condition_variable>>>>> attrubuttes_vector_ptr;
      AProgtestSolver my_solver;
      int solver_index=-1; //Index of solver with status not_full
      for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
          if(states_min[i]==not_full){
              solver_index=i;
              my_solver=solv_min[i];
              break;
          }
      }
      //Case when there is no solver with status not_full
      if(solver_index==-1){ //Finding first unused solver
          for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
              if(states_min[i]==not_created){
                  solver_index=i;
                  solv_min[i]=createProgtestMinSolver(); //initialization of new solver
                  states_min[i]=not_full;
                  my_solver=solv_min[i];
                  break;
              }
          }
      }
      //Finding vector with problems that are in our solver
      attrubuttes_vector_ptr=min_attributtes[solver_index];
      my_solver->addPolygon(problem);
      attrubuttes_vector_ptr->push_back(additional_param);
      if(my_solver->hasFreeCapacity()){ //If solver has free capacity then just leave section
          return;
      }
      else { //If solver is full then we can start our computations
          states_min[solver_index]=working;
          lock.unlock();
          if(my_solver->solve()==0){
              throw std::logic_error("solvers doesnt have capacity\n");
          }
        
          Process_polygons(attrubuttes_vector_ptr);
          
          
          lock.lock();
          states_min[solver_index]=not_created; //Indicating that solver is free now
          lock.unlock();
      }




  }

  void cnt_problem_solve(APolygon & problem, std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>> & additional_param){ 
       std::unique_lock<std::mutex> lock(mut_cnt);
       
       std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
      std::shared_ptr<condition_variable>>>>> attrubuttes_vector_ptr;
      AProgtestSolver my_solver;
      int solver_index=-1; //Index of solver with status not_full
      for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
          if(states_cnt[i]==not_full){
              solver_index=i;
              my_solver=solv_cnt[i];
              break;
          }
      }
      //Case when there is no solver with status not_full
      if(solver_index==-1){ //Finding first unused solver
          for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
              if(states_cnt[i]==not_created){
                  solver_index=i;
                  solv_cnt[i]=createProgtestCntSolver(); //initialization of new solver
                  states_cnt[i]=not_full;
                  my_solver=solv_cnt[i];
                  break;
              }
          }
      }
      attrubuttes_vector_ptr=cnt_attributtes[solver_index];
      my_solver->addPolygon(problem);
       attrubuttes_vector_ptr->push_back(additional_param);
      if(my_solver->hasFreeCapacity()){ //If solver has free capacity then just leave section
          return;
      }
      else { //If solver is full then we can start our computations
          states_cnt[solver_index]=working;
          lock.unlock();
          if(my_solver->solve()==0){
              std::cout<<"solvers doesnt have capacity\n";
          }
          
          Process_polygons(attrubuttes_vector_ptr);
          //Checking if problems was last problems in pack
          //To be implemented...
          lock.lock();
          states_cnt[solver_index]=not_created; //Indicating that solver is free now
          lock.unlock();
      }

  }
  void finish_some_solver_cnt(){
      
       std::unique_lock<std::mutex> lock(mut_cnt);
       
      std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
      std::shared_ptr<condition_variable>>>>> attrubuttes_vector_ptr;
      AProgtestSolver my_solver;
      int solver_index=-1; //Index of solver with status not_full
      for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
          if(states_cnt[i]==not_full){
              solver_index=i;
              my_solver=solv_cnt[i];
              attrubuttes_vector_ptr=cnt_attributtes[i];
              break;
          }
      }
      
     
      //If solver is full then we can start our computations
          states_cnt[solver_index]=working;
          lock.unlock();
          if(my_solver->solve()==0){
               throw std::logic_error("solvers doesnt have capacity.\n");
          }
          
          Process_polygons(attrubuttes_vector_ptr);
          //Checking if problems was last problems in pack
          
          lock.lock();
          states_cnt[solver_index]=not_created; //Indicating that solver is free now
          lock.unlock();
      

  }
  bool check_if_there_are_two_solves_not_full_min(){
    int counter=0;
     for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
          if(states_min[i]==not_full){
              counter++;
             
              break;
          }
      }
      if(counter>1){
        throw std::logic_error("2+ solvers in state not_full.\n");
      }

  }
  bool check_if_there_are_two_solves_not_full_cnt(){
    int counter=0;
     for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
          if(states_cnt[i]==not_full){
              counter++;
             
              break;
          }
      }
      if(counter>1){
        throw std::logic_error("2+ solvers in state not_full.\n");
      }

  }
  void finish_some_solver_min(){
    std::unique_lock<std::mutex> lock(mut_min);
    
      std::shared_ptr<std::vector<std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
      std::shared_ptr<condition_variable>>>>> attrubuttes_vector_ptr;
      AProgtestSolver my_solver;
      int solver_index=-1; //Index of solver with status not_full
      for(int i=0;i<solver_count;i++){  //Finding first solver with status not_full
          if(states_min[i]==not_full){
              solver_index=i;
              my_solver=solv_min[i];
              attrubuttes_vector_ptr=min_attributtes[i];
              break;
          }
      }
      
     
      //If solver is full then we can start our computations
          states_min[solver_index]=working;
          lock.unlock();
          if(my_solver->solve()==0){
            throw std::logic_error("solvers doesnt have capacity.\n");
             
          }
          
          Process_polygons(attrubuttes_vector_ptr);
          //Checking if problems was last problems in pack
          
          lock.lock();
          states_min[solver_index]=not_created; //Indicating that solver is free now
          lock.unlock();
      
  }
  bool thread_safe_check_solvers_cnt(){
    std::unique_lock<std::mutex> lock(mut_cnt);
    for(int i=0;i<solver_count;i++){
      if(states_cnt[i]==not_full){
        return true;
      }
    }
    return false;
  }
  bool thread_safe_check_solvers_min(){
    std::unique_lock<std::mutex> lock(mut_min);
    for(int i=0;i<solver_count;i++){
      if(states_min[i]==not_full){
        return true;
      }
    }
    return false;
  }
  void notify_comp(){
    no_problems.notify_all();
  }
  bool solve(atomic_int & working){
    std::unique_lock<std::mutex> lock(mut1);
    if(problems.empty() && working==0){
      if(thread_safe_check_solvers_cnt()){
      finish_some_solver_cnt();
      return true;
      }
      else if(thread_safe_check_solvers_min()){
        finish_some_solver_min();
        return true;
      }
      else{
        return false;
      }
    }
    

    no_problems.wait(lock, [ this,&working ] () { return (  !(problems.empty() && working!=0)  ); }); //No problems, no work  
    
    if(working==0 && problems.empty()){
      return false;
    }

   
    APolygon problem_to_add=problems.front().first;
    //Entaracting with problem
   std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
  std::shared_ptr<condition_variable>>> addditional_things=problems.front().second.second;
    
    problem_type pr_type=problems.front().second.first;
    problems.pop_front();
    lock.unlock();
    switch (pr_type){
        case min_pr:
        min_problem_solve(problem_to_add,addditional_things);
        break;
        case cnt_pr: //cnt_pr
        cnt_problem_solve(problem_to_add,addditional_things);
        break;
        default:
         throw std::logic_error("unknown type.\n");
        break;
    }
    
      
    

    return true;
  }
};

void producer(int tid,ACompany & company, Buffer_class & buffer,atomic_bool & working , Buffer_class_global & global_buffer,atomic_int & global_working){
  
      while(working==true){
        
        AProblemPack local= company->waitForPack();
       
         if((local)==nullptr){
          
          working=false;
          buffer.notify_before_leaving();
          global_buffer.notify_comp();
          break;
        }
        
       std::pair<AProblemPack,std::pair<std::shared_ptr<std::pair<size_t,size_t>>,std::pair<std::shared_ptr<std::mutex>,
       std::shared_ptr<condition_variable>>>> int_ptr= buffer.push_back_thread_safe(local);
      
        size_t count_of_problems=local->m_ProblemsCnt.size()+local->m_ProblemsMin.size();

        int_ptr.second.first->first=count_of_problems;
        
      for(auto & a : local->m_ProblemsCnt){
        
        //Add indicator of problem's type
        global_buffer.push_back_thread_safe(a,int_ptr.second.first,cnt_pr,int_ptr.second.second.first,int_ptr.second.second.second);
      }
      for(auto & b : local->m_ProblemsMin){
        //Add indicator of problem's type
        global_buffer.push_back_thread_safe(b,int_ptr.second.first,min_pr,int_ptr.second.second.first,int_ptr.second.second.second);
      }
      


      }
      global_working--;
      global_buffer.notify_comp();
      buffer.notify_before_leaving();

    }
    void consumer(int tid,ACompany & company, Buffer_class & buffer,atomic_bool & working , Buffer_class_global & global_buffer,atomic_int & global_working){
      
        while (true)
        {
          if(!buffer.remove_thread_safe(company,working,tid)){
            break;
          }
        }
       
        global_buffer.notify_comp();
        
    }
    
    void computation(int tid,int compt_tid, Buffer_class_global & global_buffer,
    atomic_int & working){
      
      try{
      while (true)

      {
      if(!global_buffer.solve(working)){
        break;
      }
      
      }
      
      
      }
      catch(const std::exception & error){ 
        std::cout <<error.what();
      }
    }




//-------------------------------------------------------------------------------------------------------------------------------------------------------------
class COptimizer
{
  
  public:
    
    static bool                        usingProgtestSolver                     ( void )
    {
      return true;
    }
    static void                        checkAlgorithmMin                       ( APolygon                              p )
    {
      // dummy implementation if usingProgtestSolver() returns true
    }
    static void                        checkAlgorithmCnt                       ( APolygon                              p )
    {
      // dummy implementation if usingProgtestSolver() returns true
    }
    void proceed_company(ACompany company){

    }
    



    void                               start                                   ( int                                   threadCount ){
      int thread_cnt =0;
      
        global_buffer.initialize_solvers(threadCount);
        std::shared_ptr<atomic_bool> bools;
           for(size_t i=0;i<companies.size();i++){
             buffers.push_back(std::make_shared<Buffer_class>());
             Buffer_class tmp;
          buffers_local.push_back(tmp);
          std::shared_ptr<atomic_bool> bools=std::make_shared<std::atomic_bool>(true);
         
          
          working_vector.push_back(bools);
           }   

        working=(int)companies.size();
        for(size_t i=0;i<companies.size();i++){
          std::atomic_bool working_tmp(true);
          threads_companies_producer.push_back ( thread ( producer,thread_cnt, ref(companies[i]),ref(buffers_local[i]),ref(*working_vector[i]),
          ref(global_buffer),ref(working) ) );
          thread_cnt++;
          threads_companies_consumer.push_back ( thread ( consumer,thread_cnt, ref(companies[i]),ref(buffers_local[i]),ref(*working_vector[i]),
          ref(global_buffer),ref(working)) );
          thread_cnt++;
          
        }
        for(int i=0;i<threadCount;i++){
          computations.push_back(thread(computation,thread_cnt,i,ref(global_buffer),ref(working)));
          
          thread_cnt++;
        }
        
        
        
        
      
    }
    void                               stop                                    ( void ){
      for(auto & thr : computations){
          thr.join();
        }
        for(auto & thr : threads_companies_consumer){
            thr.join();
        }
        for( auto & thr : threads_companies_producer){
          thr.join();
        }
       
     

    }
    void                               addCompany                              ( ACompany                              company ){
      companies.push_back(company);

    }
  private:
  
  std::vector<ACompany> companies;
  std::vector<thread> threads_companies_producer;
  std::vector<thread> threads_companies_consumer;
  std::vector<thread> computations;
  
  std::vector<std::shared_ptr<atomic_bool>> working_vector;
  atomic_int working=0; 
  std::vector<std::shared_ptr<Buffer_class>> buffers;
  std::vector<Buffer_class> buffers_local;
  Buffer_class_global global_buffer;
  
};
// TODO: COptimizer implementation goes here
//-------------------------------------------------------------------------------------------------------------------------------------------------------------
#ifndef __PROGTEST__
int                                    main                                    ( int argc, char * argv [] )
{
  int count =0;
  if(sscanf ( argv[1], "%d", &count )       != 1 || count <1){
    printf("Wrong value or no value\n");
  }
  COptimizer optimizer;
  ACompanyTest  company = std::make_shared<CCompanyTest> ();
  optimizer . addCompany ( company );
  

 
  optimizer . start ( 4 );
  optimizer . stop  ();
  if ( ! company -> allProcessed () )
    throw std::logic_error ( "(some) problems were not correctly processsed" );
  
  return 0;
}
#endif /* __PROGTEST__ */
