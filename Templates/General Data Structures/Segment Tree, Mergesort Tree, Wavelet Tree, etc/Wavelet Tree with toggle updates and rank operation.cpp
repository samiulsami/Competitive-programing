struct wavelet_tree{///1 indexed
    ///Wavelet tree with toggle updates and rank operation
    ///O(nlogn) preprocessing, ~O(logn) per query and toggle
    ///if index 'i' is active, call toggle(i,-1,arr[i]) to deactivate index. call toggle(i,1,arr[i]) to re-activate
    int low,high;
    wavelet_tree *lft=NULL,*rgt=NULL;
    int *BIT=NULL;
    int *pref=NULL;
    int BITlen=0;

    wavelet_tree(int *l, int *r, int low, int high):low(low),high(high){
        if(low==high){
            BIT = new int[r-l+2];
            BITlen = r-l+1;
            for(int i=0; i<=BITlen; i++)BIT[i]=0;
            for(int *i=l,cur=1; i!=r; i++,cur++)BITupdate(cur,1);
            return;
        }
        if(l>=r)return;
        pref = new int[r-l+2];
        pref[0]=0;
        int mid = (low+high)>>1;
        for(int *i=l,cnt=1; i!=r; i++,cnt++)pref[cnt] = pref[cnt-1]+((*i)<=mid);
        int *pivot = stable_partition(l,r,[&](int x){return x<=mid;});
        lft = new wavelet_tree(l, pivot, low, mid);
        rgt = new wavelet_tree(pivot, r, mid+1, high);
    }

    void swapAdjacent(int ind){///Swaps the elements at index 'ind' and 'ind+1'
        if(low==high)return;
        int firstBit=pref[ind]-pref[ind-1];
        if(firstBit==(pref[ind+1]-pref[ind])){
            if(firstBit)lft->swapAdjacent(pref[ind]);
            else rgt->swapAdjacent(ind-pref[ind]);
        }
        else{
            if(firstBit)pref[ind]--;
            else pref[ind]++;
        }
    }

    void toggle(int ind, int val, int k){
        if(low==high)BITupdate(ind,val);
        else{
            int mid = (low+high)>>1;
            if(k<=mid)lft->toggle(pref[ind],val,k);
            else rgt->toggle(ind-pref[ind],val,k);
        }
    }

    void BITupdate(int ind, int val){
        while(ind<=BITlen){
            BIT[ind]+=val;
            ind+=(ind&-ind);
        }
    }

    int BITquery(int ind){
        int ret=0;
        while(ind>0){
            ret+=BIT[ind];
            ind-=(ind&-ind);
        }
        return ret;
    }

    int Count(int l, int r, int k){///Count occurences of 'k' in range [l,r]
        if(l>r || high<k || low>k)return 0;
        if(low==high)return BITquery(r)-BITquery(l-1);
        int mid = (low+high)>>1;
        if(k<=mid)return lft->Count(pref[l-1]+1, pref[r], k);
        return rgt->Count(l-pref[l-1], r-pref[r], k);
    }

    ~wavelet_tree(){
        if(BIT!=NULL)delete []BIT;
        if(pref!=NULL)delete []pref;
        if(lft!=NULL)delete lft;
        if(rgt!=NULL)delete rgt;
    }
};
