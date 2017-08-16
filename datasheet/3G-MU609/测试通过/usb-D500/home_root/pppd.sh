#!/bin/sh

dns1="8.8.8.8"
dns2="114.114.114.114"
count=3
echo "nameserver 114.114.114.114" > /etc/resolv.conf
#等待系统运行
sleep 5  
#开始拨号
/usr/sbin/pppd call unicom & 
#等待拨号成功
sleep 10

#掉线自动重拨，每次掉线后拨号count次，如果不成功则等待一个设定的时间
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
				pppd call unicom &
				sleep 10
			fi
		fi
		count=$(($count - 1))
	done
	#如果三次拨号都不成功，则等待一定时间
	sleep 3600
done
