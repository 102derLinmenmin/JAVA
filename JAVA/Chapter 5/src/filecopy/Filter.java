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
	        System.out.println("请输入一个目录：");
	        while(true) {
	            String line = sc.nextLine();
	            File dir = new File(line);
	            if(!dir.exists()) {
	                System.out.println("您输入的目录不存在,请重新录入。");
	            }else if(dir.isFile()) {
	                System.out.println("您输入的不是目录,请重新录入。");
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
