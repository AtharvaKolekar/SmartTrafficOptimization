# Preemptive Scheduling of Emergency Vehicles for Road Safety

This project aims to enhance road safety by preemptively scheduling traffic signals to clear the path for emergency vehicles. It utilizes OpenCV technology for real-time video analysis to detect the presence of emergency vehicles in camera footage. Additionally, GPS technology is used to track the real-time location of emergency vehicles, allowing for automatic switching of traffic signals along their route, thereby minimizing response time.
## Simulation
To visualize the functionality of the project, we have created a simulation. You can access the simulation [here](https://atharvakolekar.github.io/SmartTrafficOptimization/simulation/).
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

![ambulance](https://github.com/AtharvaKolekar/SmartTrafficOptimization/assets/121168949/617a3311-aaaf-459c-8660-fbf9a9b3943f)

