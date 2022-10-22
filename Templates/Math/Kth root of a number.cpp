const double eps = 1e-9;
double kthRoot(double x, double k){
    double low=1,high=x;
    double mid = (low+high)/(double)2;
    while(abs((pow(mid,k))-x)>=eps){
        if(pow(mid,k)>x)high=mid;
        else low=mid;
        mid=(low+high)/(double)2;
    }
    return mid+eps;
}