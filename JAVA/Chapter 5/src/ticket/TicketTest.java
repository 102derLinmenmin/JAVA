/**
 * 
 */
package ticket;

/**
 * @author HY
 *
 */
public class TicketTest {

		public static void main(String[] args) {
			// TODO Auto-generated method stub
			 Ticket ticket = new Ticket();
			  for(int line = 1 ; line <= 3 ; line ++){			  
			      new Thread(ticket,""+line).start();
			  }
		}

	}

