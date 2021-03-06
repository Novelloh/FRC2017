#include <PowerDistributionPanel.h>
#include <SampleRobot.h>
#include <SmartDashboard/SmartDashboard.h>
#include <Timer.h>

/**
 * This is a sample program showing how to retrieve information from the Power
 * Distribution Panel via CAN. The information will be displayed under variables
 * through the SmartDashboard.
 */
class Robot: public frc::SampleRobot {
public:
	/**
	 * Retrieve information from the PDP over CAN and displays it on the
	 * SmartDashboard interface. SmartDashboard::PutNumber takes a string (for a
	 * label) and a double; GetCurrent takes a channel number and returns a
	 * double for current, in Amperes. Channel numbers are printed on the PDP
	 * and range from 0-15.
	 */
	void OperatorControl() override {
		while (IsOperatorControl() && IsEnabled()) {
			/* Get the current going through channel 7, in Amperes. The PDP
			 * returns the current in increments of 0.125A. At low currents the
			 * current readings tend to be less accurate.
			 */
			frc::SmartDashboard::PutNumber("Current Channel 7",
					m_pdp.GetCurrent(7));

			/* Get the voltage going into the PDP, in Volts.
			 * The PDP returns the voltage in increments of 0.05 Volts.
			 */
			frc::SmartDashboard::PutNumber("Voltage", m_pdp.GetVoltage());

			// Retrieves the temperature of the PDP, in degrees Celsius.
			frc::SmartDashboard::PutNumber("Temperature",
					m_pdp.GetTemperature());

			frc::Wait(kUpdatePeriod);
		}
	}

private:
	// Object for dealing with the Power Distribution Panel (PDP).
	frc::PowerDistributionPanel m_pdp;

	// Update every 5milliseconds/0.005 seconds.
	static constexpr double kUpdatePeriod = 0.005;
};

START_ROBOT_CLASS(Robot)
