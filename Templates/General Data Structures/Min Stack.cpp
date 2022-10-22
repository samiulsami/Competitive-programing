template<typename T>
struct minStack{
	stack<pair<T,T> >A;
	minStack(){}
	void push(T x){A.push({x,A.empty()?x:min(x,A.top().second)});}
	T pop(){T a=A.top();A.pop();return a;}
	T top(){return A.top().first;}
	T getMin(){return A.top().second;}
	bool empty(){return A.empty();}
};