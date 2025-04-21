#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here

bool search(const AvailabilityMatrix& avail,const size_t dailyNeed,const size_t maxShifts,DailySchedule& sched, std::vector<int>& worker_usage, int loc,int k, int fill);
// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    int k = avail[0].size();
    std::vector<int> worker_usage(avail[0].size());
    sched.resize(avail.size());
    return search(avail, dailyNeed, maxShifts, sched, worker_usage, 0, k,0);

}

bool search(const AvailabilityMatrix& avail,const size_t dailyNeed,const size_t maxShifts,DailySchedule& sched, std::vector<int>& worker_usage, int loc,int k, int fill){
    if(loc==avail.size()){
      return true;
    }
    if(fill==dailyNeed){
      return search(avail, dailyNeed, maxShifts, sched, worker_usage, loc+1, k, 0);
    }
    // size_t fill =0;
    for(int i =0; i< (k); ++i){
      if(avail[loc][i]==true){
        if(worker_usage[i]<maxShifts && (std::find(sched[loc].begin(), sched[loc].end(), i)==sched[loc].end())){
          sched[loc].push_back(i);
          ++worker_usage[i];
          ++fill;
          bool check = search(avail, dailyNeed, maxShifts, sched, worker_usage, loc, k, fill);
          if(check) return true;
          sched[loc].pop_back();
          --worker_usage[i];
          --fill;
        }
      }
      // if(fill!=dailyNeed)
    }
    return false;
}