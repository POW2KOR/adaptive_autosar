#!/bin/bash

echo "Post install script: copying the service files..."
sudo cp /usr/share/minerva/*.service /lib/systemd/system

echo "Post install script: enable and start the adaptive stack and ipv6 loopback..."
# enable the services, so that it will automatically start on boot
sudo systemctl enable enable-ipv6-loopback
sudo systemctl enable adaptive-stack
# start the services
sudo systemctl start enable-ipv6-loopback
sudo systemctl start adaptive-stack

echo "Post install script: done!"
