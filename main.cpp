/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- main.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <linux/input.h>
#include <linux/ioctl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <signal.h>
#include <pthread.h>
#include <dlfcn.h>
#include <termios.h> 

#include "AmrDisplay.h"


AmrDisplay *p_AmrDisplay = NULL;

void *handle = NULL;
iconv_t iconv_fd = 0;
Iconv m_Iconv = NULL;
int UartFd = 0;

int speed_arr[] = {
			B115200, B38400, B19200, B9600, B4800, 
			B2400, B1200, B300, 
};  

int name_arr[]  = {
			115200,  38400,  19200,   9600,  
			4800,  2400,  1200,  300, 
};  

void SetSpeed(int fd, int speed)  
{  
    int   i;  
    int   status;  
    struct termios   Opt;  
    tcgetattr(fd, &Opt);  
    for ( i= 0;  i < sizeof(speed_arr)/sizeof(speed_arr[0]);  i++)  
    {  
        if  (speed == name_arr[i])  
        {  
            tcflush(fd, TCIOFLUSH);  
            cfsetispeed(&Opt, speed_arr[i]);  
            cfsetospeed(&Opt, speed_arr[i]);  
            status = tcsetattr(fd, TCSANOW, &Opt);  
            if (status != 0)  
            {  
                perror("tcsetattr fd1");  
                return;  
            }  
        }  
        tcflush(fd,TCIOFLUSH);  
    }  
}  
  
int SetParity(int fd,int databits,int stopbits,int parity)  
{  
    struct termios options;
	
    if (tcgetattr(fd, &options) != 0)  
    {  
        perror("SetupSerial 1");  
        return false;  
    }  
    options.c_cflag &= ~CSIZE;
    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);  
    switch (databits)
    {  
        case 7:  
            options.c_cflag |= CS7;  
            break;  
        case 8:  
            options.c_cflag |= CS8;  
            break;  
        default:  
            fprintf(stderr, "Unsupported data size\n");  
            return false;  
    }  
    switch (parity)  
    {  
        case 'n':  
        case 'N':  
            options.c_cflag &= ~PARENB;   /* Clear parity enable */  
            options.c_iflag &= ~INPCK;     /* Enable parity checking */  
            break;  
        case 'o':  
        case 'O':  
            options.c_cflag |= (PARODD | PARENB);  /* 设置为奇效验*/   
            options.c_iflag |= INPCK;             /* Disnable parity checking */  
            break;  
        case 'e':  
        case 'E':  
            options.c_cflag |= PARENB;     /* Enable parity */  
            options.c_cflag &= ~PARODD;   /* 转换为偶效验*/    
            options.c_iflag |= INPCK;       /* Disnable parity checking */  
            break;  
        case 'S':  
        case 's':  /*as no parity*/  
            options.c_cflag &= ~PARENB;  
            options.c_cflag &= ~CSTOPB;  
            break;  
        default:  
            fprintf(stderr,"Unsupported parity\n");  
            return false;  
    }  

    switch (stopbits)  
    {  
        case 1:  
            options.c_cflag &= ~CSTOPB;  
            break;  
        case 2:  
            options.c_cflag |= CSTOPB;  
            break;  
        default:  
            fprintf(stderr,"Unsupported stop bits\n");  
            return false;  
    }  
    /* Set input parity option */  
    if (parity != 'n')  
        options.c_iflag |= INPCK;  
    options.c_cc[VTIME] = 150; // 15 seconds   
    options.c_cc[VMIN] = 0;  
  
    tcflush(fd,TCIFLUSH); /* Update the options and do it NOW */  
    if (tcsetattr(fd,TCSANOW,&options) != 0)  
    {  
        perror("SetupSerial 3");  
        return false;  
    }  
    return true;  
 }  


/*---------------------------------------------------------------------------*/
/*	Timer�̴߳�����
**		�߳�ģ��һ����ʱ����������UI��̬����
*/
void *AmrTimer(void *args)
{
	while (1)
	{
		if (p_AmrDisplay)
		{
			/* 	����豸����WAIT_TO_IDLE_TIME��ô��ʱ�����˲�������ظ�����ӭ
			*	����
			*/
			if (p_AmrDisplay->IdleCounter > WAIT_TO_IDLE_TIME)
			{
				p_AmrDisplay->IdleCounter = 0;
				p_AmrDisplay->DsiplaySetWelcome();
			}

			/* 	���õ�ǰ�����DoTimer,������ǰҳ���������� */
			p_AmrDisplay->CurDlg->DoTimer();

			if (exc_mode == p_AmrDisplay->GetMode())
			{
				if (p_AmrDisplay->ExcDataCapCount%30 == 0)
				{
					/* 	�ڽ���ģʽ�£�ÿ��30��Timer�������ϱ�һ������
					**	������ĿǰΪ�������	
					*/
					memset(&p_AmrDisplay->gExcDate, 0x00, sizeof(struct data_frame));
					p_AmrDisplay->GetExcData(&p_AmrDisplay->gExcDate);
					p_AmrDisplay->GetExcDataTime();
					p_AmrDisplay->ReportExcDate();
				}
				p_AmrDisplay->ExcDataCapCount++;
			}
			else if (amr_mode == p_AmrDisplay->GetMode())
			{
				if (p_AmrDisplay->AmrDataCapCount%10 == 0)
				{
					/* 	�ڼ�����ģʽ�£�ÿ��10��Timer�������ϱ�һ������
					**	������ĿǰΪ�������	
					*/
					p_AmrDisplay->ReportAmrDate();
				}

				p_AmrDisplay->AmrDataCapCount++;
			}

			/* ���м���������а����������ñ��������� */
			p_AmrDisplay->IdleCounter++;
			
		}
		usleep(100000);
	}
}


/*---------------------------------------------------------------------------*/
/* 	���������
** 	ֱ�����иó���Ĭ�Ͻ��뼯�п�����ģʽ��ͨ��������ʹ����뽻��ģʽ��
**	eg:
**		./power					���뼯�п�����ģʽ
**		./power exc				���뽻��ģʽ
*/
int main(int argc, char *argv[])
{
	pthread_t pid;
	unsigned int gpodisp_fd = 0;


	/* ��EMI��ʾ���豸���ó�����ҪEMI��������֧�� */
	gpodisp_fd = open("/dev/amrdisp", O_RDWR);
	if (gpodisp_fd < 0)
	{
		fprintf(stderr, "open /dev/amrdisp failed \n");
		return -1;
	}

	/* ������������Ĭ�����ı���ر� */
	if (ioctl(gpodisp_fd, AMRDISPLAY_BACKLIGHT, NULL) < 0)
	{
		fprintf(stderr, "ioctl gpodisp_fd AMRDISPLAY_BACKLIGHT failed\n");
		return -1;
	}

	/* �򿪴����豸 */
	UartFd = open(UART_DEV_NAME, O_RDWR|O_NOCTTY|O_NDELAY); 
	if (UartFd < 0)
	{
		fprintf(stderr, "open ttyS0 failed!\n");
		return -1;
	}
	/* ���ò�����Ϊ9600��8N1ģʽ */
	SetSpeed(UartFd, 9600);
	if (SetParity(UartFd, 8, 1, 'N') == false)
	{
		fprintf(stderr, "SetParity failed!\n");
		return -1;
	}	

	/* ��preloadable_libiconv��̬�⣬�����ֿ�ת����ʱ����Ҫ�õ�
	** �ÿ��iconv��صļ�����������Ϊ���õ��ÿ�������������Ҹÿ�
	** �к�����C�⺯���г�ͻ���ʲ�����ֱ�����Ӹÿ⣬�����ö�̬����
	*/
	handle = dlopen("/lib/preloadable_libiconv.so", RTLD_NOW);
	if (NULL == handle)
	{
		fprintf(stderr, "dlopen /lib/preloadable_libiconv.so failed\n");
		return -1;
	}
	IconvOpen m_IconvOpen = (IconvOpen)dlsym(handle, "iconv_open");
	m_Iconv = (Iconv)dlsym(handle, "iconv");
	if (NULL == m_IconvOpen || NULL == m_Iconv)
	{
		fprintf(stderr, "dlsym iconv_open && m_Iconv failed\n");
		return -1;
	}
	iconv_fd = m_IconvOpen("GBK","UTF-8");
	if (0 == iconv_fd)
	{
		fprintf(stderr, "m_IconvOpen GBK UTF-8 failed\n");
		return -1;
	}

	/* ��������Timer���̣߳����߳���Ҫ�����������еĶ�̬���� 
	** �����������е�����
	*/
	pthread_create(&pid, NULL, AmrTimer, NULL);


	/* AmrDisplay��: �������������п������ͽ����һ���� 
	** 				 ������ʵ����,��ز����Լ�UI����
	**				 
	*/
	AmrDisplay m_AmrDisplay(gpodisp_fd);

	/* ȫ��ָ�룬������Timer�߳��з���m_AmrDisplay */
	p_AmrDisplay = &m_AmrDisplay;	

	if (argc == 2) 
	{
		if (!strncmp("exc", argv[1], 3))
		{
			/* �����������ָ������ģʽ, ������Ϊ����ģʽ */
			p_AmrDisplay->SetExcMode();
		}
	}

	/* ������UI�������� */
	p_AmrDisplay->DisplayRun();


	if (NULL != handle)
		dlclose(handle);
	iconv_close(iconv_fd);
		
	return 0;
}


