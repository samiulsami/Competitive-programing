struct wavelet_tree{///1 indexed
    ///Wavelet tree with toggle updates
    ///O(nlog^2(n)) preprocessing, ~O(log^2(n)) per query and toggle
    ///if index 'i' is active, call toggle(i,-1,arr[i]) to deactivate index. call toggle(i,1,arr[i]) to re-activate
    int low,high;
    wavelet_tree *lft=NULL,*rgt=NULL;
    int *leftBIT=NULL;///For counting the number of elements than go to the left subtree up to index 'i';
    int *prefSumBIT=NULL;///For counting the number of elements present up to index 'i'
    int *pref=NULL;
    int BITlen=0;
    wavelet_tree(int *l, int *r, int low, int high):low(low),high(high){
        BITlen = r-l+1;
        prefSumBIT = new int[r-l+2];
        if(low<high)leftBIT = new int[r-l+2];
        for(int i=0; i<=BITlen; i++){
            if(low<high)leftBIT[i]=0;
            prefSumBIT[i]=0;
        }
        for(int i=1; i<=BITlen; i++)BITupdate(prefSumBIT,i,1);
        if(l>=r || low==high)return;

        pref = new int[r-l+2];
        pref[0]=0;
        int mid = (low+high)>>1;
        for(int *i=l,cnt=1; i!=r; i++,cnt++){
                pref[cnt] = pref[cnt-1]+((*i)<=mid);
                if((*i)<=mid)BITupdate(leftBIT,cnt,1);
        }
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
        BITupdate(prefSumBIT,ind,val);
        if(low==high)return;
        int mid = (low+high)>>1;
        if(k<=mid){
            lft->toggle(pref[ind],val,k);
            BITupdate(leftBIT,ind,val);
        }
        else rgt->toggle(ind-pref[ind],val,k);
    }
    int Count(int l, int r, int k){///Count occurences of 'k' in range [l,r]
        if(l>r || high<k || low>k)return 0;
        if(low==high)return BITquery(prefSumBIT,r)-BITquery(prefSumBIT,l-1);
        int mid = (low+high)>>1;
        if(k<=mid)return lft->Count(pref[l-1]+1, pref[r], k);
        return rgt->Count(l-pref[l-1], r-pref[r], k);
    }
    int kth(int l, int r, int k){///Returns the k'th smallest element in range [l,r]
        if(l>r)return 0;
        if(low==high)return low;
        int lftCount = BITquery(leftBIT,r)-BITquery(leftBIT,l-1);
        if(lftCount>=k)return lft->kth(pref[l-1]+1, pref[r], k);
        return rgt->kth(l-pref[l-1], r-pref[r], k-lftCount);
    }
    int LTE(int l, int r, int k){///Returns the count of elements that are less than or equal to 'k' in range [l,r]
        if(l>r || low>k)return 0;
        if(high<=k)return BITquery(prefSumBIT,r) - BITquery(prefSumBIT,l-1);
        return lft->LTE(pref[l-1]+1, pref[r], k) + rgt->LTE(l-pref[l-1], r-pref[r], k);
    }
    void BITupdate(int *BIT, int ind, int val){
        while(ind<=BITlen){
            BIT[ind]+=val;
            ind+=(ind&-ind);
        }
    }
    int BITquery(int *BIT, int ind){
        int ret=0;
        while(ind>0){
            ret+=BIT[ind];
            ind-=(ind&-ind);
        }
        return ret;
    }
    ~wavelet_tree(){
        if(leftBIT!=NULL)delete []leftBIT;
        if(prefSumBIT!=NULL)delete []prefSumBIT;
        if(pref!=NULL)delete []pref;
        if(lft!=NULL)delete lft;
        if(rgt!=NULL)delete rgt;
    }
};
