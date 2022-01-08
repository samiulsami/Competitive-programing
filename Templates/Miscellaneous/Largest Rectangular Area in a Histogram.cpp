        stack<int>st;
        st.push(-1);
        long long ans=0;
        for(int i=1; i<=n; i++){
            while(st.top()!=-1 && arr[st.top()]>=arr[i])st.pop();
            if(st.top()==-1)L[i]=i;
            else L[i]=i-st.top();
            st.push(i);
        }
        while(!st.empty())st.pop();
        st.push(-1);
        for(int i=n; i>=1; i--){
            while(st.top()!=-1 && arr[st.top()]>=arr[i])st.pop();
            if(st.top()==-1)R[i]=n-i+1;
            else R[i]=st.top()-i;
            st.push(i);
        }
        for(int i=1; i<=n; i++){
            long long val = 1LL*arr[i]*(R[i]+L[i]-1);
            ans = max(ans,val);
        }
