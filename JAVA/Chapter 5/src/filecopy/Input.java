/**
 * 
 */
package filecopy;

/**
 * @author HY
 *
 */
	import java.io.*;

	public class Input {
		public static void main(String[] args) throws IOException {
		        File file = new File(".\\line.txt");
		        BufferedReader in=new BufferedReader(new InputStreamReader(System.in));
		        BufferedWriter out=new BufferedWriter(new OutputStreamWriter(new FileOutputStream(file)));
		        String s;
		        System.out.println("请输入要录入的内容，输入'over'结束。");
		        while(!(s=in.readLine()).equals("over")){
		        	out.write(s);
		        	out.newLine();
		        }
		        out.flush();
		        in.close();
		        out.close();
		}
	}
