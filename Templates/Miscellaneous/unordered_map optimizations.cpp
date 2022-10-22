/***
Collected from
https://codeforces.com/blog/entry/21853
https://codeforces.com/blog/entry/62393
*/
#include<bits/stdc++.h>
using namespace std;


struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

struct pairHash{
  size_t operator()(const pair<int,int>&x)const{
    return hash<long long>()(((long long)x.first)^(((long long)x.second)<<32));
  }
};



int main(){
    unordered_map<long long, int, custom_hash>mp;
    mp.reserve(1024);///power of 2
    mp.max_load_factor(0.25);

return 0;
}
