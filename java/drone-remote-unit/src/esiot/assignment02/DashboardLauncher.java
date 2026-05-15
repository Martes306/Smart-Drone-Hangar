package esiot.assignment02;

public class DashboardLauncher {

	static DashboardView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {	
		
		String portName = "";
		if (args.length == 1) {
			portName = args[0];
		} else {
			// fallback default port (change to match your OS, e.g., COM3 or /dev/ttyACM0)
			portName = "/dev/ttyACM0"; 
			System.out.println("No serial port specified, defaulting to " + portName);
		}

		view = new DashboardView();
		log = new LogView();
		
		try {
			DashboardController contr = new DashboardController(portName, view, log);
			view.registerController(contr);
		} catch (Exception e) {
			System.err.println("Could not connect to serial port " + portName);
			System.err.println("Please specify the correct port as a command line argument.");
			// e.printStackTrace();
		}
		
		view.display();
		log.display();
	}
}