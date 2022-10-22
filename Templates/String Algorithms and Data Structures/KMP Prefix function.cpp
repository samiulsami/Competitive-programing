vector<int> kmp(const string &s){
    vector<int>pi((int)s.size(),0);
    for(int i=1,j=0; i<(int)s.size(); i++){
        j=pi[i-1];
        while(j && s[i]!=s[j])j=pi[j-1];
        if(s[i]==s[j])pi[i]=j+1;
    }
    return pi;
}