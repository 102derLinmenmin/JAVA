package manage;


	import java.sql.*;

	//����ѧ����Ϣ���ݿ�
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
				//�����˵��ض������ݿ������
				Connection con =getConnection();
				Statement sql = con.createStatement();
				sql.executeUpdate("drop table if exists student_information");
				sql.executeUpdate("create table student_information (Sno int not null,Sname varchar(20) not null,Scollege varchar(20) not null,Smajor varchar(20) not null,Sclassroom int not null,Sage int not null,Sadd varchar(20) not null,primary key(Sno))ENGINE=InnoDB DEFAULT CHARSET=utf8;;");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32160001, '�', '�����ѧԺ', '���繤��', 2, 19, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160002, '����', '�Զ���ѧԺ', '�Զ���', 1, 19, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160003, '������', '�����ѧԺ', '����Ӣ��', 2, 18, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32170004, 'Ǯ���', '�����ѧԺ', '�������', 1, 17, '��ʮ��');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160005, '������', '��ľѧԺ', '����ˮ', 1, 19, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31170006, '�ɴ�Ѽ', '�����ѧԺ', '��Ϣ��ȫ', 2, 18, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32160007, '������', '�Զ���ѧԺ', '������', 1, 19, '��ʮ��');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31170008, '����', '�ữѧԺ', 'Ӧ�û�ѧ', 2, 18, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31170009, '����', '�����ѧԺ', '����Ӣ��', 2, 18, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31150010, '����', '����ѧԺ', '���', 2, 20, '��ʮ��');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32170011, '����', '�Ź�ѧԺ', 'ͨ�Ź���', 1, 18, '��ʮ��');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31140012, 'ŷ��', '�����ѧԺ', '�ƿ�', 3, 21, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 31160013, '�±�', '�����ѧԺ', '�������', 3, 19, '����');");
				sql.executeUpdate("INSERT INTO student_information VALUES ( 32160014, '½����', '����ѧԺ', '΢����', 1, 19, '����');");
				//������Ϣ��ϣ�����Navicat For MySQL
				String query="select*from student_information";
				ResultSet result=sql.executeQuery(query);
				System.out.println("student_information���е��������£�");
				System.out.println("-----------------------------------------------------");
				System.out.println("ѧ��"+" "+"����"+" "+"ѧԺ"+" "+"רҵ"+" "+"�༶"+" "+"����"+" "+"��ַ");
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

