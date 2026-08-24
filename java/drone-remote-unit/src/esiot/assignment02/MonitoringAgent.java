package esiot.assignment02;

public class MonitoringAgent extends Thread {

	SerialCommChannel channel;
	DashboardView view;
	LogView logger;
	private volatile boolean stopped = false;

	public MonitoringAgent(SerialCommChannel channel, DashboardView view, LogView log) throws Exception {
		this.view = view;
		this.logger = log;
		this.channel = channel;
	}

	public void run() {
		while (!stopped) {
			try {
				String msg = channel.receiveMsg();

				// Expected format: DRONE_STATE|ALARM_STATE|DISTANCE
				// Example: TAKEOFF|NO_ALARM|25.50
				String[] parts = msg.split("\\|");
				if (parts.length >= 3) {
					// Parse the telemetry data from the message received from the Arduino
					String droneState = parts[0];
					String alarmState = parts[1];
					double distance = -1;
					try {
						distance = Double.parseDouble(parts[2]);
					} catch (NumberFormatException e) {
						// Ignore parsing errors for distance
					}

					// Set the telemetry data in the view
					view.setDroneState(droneState);
					view.setHangarState(alarmState);
					view.setDistance(distance);

					// If the drone is outside and there's an alarm, we should log it or show it.
					if ("ALARM".equals(alarmState) && "OUTSIDE".equals(droneState)) {
						logger.log("ALARM received while drone is OUTSIDE.");
					}
				}
			} catch (InterruptedException ex) {
				// Thread interrupted, exiting loop
			} catch (Exception ex) {
				if (!stopped) {
					ex.printStackTrace();
				}
			}
		}
	}

	// Stop the monitoring agent thread
	public void stopAgent() {
		stopped = true;
		this.interrupt();
	}

}