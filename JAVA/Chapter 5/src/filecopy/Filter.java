/**
 * 
 */
package filecopy;

/**
 * @author HY
 *
 */
	import java.io.*;
	import java.util.*;

	public class Filter{

	    public static void main(String[] args){
	        File dir = getDir();
	        printJavaFile(dir);
	    }
	    @SuppressWarnings("resource")
	    public static File getDir() {
	        Scanner sc = new Scanner(System.in);
	        System.out.println("������һ��Ŀ¼��");
	        while(true) {
	            String line = sc.nextLine();
	            File dir = new File(line);
	            if(!dir.exists()) {
	                System.out.println("�������Ŀ¼������,������¼�롣");
	            }else if(dir.isFile()) {
	                System.out.println("������Ĳ���Ŀ¼,������¼�롣");
	            }else {
	                return dir;
	            }
	        }
	    }
	    public static void printJavaFile(File dir) {
	        File[] Files = dir.listFiles();
	        for (File s : Files) {
	            if(s.isFile() && s.getName().endsWith(".java")) {
	                System.out.println(s.getName());
	            }else if (s.isDirectory()){
	                printJavaFile(s);
	            }
	        }
	    }
	}
