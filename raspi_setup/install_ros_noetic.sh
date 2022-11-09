#!/bin/sh
sudo apt-get update
sudu apt-get upgrade
sudo sh -c 'echo "deb http://packages.ros.org/ros/ubuntu $(lsb_release -sc) main" > /etc/apt/sources.list.d/ros-latest.list'
sudo apt install curl
curl -s https://raw.githubusercontent.com/ros/rosdistro/master/ros.asc | sudo apt-key add -
sudo apt update
sudo apt-get install build-essential cmake
sudo apt install ros-noetic-ros-base
sudo apt install python3-rosdep python3-rosinstall python3-rosinstall-generator python3-wstool build-essential
sudo apt install python3-roslaunch
source /opt/ros/noetic/setup.bash
echo "source /opt/ros/noetic/setup.bash" >> ~/.bashrc
source ~/.bashrc
sudo groupadd -f --system gpio
sudo groupadd -f --system i2c
sudo usermod -a -G gpio ubuntu
sudo usermod -a -G i2c ubuntu
