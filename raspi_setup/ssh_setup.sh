#!/bin/sh
sudo apt install openssh-client
sudo apt install openssh-server
sudo apt-get install net-tools
sudo systemctl enable ssh
sudo ufw allow ssh
sudo systemctl start ssh
sudo systemctl status ssh
ifconfig
echo "sudo systemctl enable ssh;sudo ufw allow ssh;sudo systemctl start ssh" >> ~/.bashrc
