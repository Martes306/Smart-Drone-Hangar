package esiot.assignment02;

public class DashboardController {

	SerialCommChannel channel;
	DashboardView view;
	LogView logger;
	
	public DashboardController(String port, DashboardView view, LogView logger) throws Exception {
		this.view = view;
		this.logger = logger;
		
		channel = new SerialCommChannel(port, 115200);		
		new MonitoringAgent(channel, view, logger).start();
		
		System.out.println("Waiting Arduino for rebooting...");		
		Thread.sleep(4000);
		System.out.println("Ready.");		
	}
	
	public void sendTakeOff() {
		channel.sendMsg("TAKEOFF");
		if (logger != null) logger.log("Sent command: TAKEOFF");
	}

	public void sendLand() {
		channel.sendMsg("LAND");
		if (logger != null) logger.log("Sent command: LAND");
	}

}