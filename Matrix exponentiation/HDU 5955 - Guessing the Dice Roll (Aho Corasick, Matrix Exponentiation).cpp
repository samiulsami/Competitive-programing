#include<bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef uint64_t ull;
typedef long double ld;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll>vll;
#define sf scanf
#define pf printf
#define nl printf("\n")
#define si(x) scanf("%d",&x)
#define sii(x,y) scanf("%d%d",&x,&y)
#define siii(x,y,z) scanf("%d%d%d",&x,&y,&z)
#define sl(x) scanf("%lld",&x)
#define sll(x,y) scanf("%lld%lld",&x,&y)
#define slll(x,y,z) scanf("%lld%lld%lld",&x,&y,&z)
#define FOR(i,n) for(int i=0;i<n;i++)
#define sz(x) (int)x.size()
#define all(x) x.begin(),x.end()
#define chk cerr<<"CAME HERE"<<endl
#define dbug(x) cerr<<"value of "<<#x<<" = "<<x<<endl
#define popcount(x) __builtin_popcount(x)
#define popcountll(x) __builtin_popcountll(x)
mt19937 rng((uint64_t) chrono::duration_cast<chrono::nanoseconds>(chrono::high_resolution_clock::now().time_since_epoch()).count());
inline int rand(int l, int r){uniform_int_distribution<int> RNG(l,r);return RNG(rng);}

const int N = 1e5+5;

const int _chars=7;

struct AhoCorasick{
    struct trienode{
        int next[_chars]={0};
        int link=0;
        bool terminal=0;
        trienode(){}
    };
    vector<trienode>trie;
    AhoCorasick(){trie.emplace_back();}

    int insert(const vector<int> &s){
        int id=0;
        for(int i=0; i<sz(s); i++){
            int c = s[i];
            if(!trie[id].next[c]){
                trie.emplace_back();
                trie[id].next[c]=(int)trie.size()-1;
            }
            id = trie[id].next[c];
        }
        trie[id].terminal=1;
        return id;
    }

    void build(){
        queue<int>q;
        q.push(0);
        while(!q.empty()){
            int id = q.front();
            q.pop();
            for(int c=0; c<_chars; c++){
                if(trie[id].next[c]){
                    trie[trie[id].next[c]].link = id ? trie[trie[id].link].next[c] : 0;
                    q.push(trie[id].next[c]);
                }
                else trie[id].next[c] = trie[trie[id].link].next[c];
            }
        }
    }

    inline int getnext(int id, int c){
        return trie[id].next[c];
    }
};


struct Matrix{
    double mat[101][101];
	int r,c;
    Matrix(int r, int c):r(r),c(c){
		for(int i=0; i<r; i++)
			for(int j=0; j<c; j++)mat[i][j]=0;
	}
    Matrix operator*(const Matrix &mtrx)const{
        Matrix ret(r,c);
        for(int i=0; i<r; i++){
            for(int j=0; j<r; j++){
                    for(int k=0; k<c; k++){
                        ret.mat[i][j] = ret.mat[i][j] + (mat[i][k] * mtrx.mat[k][j]);
                    }
            }
        }
        return ret;
    }
};

void solve(int casenum){
	int n,l;
	AhoCorasick ac;
	sii(n,l);
	vi ids;
	for(int i=0; i<n; i++){
		vi tmp(l);
		for(int j=0; j<l; j++)si(tmp[j]);
		ids.push_back(ac.insert(tmp));
	}
	ac.build();
	
	double val = double(1)/double(6);
	Matrix m(sz(ac.trie)+1,sz(ac.trie)+1);
	
	for(int i=0; i<sz(ac.trie); i++){
		if(ac.trie[i].terminal)m.mat[i][i]=1.0;
		else{
			for(int j=1; j<=6; j++){
				m.mat[i][ac.getnext(i,j)]+=val;
			}
		}
	}
	
	for(int i=0; i<30; i++)m = m*m;
	for(int i=0; i<n; i++){
		pf("%0.6f",m.mat[0][ids[i]]);
		if(i!=n-1)pf(" ");
	}
	nl;
}

int main(){
    //ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    //freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);
    int T=1;
    scanf("%d",&T);
    //cin>>T;
    for(int i=1; i<=T; i++)
        solve(i);

return 0;
}