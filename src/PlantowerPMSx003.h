/*
* This file and associated .cpp file are licensed under the GPLv3 License Copyright (c) 2024 Sam Groveman
* Contributors: Sam Groveman
* 
* External libraries needed:
* PMserial: https://github.com/avaldebe/PMserial
* ESPSoftwareSerial: https://github.com/plerup/espsoftwareserial
* 
* Arduino library for PM sensors with serial interface
* PMS1003 aka G1
* PMS3003 aka G2
* PMS5003 aka G5
* PMS7003 aka G7
* PMSA003 aka G10
*/

#pragma once
#include <Arduino.h>
#include <PMserial.h>
#include <Sensor.h>
#include <HardwareSerial.h>
#include <SoftwareSerial.h>

/// @brief Contoller for PMSx003 air quality sensors
class PlantowerPMSx003 : public Sensor {
	public:
		PlantowerPMSx003(HardwareSerial* SerialPort, int RX_Pin = 16, int TX_Pin = 17);
		PlantowerPMSx003(int RX_Pin, int TX_Pin);
		bool begin();
		bool takeMeasurement();
	private:

		/// @brief Pointer to HardwareSerial port, if using
		HardwareSerial* hardwareSerialPort;

		/// @brief SoftwareSerial port, if using
		SoftwareSerial softwareSerialPort;

		/// @brief Indicates if software serial is being used
		bool use_soft_serial = false;

		/// @brief The RX pin used
		int rxpin;

		/// @brief The TX pin used
		int txpin;

		/// @brief The plantower object
		SerialPM pms;
};