#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

typedef tree<int,null_type,less<int>,rb_tree_tag,tree_order_statistics_node_update> Set;

int main(){
    Set st;
    int q,n;
    char in;
    cin>>q;
    while(q--){
        cin>>in;
        if(in=='I'){
            cin>>n;
            st.insert(n);
        }
        else if(in=='D'){
            cin>>n;
            st.erase(n);
        }
        else if(in=='K'){
            cin>>n;
            n--;
            if(n>=(int)st.size())cout<<"invalid"<<endl;
            else cout<<*st.find_by_order(n)<<endl;
        }
        else if(in=='C'){
            cin>>n;
            cout<<st.order_of_key(n)<<endl;
        }
    }
return 0;
}
