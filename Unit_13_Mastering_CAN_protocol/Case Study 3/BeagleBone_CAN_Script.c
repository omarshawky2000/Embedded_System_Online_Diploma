// $ ifconfig -a    (shows all the available communication ports both enabled and disabled)
// $ dmsg			  (show messages of the linux during booting)
// We set the bitrate of the CAN before enabling it in the linux 
// $ ip link set can0 up type can bitrate 1000000 	(set the bitrate for can0)
// $ ifconfig can0 up	(enable the can module on linux)
// $ dmsg |grep can0	(Check can related messages)
// $ config-pin p9.19 can 		(configure the pin as cantx or rx depending on the pinout)
// $ config-pin p9.20 can 		(configure the pin as cantx or rx depending on the pinout)
// $ cansend can0 5A1#00.01.02.03.04 (sending a can messaage through the can utillities *must be installed* 5A1 is the id  and the payload is 00.01.02.03.04 )
// $ candump can0				(can recieve through the installed can utillities NOTE: will recieve all frames with no filters)

//Application for socket programming:
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

int s , i ;
int nbytes; 
struct sockaddr_can addr;
struct ifreq ifr;
struct can_frame frame, TXframe;
struct can_filter rfilter[1];
unsigned char speed = 0 ;

int CAN_Socket_init()
{
	if ((s = socket (PF_CAN , SOCK_RAW , CAN_RAW)) <0)
	{
		printf("Socket");
		return 1;
	}
	strcpy( ifr.ifr_name , "can0" );
	ioctl( s , SIOCGIFINDEX,&ifr );
	memset(&addr , 0 , sizeof(addr));
	addr.can_family = AF_CAN;
	addr.can_ifindex = ifr.ifr_ifindex;

	if(bund(s,(struct sockaddr *)&addr , sizeof(addr))<0)
	{
		printf("Bind");
		return 1;
	}
	return 0;
}

void Set_Filter_RXinit(unsigned short ID , unsigned short Mask)
{
	rfilter[0].can_id = ID; 
	rfilter[0].can_mask = Mask;

	setsockopt(s , SOL_CAN_RAW , CAN_RAW_FILTER , &rfilter , sizeof(rfilter));
}

int int main(int argc, char **argv)
{
	unsigned char ACC ; 
	printf( " CAN Socket (Lean-in-depth) CAN CaseStudy 3 (ECU2) \r\n");

	if (CAN_Socket_init() != 0)  return 1;

	Set_Filter_RXinit(0x030 , 0x7ff);

	TXframe.can_id = 0x3A8;
	TXframe.can_dlc = 1;

	while(1)
	{
		nbytes = read(s, &frame , sizeof(can_frame));

		if(nbytes< 0 )
		{
			printf("Read");
			return 1;
		}

		printf("ox%03X [%d] ",frame.can_id , frame.can_dlc);

		for (i = 0 ; i< frame.can_dlc ; i++) printf("%02X " , frame.data[i]);

		printf("\r\n");

		ACC = frame.data[0];

		for (int i = 0 ; i < 10 ; i++)
		{
			if(ACC==1)
			{
				if(speed = 0xFF)
				{
					TXframe.data[0] = speed;
				}
				else
				{
					TXframe.data[0] = ++speed;
				}
			}
			else
			{
				if (speed == 0 )
				{
					TXframe.data[0] = speed;
				}
				else
				{
					TXframe.data[0] = --speed;
				}
			}

			if(write(s , &TXframe , sizeof(struct can_frame)) != sizeof(struct can_frame))
			{
				printf("Write");
				return 1;
			}

			printf("Send CAN Frame Speed = %d \r\n" , speed);

			sleep(0.1);
		}
	}
	return 0;
}