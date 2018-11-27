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
			lblNewLabel.setFont(new Font("΢���ź�", Font.BOLD, 18));
			frame.getContentPane().add(lblNewLabel);
			
			JLabel lblNewLabel_1 = new JLabel("\u5BC6\u7801");
			lblNewLabel_1.setBounds(65, 79, 54, 20);
			lblNewLabel_1.setFont(new Font("΢���ź�", Font.BOLD, 18));
			frame.getContentPane().add(lblNewLabel_1);
			
			user = new JTextField();
			user.setBounds(125, 43, 100, 20);
			frame.getContentPane().add(user);
			user.setColumns(10);
			
			pass = new JTextField();
			pass.setBounds(125, 80, 100, 20);
			pass.setColumns(10);
			frame.getContentPane().add(pass);
			
			JButton stulog = new JButton("ѧ����¼");
			stulog.setFont(new Font("΢���ź�", Font.BOLD, 20));
			stulog.setBounds(30, 157, 140, 44);
			stulog.addActionListener(new java.awt.event.ActionListener() {
	            public void actionPerformed(java.awt.event.ActionEvent evt) {
	            	try { //�����¼��ť���е�¼����
	                    stuloginActionPerformed(evt); 
	                 } catch (IOException e){
	                     e.printStackTrace();
	                 }
	            }
	        });
			frame.getContentPane().add(stulog);
			
			JButton telog = new JButton("��ʦ��¼");
			telog.setFont(new Font("΢���ź�", Font.BOLD, 20));
			telog.setBounds(172, 157, 140, 44);
			telog.addActionListener(new java.awt.event.ActionListener() {
	            public void actionPerformed(java.awt.event.ActionEvent evt) {
	            	try { //�����¼��ť���е�¼����
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
		
		
			 public boolean stucheck(String number,String pass) { //����û��Ƿ�Ϸ�
			        try {
			         Connection con1 = getConnection();
			         System.out.println(1);
			        
			         PreparedStatement ps = con1.prepareStatement("select * from student where sno = "+number);
			         System.out.println(2);

			        
			         ResultSet pswd = ps.executeQuery();
			         System.out.println(3);
			         pswd.next();
			       
			         System.out.println(pswd.getString("Spassword"));
			         if(pswd.getString("Spassword").equals(pass)){ //����û�������û����������Ƿ������ݿ��еļ�¼ƥ��
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
			    
			    private boolean stucheckNull(String u, String p) { //�����û�����������Ƿ�Ϊ��
			        if(!u.equals("")) {
			            if(!p.equals("")) {
			                return true;
			            } else {
			                JOptionPane.showConfirmDialog(null,"����������","��ʾ",JOptionPane.WARNING_MESSAGE);
			                pass.setText("");
			                return false;
			            }
			        } else {
			            JOptionPane.showConfirmDialog(null,"�������û���","��ʾ",JOptionPane.WARNING_MESSAGE);
			            return false;
			        }
			    }
			    
			    
			    private void stuloginBean() throws IOException { //��¼����
			        String u = user.getText().trim();
			        String p = pass.getText();
			        if(stucheckNull(u,p)) {
			        	
			            if(stucheck(u,p)){
			                JOptionPane.showConfirmDialog(null,"��¼�ɹ�,��ӭ��","��¼",JOptionPane.PLAIN_MESSAGE);
			                frame.setVisible(false);
			                new ProgramFrame(u,p,"S");
			            } else {
			                JOptionPane.showConfirmDialog(null,"�û������������","��ʾ",JOptionPane.WARNING_MESSAGE);
			            }
			        }
			    }
        
        	 public boolean check(String number,String pass) { //����û��Ƿ�Ϸ�
			        try {
			         Connection con1 = getConnection();
			         PreparedStatement ps = con1.prepareStatement("select * from teacher_information where tno = "+number);
			         
			         ResultSet pswd = ps.executeQuery();
			         pswd.next();
			         if(pswd.getString("Tpassword").equals(pass)){ //����û�������û����������Ƿ������ݿ��еļ�¼ƥ��
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
			    
			    private boolean checkNull(String u, String p) { //�����û�����������Ƿ�Ϊ��
			        if(!u.equals("")) {
			            if(!p.equals("")) {
			                return true;
			            } else {
			                JOptionPane.showConfirmDialog(null,"����������","��ʾ",JOptionPane.WARNING_MESSAGE);
			                pass.setText("");
			                return false;
			            }
			        } else {
			            JOptionPane.showConfirmDialog(null,"�������û���","��ʾ",JOptionPane.WARNING_MESSAGE);
			            return false;
			        }
			    }
			    
			    
			    private void teloginBean() throws IOException { //��¼����
			        String u = user.getText().trim();
			        String p = pass.getText();
			        if(checkNull(u,p)) {
			            if(check(u,p)){
			                JOptionPane.showConfirmDialog(null,"��¼�ɹ�,��ӭ��","��¼",JOptionPane.PLAIN_MESSAGE);
			                frame.setVisible(false);
			                new ProgramFrame(u,p,"T");
			            } else {
			                JOptionPane.showConfirmDialog(null,"�û������������","��ʾ",JOptionPane.WARNING_MESSAGE);
			            }
			        }
			    }	
		}


