package manage;



import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Font;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.Toolkit;
import java.awt.event.ActionListener;
import java.awt.event.KeyAdapter;
import java.awt.event.KeyEvent;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JButton;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTable;
import javax.swing.JTextField;
import javax.swing.table.DefaultTableModel;

		public class ProgramFrame extends JFrame {
			private int windowWight = 720;
			private int windowHight = 540;
			
			ArrayList<String> sqls;
			ArrayList<Integer> rowindex;
			
			private int width = Toolkit.getDefaultToolkit().getScreenSize().width;
			private int height = Toolkit.getDefaultToolkit().getScreenSize().height;

			public static void main(String [] args) {
				ProgramFrame pf = new ProgramFrame("31140012","140012","T");
			}
			
			
			public ProgramFrame(String username,String password,String identity) {
				//设置窗口名
				this.setDefaultCloseOperation(EXIT_ON_CLOSE);//关闭窗口结束程序
				this.setSize(this.windowWight,this.windowHight);
				this.setBounds((width - windowWight) / 2,
		                (height - windowHight) / 2, windowWight, windowHight); 
				JPanel rootPanel = (JPanel) this.getContentPane();
				if(identity.equals("S")) {
					/*如果是学生*/
					this.setTitle("学生客户端");
					rootPanel.add(StudentFrame(username));
				}else {
					this.setTitle("教师客户端");
					 TeacherFrame(username ) ;
				}
//				this.setResizable(false);
				
				this.setVisible(true);
			}

				
			private void TeacherFrame(String username) {
				sqls = new ArrayList<String>();
				rowindex = new ArrayList<Integer>();
		    
				JPanel rootPanel = (JPanel) this.getContentPane();
				
				JMenuBar menuBar = new JMenuBar();
				rootPanel.setLayout(new BorderLayout());//设置BorderLayout布局，一行两列

			
				JMenu file = new JMenu("系统");
				
				JMenuItem open = new JMenuItem("保存");
				JMenuItem quit = new JMenuItem("退出");
				file.add(open);
				file.addSeparator();
				file.add(quit);
				menuBar.add(file);		
				// 窗口设置菜单栏
				this.setJMenuBar(menuBar);
				
				ActionListener menuListener = e ->{
					String cmd = e.getActionCommand();
					if(cmd.equals("保存")) {
				
						Connection con;
						try {
							con = Student.getConnection();
							while(sqls.size()!=0) {
								PreparedStatement ps = con.prepareStatement(sqls.get(0));
								System.out.println(111);
								ps.executeUpdate();
								sqls.remove(0);
							}
							
						} catch (ClassNotFoundException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						} catch (SQLException e1) {
							// TODO Auto-generated catch block
							e1.printStackTrace();
						}
					}
						
				};
				
				open.addActionListener(menuListener);
				//设置菜单点击事件
		        //quit.addActionListener(menuListener);
				
			
		
			
				JTable table;
				DefaultTableModel model;


		        String[] columns = {   "学号","姓名","年龄","学院","专业","班级","地址" };
		        
		        model = new DefaultTableModel(null, columns){
		            public boolean isCellEditable(int rowindex,int colindex){
		                if (colindex==0||colindex ==1) return false;   //设置第二列只读
		                return true;                     //其他列可以修改
		        }
		        };
		        String sql = "select * from  myDB.student_information";
		        ResultSet result = null;
		        Connection con = null;
		        try {
					con = Student.getConnection();
					java.sql.PreparedStatement ps = con.prepareStatement(sql);
					result = ps.executeQuery();
				} catch (ClassNotFoundException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
		        
		       // 把数据库查出来的数据放到表格里 columns = {   "学号","姓名","年龄","学院","专业","班级","地址" };
		        
		       try {
				while(result.next()) {
					   String []values = {result.getString("Sno"),result.getString("SName"),result.getString("Sage"),result.getString("Scollege"),result.getString("Smajor"),result.getString("Sclassroom"),result.getString("Sadd")};
					   
					   model.addRow(values);
				   }
			} catch (SQLException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		       	
		        table = new JTable(model);
		        JScrollPane pane = new JScrollPane(table);
		        JPanel rightPanel = new JPanel();
				rightPanel.setLayout(new BorderLayout());
				JPanel title = new JPanel();
				JLabel word = new JLabel("学生信息表");
				
				
				table.addKeyListener(new KeyAdapter() {
					public void keyPressed(KeyEvent e) {
						int row = table.getSelectedRow();
						//"学号","姓名","年龄","学院","专业","班级","地址"
						System.out.println(row);
						String name,number,collage,classroom,major,age,add;
						number = (String) table.getValueAt(row, 0);
						collage = (String) table.getValueAt(row,3 );
						classroom = (String) table.getValueAt(row, 5);
						major =(String)  table.getValueAt(row, 4);
						age = (String) table.getValueAt(row,2 );
						add = (String) table.getValueAt(row, 6);
						name = (String) table.getValueAt(row, 1);
						if(rowindex.contains(row))
							rowindex.remove(row);
						sqls.add("update myDB.student_information set Sno = "+number+",Scollege = '"+collage+"',Sclassroom = "+classroom+",Smajor = '"+major+"',Sage = "+age+",Sadd = '"+add+"',Sname = '"+name+"'" + "where Sno = " + number);
						rowindex.add(row);
						System.out.println("update myDB.student_information set Sno = "+number+",Scollege = "+collage+",Sclassroom = "+classroom+",Smajor = "+major+",Sage = "+age+",Sadd = "+add+",Sname = "+name);
						
					}
					
				});
				
				title.add(word);
				rightPanel.add(pane, BorderLayout.CENTER);
				rightPanel.add(title,BorderLayout.NORTH);
	            rootPanel.add(rightPanel, BorderLayout.CENTER);
				
			}

			private JPanel StudentFrame(String username) {
				JPanel rootPanel = (JPanel) this.getContentPane();
				JPanel leftPanel = new JPanel();//左边的信息栏的容器
				JMenuBar menuBar = new JMenuBar();
				rootPanel.setLayout(new BorderLayout());//设置BorderLayout布局，一行两列
                leftPanel.setBackground(new Color(237,181,180));//左边容器的颜色为粉色
				leftPanel.setLayout(new BorderLayout());
                JPanel leftSouth = new JPanel();
				leftSouth.setLayout(new GridLayout(1,1));
				leftSouth.setBackground(Color.pink);
				JButton explain = new JButton("这个人很懒，什么都没写");
				explain.setFont(new Font("微软雅黑",1,30));
				explain.setBorderPainted(false);
				explain.setForeground(Color.WHITE);
			
				
				
				//查询数据库，获取个人信息结果集
				String sql = "select *from mydb.student_information where Sno = "+ username;
				ResultSet result = null;
				
				Connection con  = null;
				try {
						con = Student.getConnection();
						java.sql.PreparedStatement ps = con.prepareStatement(sql);
						result = ps.executeQuery();
				} catch (ClassNotFoundException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
				
				
				leftPanel.setLayout(new BorderLayout());
				JButton nameFiled = new JButton("            姓名 :            ");
				
				JTextField nameLabel = new JTextField(" ");//填入姓名
				
				JButton numberFiled = new JButton("            学号 :            ");
				JTextField numberLabel = new JTextField(" ");//填入学号
				
				JButton collegeFiled = new JButton("            学院 :            ");
				JTextField collegeLabel = new JTextField(" ");//填入学院
				
				JButton majorFiled = new JButton("            专业 :            ");
				JTextField majorLabel = new JTextField(" ");//填入专业
				
				JButton classroomFiled = new JButton("            班级 :            ");
				JTextField classroomLabel = new JTextField(" ");//填入班级
				
				JButton ageFiled = new JButton("            年龄 :            ");
				JTextField ageLabel = new JTextField(" ");//填入年龄
				
				JButton addFiled = new JButton("            地址 :            ");
				JTextField addLabel = new JTextField(" ");//填入地址
				
				
				try {
					if(result.next()) {
						nameLabel.setText(result.getString("Sname"));
						numberLabel.setText(result.getString("Sno"));
						collegeLabel.setText(result.getString("Scollege"));
						majorLabel.setText(result.getString("Smajor"));
						classroomLabel.setText(result.getString("Sclassroom"));
						ageLabel.setText(result.getString("Sage"));
						addLabel.setText(result.getString("Sadd"));
						
						
					}
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				
				nameLabel.setEditable(false);
				numberLabel.setEditable(false);
				collegeLabel.setEditable(false);
				majorLabel.setEditable(false);
				classroomLabel.setEditable(false);
				ageLabel.setEditable(false);
				addLabel.setEditable(false);
				
				
				nameFiled.setBorderPainted(false);
				numberFiled.setBorderPainted(false);	
				collegeFiled.setBorderPainted(false);
				majorFiled.setBorderPainted(false);
				classroomFiled.setBorderPainted(false);
				ageFiled.setBorderPainted(false);
				addFiled.setBorderPainted(false);

				
				
				JPanel infoPanel = new  JPanel();
				GridLayout layout = new GridLayout(7,1);

				infoPanel.setLayout(layout);
				infoPanel.setLayout(layout);
				
				JPanel p[] = new JPanel[7];
				for(int i = 0; i <7;i++) {
					p[i] = new JPanel();
					p[i].setLayout(new BorderLayout());
					p[i].setBackground(new Color(250,219,217));
					
				}
				nameFiled.setFont(new Font("微软雅黑",1,18));
				numberFiled.setFont(new Font("微软雅黑",1,18));
				collegeFiled.setFont(new Font("微软雅黑",1,18));
				majorFiled.setFont(new Font("微软雅黑",1,18));
				classroomFiled.setFont(new Font("微软雅黑",1,18));
				ageFiled.setFont(new Font("微软雅黑",1,18));
				addFiled.setFont(new Font("微软雅黑",1,18));
				
				
				nameLabel.setFont(new Font("微软雅黑",1,18));
				numberLabel.setFont(new Font("微软雅黑",1,18));
				collegeLabel.setFont(new Font("微软雅黑",1,18));
				majorLabel.setFont(new Font("微软雅黑",1,18));
				classroomLabel.setFont(new Font("微软雅黑",1,18));
				ageLabel.setFont(new Font("微软雅黑",1,18));
				addLabel.setFont(new Font("微软雅黑",1,18));
				
				p[0].add(nameFiled, BorderLayout.WEST);
				p[1].add(numberFiled, BorderLayout.WEST);
				p[2].add(collegeFiled, BorderLayout.WEST);
				p[3].add(majorFiled, BorderLayout.WEST);
				p[4].add(classroomFiled, BorderLayout.WEST);
				p[5].add(ageFiled, BorderLayout.WEST);
				p[6].add(addFiled, BorderLayout.WEST);
				p[0].add(nameLabel, BorderLayout.CENTER);
				p[1].add(numberLabel, BorderLayout.CENTER);
				p[2].add(collegeLabel, BorderLayout.CENTER);
				p[3].add(majorLabel, BorderLayout.CENTER);
				p[4].add(classroomLabel, BorderLayout.CENTER);
				p[5].add(ageLabel, BorderLayout.CENTER);
				p[6].add(addLabel, BorderLayout.CENTER);
				
				for(int i = 0; i <7;i++) {
					infoPanel.add(p[i]);
				}
				

				Font font1 = new Font("微软雅黑",1,30);
				
				JButton welcome = new JButton("\n欢迎使用\n");
			
				welcome.setBorderPainted(false);
				welcome.setFont(font1);
				welcome.setForeground(Color.WHITE);

				leftSouth.add(explain);
				
				JMenu file = new JMenu("系统");
			

				
				JMenuItem open = new JMenuItem("保存");
				JMenuItem quit = new JMenuItem("退出");
				file.add(open);
				file.addSeparator();
				file.add(quit);
				menuBar.add(file);		
				// 窗口设置菜单栏
				this.setJMenuBar(menuBar);
				ActionListener menuListener = e -> {  
		            String cmd = e.getActionCommand();  
		            if(cmd.equals("保存")) {
		            	/*数据库进行保存*/
		            	//String sql = 
		            }
		            if (cmd.equals("退出")) {
		             	/*如果点击到退出*/
		                System.exit(0);  
		            }  
		        };  
				//设置菜单点击事件
				
				
			
				leftPanel.add(infoPanel,BorderLayout.CENTER);
				leftPanel.add(leftSouth,BorderLayout.SOUTH);
				leftPanel.add(welcome,BorderLayout.NORTH);		
				
				return leftPanel;
			}
			

	
		
	}
		