package ticket;

import java.util.*;

public class Ticket implements Runnable {
	static int num;
	static int count;
	Ticket(){
	    num = 50;
	    count = 0;
	}

	@Override
	public void run() {
		// TODO Auto-generated method stub
		while(num > 2){
		    synchronized (this) {		    	
		        try{  		        	
		            Thread.sleep(new Random().nextInt(20));
		        }catch(Exception e){		        
		            e.printStackTrace();
		    }
		        num--;
		    System.out.println(" ��Ʊ���ڣ�" + Thread.currentThread().getName()+" ʣ��Ʊ����"+num);	  
		    count ++;
		   }
		     }
	}
}
	