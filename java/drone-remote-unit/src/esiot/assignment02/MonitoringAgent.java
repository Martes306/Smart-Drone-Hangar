package esiot.assignment02;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	DashboardView view;
	LogView logger;
	
	public MonitoringAgent(SerialCommChannel channel, DashboardView view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.channel = channel;
	}
	
	public void run() {
		while (true) {
			try {
				String msg = channel.receiveMsg();
				
				// Optional: log every message
				// logger.log("Received: " + msg);
				
				// Expected format: DRONE_STATE|ALARM_STATE|DISTANCE
				// Example: TAKEOFF|NO_ALARM|25.50
				String[] parts = msg.split("\\|");
				if (parts.length >= 3) {
					String droneState = parts[0];
					String alarmState = parts[1];
					double distance = -1;
					try {
						distance = Double.parseDouble(parts[2]);
					} catch (NumberFormatException e) {
						// Ignore parsing errors for distance
					}
					
					view.setDroneState(droneState);
					view.setHangarState(alarmState);
					view.setDistance(distance);
					
					// If the drone is outside and there's an alarm, we should log it or show it.
					// The assignment says: "If the drone is outside the hangar, the ALARM message is also sent to the drone via DRU."
					if ("ALARM".equals(alarmState) && "OUTSIDE".equals(droneState)) {
						logger.log("ALARM received while drone is OUTSIDE.");
					}
				} else {
					// Fallback for logging arbitrary messages (e.g., debug messages from Arduino)
					if (!msg.trim().isEmpty()) {
						logger.log("MSG: " + msg);
					}
				}
			} catch (Exception ex) {
				ex.printStackTrace();
			}
		}
	}

}