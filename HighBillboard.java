
/*
IM
Description: File implements the Dynamic program solution to the Highway Billboard problem.
*/
import java.io.File;
import java.lang.Math;
import java.util.Scanner;
import java.util.ArrayList;
import java.io.FileNotFoundException;




public class HighwayBillboard{
    
    
    private static void print(String s ){System.out.print(s);}
    private static void println(String s){System.out.println(s);}
	private static String greeting = "**************\nSolution to High Billboard problem\n*****************\n";
    public static void main(String [] args)throws FileNotFoundException{
                                
        
        File file;
        Scanner in;
        int minInterval =0; int maxInterval =0;
        Scanner user = new Scanner(System.in); 
        ArrayList<Integer> list = new ArrayList<Integer>();
       
		print(greeting); 
		if( args.length == 1)
			file = new File(args[0]);
       	
		else{ 
			print("Enter the file name: ");        
			file = new File( user.nextLine() );
	    }
 
        if(!file.canRead()){
            println("File not found");
            System.exit(0);
        }            
        
        in = new Scanner(file);                
        
        for(int i =0; i<1 && in.hasNext(); i++){
            minInterval = Integer.parseInt(in.next());
            maxInterval = Integer.parseInt(in.next());
        }               
        
        while(in.hasNextLine()){
            list.add(Integer.parseInt(in.next()));        
       	}

 
        findPlacements(list, minInterval, maxInterval);
        in.close();
        user.close();                      
    }//end main 
    
    private static void findPlacements(ArrayList<Integer> priceTable, int minInterval, int maxInterval){
        int N = priceTable.size();
        int totalRevenue = 0;
        int [] revenueTable = new int [N];
        ArrayList<Integer> placementList = new ArrayList<Integer>();
        
        revenueTable[0] =0;
        for(int i = 1; i < N; ++i){
            if(i < minInterval)
                revenueTable[i] = Math.max(revenueTable[i-1], priceTable.get(i));                                                             
            else                
                revenueTable[i] = Math.max(revenueTable[i-minInterval] + priceTable.get(i), revenueTable[i-1]);                                  
        }
                    
                    
        //extracting indices
        int i = N-1;
        while( i>= 0){
            if(i == 0){
                placementList.add(i);
                i = i - minInterval;
            }
            else{
                if(revenueTable[i] == revenueTable[i-1])
                    --i;
                else{
                    placementList.add(0, i);
                    i -=minInterval;
                }
            }
        }

        
        println("Billboard locations: ");        
        for(int k: placementList){
            print(k + " ");
            totalRevenue += priceTable.get(k);
        }
		println("\nIntervals<" + minInterval + ", " + maxInterval+ ">");
        println("\nTotal Revenue: " + totalRevenue);                     
    }//end findPlacements
    
}//end class
