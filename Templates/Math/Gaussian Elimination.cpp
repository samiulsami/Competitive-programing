------------------------------Gauss-Elimination------------------
/*n=number of linear equations, m=number of variables ar[i][m]=right-hand side value of constants
2x+y-z=8      ----->  (i)
-3x-y+2z=-11  ----->  (ii)
-2x+y+2z=-3  ----->  (iii)
n=3 (x, y, z), m=3 (i, ii, iii)
ar[0]={2, 1, -1, 8}    ----->  (i)
ar[1]={-3, -1, 2, -11} ----->  (ii)
ar[2]={-2, 1, 2, -3}   ----->  (iii)
Returns-1 when there is no solution
Otherwise, returns the number of independent variables(0 for an unique solution), Contains a solution in the vector res on successful completion, Note that the array is modified in the process
NOTE : For solving problems on graphs probability/expectation, make sure the graph is connectedand a single component.If not, then re-number the vertexand
solve for each connected component separately. */
int gauss(int n, int m, double ar[102][102], vector<double>&res){
 res.assign(m, 0);
 vector<int> pos(m, -1);
 const double EPS=1e-9;
 int i, j, k, l, p, free_var=0;
 for(j=0, i=0; j<m&&i<n; j++){
  for(k=i, p=i; k<n; k++)
   if(fabs(ar[k][j])>fabs(ar[p][j])) p=k;
  if(fabs(ar[p][j])>EPS){
   pos[j]=i;
   for(l=j; l<=m; l++) swap(ar[p][l], ar[i][l]);
   for(k=0; k<n; k++){
    if(k!=i){
     double x=ar[k][j]/ar[i][j];
     for(l=j; l<=m; l++) ar[k][l]-=(ar[i][l]*x);
    }
   }
   i++;
  }
 }
 for(i=0; i<m; i++){
  if(pos[i]==-1)
   free_var++;
  else
   res[i]=ar[pos[i]][m]/ar[pos[i]][i];
 }
 for(i=0; i<n; i++){
  double val=0.0;
  for(j=0; j<m; j++) val+=(res[j]*ar[i][j]);
  if(fabs(val-ar[i][m])>EPS) return -1;
 }
 return free_var;
}

----------------------Gauss with MOD(Prime) N^3*log(MOD)---------------------------
int gauss(int n, int m, int MOD, int ar[102][103], vector<int>&res){
 res.assign(m, 0);
 vector<int> pos(m, -1);
 int i, j, k, l, p, d, free_var=0;
 const long long MODSQ=(long long)MOD*MOD;
 for(j=0, i=0; j<m&&i<n; j++){
  for(k=i, p=i; k<n; k++){
   if(ar[k][j]>ar[p][j]) p=k;
  }
  if(ar[p][j]){
   pos[j]=i;
   for(l=j; l<=m; l++) swap(ar[p][l], ar[i][l]);
   d=powerMod(ar[i][j], MOD-2, MOD);
   for(k=0; k<n&&d; k++){
    if(k!=i&&ar[k][j]){
     int x=((long long)ar[k][j]*d)%MOD;
     for(l=j; l<=m&&x; l++){
      if(ar[i][l])
       ar[k][l]=(MODSQ+ar[k][l]-((long long)ar[i][l]*x))%MOD;
     }
    }
   }
   i++;
  }
 }
 for(i=0; i<m; i++){
  if(pos[i]==-1)
   free_var++;
  else
   res[i]=
   ((long long)ar[pos[i]][m]*powerMod(ar[pos[i]][i], MOD-2, MOD))%
   MOD;
 }
 for(i=0; i<n; i++){
  long long val=0;
  for(j=0; j<m; j++) val=(val+((long long)res[j]*ar[i][j]))%MOD;
  if(val!=ar[i][m]) return -1;
 }
 return free_var;
}
