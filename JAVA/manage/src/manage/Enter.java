/**
 * 
 */
package manage;

import static manage.Student.getConnection;

/**
 * @author HY
 *
 */

	import java.awt.EventQueue;
    import java.awt.event.*;
	import javax.swing.JFrame;
	import java.awt.SystemColor;
    import java.io.IOException;
    import java.sql.Connection;
    import java.sql.PreparedStatement;
    import java.sql.ResultSet;
    import java.sql.SQLException;

    import javax.swing.JTextField;
    import java.awt.Font;
    import javax.swing.JLabel;
    import javax.swing.JOptionPane;
    import javax.swing.JButton;

	public class Enter{

		private JFrame frame;
		private JTextField user;
		private JTextField pass;
		boolean islogin = false;

		/**
		 * Launch the application.
		 */
		public static void main(String[] args) {
			EventQueue.invokeLater(new Runnable() {
				public void run() {
					try {
						Enter window = new Enter();
						window.frame.setVisible(true);
					} catch (Exception e) {
						e.printStackTrace();
					}
				}
			});
		}

		/**
		 * Create the application.
		 */
		public Enter() {
			initialize();
		}

		/**
		 * Initialize the contents of the frame.
		 */
		private void initialize() {
			frame = new JFrame();
			frame.getContentPane().setBackground(SystemColor.window);
			frame.setBackground(SystemColor.info);
			frame.setBounds(100, 100, 335, 257);
			frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
			frame.getContentPane().setLayout(null);
			
			JLabel lblNewLabel = new JLabel("\u8D26\u53F7");
			lblNewLabel.setBounds(65, 41, 54, 20);
			lblNewLabel.setFont(new Font("微软雅黑", Font.BOLD, 18));
			frame.getContentPane().add(lblNewLabel);
			
			JLabel lblNewLabel_1 = new JLabel("\u5BC6\u7801");
			lblNewLabel_1.setBounds(65, 79, 54, 20);
			lblNewLabel_1.setFont(new Font("微软雅黑", Font.BOLD, 18));
			frame.getContentPane().add(lblNewLabel_1);
			
			user = new JTextField();
			user.setBounds(125, 43, 100, 20);
			frame.getContentPane().add(user);
			user.setColumns(10);
			
			pass = new JTextField();
			pass.setBounds(125, 80, 100, 20);
			pass.setColumns(10);
			frame.getContentPane().add(pass);
			
			JButton stulog = new JButton("学生登录");
			stulog.setFont(new Font("微软雅黑", Font.BOLD, 20));
			stulog.setBounds(30, 157, 140, 44);
			stulog.addActionListener(new java.awt.event.ActionListener() {
	            public void actionPerformed(java.awt.event.ActionEvent evt) {
	            	try { //点击登录按钮进行登录处理
	                    stuloginActionPerformed(evt); 
	                 } catch (IOException e){
	                     e.printStackTrace();
	                 }
	            }
	        });
			frame.getContentPane().add(stulog);
			
			JButton telog = new JButton("教师登录");
			telog.setFont(new Font("微软雅黑", Font.BOLD, 20));
			telog.setBounds(172, 157, 140, 44);
			telog.addActionListener(new java.awt.event.ActionListener() {
	            public void actionPerformed(java.awt.event.ActionEvent evt) {
	            	try { //点击登录按钮进行登录处理
	                    teloginActionPerformed(evt); 
	                 } catch (IOException e){
	                     e.printStackTrace();
	                 }
	            }
	        });
			frame.getContentPane().add(telog);
		}
		
		public void stuloginActionPerformed(ActionEvent e) throws IOException {
			stuloginBean();
		}
		
		public void teloginActionPerformed(ActionEvent e) throws IOException {
			teloginBean();
		}
		
		
			 public boolean stucheck(String number,String pass) { //检测用户是否合法
			        try {
			         Connection con1 = getConnection();
			         System.out.println(1);
			        
			         PreparedStatement ps = con1.prepareStatement("select * from student where sno = "+number);
			         System.out.println(2);

			        
			         ResultSet pswd = ps.executeQuery();
			         System.out.println(3);
			         pswd.next();
			       
			         System.out.println(pswd.getString("Spassword"));
			         if(pswd.getString("Spassword").equals(pass)){ //检测用户输入的用户名及密码是否与数据库中的记录匹配
			             islogin = true;
			         }
			         con1.close();
			        }catch (java.lang.ClassNotFoundException e) {
			         System.err.println("ClassNotFoundException: ");
			         System.err.println(e.getMessage());
			        }catch (SQLException ex) {
			            System.out.println("SQLException: "+ex.getMessage());
			        }
			        return islogin;
			    }
			    
			    private boolean stucheckNull(String u, String p) { //检验用户名或密码框是否为空
			        if(!u.equals("")) {
			            if(!p.equals("")) {
			                return true;
			            } else {
			                JOptionPane.showConfirmDialog(null,"请输入密码","提示",JOptionPane.WARNING_MESSAGE);
			                pass.setText("");
			                return false;
			            }
			        } else {
			            JOptionPane.showConfirmDialog(null,"请输入用户名","提示",JOptionPane.WARNING_MESSAGE);
			            return false;
			        }
			    }
			    
			    
			    private void stuloginBean() throws IOException { //登录处理
			        String u = user.getText().trim();
			        String p = pass.getText();
			        if(stucheckNull(u,p)) {
			        	
			            if(stucheck(u,p)){
			                JOptionPane.showConfirmDialog(null,"登录成功,欢迎您","登录",JOptionPane.PLAIN_MESSAGE);
			                frame.setVisible(false);
			                new ProgramFrame(u,p,"S");
			            } else {
			                JOptionPane.showConfirmDialog(null,"用户名或密码错误","提示",JOptionPane.WARNING_MESSAGE);
			            }
			        }
			    }
        
        	 public boolean check(String number,String pass) { //检测用户是否合法
			        try {
			         Connection con1 = getConnection();
			         PreparedStatement ps = con1.prepareStatement("select * from teacher_information where tno = "+number);
			         
			         ResultSet pswd = ps.executeQuery();
			         pswd.next();
			         if(pswd.getString("Tpassword").equals(pass)){ //检测用户输入的用户名及密码是否与数据库中的记录匹配
			             islogin = true;
			         }
			         con1.close();
			        }catch (java.lang.ClassNotFoundException e) {
			         System.err.println("ClassNotFoundException: ");
			         System.err.println(e.getMessage());
			        }catch (SQLException ex) {
			            System.out.println("SQLException: "+ex.getMessage());
			        }
			        return islogin;
			    }
			    
			    private boolean checkNull(String u, String p) { //检验用户名或密码框是否为空
			        if(!u.equals("")) {
			            if(!p.equals("")) {
			                return true;
			            } else {
			                JOptionPane.showConfirmDialog(null,"请输入密码","提示",JOptionPane.WARNING_MESSAGE);
			                pass.setText("");
			                return false;
			            }
			        } else {
			            JOptionPane.showConfirmDialog(null,"请输入用户名","提示",JOptionPane.WARNING_MESSAGE);
			            return false;
			        }
			    }
			    
			    
			    private void teloginBean() throws IOException { //登录处理
			        String u = user.getText().trim();
			        String p = pass.getText();
			        if(checkNull(u,p)) {
			            if(check(u,p)){
			                JOptionPane.showConfirmDialog(null,"登录成功,欢迎您","登录",JOptionPane.PLAIN_MESSAGE);
			                frame.setVisible(false);
			                new ProgramFrame(u,p,"T");
			            } else {
			                JOptionPane.showConfirmDialog(null,"用户名或密码错误","提示",JOptionPane.WARNING_MESSAGE);
			            }
			        }
			    }	
		}


