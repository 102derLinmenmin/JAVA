/**
 * 
 */
package manage;

/**
 * @author HY
 *
 */


	import java.sql.*;

	//��ʦ��Ϣ��Ĵ���
	public class Teacher {
		public static Connection getConnection()throws SQLException,java.lang.ClassNotFoundException{
			String url="jdbc:mysql://localhost:3306/myDB?characterEncoding=utf8&useSSL=true";
			Class.forName("com.mysql.jdbc.Driver");
			String user="root";
			String password="laji";
			Connection con =DriverManager.getConnection(url,user,password);
			return con;
	}
		/**
		 *
		 */
		public static void main (String[] args) {
			try {
				//�����˵��ض������ݿ������
				Connection con =getConnection();
				Statement sql = con.createStatement();
				sql.executeUpdate("drop table if exists teacher_information");//���֮ǰ����ͬ���ı���ɾ��
				sql.executeUpdate("create table teacher_information (Tno int not null,Tpassword int  not null)ENGINE=InnoDB DEFAULT CHARSET=utf8;;");
				//������Ϊteacher_information��
				
				//�����ʦ��¼��Ϣ
				sql.executeUpdate("INSERT INTO teacher_information VALUES (1216004669, 160506)");
				sql.executeUpdate("INSERT INTO teacher_information VALUES (1216004660, 160304)");
				
				//������Ϣ��ϣ�����Navicat For MySQL
				String query="select*from teacher_information";
				ResultSet result=sql.executeQuery(query);
				System.out.println("teacher_information���е��������£�");
				System.out.println("----------------------");
				System.out.println("�ʺ�"+" "+"����");
				System.out.println("----------------------");
			while (result.next()) {
				int number=result.getInt("Tno");
				int password=result.getInt("Tpassword");
				System.out.println(" "+number+" "+password);
			}
			sql.close();
			con.close();
		}catch(java.lang.ClassNotFoundException e) {
			System.err.println("ClassNotFoundException:");
			System.err.println(e.getMessage());
		}catch  (SQLException ex) {
			System.err.println("SQLException:"+ex.getMessage());	
		}
		}
	}
	




