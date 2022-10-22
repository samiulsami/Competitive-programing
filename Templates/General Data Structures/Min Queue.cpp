template<typename T>
struct minQueue{
	stack<pair<T,T> >A,B;
	minQueue(){}
	T check(const T &a, const T &b){return min(a,b);}
	void push(T x){
		T y = A.empty()?x:check(x,A.top().second);
		A.push({x,y});
	}
	void work(){
		if(B.empty()){
			while(!A.empty()){
				T x=A.top().first;
				A.pop();
				T y = B.empty()?x:check(x,B.top().second);
				B.push({x,y});
			}
		}
	}
	T pop(){
		work();
		T ret=B.top().first;
		B.pop();
		return ret;
	}
	T front(){
		work();
		return B.top().first;
	}
	T getMin(){
		if(A.empty())return B.top().second;
		if(B.empty())return A.top().second;
		return check(A.top().second, B.top().second);
	}
	bool empty(){return A.empty() && B.empty();}
};