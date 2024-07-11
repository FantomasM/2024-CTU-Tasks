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


std::vector<Path> longest_track(size_t points, const std::vector<Path>& all_paths){

    int max_price=0;
    int from=0;
    int to=0;
    std::vector<std::vector<std::pair<int,int>>> path_from_point; // pair of to and length(price)
    path_from_point.resize(points);
    std::vector<bool> main;
    main.resize(points, true);
    for(size_t i=0;i<all_paths.size();i++){
        path_from_point[all_paths[i].from].push_back(std::make_pair(all_paths[i].to,all_paths[i].length));
        main[all_paths[i].to]=false;
    }




    for(size_t i=0;i<points;i++) {
        if(path_from_point[i].empty() ||!main[i]){
            continue;
        }
        std::vector<bool> visited;
        std::queue<int> main_queue;
        //Inicialization of all vertexes to state: unvisited
        visited.resize(points, false);
        std::vector<int> price;
        price.resize(points, 0);
        //First vertex is opened and pushed to queue
        visited[i] = true;

        price[i] = 0;
        main_queue.push(i);

        //While queue is not empty try to access to new vertex by looking for neighbourhoods of u
        while (!main_queue.empty()) {
            int u = main_queue.front();

            main_queue.pop();
            for (auto vertexes: path_from_point[u]) {

                    if (!visited[vertexes.first] || price[vertexes.first]<price[u]+int(vertexes.second)) {
                        visited[vertexes.first] = true;
                        main_queue.push(vertexes.first);

                        price[vertexes.first] = price[u] + vertexes.second;
                        if(price[vertexes.first]>max_price){
                            max_price=price[vertexes.first];
                            from=i;
                            to=vertexes.first;
                        }
                    }

            }


        }
    }
    //std::cout <<"Longest path is from " <<from <<" to " <<to <<" and price is " <<max_price <<std::endl;
    std::vector<bool> visited;
    std::queue<int> main_queue;
    //Inicialization of all vertexes to state: unvisited
    visited.resize(points, false);
    std::vector<int> price;
    price.resize(points, 0);
    //First vertex is opened and pushed to queue
    visited[from] = true;

    price[from] = 0;
    main_queue.push(from);
   // std::unordered_map<int,std::vector<std::pair<int,int>>> old_paths;
  //  std::unordered_map<int,std::vector<std::pair<int,int>>> new_paths;
    std::vector<std::vector<std::pair<int,int>>> path_new;
    path_new.resize(points);
    path_new[from].push_back(std::make_pair(from,0));
  //  new_paths[from].push_back(std::make_pair(from,0));

    //While queue is not empty try to access to new vertex by looking for neighbourhoods of u
    while (!main_queue.empty()) {
        int u = main_queue.front();

        main_queue.pop();
        for (auto vertexes: path_from_point[u]) {

                if (!visited[vertexes.first] || price[vertexes.first]<price[u]+int(vertexes.second)) {
                    visited[vertexes.first] = true;
                    path_new[vertexes.first]=path_new[u];
                    path_new[vertexes.first].push_back(std::make_pair(vertexes.first,vertexes.second));
                   // new_paths[vertexes.first]=new_paths[u];
                  //  new_paths[vertexes.first].push_back(std::make_pair(vertexes.first,vertexes.second));
                    main_queue.push(vertexes.first);

                    price[vertexes.first] = price[u] + vertexes.second;
                    if(int(vertexes.first)==to && price[vertexes.first]==max_price){
                        break;
                    }
                }

        }
       // old_paths=new_paths;


    }
  //  std::cout <<" path from " <<from <<" to " <<to <<"is look like:\n";
  //  for(auto c : new_paths[to]){
       // std::cout <<" "<<c.first <<" ";

  //  }
    std::vector<Path> final;

    for(size_t i=0;i<path_new[to].size()-1;i++){
        final.push_back(Path(path_new[to][i].first,path_new[to][i+1].first,path_new[to][i+1].second));

    }
    //std::cout<<std::endl;
    return final;

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


