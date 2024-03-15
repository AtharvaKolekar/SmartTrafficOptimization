# Preemptive Scheduling of Emergency Vehicles for Road Safety

This project aims to enhance road safety by preemptively scheduling traffic signals to clear the path for emergency vehicles. It utilizes OpenCV technology for real-time video analysis to detect the presence of emergency vehicles in camera footage. Additionally, GPS technology is used to track the real-time location of emergency vehicles, allowing for automatic switching of traffic signals along their route, thereby minimizing response time.
## Simulation
To visualize the functionality of the project, we have created a simulation. You can access the simulation 
## Simulation
To visualize the functionality of the project, we have created a simulation. 

[![View Simulation](https://img.shields.io/badge/View%20Simulation-Click%20Here-blue)]((https://atharvakolekar.github.io/SmartTrafficOptimization/simulation/)]

## Steps for ESP32 Code

1. **Setup ESP32**: Make sure you have set up your ESP32 development environment.
2. **Upload Code**: Upload the provided ESP32 code to your ESP32 board.
3. **Connect to Network**: Ensure that your ESP32 is connected to the network where the camera feed is accessible.

## OpenCV Model - YOLO
We have utilized the YOLO (You Only Look Once) model for object detection in the OpenCV framework. Below are the steps for utilizing the YOLO model:

1. **Installation**: Install OpenCV library on your system.
2. **Model Weights and Configurations**: Download the pre-trained YOLO weights and configurations from the official source.
3. **Object Detection**: Implement YOLO for object detection in real-time camera feed.
4. **Thresholding**: Set appropriate confidence thresholds for detecting emergency vehicles.
5. **Integration**: Integrate the YOLO model with the rest of the project for real-time analysis of camera footage.

<img width="310" alt="image" src="https://github.com/AtharvaKolekar/SmartTrafficOptimization/assets/121168949/c7a726db-768d-4e60-9e15-a6ef04b52950">

## Android Code (Kotlin)

The Android application is developed in Kotlin and serves as an interface for monitoring the status of emergency vehicles and receiving alerts. Below are the steps for using the Android code:

1. **Setup Android Studio**: Ensure that you have Android Studio installed.
2. **Clone Repository**: Clone the repository containing the Android code.
3. **Open Project**: Open the project in Android Studio.
4. **Build and Run**: Build the project and run it on an Android device or emulator.
5. **Interface**: Navigate through the interface to monitor emergency vehicle locations and receive alerts.

