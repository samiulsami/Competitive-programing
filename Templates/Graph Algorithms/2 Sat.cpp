///Stolen code
namespace sat{///1 indexed
    const int MAX = 200010; /// number of variables * 2
    bool vis[MAX];
    vector <int> ed[MAX], rev[MAX];
    int n, m;
    vector <int> order;
    int comp[MAX];
    inline int inv(int x){
        return ((x) <= n ? (x + n) : (x - n));
    }
    /// Call init once
    void init(int vars){
        n = vars, m = vars << 1;
        for (int i = 1; i <= m; i++){
            ed[i].clear();
            rev[i].clear();
        }
    }
    /// Adding implication, if a then b ( a --> b )
    inline void add(int a, int b){
        ed[a].push_back(b);
        rev[b].push_back(a);
    }
    /// (a or b) is true --> OR(a,b)
    /// (�a or b) is true --> OR(inv(a),b)
    /// (a or �b) is true --> OR(a,inv(b))
    /// (�a or �b) is true --> OR(inv(a),inv(b))
    inline void OR(int a, int b){
        add(inv(a), b);
        add(inv(b), a);
    }
    /// same rule as or
    inline void AND(int a, int b){
        add(a, b);
        add(b, a);
    }
    /// same rule as or
    void XOR(int a,int b){
        add(inv(b), a);
        add(a, inv(b));
        add(inv(a), b);
        add(b, inv(a));
    }
    /// same rule as or
    inline void XNOR(int a, int b){
        add(a,b);
        add(b,a);
        add(inv(a), inv(b));
        add(inv(b), inv(a));
    }
    /// (x <= n) means forcing variable x to be true
    /// (x = n + y) means forcing variable y to be false
    inline void force_true(int x){
        add(inv(x), x);
    }
    void dfs(int s) {
        vis[s] = true;
        for(int x : ed[s]) {
            if(vis[x]) continue;
            dfs(x);
        }
        order.push_back(s);
    }
    void mark(int s, int c) {
        comp[s] = c;
        vis[s] = true;
        for(int x : rev[s]) {
            if(vis[x]) continue;
            mark(x, c);
        }
    }
    bool satisfy(vector <int> &res){
        memset(vis,0,sizeof vis);
        for(int i=1;i<=m;i++) {
            if(vis[i]) continue;
            dfs(i);
        }
        memset(vis,0,sizeof vis);
        reverse(order.begin(),order.end());
        int it = 0;
        for(int s : order) {
            if(vis[s]) continue;
            mark(s, ++it);
        }
        res.clear();
        res.resize(n+1);
        for(int i=1;i<=n;i++) {
            if(comp[i] == comp[inv(i)]) return false;
            res[i] = int(comp[i] > comp[inv(i)]);
        }
        return true;
    }
}