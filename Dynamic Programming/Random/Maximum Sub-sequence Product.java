import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Scanner;

public class Main {

    public static void main(String[] args) {
        ArrayList<BigInteger> arr = new ArrayList<BigInteger>();
        BigInteger ans,tmp,in,stop;
        stop=new BigInteger("-999999");
        Scanner sc = new Scanner(System.in);
        while(sc.hasNext()){
            in = sc.nextBigInteger();
            if(in.compareTo(stop)!=0)arr.add(in);
            else{
                ans = arr.get(0);
                for(int i=0; i<arr.size(); i++){
                    tmp = BigInteger.ONE;
                    for(int j=i; j<arr.size(); j++){
                        tmp=tmp.multiply(arr.get(j));
                        ans=ans.max(tmp);
                    }
                }
                System.out.println(ans);
                arr.clear();
            }
        }
    }
}
