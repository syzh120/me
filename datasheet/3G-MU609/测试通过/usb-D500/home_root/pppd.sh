#!/bin/sh

dns1="8.8.8.8"
dns2="114.114.114.114"
count=3
echo "nameserver 114.114.114.114" > /etc/resolv.conf
#�ȴ�ϵͳ����
sleep 5  
#��ʼ����
/usr/sbin/pppd call unicom & 
#�ȴ����ųɹ�
sleep 10

#�����Զ��ز���ÿ�ε��ߺ󲦺�count�Σ�������ɹ���ȴ�һ���趨��ʱ��
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
	#������β��Ŷ����ɹ�����ȴ�һ��ʱ��
	sleep 3600
done
