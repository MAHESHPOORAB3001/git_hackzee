# Waste water treatment using electrocougualtion
[Watch the demo video](./video.mp4) \
[project image 1](./image1.jpg) \
[project image 2](./image2.jpg) \
[project image 3](./image3.jpg) \
[project image 4](./image4.jpg) \

# IoT-Enabled Electrocoagulation Water Treatment System

## Overview

This project focuses on developing an innovative electrocoagulation-based water treatment system powered by IoT technology. It integrates pH and TDS sensors with an ESP32 microcontroller to monitor water quality in real-time. The system employs the ThingSpeak platform for cloud-based data visualization and optimization, ensuring efficient and sustainable water purification.

Electrocoagulation is a chemical-free process that uses electrical currents to remove pollutants from water by coagulating impurities. This project demonstrates a scalable and efficient solution for addressing water pollution in industrial and environmental settings.

---

## Features

- Real-Time Monitoring: Tracks water quality parameters, including pH and TDS levels, during the electrocoagulation process.
- Cloud Integration: Utilizes the ThingSpeak platform for real-time data visualization and remote monitoring.
- IoT-Based Automation: The ESP32 microcontroller collects sensor data and transmits it to the cloud, enabling process optimization.
- Sustainable Design: Promotes energy-efficient and environmentally friendly water treatment.

---

## Hardware Components

1. ESP32 Microcontroller: The core processing unit, responsible for data acquisition and transmission.
2. pH Sensor: Measures the acidity or alkalinity of water.
3. TDS Sensor: Monitors the concentration of dissolved solids in water.
4. Electrodes: Aluminum electrodes used for the electrocoagulation process.
5. Power Supply: Provides voltage and current for the electrodes.
6. Miscellaneous Components: Jumper wires, breadboard, resistors, and capacitors for circuit assembly.

---

## Software Tools

- Arduino IDE: For programming and uploading code to the ESP32.
- ThingSpeak: For cloud-based data logging and visualization.
- Libraries:
  - WiFi.h for Wi-Fi connectivity.
  - HTTPClient.h for sending data to ThingSpeak.

---

## How It Works

1. Sensor Data Acquisition:
   - The pH sensor measures the water's acidity or alkalinity.
   - The TDS sensor tracks the concentration of dissolved solids.

2. Data Processing:
   - The ESP32 reads the sensor values via its ADC pins and processes the data.

3. Cloud Integration:
   - The processed data is transmitted to ThingSpeak using the ESP32's Wi-Fi module.
   - ThingSpeak visualizes the data in real-time, displaying pH and TDS levels as graphs.

4. Electrocoagulation Process:
   - Electrical currents are passed through the water using aluminum electrodes, coagulating and removing impurities.

---

## Setup Instructions

### Hardware Setup
1. Connect the pH sensor to the ESP32:
   - Signal → GPIO 32
   - VCC → 3.3V
   - GND → GND
2. Connect the TDS sensor to the ESP32:
   - Signal → GPIO 36
   - VCC → 3.3V or 5V
   - GND → GND
3. Connect the electrodes to the power supply and position them in the water container.
4. Ensure all components are securely connected using jumper wires and a breadboard.

### Software Setup
1. Install the required libraries in the Arduino IDE:
   - WiFi.h
   - HTTPClient.h
2. Configure the Wi-Fi credentials and ThingSpeak API key in the code.
3. Upload the code to the ESP32 using the Arduino IDE.
4. Monitor the real-time data on the ThingSpeak dashboard.

---

## Applications

- Industrial Effluent Treatment: Removes pollutants from wastewater in industries.
- Environmental Management: Cleans polluted water bodies.
- Agricultural Water Recycling: Purifies water for reuse in irrigation.

---

## Future Enhancements

- Integrate additional sensors (e.g., heavy metal detectors) for comprehensive water quality analysis.
- Develop a mobile application for better accessibility and control.
- Enhance the scalability of the system for large-scale applications.

---

## Acknowledgments

This project was developed as part of the HackeZee'24 Hardware Contest, hosted by JoEL @ ECE in collaboration with MathWorks. Special thanks to:
- Dr. Shikha Tripathi, Professor & Chairperson, Dept. of ECE, PES University.
- Prof. M Rajasekar, Associate Professor, Dept. of ECE, PES University.
- Sponsors: MathWorks, Synaptics, and CrazyPi.

---

## Contributors

- [Poorab Mahesh]
- [Rahul Pradeep Palasamudram]
- [Pramiti Raghuvir]
