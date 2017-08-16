#!/bin/sh
cp /mnt/ppp /etc/ -r
cp /mnt/usr_sbin/* /usr/sbin/
cp /mnt/home_root/pppd.sh /home/root/
echo "nameserver 114.114.114.114" >> /etc/resolv.conf
echo "/home/root/pppd.sh &" >> /home/root/runall.sh

