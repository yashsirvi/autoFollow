#!/bin/sh
sudo apt-get update
sudo apt-get install network-manager
nmcli r wifi on
nmcli d wifi list
echo "nmcli r wifi on;sudo nmcli d wifi connect CAMPUS_SECURED" >> ~/.bashrc