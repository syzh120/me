#!/bin/sh

ifconfig eth0 down
ifconfig eth1 down

dns1="8.8.8.8"
dns2="114.114.114.114"
count=3
echo "nameserver 114.114.114.114" > /etc/resolv.conf
sleep 5
pppd call wcdma & 
sleep 10
while true
do 
	count=3
	while [ 0 -lt $count ]
	do
		ping -s 1 -c 1 $dns1
		if [ "$?" != "0" ]
		then
			ping -s 1 -c 2 $dns2
			if [ "$?" != "0" ]
			then
				killall pppd
				pppd call wcdma &
				sleep 10
			fi
		fi
		count=$(($count - 1))
	done
	sleep 3600
done
