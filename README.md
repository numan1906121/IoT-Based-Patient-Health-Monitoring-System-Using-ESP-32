# IoT-Based-Patient-Health-Monitoring-System-Using-ESP-32

This IoT-based real-time patient monitoring system measures temperature, pressure, humidity, gas levels, heart rate, and oxygen saturation using multiple sensors. Data are sent via RF communication, and alerts trigger automatically when parameters exceed safe thresholds to ensure timely care.


## 📋 Table of Contents
- [Introduction](#introduction)
- [Key Features](#key-features)
- [Hardware Requirements with Cost Analysis](#hardware-requirements-with-cost-analysis)
- [Full Source Code of Firmware](#full-source-code-of-firmware)
- [Implementation and Result](#implementation-and-result)
- [Design Analysis and Evaluation](#design-analysis-and-evaluation)
- [Future Work](#future-work)


##  Introduction

This project was developed as part of the EEE 416 Microprocessor and Embedded System Laboratory course at Bangladesh University of Engineering and Technology (BUET).This IoT-based real-time patient monitoring system measures temperature, pressure, humidity, gas levels, heart rate, and oxygen saturation using multiple sensors.


##  Key Features

- **Real-Time Environmental Monitoring**: Tracks Humidity and Temperature of the environment in patient's surroindings
- **Pulse Rate Monitoring**: Continuously measures the patient's heart rate, offering critical data for assessing cardiovascular health.
- **Body Temperature Monitoring**: Provides real-time tracking of the patient’s body temperature, enabling the detection of fever or other health issues.
- **Oxygen Saturation Monitoring**: Measures the oxygen levels in the patient's blood, a vital parameter for assessing respiratory and overall health.

##  Hardware Requirements with Cost Analysis

| Component | Quantity | Price (BDT) |
|-----------|----------|-------------|
| DHT11 sensor | 1 | 100 |
| MQ sensor | 1 | 100|
| Flame IR sensor | 1 | 60 |
| MAX 30102 | 1 | 150 |
| DS18B20s | 1 | 120 |
| OLED display | 1 | 210 |
| ESP 32 microcontroller | 2 | 760 |
| LCD display | 1 | 130 |
| I2C driver | 1 | 80 |
| PCB board | 2 | 768 |
| Buzzer & LED | 3 | 15 |
| **Total** | | **2,493** |

## Full Source Code of Firmware
Added in the commit list

##  Implementation and Result
Added in the commit list



### Design Analysis and Evaluation

Several novel features were added to enhance the system. It enables mobile real-time monitoring of patient vitals, sends automatic SOS alerts to doctors when thresholds are exceeded, operates without an external Wi-Fi module, and uses an LED-buzzer for instant environmental alerts.

### Future Work

The future works and prospects of the IoT-based health monitoring system project are promising, with potential avenues for further development and expansion. Some key areas for future exploration include:
1.	Enhanced Sensor Integration:
    -	Explore the integration of additional sensors and health monitoring devices to broaden the scope of monitored parameters, providing a more comprehensive health profile for patients.
2.	Machine Learning and Predictive Analytics:
    -	Implement machine learning algorithms and predictive analytics to analyze historical health data. This can enable the system to anticipate potential health issues and proactively suggest interventions.
3.	Telemedicine Integration:
    -	Integrate telemedicine functionalities to facilitate remote consultations between healthcare providers and patients, fostering a more holistic approach to virtual healthcare.


##  Contact

For questions or suggestions, please open an issue or contact the team members through the university email system.

---

**Note**: This project was presented as part of the EEE 414 curriculum. The code and documentation are provided for educational purposes.
