package esiot.assignment02;

public class DashboardLauncher {

	static DashboardView view = null;
	static LogView log = null;

	public static void main(String[] args) throws Exception {

		String portName = "/dev/ttyACM0";

		view = new DashboardView();
		log = new LogView();

		try {
			DashboardController contr = new DashboardController(portName, view, log);
			view.registerController(contr);
		} catch (Exception e) {
			System.err.println("Could not connect to serial port " + portName);
			System.err.println("Error: " + e.getMessage());
		}

		view.display();
		log.display();
	}
}