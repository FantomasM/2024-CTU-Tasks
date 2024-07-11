#include <unistd.h>
#ifndef __PROGTEST__
#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cstdint>
#include <deque>
#include <iomanip>
#include <iostream>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <optional>
#include <queue>
#include <random>
#include <set>
#include <stack>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

enum Point : size_t {};

struct Path {
  Point from, to;
  unsigned length;

  Path(size_t f, size_t t, unsigned l) : from{f}, to{t}, length{l} {}

  friend bool operator == (const Path& a, const Path& b) {
    return std::tie(a.from, a.to, a.length) == std::tie(b.from, b.to, b.length);
  }
  
  friend bool operator != (const Path& a, const Path& b) { return !(a == b); }
};

#endif
//Creating vector of vectors with representation of all neighbours of vertexes in their verctors
//Also indicating, what vertexes are not sources
std::vector<std::vector<std::pair<int,int>>> add_neighbours_to_vertexes(const size_t points ,const std::vector<Path>& all_paths, std::vector<bool> & is_source){
    std::vector<std::vector<std::pair<int,int>>> vector_of_neighbours;
    vector_of_neighbours.resize(points);
    for(size_t i=0;i<all_paths.size();i++){
        vector_of_neighbours[all_paths[i].from].push_back(std::make_pair(all_paths[i].to,all_paths[i].length));
        is_source[all_paths[i].to]=false;
    }
    return vector_of_neighbours;
}



std::vector<int> TopSort(const size_t points,const std::vector<std::vector<std::pair<int,int>>> & vector_of_neighbours) {
        std::queue<int> Q;
        std::vector<int> Beta;
        Beta.resize(points,0);
        for(size_t i=0;i<vector_of_neighbours.size();i++) {
            for(size_t z=0;z<vector_of_neighbours[i].size();z++) {
                    Beta[vector_of_neighbours[i][z].first]++;
            }
        }
        for(size_t i=0;i<points;i++) {
            if(Beta[i]==0) {
                Q.push(i);
            }
        }
    std::vector<int> sorted_vector;
    while(!Q.empty()) {
        int z=Q.front();
        Q.pop();
        sorted_vector.push_back(z);
        for(size_t i=0;i<vector_of_neighbours[z].size();i++) {
           Beta[vector_of_neighbours[z][i].first]--;
            if(Beta[vector_of_neighbours[z][i].first]==0) {
                Q.push(vector_of_neighbours[z][i].first);
            }
        }
    }
    return sorted_vector;

}

std::vector<Path> path_reconstruction(const int index_of_start,const std::vector<std::pair<std::vector<Path>,int>> & path_from_point) {
    int current_index=index_of_start;

    std::vector<Path> final_path;
    while (path_from_point[current_index].second!=-1) {
        int index_in_loop=current_index;

        for(int i=(int)(path_from_point[index_in_loop].first.size()-1);i>=0;i--) {


                final_path.push_back(path_from_point[index_in_loop].first[i]);

            current_index=path_from_point[index_in_loop].first[i].to;


        }

    }

    return final_path;
}
void mini_path_reconstruction(std::vector<std::pair<std::vector<Path>,int>> & path_from_point, int & max_price_from_u,int & i,int & index_of_elem_with_max_price,std::vector<std::pair<int,int>> & Predecessors,
    const size_t & points);
void BFS(int & i,std::vector<std::vector<std::pair<int,int>>> & vector_of_neighbours,int & max_price, int & from ,const size_t & points, std::vector<std::pair<std::vector<Path>,int>> & path_from_point) {
    if(vector_of_neighbours[i].empty()){
            return;
        }
        //Initialization of vector of predecessors for further path reconstruction
        std::vector<std::pair<int,int>> Predecessors; //pair of predecessor and price of this edge
        std::vector<int> Distance;
        Predecessors.resize(points,std::pair<int,int>(-1,-1));
        Distance.resize(points,-1);
        std::vector<bool> visited;
        std::queue<int> main_queue;
        //Inicialization of all vertexes to state: unvisited
        visited.resize(points, false);
        std::vector<int> price;
        price.resize(points, -1);
        //First vertex is opened and pushed to queue
        visited[i] = true;

        price[i] = 0;
        main_queue.push(i);
        int max_price_from_u=0;
        int index_of_elem_with_max_price=-1;
        //While queue is not empty try to access to new vertex by looking for neighbourhoods of u
        while (!main_queue.empty()) {
            int u = main_queue.front();

            main_queue.pop();
            for (auto vertexes: vector_of_neighbours[u]) {

                    if (!visited[vertexes.first] || (path_from_point[vertexes.first].second==-1 && price[vertexes.first]<price[u]+int(vertexes.second)) ||
                        (path_from_point[vertexes.first].second!=-1 && price[vertexes.first]<price[u]+int(vertexes.second)+path_from_point[vertexes.first].second)) {
                        visited[vertexes.first] = true;
                        Predecessors[vertexes.first].first=u;
                        Predecessors[vertexes.first].second=vertexes.second;
                        if(path_from_point[vertexes.first].second!=-1){
                        price[vertexes.first]=price[u]+vertexes.second+path_from_point[vertexes.first].second;
                        Distance[vertexes.first]=price[u]+vertexes.second+path_from_point[vertexes.first].second;
                            for(auto edge : path_from_point[vertexes.first].first) {
                                visited[edge.from]=true;
                                visited[edge.to]=true;
                            }
                        }

                        else{
                        main_queue.push(vertexes.first);



                        Distance[vertexes.first]=price[u]+vertexes.second;
                        //Indicating, what element has the longest path to u

                        price[vertexes.first] = price[u] + vertexes.second;
                        }
                        if(Distance[vertexes.first] > max_price_from_u){
                            max_price_from_u=Distance[vertexes.first];
                            index_of_elem_with_max_price=vertexes.first;
                        }
                        if(price[vertexes.first]>max_price){
                            max_price=price[vertexes.first];
                            from=i;

                        }
                    }


            }


        }
    mini_path_reconstruction(path_from_point,max_price_from_u,i,index_of_elem_with_max_price,Predecessors,points);
}
void mini_path_reconstruction(std::vector<std::pair<std::vector<Path>,int>> & path_from_point, int & max_price_from_u,int & i,int & index_of_elem_with_max_price,std::vector<std::pair<int,int>> & Predecessors,
    const size_t & points) {
    path_from_point[i].second=max_price_from_u;
    int current_point=index_of_elem_with_max_price;
    Path tmp(Predecessors[index_of_elem_with_max_price].first,current_point,Predecessors[index_of_elem_with_max_price].second);
    path_from_point[i].first.push_back(tmp);
    if(index_of_elem_with_max_price==-1){
        throw std::logic_error("Elements without neighbours shouldn't be in this process.\n");
    }
    size_t len=0;
    while(current_point!=i){
        if(len>points) {
            throw std::out_of_range("Count of vertexes in path exceeds count of all vertexes");
        }
        current_point=Predecessors[current_point].first;

        if(current_point!=i) {
            Path tmp_while(Predecessors[current_point].first,current_point,Predecessors[current_point].second);
            path_from_point[i].first.push_back(tmp_while);
        }
        len++;
    }
}
std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths){

    int max_price=0;
    int from=0;

    std::vector<std::vector<std::pair<int,int>>> vector_of_neighbours; // pair of to and length(price)
    vector_of_neighbours.resize(points);
    std::vector<bool> is_source;
    is_source.resize(points, true);
    vector_of_neighbours=add_neighbours_to_vertexes(points,all_paths,is_source);
    std::vector<std::pair<std::vector<Path>,int>> path_from_point; //Vector of longest paths from every vertex with price of path
    path_from_point.resize(points,std::pair<std::vector<Path>,int>(std::vector<Path>(),-1));



    std::vector<int> after_TopSort;
    after_TopSort=TopSort(points,vector_of_neighbours);
    if(after_TopSort.size()!=points) {
        printf("Graph contains an oriented cycle\n");
        return std::vector<Path>();

    }

    for(auto i : after_TopSort) {
        BFS(i,vector_of_neighbours,max_price,from,points,path_from_point);


    }
    return path_reconstruction(from,path_from_point);
}


#ifndef __PROGTEST__


struct Test {
  unsigned longest_track;
  size_t points;
  std::vector<Path> all_paths;
};

inline const Test TESTS[] = {
  {13, 5, { {3,2,10}, {3,0,9}, {0,2,3}, {2,4,1} } },
  {11, 5, { {3,2,10}, {3,1,4}, {1,2,3}, {2,4,1} } },
  {16, 8, { {3,2,10}, {3,1,1}, {1,2,3}, {1,4,15} } },
};

#define CHECK(cond, ...) do { \
    if (cond) break; \
    printf("Fail: " __VA_ARGS__); \
    printf("\n"); \
    return false; \
  } while (0)

bool run_test(const Test& t) {
  auto sol = longest_track(t.points, t.all_paths);

  unsigned length = 0;
  for (auto [ _, __, l ] : sol) length += l;

  CHECK(t.longest_track == length,
    "Wrong length: got %u but expected %u", length, t.longest_track);

  for (size_t i = 0; i < sol.size(); i++) {
    CHECK(std::count(t.all_paths.begin(), t.all_paths.end(), sol[i]),
      "Solution contains non-existent path: %zu -> %zu (%u)",
      sol[i].from, sol[i].to, sol[i].length);

    if (i > 0) CHECK(sol[i].from == sol[i-1].to,
      "Paths are not consecutive: %zu != %zu", sol[i-1].to, sol[i].from);
  }

  return true;
}
#undef CHECK

int main() {
  int ok = 0, fail = 0;

  for (auto&& t : TESTS) (run_test(t) ? ok : fail)++;
  
  if (!fail) printf("Passed all %i tests!\n", ok);
  else printf("Failed %u of %u tests.\n", fail, fail + ok);
}

#endif


