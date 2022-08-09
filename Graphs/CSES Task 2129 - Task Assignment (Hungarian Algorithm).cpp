#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
#define pii(x) array<int,x>
#define sz(x) int(x.size())
#define all(x) x.begin(), x.end()
#define dbug(x) cout<<"Value of "<<#x<<": "<<x<<"\n"
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 205;

const int INF = INT_MAX;
// Given the cost matrix "vector<vector<int>> A {...};"
// Find the maximum matching "vector<pair<int,int>>result;" with all pairs
// As well as total cost "int C;" with the minimum assignment cost.

///Source: http://zafar.cc/2017/7/19/hungarian-algorithm/
/// 1 Indexed
pair<int, vector<pair<int, int> > > Hungarian(int n, int m, vector<vector<int> >A){
  vector<int> u (n+1), v (m+1), p (m+1), way (m+1);
  for (int i=1; i<=n; ++i) {
    p[0] = i;
    int j0 = 0;
    vector<int> minv (m+1, INF);
    vector<char> used (m+1, false);
    do {
      used[j0] = true;
      int i0 = p[j0],  delta = INF,  j1;
      for (int j=1; j<=m; ++j)
        if (!used[j]) {
          int cur = A[i0][j]-u[i0]-v[j];
          if (cur < minv[j])
            minv[j] = cur,  way[j] = j0;
          if (minv[j] < delta)
            delta = minv[j],  j1 = j;
        }
      for (int j=0; j<=m; ++j)
        if (used[j])
          u[p[j]] += delta,  v[j] -= delta;
        else
          minv[j] -= delta;
      j0 = j1;
    } while (p[j0] != 0);
    do {
      int j1 = way[j0];
      p[j0] = p[j1];
      j0 = j1;
    } while (j0);
  }

  vector<pair<int, int>> result;
  for (int i = 1; i <= m; ++i){
    result.push_back(make_pair(p[i], i));
  }

  int C = -v[0];
  return {C,result};
}

inline void solve(int caseNum){
  int n;
  cin>>n;
  
  vector<vector<int> >c(n+1,vector<int>(n+1));
  for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)cin>>c[i][j];

  auto ans = Hungarian(n,n,c);
  cout<<ans.first<<"\n";
  sort(all(ans.second));
  for(auto it:ans.second)
    cout<<it.first<<" "<<it.second<<"\n";

  
}

int main(){
  #ifdef idk123
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
  #endif
   ios_base::sync_with_stdio(0);cin.tie(0);
   //freopen("input.txt","r",stdin);
   //freopen("output.txt","w",stdout);
  int T=1;
  //cin>>T;
  for(int i=1; i<=T; i++)
    solve(i);
return 0;
}