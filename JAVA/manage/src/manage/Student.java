package manage;


	import java.sql.*;

	//所有学生信息数据库
	public class Student {
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
				sql.executeUpdate("drop table if exists student_information");
				sql.executeUpdate("create table student_information (Sno int not null,Sname varchar(20) not null,Scollege varchar(20) not null,Smajor varchar(20) not null,Sclassroom int not null,Sage int not null,Sadd varchar(20) not null,primary key(Sno))ENGINE=InnoDB DEFAULT CHARSET=utf8;;");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32160001, '李华', '计算机学院', '网络工程', 2, 19, '西六');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160002, '李明', '自动化学院', '自动化', 1, 19, '西八');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160003, '江乎乎', '外国语学院', '商务英语', 2, 18, '西七');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32170004, '钱多多', '计算机学院', '软件工程', 1, 17, '东十三');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160005, '李章鱼', '土木学院', '给排水', 1, 19, '东八');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31170006, '可达鸭', '计算机学院', '信息安全', 2, 18, '西二');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32160007, '林文明', '自动化学院', '物联网', 1, 19, '东十三');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31170008, '张三', '轻化学院', '应用化学', 2, 18, '东八');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31170009, '李四', '外国语学院', '翻译英语', 2, 18, '东七');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31150010, '王二', '物理学院', '光电', 2, 20, '东十四');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32170011, '赵五', '信工学院', '通信工程', 1, 18, '东十三');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31140012, '欧阳', '计算机学院', '计科', 3, 21, '西二');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160013, '月饼', '计算机学院', '软件工程', 3, 19, '西二');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32160014, '陆飞燕', '材能学院', '微电子', 1, 19, '西六');");
				//补充信息完毕，借助Navicat For MySQL
				String query="select*from student_information";
				ResultSet result=sql.executeQuery(query);
				System.out.println("student_information表中的数据如下：");
				System.out.println("-----------------------------------------------------");
				System.out.println("学号"+" "+"姓名"+" "+"学院"+" "+"专业"+" "+"班级"+" "+"年龄"+" "+"地址");
				System.out.println("-----------------------------------------------------");
			while (result.next()) {
				int number=result.getInt("Sno");
				String name=result.getString("Sname");
				String college=result.getString("Scollege");
				String major=result.getString("Smajor");
				int classroom=result.getInt("Sclassroom");
				int age=result.getInt("Sage");
				String add=result.getString("Sadd");
				System.out.println(" "+number+" "+name+" "+college+" "+major+" "+classroom+" "+age+" "+add);
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

