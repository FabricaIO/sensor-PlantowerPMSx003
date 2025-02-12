#include "PlantowerPMSx003.h";

/// @brief Creates a Plantower PMS object using hardware serial
/// @param SerialPort Pointer to the serial port to use
/// @param RX_Pin The RX pin to use
/// @param TX_Pin The TX pin to use
PlantowerPMSx003::PlantowerPMSx003(HardwareSerial* SerialPort, int RX_Pin, int TX_Pin) : pms(PMSx003, *SerialPort) {
	rxpin = RX_Pin;
	txpin = TX_Pin;
	hardwareSerialPort = SerialPort;
}

/// @brief Creates a Plantower PMS object using software serial
/// @param RX_Pin The RX pin to use
/// @param TX_Pin The TX pin to use
PlantowerPMSx003::PlantowerPMSx003(int RX_Pin, int TX_Pin) : pms(PMSx003), softwareSerialPort(RX_Pin, TX_Pin) {
	pms.setSerialPort(&softwareSerialPort);
	use_soft_serial = true;
}

bool PlantowerPMSx003::begin() {
	Description.parameterQuantity = 3;
	Description.name = "Plantower PMS";
	Description.type = "air quality";
	Description.parameters = {"PM1", "PM2.5", "PM10"};
	Description.units = {"ug/m3", "ug/m3", "ug/m3"};
	Description.version = "0.5";
	values.resize(Description.parameterQuantity);
	if (use_soft_serial) {
		softwareSerialPort.begin(9600);
	} else 
	{
		hardwareSerialPort->begin(9600, SERIAL_8N1, rxpin, txpin);
	}
	pms.init();
	return true;
}

bool PlantowerPMSx003::takeMeasurement() {
	pms.read();
	Logger.println("PlantowerPMSx003 status: " + String(pms.status));
	if (pms.status == SerialPM::STATUS::OK) {
		values[0] = pms.pm01;
		values[1] = pms.pm25;
		values[2] = pms.pm10;
		return true;
	} else {
		Logger.println("PlantowerPMSx003: Error taking measurement");
		return false;
	}
}