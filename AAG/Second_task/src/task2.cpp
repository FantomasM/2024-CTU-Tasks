#ifndef __PROGTEST__
#include <algorithm>
#include <cassert>
#include <cctype>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <memory>
#include <numeric>
#include <optional>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <vector>

using namespace std;
using Symbol = char;
using Word = std::vector<Symbol>;

struct Grammar {
    std::set<Symbol> m_Nonterminals;
    std::set<Symbol> m_Terminals;
    std::vector<std::pair<Symbol, std::vector<Symbol>>> m_Rules;
    Symbol m_InitialSymbol;
};
#endif

struct Symbol_track{
    Symbol symbol;
    const Symbol_track * first_rod= nullptr,*second_rod= nullptr;
    int rule_number;
    int step;
    bool last;
};

bool operator < (const  Symbol_track & one, const Symbol_track & two){
    return one.symbol <two.symbol;
}


void generate_all_combinations(const std::vector<Symbol> & symbols,std::vector<std::vector<Symbol>> & combinations){
    size_t base=symbols.size();

    for(int i=0;i<std::pow(base,base);i++){
        size_t tmp=i;
        std::vector<Symbol> combination;

        for(size_t j=0;j<base;j++){
            combination.push_back(symbols[tmp%base]);
            tmp /=base;
        }

            combinations.push_back(combination);

    }
    combinations.push_back(std::vector<Symbol>());




}

void generate_almost_all_combinations_rec(const std::vector<Symbol> & symbols,size_t start,std::vector<Symbol> & cur,std::vector<std::vector<Symbol>> & combinations){
    size_t len=symbols.size();

    combinations.push_back(cur);

    for(size_t i=start;i<len;i++){
        cur.push_back(symbols[i]);
        generate_almost_all_combinations_rec(symbols,i+1,cur,combinations);
        cur.pop_back();
    }
    // for(size_t i=0;i<len;i++){
    //  for(size_t)
    // }




}
void generate_almost_all_combinations(const std::vector<Symbol> & symbols,std::vector<std::vector<Symbol>> & combinations){
    size_t len=symbols.size();
    for(size_t i=0;i<len;i++){
        std::vector<Symbol> combination;
        for(size_t z=i;z<len;z++){
            combination.push_back(symbols[z]);

            //std::vector<Symbol> combination(symbols.begin()+i,symbols.begin()+z+1);
            combinations.push_back(combination);
        }
    }
   // for(size_t i=0;i<len;i++){
      //  for(size_t)
   // }


    combinations.push_back(std::vector<Symbol>());

}

bool has_all_must_have_term(const std::vector<Symbol> & first, const std::vector<Symbol> & second){
    for(const auto & sec_el : second){
        bool there= false;
        for(const auto & first_el : first){
            if(sec_el==first_el){
                there= true;
            }
        }
        if(!there){
            return false;
        }
    }
    return true;
}


void epsilon_rules_delete( Grammar & gram){
    std::set<Symbol> eps_gen;
    bool start_symbol_epsilon= false;
    /// First iteration : adding nonterminals that have rule "Nonterminal ->epsilon"
    for( const auto & term : gram.m_Nonterminals){
        for(const auto & rule : gram.m_Rules){
            if(rule.first==term && rule.second.empty()){
                eps_gen.insert(term);
                if(term==gram.m_InitialSymbol){
                    start_symbol_epsilon= true;
                }
            }
        }
    }
    //2 - n iteration : adding nonterminals, that have rule "Nonterminal -> nonterminal, who can generate espilon"
    std::cout <<"size of nont is " <<gram.m_Nonterminals.size() <<std::endl;
    for(size_t i=0;i<gram.m_Nonterminals.size();i++) {
        bool do_something= false;
        for (const auto & term: gram.m_Nonterminals) {

            for(const auto & rule : gram.m_Rules){
                /*
                if(rule.first==term && !rule.second.empty() && std::all_of(rule.second.begin(),rule.second.end(),[&eps_gen](Symbol a){
                    if(eps_gen.find(a)!=eps_gen.end()){
                    return true;
                }
                    return false;
                })){
                 */
                bool all_same= false;
                std::cout <<" rule first is " <<rule.first << "term is" <<term <<std::endl;
                if(rule.first==term && !rule.second.empty()){
                    all_same= true;
                    for(const auto & to : rule.second){
                        if(eps_gen.find(to)==eps_gen.end()){
                            all_same= false;
                        }
                    }
                }

                if(all_same){
                    eps_gen.insert(term);
                    if(gram.m_InitialSymbol==term && !start_symbol_epsilon){

                        gram.m_Rules.push_back(std::pair<Symbol ,std::vector<Symbol>>(gram.m_InitialSymbol,std::vector<Symbol>()));
                        start_symbol_epsilon= true;
                    }
                    do_something= true;
                }
            }
        }
        if(!do_something){
            break;
        }
    }
    // checking if Start symbol is on the left side of some rule
    bool start_symbol_on_left = false;
    if(start_symbol_epsilon) {

        for (const auto &rule: gram.m_Rules) {
            if(!rule.second.empty()){
                for(const auto & prob_start_symbol : rule.second){
                    if(gram.m_InitialSymbol==prob_start_symbol){
                        start_symbol_on_left= true;
                    }
                }
            }
        }



    }
    std::vector<std::pair<Symbol, std::vector<Symbol>>> new_m_Rules;
    //Deleting epsilon rules except for situation, when start symbol-> epsilon
    for(const auto & rule : gram.m_Rules){
        if(!rule.second.empty() || (rule.first==gram.m_InitialSymbol && start_symbol_epsilon && !start_symbol_on_left)){
            new_m_Rules.push_back(rule);
        }
    }

   //Adding new initial symbol and rules for him
    if(start_symbol_epsilon && start_symbol_on_left){
        gram.m_Nonterminals.insert('*');
        new_m_Rules.push_back(std::pair<Symbol ,std::vector<Symbol>>('*',{gram.m_InitialSymbol}));
        new_m_Rules.push_back(std::pair<Symbol ,std::vector<Symbol>>('*',{}));
        gram.m_InitialSymbol='*';
    }
    std::vector<std::pair<Symbol, std::vector<Symbol>>> new_new_m_Rules;
    for(const auto & rule : new_m_Rules){
        std::pair<bool,bool> indic=std::make_pair(false, false);
        std::vector<Symbol> to_combine;
        std::vector<Symbol> must_have;

        for(const auto & sec_par : rule.second){

            to_combine.push_back(sec_par);
            if(eps_gen.find(sec_par)!=eps_gen.end()){
                if(!indic.first){

                    indic.first= true;
                    continue;
                }
                else{

                    indic.second= true;
                }
            }
            else{
                must_have.push_back(sec_par);
            }
        }

        if(indic.first && indic.second){
            std::vector<std::vector<Symbol>> tmp_vector;
            std::vector<Symbol> tmp_2;
            generate_almost_all_combinations_rec(to_combine,0,tmp_2,tmp_vector);
            tmp_vector.push_back(std::vector<Symbol>());

            for(const auto & str : tmp_vector) {
                if (has_all_must_have_term(str, must_have) && !str.empty()) {
                    new_new_m_Rules.push_back(std::pair<Symbol, std::vector<Symbol>>(rule.first, str));
                }
            }


        }
        else if(indic.first){
            std::vector<Symbol> new_rule_to;
            if(rule.second.size()>1){

                for(const auto & sym : rule.second){
                    if(eps_gen.find(sym)==eps_gen.end()){
                        new_rule_to.push_back(sym);
                    }
                }
            }
            new_new_m_Rules.push_back(rule);
            if(!new_rule_to.empty()) {
                new_new_m_Rules.push_back(std::pair<Symbol, std::vector<Symbol>>(rule.first, new_rule_to));
            }
        }
        else{
            new_new_m_Rules.push_back(rule);
        }
    }
    for(const auto & rule : new_new_m_Rules){
        std::cout <<"From " <<rule.first <<"to ";
        for(const auto & to : rule.second){
            std::cout <<" " <<to <<" ";
        }
        std::cout<<std::endl;
    }
    gram.m_Rules=new_new_m_Rules;

}

void simple_rules_delete(Grammar & gram){
    std::map<Symbol,std::set<Symbol>> closure;
    //Adding elem to closure
    for(const auto & sym : gram.m_Nonterminals){
        closure[sym].insert(sym);
    }
    //Creating closure of simple rules
    for(const auto & rule : gram.m_Rules) {
        if(rule.second.size()==1 && gram.m_Nonterminals.find(rule.second[0])!=gram.m_Nonterminals.end()){
            closure[rule.first].insert(rule.second[0]);
        }
    }
    for(size_t i=0;i<gram.m_Nonterminals.size();i++){
        bool smth= false;
        for(const auto & sec_sym : gram.m_Nonterminals){
            for(const auto & uz : closure[sec_sym]){
                for(const auto & sec_uz : closure[uz]){
                    if(closure[sec_sym].find(sec_uz) == closure[sec_sym].end()){
                        smth= true;
                        closure[sec_sym].insert(sec_uz);
                    }
                }
            }
        }
        if(!smth){
            break;
        }
    }
    std::vector<std::pair<Symbol, std::vector<Symbol>>> new_m_Rules;
    for(const auto & sym : gram.m_Nonterminals){
        for(const auto & uz : closure[sym]){
            for(const auto & rule : gram.m_Rules){
                if( rule.first==uz && ( rule.second.size() >1 || (rule.second.size()==1 && gram.m_Nonterminals.find(rule.second[0])==gram.m_Nonterminals.end() ) )){
                    new_m_Rules.push_back(std::pair<Symbol,std::vector<Symbol>>(sym,rule.second));
                }
            }
        }
    }
    gram.m_Rules=new_m_Rules;
    /*
    for(const auto & sym : closure){
        std::cout <<"from " <<sym.first <<" to ";
        for(const auto & to : sym.second){
            std::cout <<" " <<to <<" ";
        }
        std::cout <<std::endl;
    }
     */
    for(const auto & rule : new_m_Rules){
        std::cout <<"from " <<rule.first <<" to ";
        for(const auto & to : rule.second){
            std::cout<<" " <<to <<" ";
        }
        std::cout<<std::endl;
    }





}
void deletion_of_not_gen_symbols(Grammar & gram){
    std::set<Symbol> fin_symbols;
    for(const auto & rule : gram.m_Rules){
        bool fin= true;
        for(const auto & to : rule.second){
            if(gram.m_Nonterminals.find(to)!=gram.m_Nonterminals.end()){
                fin= false;
            }
        }
        if(fin){
            fin_symbols.insert(rule.first);
        }


    }

    for(size_t i=0;i<gram.m_Nonterminals.size();i++){
        bool smth= false;
        for(const auto & non_t_2 : gram.m_Nonterminals){

            for(const auto & rule : gram.m_Rules){
                if(rule.first==non_t_2){
                    bool all_gen= true;
                    if(rule.second.empty()){
                        all_gen= false;
                    }
                    std::cout <<"Parsing rule " <<rule.first <<" to ";
                    for(const auto & to : rule.second){
                        std::cout<<" " <<to <<" ";
                        if(fin_symbols.find(to)==fin_symbols.end()){
                            all_gen= false;
                        }
                    }
                    std::cout <<std::endl;
                    if(all_gen){
                        smth= true;
                        fin_symbols.insert(non_t_2);
                    }
                }
            }

        }
        if(!smth){
            break;
        }
    }
    std::cout <<"Fin symbols : ";
    for(const auto & fin : fin_symbols){
        std::cout <<" " <<fin;
    }
    std::cout <<std::endl;

    std::vector<std::pair<Symbol, std::vector<Symbol>>> new_m_Rules;
    gram.m_Nonterminals=fin_symbols;
    for(const auto & rule : gram.m_Rules){
        bool all_ok= true;
        if(gram.m_Nonterminals.find(rule.first)==gram.m_Nonterminals.end()){
            all_ok= false;
            continue;
        }
        else{
            for(const auto & to : rule.second){
                if(gram.m_Terminals.find(to)==gram.m_Terminals.end() && gram.m_Nonterminals.find(to)==gram.m_Nonterminals.end()){
                    all_ok= false;
                }
            }
            if(all_ok){
                new_m_Rules.push_back(rule);
            }
        }
    }

    for(const auto & rule : new_m_Rules){
        std::cout <<"from " <<rule.first <<" to ";
        for(const auto & to : rule.second){
            std::cout<<" " <<to <<" ";
        }
        std::cout<<std::endl;
    }
    gram.m_Rules=new_m_Rules;




}


void unreachable_symbols_deletion(Grammar & gram){
    ///Finally its time for bfs

    queue<Symbol> queue1;
    std::set<Symbol> visited;
    queue1.push(gram.m_InitialSymbol);
    visited.insert(gram.m_InitialSymbol);

    while(!queue1.empty()){
        Symbol cur=queue1.front();
        queue1.pop();


        for(const auto & rule : gram.m_Rules){
            if(rule.first==cur){
                for(const auto & to : rule.second){
                    if(gram.m_Nonterminals.find(to)!=gram.m_Nonterminals.end() && visited.find(to)==visited.end()){
                        queue1.push(to);
                        visited.insert(to);
                    }
                }
            }
        }




    }
    gram.m_Nonterminals=visited;
    std::vector<std::pair<Symbol, std::vector<Symbol>>> new_m_Rules;
    for(const auto & rule : gram.m_Rules) {

        if (gram.m_Nonterminals.find(rule.first) == gram.m_Nonterminals.end()) {

            continue;
        }
        else{
            new_m_Rules.push_back(rule);
        }
    }
    std::cout <<std::endl;
    for(const auto & rule : new_m_Rules){
        std::cout <<"from " <<rule.first <<" to ";
        for(const auto & to : rule.second){
            std::cout<<" " <<to <<" ";
        }
        std::cout<<std::endl;
    }
    gram.m_Rules=new_m_Rules;





}

void postorder_ins(const Symbol_track * sym,std::vector<size_t> & trace_1){
    if(sym!= nullptr){
        cout<<sym->rule_number <<" ";
        trace_1.push_back(sym->rule_number);
        postorder_ins(sym->first_rod,trace_1);
        postorder_ins(sym->second_rod,trace_1);

    }
}
void postorder_inner(const Symbol_track & sym,std::vector<size_t> & trace_1){
    postorder_ins(&sym,trace_1);
}

std::vector<size_t> trace(const Grammar& gram, const Word & word){
    Grammar  grammar=gram;
   // epsilon_rules_delete(grammar);
   // simple_rules_delete(grammar);
   // deletion_of_not_gen_symbols(grammar);
   // unreachable_symbols_deletion(grammar);
   /* std::cout <<"Final res is \n";
    for(const auto & rule : grammar.m_Rules){
        std::cout <<"from " <<rule.first <<" to ";
        for(const auto & to : rule.second){
            std::cout<<" " <<to <<" ";
        }
        std::cout<<std::endl;
    }
    */
    ///CYK parse
    int size_word=(int)word.size();


    map<size_t,map<size_t ,set<Symbol_track>>> Array;

    for(int i=0;i<size_word;i++){

        for(const auto & rule : grammar.m_Rules){

            Symbol lhs=rule.first;

            vector<std::pair<int,vector<Symbol>>> rule_x;
            size_t num_of_rule=0;
            for(const auto & rule_2 : grammar.m_Rules){
                if(rule_2.first==lhs){
                    rule_x.push_back(std::make_pair(num_of_rule,rule_2.second));
                }
                num_of_rule++;
            }
            size_t rhs_index=0;
            for(auto rhs : rule_x){

                if(rhs.second.size()==1 && rhs.second[0]==word[i]){
                    Symbol_track sym[1];
                    sym[0].symbol=lhs;
                    sym[0].rule_number=rhs.first;
                    sym[0].step=0;
                    sym[0].last= true;
                    Array[i][i].insert(sym[0]);

                }
                rhs_index++;
            }

        }

        for(int j=i;j>=0;j--){

            for(int k=j;k<=i;k++){
                for(const auto & rule : grammar.m_Rules){

                    Symbol lhs=rule.first;
                    vector<std::pair<int,vector<Symbol>>> rule_x;
                    size_t num_of_rule=0;
                    for(const auto & rule_2 : grammar.m_Rules){
                        if(rule_2.first==lhs){
                            rule_x.push_back(std::make_pair(num_of_rule,rule_2.second));
                        }
                        num_of_rule++;
                    }
                    size_t rhs_index=0;
                    for(const auto & rhs : rule_x){
                            Symbol_track tmp[2];
                            if(rhs.second.size()==2) {
                                tmp[0].symbol = rhs.second[0];
                                tmp[1].symbol = rhs.second[1];
                            }
                        if(rhs.second.size()==2 && Array[j][k].find(tmp[0])!=Array[j][k].end() &&
                        Array[k+1][i].find(tmp[1])!=Array[k+1][i].end()){
                            Symbol_track to_ins[1];
                            to_ins[0].symbol=lhs;
                            to_ins[0].step=j;
                            to_ins[0].rule_number=rhs.first;
                            to_ins[0].last= false;
                            auto iter=(Array[j][k].find(tmp[0]));
                         //   to_ins[0].first_rod=std::addressof(*iter);
                            to_ins[0].first_rod=&(*iter);
                            iter=(Array[k+1][i].find(tmp[1]));
                            to_ins[0].second_rod=&(*iter);
                           /* if(Array[j][i].find(to_ins[0])!=Array[j][i].end()){
                                if(rhs.first< Array[j][i].find(to_ins[0])->rule_number){
                                    Array[j][i].erase(to_ins[0]);
                                    Array[j][i].insert(to_ins[0]);
                                }
                            }
                            */
                           // else {
                                Array[j][i].insert(to_ins[0]);
                            //}

                        }
                        rhs_index++;
                    }

                }


            }




        }








    }
    std::vector<size_t> trace_ret;
    if(size_word==0){
        size_t rule_n0=0;
        for(const auto & rule : grammar.m_Rules){
            if(rule.first==grammar.m_InitialSymbol && rule.second.empty()){
                trace_ret.push_back(rule_n0);
                return trace_ret;
            }
            rule_n0++;
        }
    }


    if(Array[0][size_word-1].size()!=0){
        bool Yes=false;
        for(const auto & s : Array[0][size_word-1]){
            if(s.symbol==grammar.m_InitialSymbol){
                Yes= true;
                postorder_inner(s,trace_ret);
            }
        }
        if(Yes) {
            //std::cout << "Vyslo \n";
            return trace_ret;
        }
        else{

            std::cout <<"Ne\n";
            return std::vector<size_t>();
        }


        for(const auto & row : Array){
            for(const auto & col : row.second){
                std::cout<<" From [" <<row.first<<","<<col.first<<"]: ";
                for(Symbol_track sym : col.second){
                    char ruleindex=sym.symbol;
                    if(!sym.last) {
                        std::cout << ruleindex << " was created by " << sym.first_rod->symbol << " and " << sym.second_rod->symbol
                                  << " v kroku " << sym.step <<" | ";
                    }
                    else{
                        std::cout << ruleindex << "was created v kroku " << sym.step <<" | ";
                    }
                }
                std::cout<<std::endl;
            }

        }

    }
    else{
        std::cout <<"Ne\n";
    }


    return std::vector<size_t>();
}

#ifndef __PROGTEST__
/*
int main()
{

    Grammar test0{
            {'S','A','B','C'},
            {'a','b'},
            {
                    {'S', {'A', 'B', 'C'}},

                    {'A',{'a','A'}},
                    {'A',{}},
                    {'B',{'A'}},
                    {'B',{'b','b'}},
                    {'C',{}}
            },
            'S'};


    //epsilon_rules_delete(test0);

    Grammar test1{
            {'S','A','B','C','D'},
            {'a','b','c','d'},
            {
                    {'S',{'A'}},
                    {'S',{'B'}},
                    {'A',{'C'}},
                    {'A',{'a','A'}},
                    {'A',{'b','S'}},
                    {'B',{'D'}},
                    {'B',{'c','B'}},
                    {'B',{'d','S'}},
                    {'C',{'b','C'}},
                    {'C',{'a'}},
                    {'D',{'d','D'}},
                    {'D',{'c'}}
            },
            'S'
    };
    //simple_rules_delete(test1);

    Grammar test2{
            {'S','A','B','C','D'},
            {'a','b','c'},
            {
                    {'S',{'A','B'}},
                    {'S',{'C'}},
                    {'A',{'a','A'}},
                    {'A',{'a'}},
                    {'B',{'b','B'}},
                    {'C',{'c'}},
                    {'D',{'b','c'}}
            },
            'S'
    };
    Grammar test3{
            {'S','A','B','C'},
            {'a','b'},
            {
                    {'S', {'A', 'B'}},
                    {'S', {'B', 'C'}},
                    {'A', {'B', 'A'}},
                    {'A', {'a'}},
                    {'B', {'C', 'C'}},
                    {'B', {'b'}},
                    {'C', {'A', 'B'}},
                    {'C', {'a'}},
            },


    'S'};
   std::vector<size_t> ran=trace(test3,{'b', 'a', 'a', 'b', 'a'});
   // deletion_of_not_gen_symbols(test2);
    //unreachable_symbols_deletion(test2);

    Grammar g0{
        {'A', 'B', 'C', 'S'},
        {'a', 'b'},
        {
            {'S', {'A', 'B'}},
            {'S', {'B', 'C'}},
            {'A', {'B', 'A'}},
            {'A', {'a'}},
            {'B', {'C', 'C'}},
            {'B', {'b'}},
            {'C', {'A', 'B'}},
            {'C', {'a'}},
        },
        'S'};
   // std::vector<size_t> ran=trace(g0,{'b', 'a', 'a', 'b', 'a'});
    //std::vector<size_t> ran_2=trace(g0,{'b'});
    trace(g0, {'b', 'a', 'a', 'b', 'a'});
    trace(g0, {'b'});
    trace(g0, {'a'});
    trace(g0, {});
    trace(g0, {'a', 'a', 'a', 'a', 'a'});
    trace(g0, {'a', 'b'});
    trace(g0, {'b', 'a'});
    trace(g0, {'c', 'a'});



   // assert(trace(g0, {'b', 'a', 'a', 'b', 'a'}) == std::vector<size_t>({0, 2, 5, 3, 4, 6, 3, 5, 7}));
    assert(trace(g0, {'b'}) == std::vector<size_t>({}));
    assert(trace(g0, {'a'}) == std::vector<size_t>({}));
    assert(trace(g0, {}) == std::vector<size_t>({}));
    assert(trace(g0, {'a', 'a', 'a', 'a', 'a'}) == std::vector<size_t>({1, 4, 6, 3, 4, 7, 7, 7, 7}));
    assert(trace(g0, {'a', 'b'}) == std::vector<size_t>({0, 3, 5}));
    assert(trace(g0, {'b', 'a'}) == std::vector<size_t>({1, 5, 7}));
    assert(trace(g0, {'c', 'a'}) == std::vector<size_t>({}));

    Grammar g1{
        {'A', 'B'},
        {'x', 'y'},
        {
            {'A', {}},
            {'A', {'x'}},
            {'B', {'x'}},
            {'A', {'B', 'B'}},
            {'B', {'B', 'B'}},
        },
        'A'};

    assert(trace(g1, {}) == std::vector<size_t>({0}));
    assert(trace(g1, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g1, {'x', 'x'}) == std::vector<size_t>({3, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2}));

    Grammar g2{
        {'A', 'B'},
        {'x', 'y'},
        {
            {'A', {'x'}},
            {'B', {'x'}},
            {'A', {'B', 'B'}},
            {'B', {'B', 'B'}},
        },
        'B'};

    assert(trace(g2, {}) == std::vector<size_t>({}));
    assert(trace(g2, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g2, {'x', 'x'}) == std::vector<size_t>({3, 1, 1}));
    assert(trace(g2, {'x', 'x', 'x'}) == std::vector<size_t>({3, 3, 1, 1, 1}));

    Grammar g3{
        {'A', 'B', 'C', 'D', 'E', 'S'},
        {'a', 'b'},
        {
            {'S', {'A', 'B'}},
            {'S', {'S', 'S'}},
            {'S', {'a'}},
            {'A', {'B', 'S'}},
            {'A', {'C', 'D'}},
            {'A', {'b'}},
            {'B', {'D', 'D'}},
            {'B', {'b'}},
            {'C', {'D', 'E'}},
            {'C', {'b'}},
            {'C', {'a'}},
            {'D', {'a'}},
            {'E', {'S', 'S'}},
        },
        'S'};

    assert(trace(g3, {}) == std::vector<size_t>({}));
    assert(trace(g3, {'b'}) == std::vector<size_t>({}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b'}) == std::vector<size_t>({1, 2, 0, 3, 7, 1, 2, 2, 7}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'a'}) == std::vector<size_t>({1, 1, 0, 4, 8, 11, 12, 0, 5, 6, 11, 11, 0, 4, 9, 11, 7, 11, 7, 2, 2}));

}
*/
int main()
{
    /*
    Grammar g0{
            {'A', 'B', 'C', 'S'},
            {'a', 'b'},
            {
                    {'S', {'A', 'B'}},
                    {'S', {'B', 'C'}},
                    {'A', {'B', 'A'}},
                    {'A', {'a'}},
                    {'B', {'C', 'C'}},
                    {'B', {'b'}},
                    {'C', {'A', 'B'}},
                    {'C', {'a'}},
            },
            'S'};

    assert(trace(g0, {'b', 'a', 'a', 'b', 'a'}) == std::vector<size_t>({0, 2, 5, 3, 4, 6, 3, 5, 7}));
    assert(trace(g0, {'b'}) == std::vector<size_t>({}));
    assert(trace(g0, {'a'}) == std::vector<size_t>({}));
    assert(trace(g0, {}) == std::vector<size_t>({}));
    assert(trace(g0, {'a', 'a', 'a', 'a', 'a'}) == std::vector<size_t>({1, 4, 6, 3, 4, 7, 7, 7, 7}));
    assert(trace(g0, {'a', 'b'}) == std::vector<size_t>({0, 3, 5}));
    assert(trace(g0, {'b', 'a'}) == std::vector<size_t>({1, 5, 7}));
    assert(trace(g0, {'c', 'a'}) == std::vector<size_t>({}));
    */
    Grammar g1{
            {'A', 'B'},
            {'x', 'y'},
            {
                    {'A', {}},
                    {'A', {'x'}},
                    {'B', {'x'}},
                    {'A', {'B', 'B'}},
                    {'B', {'B', 'B'}},
            },
            'A'};

    assert(trace(g1, {}) == std::vector<size_t>({0}));

    assert(trace(g1, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g1, {'x', 'x'}) == std::vector<size_t>({3, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert(trace(g1, {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'}) == std::vector<size_t>({3, 4, 4, 4, 4, 4, 4, 4, 2, 2, 2, 2, 2, 2, 2, 2, 2}));

    Grammar g2{
            {'A', 'B'},
            {'x', 'y'},
            {
                    {'A', {'x'}},
                    {'B', {'x'}},
                    {'A', {'B', 'B'}},
                    {'B', {'B', 'B'}},
            },
            'B'};

    assert(trace(g2, {}) == std::vector<size_t>({}));
    assert(trace(g2, {'x'}) == std::vector<size_t>({1}));
    assert(trace(g2, {'x', 'x'}) == std::vector<size_t>({3, 1, 1}));
    assert(trace(g2, {'x', 'x', 'x'}) == std::vector<size_t>({3, 3, 1, 1, 1}));

    Grammar g3{
            {'A', 'B', 'C', 'D', 'E', 'S'},
            {'a', 'b'},
            {
                    {'S', {'A', 'B'}},
                    {'S', {'S', 'S'}},
                    {'S', {'a'}},
                    {'A', {'B', 'S'}},
                    {'A', {'C', 'D'}},
                    {'A', {'b'}},
                    {'B', {'D', 'D'}},
                    {'B', {'b'}},
                    {'C', {'D', 'E'}},
                    {'C', {'b'}},
                    {'C', {'a'}},
                    {'D', {'a'}},
                    {'E', {'S', 'S'}},
            },
            'S'};

    assert(trace(g3, {}) == std::vector<size_t>({}));
    assert(trace(g3, {'b'}) == std::vector<size_t>({}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b'}) == std::vector<size_t>({1, 2, 0, 3, 7, 1, 2, 2, 7}));
    assert(trace(g3, {'a', 'b', 'a', 'a', 'b', 'a', 'b', 'a', 'b', 'a', 'a'}) == std::vector<size_t>({1, 1, 0, 4, 8, 11, 12, 0, 5, 6, 11, 11, 0, 4, 9, 11, 7, 11, 7, 2, 2}));
}

#endif

