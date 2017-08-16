#!/bin/sh

killall pppd.sh
killall pppd
ifconfig ppp0 down
ifconfig eth0 down
sleep 10

ifconfig eth1 down
ifconfig eth1 192.168.1.211 netmask 255.255.255.0
route add default gw 192.168.1.1 dev eth1
ifconfig eth1 up


