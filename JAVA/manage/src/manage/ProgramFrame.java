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
				//���ô�����
				this.setDefaultCloseOperation(EXIT_ON_CLOSE);//�رմ��ڽ�������
				this.setSize(this.windowWight,this.windowHight);
				this.setBounds((width - windowWight) / 2,
		                (height - windowHight) / 2, windowWight, windowHight); 
				JPanel rootPanel = (JPanel) this.getContentPane();
				if(identity.equals("S")) {
					/*�����ѧ��*/
					this.setTitle("ѧ���ͻ���");
					rootPanel.add(StudentFrame(username));
				}else {
					this.setTitle("��ʦ�ͻ���");
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
				rootPanel.setLayout(new BorderLayout());//����BorderLayout���֣�һ������

			
				JMenu file = new JMenu("ϵͳ");
				
				JMenuItem open = new JMenuItem("����");
				JMenuItem quit = new JMenuItem("�˳�");
				file.add(open);
				file.addSeparator();
				file.add(quit);
				menuBar.add(file);		
				// �������ò˵���
				this.setJMenuBar(menuBar);
				
				ActionListener menuListener = e ->{
					String cmd = e.getActionCommand();
					if(cmd.equals("����")) {
				
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
				//���ò˵�����¼�
		        //quit.addActionListener(menuListener);
				
			
		
			
				JTable table;
				DefaultTableModel model;


		        String[] columns = {   "ѧ��","����","����","ѧԺ","רҵ","�༶","��ַ" };
		        
		        model = new DefaultTableModel(null, columns){
		            public boolean isCellEditable(int rowindex,int colindex){
		                if (colindex==0||colindex ==1) return false;   //���õڶ���ֻ��
		                return true;                     //�����п����޸�
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
		        
		       // �����ݿ����������ݷŵ������ columns = {   "ѧ��","����","����","ѧԺ","רҵ","�༶","��ַ" };
		        
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
				JLabel word = new JLabel("ѧ����Ϣ��");
				
				
				table.addKeyListener(new KeyAdapter() {
					public void keyPressed(KeyEvent e) {
						int row = table.getSelectedRow();
						//"ѧ��","����","����","ѧԺ","רҵ","�༶","��ַ"
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
				JPanel leftPanel = new JPanel();//��ߵ���Ϣ��������
				JMenuBar menuBar = new JMenuBar();
				rootPanel.setLayout(new BorderLayout());//����BorderLayout���֣�һ������
                leftPanel.setBackground(new Color(237,181,180));//�����������ɫΪ��ɫ
				leftPanel.setLayout(new BorderLayout());
                JPanel leftSouth = new JPanel();
				leftSouth.setLayout(new GridLayout(1,1));
				leftSouth.setBackground(Color.pink);
				JButton explain = new JButton("����˺�����ʲô��ûд");
				explain.setFont(new Font("΢���ź�",1,30));
				explain.setBorderPainted(false);
				explain.setForeground(Color.WHITE);
			
				
				
				//��ѯ���ݿ⣬��ȡ������Ϣ�����
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
				JButton nameFiled = new JButton("            ���� :            ");
				
				JTextField nameLabel = new JTextField(" ");//��������
				
				JButton numberFiled = new JButton("            ѧ�� :            ");
				JTextField numberLabel = new JTextField(" ");//����ѧ��
				
				JButton collegeFiled = new JButton("            ѧԺ :            ");
				JTextField collegeLabel = new JTextField(" ");//����ѧԺ
				
				JButton majorFiled = new JButton("            רҵ :            ");
				JTextField majorLabel = new JTextField(" ");//����רҵ
				
				JButton classroomFiled = new JButton("            �༶ :            ");
				JTextField classroomLabel = new JTextField(" ");//����༶
				
				JButton ageFiled = new JButton("            ���� :            ");
				JTextField ageLabel = new JTextField(" ");//��������
				
				JButton addFiled = new JButton("            ��ַ :            ");
				JTextField addLabel = new JTextField(" ");//�����ַ
				
				
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
				nameFiled.setFont(new Font("΢���ź�",1,18));
				numberFiled.setFont(new Font("΢���ź�",1,18));
				collegeFiled.setFont(new Font("΢���ź�",1,18));
				majorFiled.setFont(new Font("΢���ź�",1,18));
				classroomFiled.setFont(new Font("΢���ź�",1,18));
				ageFiled.setFont(new Font("΢���ź�",1,18));
				addFiled.setFont(new Font("΢���ź�",1,18));
				
				
				nameLabel.setFont(new Font("΢���ź�",1,18));
				numberLabel.setFont(new Font("΢���ź�",1,18));
				collegeLabel.setFont(new Font("΢���ź�",1,18));
				majorLabel.setFont(new Font("΢���ź�",1,18));
				classroomLabel.setFont(new Font("΢���ź�",1,18));
				ageLabel.setFont(new Font("΢���ź�",1,18));
				addLabel.setFont(new Font("΢���ź�",1,18));
				
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
				

				Font font1 = new Font("΢���ź�",1,30);
				
				JButton welcome = new JButton("\n��ӭʹ��\n");
			
				welcome.setBorderPainted(false);
				welcome.setFont(font1);
				welcome.setForeground(Color.WHITE);

				leftSouth.add(explain);
				
				JMenu file = new JMenu("ϵͳ");
			

				
				JMenuItem open = new JMenuItem("����");
				JMenuItem quit = new JMenuItem("�˳�");
				file.add(open);
				file.addSeparator();
				file.add(quit);
				menuBar.add(file);		
				// �������ò˵���
				this.setJMenuBar(menuBar);
				ActionListener menuListener = e -> {  
		            String cmd = e.getActionCommand();  
		            if(cmd.equals("����")) {
		            	/*���ݿ���б���*/
		            	//String sql = 
		            }
		            if (cmd.equals("�˳�")) {
		             	/*���������˳�*/
		                System.exit(0);  
		            }  
		        };  
				//���ò˵�����¼�
				
				
			
				leftPanel.add(infoPanel,BorderLayout.CENTER);
				leftPanel.add(leftSouth,BorderLayout.SOUTH);
				leftPanel.add(welcome,BorderLayout.NORTH);		
				
				return leftPanel;
			}
			

	
		
	}
		