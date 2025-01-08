import java.lang.*;
import java.util.*;
import static java.lang.System.*;

public class Main{
    public final static int maxn = 100;
    public static ArrayList<ArrayList>[] v = new ArrayList[maxn]; 
    
    public static void main(String args[]){
        Scanner in = new Scanner(System.in);
        for(int i = 0; i < maxn; i++)
            v[i] = new ArrayList<ArrayList>();
        String input_1[] = in.nextLine().split("00"), n = in.nextLine();
        int  last = 0;
        for(int i = 0; i < input_1.length; i++){
            String[] now = input_1[i].split("0");
            ArrayList<Integer> ss = new ArrayList<Integer>();
            for(int j = 1; j < now.length; j++)
                ss.add(now[j].length());
            last = Math.max(last, now[2].length());
	     last = Math.max(last, now[0].length());
            v[now[0].length()].add(ss);
        }
         for(int test = 0; test < Integer.parseInt(n); test++){
            
            String Get = in.nextLine(), ss[] = Get.split("0");
            int s[] = new int [1000];
            int now = 1, index = 1;
            for(int i = 0; i < 1000; i++)
                s[i] = 1;
            if(Get.length() != 0)
            {
                for(int i = 500; i < 500 + ss.length; i++)
                    s[i] = ss[i - 500].length();
                index = 500;
            }
            //index for left and right
            //now for number of state
             Boolean go = false;
            do{
                go = false;
                for(int i = 0; i < v[now].size(); i++)
                    if(s[index] == (int)v[now].get(i).get(0)){
                        s[index] =  (int)v[now].get(i).get(2);
                        if((int)v[now].get(i).get(3) == 1)
                            index--;
                        else
                            index++;
                        now = (int)v[now].get(i).get(1);
                        go = true;
                        break;
                    }
            }while(go == true && index >= 0 && index < s.length);
            if(now == last)
                out.println("Accepted");
            else
                out.println("Rejected");
        }
        // last edit
    }
}
