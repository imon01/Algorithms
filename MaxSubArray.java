/*
IM
Description: File implements Divide and Conquer algorithm mentioned in CSCI 405 with Dr. Hearne.
*/
import java.util.ArrayList;
import java.util.Scanner;
import java.io.FileNotFoundException;
import java.io.File;

public class MaxSubArray{
    private static int divideCounter;
    private  static double NEGINFINITY;
    
    
    /*
    Class helps with code readability
    */
    /*-------------------------------------Helper Class------------------------------------------*/
    public class ReturnList{
        
        double sum;
        int low, high;
        
        ReturnList(int low, int high, double sum){
            this.low = low;
            this.high = high;
            this.sum = sum;
        }
    }    
    /*-------------------------------------------------------------------------------*/

    
    public static void main(String [] args)throws FileNotFoundException{
                        
        ArrayList<Double> A = new ArrayList<Double>();        
        Scanner user = new Scanner(System.in);
        Scanner in;
        File file;
        divideCounter = 0;
        
        print("Input filename: ");                
        file = new File( user.nextLine() );
        
        if(!file.canRead()){
            println("File not found");
            System.exit(0);
        }            
        in = new Scanner(file);
        
        
        while(in.hasNext())
            A.add(Double.parseDouble(in.next()) );
        
        NEGINFINITY = Double.NEGATIVE_INFINITY;
        ReturnList output = FindMaximumSubArray(A, 0, A.size()-1);
        
        
        println("low: " + output.low + "\nhigh: "+ output.high+ "\nsum: " + output.sum + "\nNumber of Recursive calls: " + divideCounter);
        print("Maximum subarray: [ ");
        for(int i = output.low; i<=output.high; ++i)
            print(A.get(i)+ " ");
        
        in.close();
        user.close();
        print(" ]\n");
    }
    
    
    
    private static void println(String s){System.out.println(s);}
    private static void print(String s){System.out.print(s);}
            
    private static ReturnList FindMaximumSubArray(ArrayList<Double> A, int low, int high){
        if(low == high)
            return new MaxSubArray().new ReturnList(low, high, A.get(low));
        else{
            int mid = (low+high)/2;
            ++divideCounter;
            ReturnList Left = FindMaximumSubArray(A, low, mid);            
            
            ++divideCounter;
            ReturnList Right = FindMaximumSubArray(A, mid+1, high);
            
            double [] crossSubArray = FindMaxCrossingSubArray(A, low, mid, high);
            
            if( Left.sum >= Right.sum && Left.sum >= crossSubArray[2])
              return Left;  
            else if( Right.sum >= Left.sum && Right.sum >= crossSubArray[2] )
                return Right;  
            else 
                return new MaxSubArray().new ReturnList ( (int)crossSubArray[0], (int)crossSubArray[1], crossSubArray[2]);
        }    
    }
    
    
    private static double [] FindMaxCrossingSubArray(ArrayList<Double> A,int low, int mid, int high){
        double leftSum, rightSum;
        rightSum = NEGINFINITY;
        leftSum = NEGINFINITY;
        double sum =0;
        int maxLeft =0;
        int maxRight =0;
        
        for(int i=mid; i >= low; --i){
            sum += A.get(i);
            if(sum > leftSum){
                leftSum = sum;
                maxLeft =i;
            }
        }
        
        sum =0;
        for(int j = (mid +1); j <= high; ++j){
            sum += A.get(j);
            if(sum > rightSum){
                rightSum = sum;
                maxRight = j;
            }            
        }        
        return new double []{maxLeft, maxRight, leftSum+rightSum};
    }
        
                

}
