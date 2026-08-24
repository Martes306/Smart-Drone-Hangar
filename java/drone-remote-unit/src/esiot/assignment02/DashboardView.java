package esiot.assignment02;

import java.awt.Dimension;
import java.awt.Font;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import javax.swing.*;

class DashboardView extends JFrame implements ActionListener {

	private JButton btnTakeOff;
	private JButton btnLand;
	
	private JLabel lblDroneState;
	private JLabel lblHangarState;
	private JLabel lblDistance;
	
	private DashboardController controller;	
	
	public DashboardView() {
		super(".:: Smart Drone Hangar - DRU ::.");
		setSize(400, 300);
		this.setResizable(false);
		
		JPanel mainPanel = new JPanel();
		mainPanel.setLayout(new BoxLayout(mainPanel, BoxLayout.Y_AXIS));
		mainPanel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));
		
		// Status Panel
		JPanel statusPanel = new JPanel();
		statusPanel.setLayout(new BoxLayout(statusPanel, BoxLayout.Y_AXIS));
		statusPanel.setBorder(BorderFactory.createTitledBorder("Telemetry"));

		lblDroneState = new JLabel("Drone State: UNKNOWN");
		lblDroneState.setFont(new Font("Arial", Font.BOLD, 14));
		lblHangarState = new JLabel("Hangar State: UNKNOWN");
		lblHangarState.setFont(new Font("Arial", Font.BOLD, 14));
		lblDistance = new JLabel("Distance: --");
		lblDistance.setFont(new Font("Arial", Font.BOLD, 14));
		
		statusPanel.add(lblDroneState);
		statusPanel.add(Box.createRigidArea(new Dimension(0, 10)));
		statusPanel.add(lblHangarState);
		statusPanel.add(Box.createRigidArea(new Dimension(0, 10)));
		statusPanel.add(lblDistance);
		
		mainPanel.add(statusPanel);
		mainPanel.add(Box.createRigidArea(new Dimension(0, 20)));

		// Control Panel
		JPanel controlPanel = new JPanel();
		controlPanel.setBorder(BorderFactory.createTitledBorder("Commands"));
		
		btnTakeOff = new JButton("Take Off");
		btnTakeOff.addActionListener(this);
		
		btnLand = new JButton("Land");
		btnLand.addActionListener(this);
		
		controlPanel.add(btnTakeOff);
		controlPanel.add(btnLand);
		
		mainPanel.add(controlPanel);
		
		setContentPane(mainPanel);	
		
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent ev) {
				if (controller != null) {
					controller.close();
				}
				System.exit(0);
			}
		});
	}
	
	public void display() {
		SwingUtilities.invokeLater(() -> {
			this.setVisible(true);
		});
	}

	public void registerController(DashboardController contr) {
		this.controller = contr;
	}

	// Update the drone state label in the GUI
	public void setDroneState(String state) {
		SwingUtilities.invokeLater(() -> {
			lblDroneState.setText("Drone State: " + state); 
		});
	}

	// Update the hangar state label in the GUI
	public void setHangarState(String state) {
		SwingUtilities.invokeLater(() -> {
			lblHangarState.setText("Hangar State: " + state);
		});
	}

	// Update the distance label in the GUI
	public void setDistance(double dist) {
		SwingUtilities.invokeLater(() -> {
			if (dist < 0) {
				lblDistance.setText("Distance: N/A");
			} else {
				lblDistance.setText(String.format("Distance: %.2f cm", dist));
			}
		});
	}
	
	// Handle button clicks for Take Off and Land commands
	public void actionPerformed(ActionEvent ev) {
		try {
			if (ev.getSource() == btnTakeOff) {
				if (controller != null) controller.sendTakeOff();
			} else if (ev.getSource() == btnLand) {
				if (controller != null) controller.sendLand();
			}
		} catch (Exception ex) {
			ex.printStackTrace();
		}
	}
}