struct wavelet_tree{///1 indexed
    int low,high;
    wavelet_tree *lft=NULL,*rgt=NULL;
    int *pref=NULL;
    wavelet_tree(int *l, int *r, int low, int high):low(low),high(high){
        if(l>=r || low>=high)return;
        pref = new int[r-l+2];
        pref[0]=0;
        int mid = (low+high)>>1, cnt=1;
        for(int *i=l; i!=r; i++,cnt++)pref[cnt] = pref[cnt-1]+((*i)<=mid);
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
    int Count(int l, int r, int k){///Count occurences of 'k' in range [l,r]
        if(l>r || high<k || low>k)return 0;
        if(low==high)return r-l+1;
        int mid = (low+high)>>1;
        if(k<=mid)return lft->Count(pref[l-1]+1, pref[r], k);
        return rgt->Count(l-pref[l-1], r-pref[r], k);
    }
    int kth(int l, int r, int k){///Returns the k'th smallest element in range [l,r]
        if(l>r)return 0;
        if(low==high)return low;
        int lftCount = pref[r]-pref[l-1];
        if(lftCount>=k)return lft->kth(pref[l-1]+1, pref[r], k);
        return rgt->kth(l-pref[l-1], r-pref[r], k-lftCount);
    }
    int LTE(int l, int r, int k){///Returns the count of elements that are less than or equal to 'k' in range [l,r]
        if(l>r || low>k)return 0;
        if(high<=k)return r-l+1;
        return lft->LTE(pref[l-1]+1, pref[r], k) + rgt->LTE(l-pref[l-1], r-pref[r], k);
    }
    ~wavelet_tree(){
        if(pref!=NULL)delete []pref;
        if(lft!=NULL)delete lft;
        if(rgt!=NULL)delete rgt;
    }
};
