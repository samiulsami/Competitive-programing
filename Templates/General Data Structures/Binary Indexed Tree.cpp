template<typename T>
struct fenwick{///1 indexed
    vector<T>BIT;
    int n;
    fenwick(){n=0;}
    fenwick(int x):n(x),BIT(n+1,0){}

    void update(int ind, T val){
        while(ind<=n){
            BIT[ind]+=val;
            ind+=(ind&-ind);
        }
    }

    T query(int ind){
        T ret=0;
        while(ind>0){
            ret+=BIT[ind];
            ind-=(ind&-ind);
        }
        return ret;
    }

    void range_update(int l, int r, T val){
        update(l,val);
        update(r+1,-val);
    }
};
