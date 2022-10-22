const int _chars=26;
int nxt[1005][_chars];

inline int charMap(char c){
	if(c>='a' && c<='z')return c-'a';
	if(c>='A' && c<='Z')return c-'A'+26;
	return c-'0'+52;
}

void prefixautomaton(const string &s){
	int n = (int)s.size();
	vector<int>pi(n);
	for(int i=1,j=0; i<n; i++){
		j=pi[i-1];
		while(j && s[i]!=s[j])j=pi[j-1];
		if(s[i]==s[j])pi[i]=j+1;
		else pi[i]=0;
	}
	for(int i=0; i<_chars; i++){
		if(charMap(s[0])==i)nxt[0][i]=1;
		else nxt[0][i]=0;
	}
	for(int i=1; i<=n; i++){
		for(int c=0; c<_chars; c++){
			if(i==n || charMap(s[i])!=c)nxt[i][c]=nxt[pi[i-1]][c];
			else nxt[i][c]=i+1;
		}
	}
}