1.根据官方文档《华为模块Linux内核驱动集成指导.pdf》进行相关配置，重新编译内核。
2.将usb/ppp文件夹拷贝到板子/etc/目录下。
3.将usb/usr_sbin文件夹下的两个可执行程序拷贝到板子/usr/sbin/目录下。
4.将usb/home_root文件夹下的脚本拷贝到板子/home/root目录下.
5.在板子的/home/root/runall.sh脚本末尾中添加一行：/home/root/pppd.sh &
在板子的/etc/resolv.conf文件中添加：nameserver 114.114.114.114
注：如果通过U盘拷贝，可将usb-D500/usb-feiling文件夹下所有文件拷贝到U盘，直接执行copy.sh脚本,可省略2-5步。



一.pppd：
1.下载地址：http://www.linuxfromscratch.org/blfs/view/6.3/basicnet/ppp.html
2.解压：                        ppp-2.4.4.tar.gz
3.执行脚本产生Makefile等文件：./configure
若为android系统，则需要改变编译方式，需要静态编译；（因为 android c库使用的是Bionic库，不与GNU C库，ucLibc，或任何已知的Linux C库相兼容,所以编译时需要静态编译）
chat:   chat.o
                $(CC) -o chat chat.o  -static
        chat.o: chat.c
                $(CC) -c $(CFLAGS) -o chat.o chat.c  -static
4.用开发板的交叉编译工具链编译: make CC=arm-arago-linux-gnueabi-gcc
5.将ppp-2.4.4/chat/chat      ppp-2.4.4/pppd/pppd  复制到开发板文件系统/usr/sbin
6.到开发板文件系统/var/ 下建立run目录(测试是否需要？？？)

二.编写脚本
1.chat和peers两个目录没有，需要自己mkdir。
2.编写脚本：/etc/ppp/chat/unicom，内容如下：
ABORT "NO CARRIER"

ABORT "NO DIALTONE"

ABORT "ERROR"

ABORT "NO ANSWER"

ABORT "BUSY"

TIMEOUT 120

"" at

OK AT+CGDCONT=1,"IP","3gnet"

OK atdt*99#

CONNECT

3.编写脚本：/etc/ppp/peers/unicom,内容如下:
/dev/ttyUSB0
115200
crtscts
connect '/usr/sbin/chat -v -f /etc/ppp/chat/unicom'
debug
nodetach
ipcp-accept-local
ipcp-accept-remote
defaultroute
usepeerdns
user card
password card
persist  (永久连接，自动重拨)
modem(使ppp使用DCD信号来判断是否连接正常，有无掉线现象)
idle（设置一个时间限制，当在300s的时间内无数据传送，就断开链接）
demond（使ppp停留在后台，监视网络数据，一旦有要求就立即进行联网，超时后就断开，但仍然停留在后台等待下次数据传送）


三.调用脚本开始拨号
1.输入命令：pppd call unicom & 


cd /dev/
cat ttyUSB0 &
echo AT+CGMI > ttyUSB0
echo AT+CGMM > ttyUSB0
echo AT+CSQ > ttyUSB0

四.问题：
1.pppd call unicom & 后出现问题：Serial connection established.
Couldn't set tty to PPP discipline: Invalid argument
配置内核将ppp相关项(Device Drivers->Network device support下)全部选上，即可。

2.内核使用sdc1/TI/kernel20141028/ti-a8-linux-04.06.00.07/
内核配置：make menuconfig ARCH=arm
内核编译：./mk k(编译) ./mk c（make clean）

3.又说是还需要两个文件，需要有卡时测试是否需要
1./etc/ppp/chap-secrets /etc/ppp/pap-secrets 内容为：
card * card *
2./etc/ppp/resolv.conf内容
nameserver 123.123.123.123
nameserver 123.123.123.124
