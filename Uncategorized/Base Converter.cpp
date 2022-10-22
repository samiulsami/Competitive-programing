#include<iostream>
#include<string>
using namespace std;

class Number{
    private:
        string value;
        long int base;
    public:
        Number(){}
        int pow(int a, int b){
            if(b==0)return 1;
            int x=a;
            while(--b)a*=x;
            return a;
        }
        void setValue(string value){
            this->value = value;
        }
        void setBase(long int base){
            this->base = base;
        }
        long int getBase(){
            return base;
        }
        string getValue(){
            return value;
        }
        Number(string value, long int base){
            this->value = value;
            this->base = base;
        }
        string convertToBase(long int x){
                //Converting to decimal
                long int len = value.length(),value_decimal=0,power=len-1;
                    for(long int i=0; i<len; i++){
                        long int y;
                        if(value[i]>=48 && value[i]<=57)y=value[i]-48;
                        else y=value[i]-65+10;
                        value_decimal+=pow(base,power)*y;
                        power--;
                    }
                string value_x;
                //Converting to base(x)
                while(value_decimal){
                    long int a = value_decimal%x;
                    if(a>=10)value_x+=(char)(a+65-10);
                    else value_x+=(char)(a+48);
                    value_decimal/=x;
                }
                 len = value_x.length();
                for(long int i=0; i<len/2; i++){
                    char tmp=value_x[len-1-i];
                    value_x[len-1-i]=value_x[i];
                    value_x[i]=tmp;
                }
                if(value_x=="")value_x="0";
                return value_x;
        }

};

int main(){
Number test;
string value;
long int base,newbase;
while(true){
    bool b=0;
    cout<<"Enter a number: ";
    cin>>value;
    cout<<"Enter its base: ";
    cin>>base;
    if(base==1){
        cout<<"Invalid input\n"<<endl;
        continue;
    }
    long int len=value.length();
    for(long int i=0; i<len; i++)if(value[i]>=97 && value[i]<=122)value[i]-=32;
    for(long int i=0; i<len; i++){
        if(!(value[i]>=65 && value[i]<=90) && !(value[i]>=48 && value[i]<=57)){
            b=1;
            break;
        }
        if(value[i]>=48 && value[i]<=57 && value[i]-48>base-1){
            b=1;
            break;
        }
        else if(value[i]>=65 && value[i]<=90 && value[i]-65+10>base-1){
                b=1;
                break;
        }
    }
    if(b){
        b=0;
        cout<<"Invalid input\n"<<endl;
        continue;
    }
    test.setValue(value);
    test.setBase(base);
    cout<<"Enter a base to convert the number to: ";
    cin>>newbase;
    cout<<"\'"<<test.getValue()<<"\' in base("<<base<<") is \'"<<test.convertToBase(newbase)<<"\' in base("<<newbase<<")\n"<<endl;
}
return 0;
}
