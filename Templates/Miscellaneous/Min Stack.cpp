#include<bits/stdc++.h>
using namespace std;

struct MinStack{
	stack<ll>st;
	ll minEle;
	
	MinStack(){}
	
	void push(ll x){
		if(st.empty()){
			st.push(x);
			minEle=x;
		}
		else{
			if(x<minEle){
				ll tmp=x;
				x=x-minEle+x;
				minEle=tmp;
			}
			st.push(x);
		}
	}
	
	ll top(){
		assert(!st.empty());
		ll t=st.top();
		if(t<minEle)t=minEle;
		return t;
	}
	
	void pop(){
		assert(!st.empty());
		ll t=st.top();
		if(t<minEle)minEle=minEle-t+minEle;
		st.pop();
	}
	
	ll getMin(){
		assert(!st.empty());
		return minEle;
	}
	
	bool empty(){return st.empty();}
	
	
};

int main(){


return 0;
}