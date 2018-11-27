package manage;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class Senter {
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
				sql.executeUpdate("drop table if exists student");//如果之前存在同名的表则删除
				sql.executeUpdate("create table student (Sno int not null,Spassword int  not null)ENGINE=InnoDB DEFAULT CHARSET=utf8;;");
				//创建名为student表
				
				//补充学生登录信息
				sql.executeUpdate("INSERT INTO student VALUES ( 32160001, 160001 );");
				sql.executeUpdate("INSERT INTO student VALUES ( 31160002, 160002);");
				sql.executeUpdate("INSERT INTO student VALUES ( 31160003, 160003 );");
				sql.executeUpdate("INSERT INTO student VALUES ( 32170004, 170004 );");
				sql.executeUpdate("INSERT INTO student VALUES ( 31160005, 160005);");
				sql.executeUpdate("INSERT INTO student VALUES ( 31170006, 170006);");
				sql.executeUpdate("INSERT INTO student VALUES ( 32160007, 160007 );");
				sql.executeUpdate("INSERT INTO student VALUES ( 31170008, 170008 );");
				sql.executeUpdate("INSERT INTO student VALUES ( 31170009, 170009);");
				sql.executeUpdate("INSERT INTO student VALUES ( 31150010, 150010);");
				sql.executeUpdate("INSERT INTO student VALUES ( 32170011, 170011);");
				sql.executeUpdate("INSERT INTO student VALUES ( 31140012, 140012);");
				sql.executeUpdate("INSERT INTO student VALUES ( 31160013, 160013);");
				sql.executeUpdate("INSERT INTO student VALUES ( 32160014, 160014);");
				
				//补充信息完毕，借助Navicat For MySQL
				String query="select*from student";
				ResultSet result=sql.executeQuery(query);
				System.out.println("student表中的数据如下：");
				System.out.println("---------------------");
				System.out.println("帐号"+" "+"密码");
				System.out.println("---------------------");
			while (result.next()) {
				int number=result.getInt("Sno");
				int password=result.getInt("Spassword");
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
	

