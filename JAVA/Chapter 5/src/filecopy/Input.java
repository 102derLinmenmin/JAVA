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
		        System.out.println("������Ҫ¼������ݣ�����'over'������");
		        while(!(s=in.readLine()).equals("over")){
		        	out.write(s);
		        	out.newLine();
		        }
		        out.flush();
		        in.close();
		        out.close();
		}
	}
