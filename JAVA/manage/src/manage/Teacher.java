/**
 * 
 */
package manage;

/**
 * @author HY
 *
 */


	import java.sql.*;

	//教师信息表的创建
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
				//建立了到特定的数据库的连接
				Connection con =getConnection();
				Statement sql = con.createStatement();
				sql.executeUpdate("drop table if exists teacher_information");//如果之前存在同名的表则删除
				sql.executeUpdate("create table teacher_information (Tno int not null,Tpassword int  not null)ENGINE=InnoDB DEFAULT CHARSET=utf8;;");
				//创建名为teacher_information表
				
				//补充教师登录信息
				sql.executeUpdate("INSERT INTO teacher_information VALUES (1216004669, 160506)");
				sql.executeUpdate("INSERT INTO teacher_information VALUES (1216004660, 160304)");
				
				//补充信息完毕，借助Navicat For MySQL
				String query="select*from teacher_information";
				ResultSet result=sql.executeQuery(query);
				System.out.println("teacher_information表中的数据如下：");
				System.out.println("----------------------");
				System.out.println("帐号"+" "+"密码");
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
	




