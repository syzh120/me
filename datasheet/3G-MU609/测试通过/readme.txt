1.���ݹٷ��ĵ�����Ϊģ��Linux�ں���������ָ��.pdf������������ã����±����ںˡ�
2.��usb/ppp�ļ��п���������/etc/Ŀ¼�¡�
3.��usb/usr_sbin�ļ����µ�������ִ�г��򿽱�������/usr/sbin/Ŀ¼�¡�
4.��usb/home_root�ļ����µĽű�����������/home/rootĿ¼��.
5.�ڰ��ӵ�/home/root/runall.sh�ű�ĩβ�����һ�У�/home/root/pppd.sh &
�ڰ��ӵ�/etc/resolv.conf�ļ�����ӣ�nameserver 114.114.114.114
ע�����ͨ��U�̿������ɽ�usb-D500/usb-feiling�ļ����������ļ�������U�̣�ֱ��ִ��copy.sh�ű�,��ʡ��2-5����



һ.pppd��
1.���ص�ַ��http://www.linuxfromscratch.org/blfs/view/6.3/basicnet/ppp.html
2.��ѹ��                        ppp-2.4.4.tar.gz
3.ִ�нű�����Makefile���ļ���./configure
��Ϊandroidϵͳ������Ҫ�ı���뷽ʽ����Ҫ��̬���룻����Ϊ android c��ʹ�õ���Bionic�⣬����GNU C�⣬ucLibc�����κ���֪��Linux C�������,���Ա���ʱ��Ҫ��̬���룩
chat:   chat.o
                $(CC) -o chat chat.o  -static
        chat.o: chat.c
                $(CC) -c $(CFLAGS) -o chat.o chat.c  -static
4.�ÿ�����Ľ�����빤��������: make CC=arm-arago-linux-gnueabi-gcc
5.��ppp-2.4.4/chat/chat      ppp-2.4.4/pppd/pppd  ���Ƶ��������ļ�ϵͳ/usr/sbin
6.���������ļ�ϵͳ/var/ �½���runĿ¼(�����Ƿ���Ҫ������)

��.��д�ű�
1.chat��peers����Ŀ¼û�У���Ҫ�Լ�mkdir��
2.��д�ű���/etc/ppp/chat/unicom���������£�
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

3.��д�ű���/etc/ppp/peers/unicom,��������:
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
persist  (�������ӣ��Զ��ز�)
modem(ʹpppʹ��DCD�ź����ж��Ƿ��������������޵�������)
idle������һ��ʱ�����ƣ�����300s��ʱ���������ݴ��ͣ��ͶϿ����ӣ�
demond��ʹpppͣ���ں�̨�������������ݣ�һ����Ҫ�������������������ʱ��ͶϿ�������Ȼͣ���ں�̨�ȴ��´����ݴ��ͣ�


��.���ýű���ʼ����
1.�������pppd call unicom & 


cd /dev/
cat ttyUSB0 &
echo AT+CGMI > ttyUSB0
echo AT+CGMM > ttyUSB0
echo AT+CSQ > ttyUSB0

��.���⣺
1.pppd call unicom & ��������⣺Serial connection established.
Couldn't set tty to PPP discipline: Invalid argument
�����ں˽�ppp�����(Device Drivers->Network device support��)ȫ��ѡ�ϣ����ɡ�

2.�ں�ʹ��sdc1/TI/kernel20141028/ti-a8-linux-04.06.00.07/
�ں����ã�make menuconfig ARCH=arm
�ں˱��룺./mk k(����) ./mk c��make clean��

3.��˵�ǻ���Ҫ�����ļ�����Ҫ�п�ʱ�����Ƿ���Ҫ
1./etc/ppp/chap-secrets /etc/ppp/pap-secrets ����Ϊ��
card * card *
2./etc/ppp/resolv.conf����
nameserver 123.123.123.123
nameserver 123.123.123.124
