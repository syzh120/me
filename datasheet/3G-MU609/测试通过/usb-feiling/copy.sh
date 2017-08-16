#!/bin/sh

cp autonet.rules /etc/udev/rules.d/
cp interfaces /etc/network/
cp pppd.sh /home/root/
cp runme.sh /home/root/
cp connect_eth1.sh /home/root/
cp wcdma /etc/ppp/peers/

ln -sf /home/root/runme.sh /etc/rc5.d/S999runme.sh


