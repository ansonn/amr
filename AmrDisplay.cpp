/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDisplay.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include <iostream>
#include <dlfcn.h>
#include <linux/input.h>
#include "AmrDisplay.h"

extern int UartFd;
extern iconv_t iconv_fd;
extern Iconv m_Iconv;

/* ½öÖ§³ÖÒ»ÖÖ¹¹Ôìº¯Êý */
AmrDisplay::AmrDisplay(unsigned int fd):
							  m_DlgWelcome(*this, fd)
							, m_AmrDlgMain(*this, fd)
							, m_AmrDlgDevInfo(*this, fd)
							, m_AmrDlgDate(*this, fd)
							, m_AmrDlgLedCtrl(*this, fd)
							, m_AmrDlgSysSetting(*this, fd)
							, m_AmrDlgUartCtrl(*this, fd)
							, m_ExcDlgWelcome(*this, fd)
							, m_ExcDlgMain(*this, fd)
							, m_ExcDlgPowerHave(*this, fd)
							, m_ExcDlgPowerNo(*this, fd)
							, m_ExcDlgPowerTotal(*this, fd)
							, m_ExcDlgTelemetry(*this, fd)
							, IdleCounter(0)
							, ExcDataCapCount(0)
							, power_count(0.0)
							, rower_count(0.0)
							, PI(3.1415926)
							, AmrTick(0)
							, voltage(220)
							, current(1)
							, disp_fd(fd)
{

	memset(ipaddr, 0x00, sizeof(ipaddr));

	/* Ä¬ÈÏÎª¼¯ÖÐ¿ØÖÆÆ÷Ä£Ê½ */
	m_Mode = amr_mode;
	CurDlg = &m_DlgWelcome;

	AmrData[0] = random()%100000;
	AmrData[1] = random()%100000;
	AmrData[2] = random()%100000;
	AmrData[3] = random()%100000;


}

AmrDisplay::~AmrDisplay()
{

}

int AmrDisplay::str_align(char *buf, int length)
{
	char *p = (char*)malloc(length+3);
	int count;
	int i;

	strcpy(p, buf);
	count = strlen(buf);
	if(length <= count){
		return 0;
	}else{
		for( i = 0; i < length - count; i ++ ){
			buf[i] = ' ';	
		}
		strcpy(&buf[i], p);
	}
	free(p);		

	return 0;
}

/*---------------------------------------------------------------------------*/
/*	ÑÝÊ¾°æ±¾ÖÐ£¬»ñÈ¡dummyµÄËæ»úÊý¾Ý
*/
int AmrDisplay::GetExcData(struct data_frame *cur)
{
		struct timeval tpstart;
		int sign;
		double PI = (3.1415926);

		/****************************** point a *************************/
		float cur_volt, cur_curr, cur_degree, cur_power, cur_rower;

		cur->a.type = 0;


		gettimeofday(&tpstart,NULL);
		//srandom((int)time(NULL) * (int)time(NULL));
		srandom(tpstart.tv_usec);

		sign = random()%2?-1:1;

		cur_volt = (float)(voltage * (100 + sign * (random()%VOLT_FLUCT)))/100 + (float)((random()%100)/100) ;
		sprintf(cur->a.volt, "%3.1f", cur_volt);
		str_align(cur->a.volt, 4 + 1);

		sign = random()%2?-1:1;
		cur_curr = (float)(current * (100 +  sign * (random()%CURR_FLUCT)))/100 + (float)((random()%1000)/1000);
		sprintf(cur->a.curr, "%1.3f", cur_curr);
		str_align(cur->a.curr, 4 + 1);

		cur_degree = (float)(random()%15);
		sprintf(cur->a.degree, "%2.1f", cur_degree);
		str_align(cur->a.degree, 3 + 1);

		cur_power = (float)(cur_volt * cur_curr * (float)cos(cur_degree*PI/180))/1000;
		sprintf(cur->a.power, "%2.4f", cur_power);
		str_align(cur->a.power, 6 + 1);

		cur_rower = (float)(cur_volt * cur_curr * (float)sin(cur_degree*PI/180))/1000;
		sprintf(cur->a.rower, "%2.4f", cur_rower);
		str_align(cur->a.rower, 6 + 1);

		
		/****************************** point b *************************/
		float cur1_volt, cur1_curr, cur1_degree, cur1_power, cur1_rower;

		cur->b.type = 1;

		gettimeofday(&tpstart,NULL);
		//srandom((int)time(NULL) * (int)time(NULL));
		srandom(tpstart.tv_usec);

		sign = random()%2?-1:1;
		cur1_volt = (float)(voltage * (100 + sign * (random()%VOLT_FLUCT)))/100 + (float)((random()%100)/100) ;
		sprintf(cur->b.volt, "%3.1f", cur1_volt);
		str_align(cur->b.volt, 4 + 1);

		sign = random()%2?-1:1;
		cur1_curr = (float)(current * (100 + sign * (random()%CURR_FLUCT)))/100 + (float)((random()%1000)/1000);
		sprintf(cur->b.curr, "%1.3f", cur1_curr);
		str_align(cur->b.curr, 4 + 1);

		cur1_degree = (float)(random()%15);
		sprintf(cur->b.degree, "%2.1f", cur1_degree);
		str_align(cur->b.degree, 3 + 1);

		cur1_power = (float)(cur1_volt * cur1_curr * (float)cos(cur1_degree*PI/180))/1000;
		sprintf(cur->b.power, "%2.4f", cur1_power);
		str_align(cur->b.power, 6 + 1);

		cur1_rower = (float)(cur1_volt * cur1_curr * (float)sin(cur1_degree*PI/180))/1000;
		sprintf(cur->b.rower, "%2.4f", cur1_rower);
		str_align(cur->b.rower, 6 + 1);


		/****************************** point c *************************/
		float cur2_volt, cur2_curr, cur2_degree, cur2_power, cur2_rower;

		cur->c.type = 2;

		gettimeofday(&tpstart,NULL);
		//srandom((int)time(NULL) * (int)time(NULL));
		srandom(tpstart.tv_usec);

		sign = random()%2?-1:1;
		cur2_volt = (float)(voltage * (100 + sign * (random()%VOLT_FLUCT)))/100 + (float)((random()%100)/100) ;
		sprintf(cur->c.volt, "%3.1f", cur2_volt);
		str_align(cur->c.volt, 4 + 1);

		sign = random()%2?-1:1;
		cur2_curr = (float)(current * (100 + sign * (random()%CURR_FLUCT)))/100 + (float)((random()%1000)/1000);
		sprintf(cur->c.curr, "%1.3f", cur2_curr);
		str_align(cur->c.curr, 4 + 1);

		cur2_degree = (float)(random()%15);
		sprintf(cur->c.degree, "%2.1f", cur2_degree);
		str_align(cur->c.degree, 3 + 1);

		cur2_power = (float)(cur2_volt * cur2_curr * (float)cos(cur2_degree*PI/180))/1000;
		sprintf(cur->c.power, "%2.4f", cur2_power);
		str_align(cur->c.power, 6 + 1);

		cur2_rower = (float)(cur2_volt * cur2_curr * (float)sin(cur2_degree*PI/180))/1000;
		sprintf(cur->c.rower, "%2.4f", cur2_rower);
		str_align(cur->c.rower, 6 + 1);


		/*  active power and reactive power */
		float cur_active_power, cur_reactive_power;

		cur_active_power = cur_power + cur1_power + cur2_power;
		sprintf(cur->active_power, "%2.4f", cur_active_power);
		str_align(cur->active_power, 6 + 1);

		cur_reactive_power = cur_rower + cur1_rower + cur2_rower;
		sprintf(cur->reactive_power, "%2.4f", cur_reactive_power);
		str_align(cur->reactive_power, 6 + 1);

		if((int)power_count > 1000){
			power_count = 0000.00;
			rower_count = 0000.00;
		}

		power_count += cur_active_power * 5 / 60 /60;
		rower_count += cur_reactive_power * 5 / 60 /60;
		sprintf(cur->power_count, "%4.2f", power_count);
		sprintf(cur->rower_count, "%4.2f", rower_count);
		str_align(cur->power_count, 6 + 1);
		str_align(cur->rower_count, 6 + 1);
		
		sprintf(cur->re_power_count,"%4.2f", 0.00);
		sprintf(cur->re_rower_count,"%4.2f", 0.00);
		str_align(cur->re_power_count, 6 + 1);
		str_align(cur->re_rower_count, 6 + 1);
		

		return 0;
}

int AmrDisplay::PrintExcData(struct data_frame * cur)
{

	/***************************a**************************/
	printf("A..................................\n");
	/* type: */
	printf("type is %d\n", cur->a.type);
	/* volt: */
	printf("vol is %s\n", cur->a.volt);
	/* curr: */
	printf("cur is %s\n", cur->a.curr);
	/* degree */
	printf("degree is %s\n", cur->a.degree);
	/* power */
	printf("power is %s\n", cur->a.power);
	/* rower */
	printf("rower is %s\n", cur->a.rower);
	
	
	/***************************b**************************/
	printf("B..................................\n");
	/* type: */
	printf("type is %d\n", cur->b.type);
	/* volt: */
	printf("vol is %s\n", cur->b.volt);
	/* curr: */
	printf("cur is %s\n", cur->b.curr);
	/* degree */
	printf("degree is %s\n", cur->b.degree);
	/* power */
	printf("power is %s\n", cur->b.power);
	/* rower */
	printf("rower is %s\n", cur->b.rower);


	/***************************c**************************/
	printf("C..................................\n");
	/* type: */
	printf("type is %d\n", cur->c.type);
	/* volt: */
	printf("vol is %s\n", cur->c.volt);
	/* curr: */
	printf("cur is %s\n", cur->c.curr);
	/* degree */
	printf("degree is %s\n", cur->c.degree);
	/* power */
	printf("power is %s\n", cur->c.power);
	/* rower */
	printf("rower is %s\n", cur->c.rower);


	/***************************c**************************/
	printf("active power............................\n");
	printf("active power is %s\n", cur->active_power);
	printf("reactive power............................\n");
	printf("reactive power is %s\n", cur->reactive_power);
	printf("power count............................\n");
	printf("power count is %s\n", cur->power_count);
	printf("rower count............................\n");
	printf("rower count is %s\n", cur->rower_count);
	printf("reverse power count............................\n");
	printf("reverse power count is %s\n", cur->re_power_count);
	printf("reverse rower count............................\n");
	printf("reverse rower count is %s\n", cur->re_rower_count);

	return 0;
}

/*---------------------------------------------------------------------------*/
/*	´ÓÎÄ¼þÖÐµÄÄ³¸öÎ»ÖÃ¶ÁÈ¡Êý¾Ý
*/
unsigned int AmrDisplay::FileReadOffset(unsigned int hfile, unsigned long offset, 
									unsigned char * pbuffer, unsigned int size)
{
	size_t DataLength = 0 ;
	int FileMove = -1 ;

	
	if (( hfile != 0) && (pbuffer != NULL) && (size > 0))
	{
		FileMove = lseek(hfile, offset, SEEK_SET);
		if (FileMove > 0)
		{
			DataLength = read(hfile, pbuffer, size);
		}
		else
			return 0;
	}

	return (unsigned int)DataLength ;
}

/*---------------------------------------------------------------------------*/
/*	°Ñ×Ö¿âºº×Ö£¬×ª»»ÎªµãÕóÊý¾Ý
*/
unsigned int AmrDisplay::ZKDisplayConvert(char *pdata , 
							  			  unsigned char font_t , 
							  			  unsigned char *pbuffer)
{
	unsigned int t_File = NULL;
	unsigned int DataLength;
	unsigned long Offset;
	unsigned int ReadLength;
	unsigned int Index;

	size_t inlen = strlen(pdata);
	size_t outlen = inlen * 4;
	unsigned char outbuf[64] = { 0 };
	char *out = (char *)outbuf;
	
	if ((pdata == NULL) || (pbuffer == NULL))
		return 0;	

	if (font_t == ASCII12)
	{
		// 6 x 12
		t_File = open(FILE_ASCII_12_NAME, O_RDONLY);
		Offset = (pdata[0] - 0x20) * 12;
		DataLength = 12 ;
	}
	else if (font_t == ASCII16)
	{
		// 8 x16
		t_File = open(FILE_ASCII_16_NAME, O_RDONLY);
		Offset = pdata[0] * 16;
		DataLength = 16 ;
	}
 	else if (font_t == CHINESE12)
	{	m_Iconv(iconv_fd, &pdata, &inlen, &out, &outlen);
		// 12 x 12
		t_File = open(FILE_CHINESE_12_NAME, O_RDONLY);
		Offset = ((outbuf[0] - 0xA0 - 1) * 94 
						+ (outbuf[1] - 0xA0 - 1)) * 24 ;
		DataLength = 24 ;
	}
	else if (font_t == CHINESE16)
	{
		m_Iconv(iconv_fd, &pdata, &inlen, &out, &outlen);
		// 16 x 16
		t_File = open(FILE_CHINESE_16_NAME, O_RDONLY);	
		Offset = ((outbuf[0] - 0xA0 - 1 ) * 94 
						+ (outbuf[1] - 0xA0 - 1)) * 32 ;
		DataLength = 32 ;
	}
	else {
		fprintf(stderr, "ZKDisplayConvert font_t[%d] err!\n", font_t);
		return -1;
	}

	/* 	ÉÏÃæif else·ÖÖ§£»Í¨¹ýºº×ÖÊý¾Ý¸ñÊ½£¬¼ÆËã³ö¸ÃÎÄ×ÖËùÔÚ×Ö¿âÖÐµÄ
	**	Î»ÖÃ£¬ÒÔ¼°ËùÕ¼Êý¾Ý´óÐ¡£»
	**	ÏÂÃæÖ±½Ó¶ÁÖ®
	*/
	
	ReadLength = FileReadOffset(t_File, Offset, pbuffer, DataLength);
	if (ReadLength != DataLength)
	{
		ReadLength = 0 ;
	}
  	else if (DataLength == 24)
	{
		for (Index = 0; Index < 12; Index ++ )
		{
			/* 	Èç¹û¸Ãºº×Ö²»ÊÇ8×Ö½Ú¶ÔÆëµÄ£¬Ôò×öÒ»¸ö×ª»»
			**	¸Ã·ÖÖ§ÑÝÊ¾°æ±¾ÖÐÃ»ÓÐÊ¹ÓÃµ½£¬ÒòÎªÑÝÊ¾°æ±¾ÖÐºº×Ö¶¼Îª16x16
			**	eg
			**		12x12µÄºº×Ö£¬Ò»ÑùÓÐ12bit£»
			**		ÔÚ×Ö¿âÖÐ£¬12bitÐèÒªÕ¼ÓÃ2¸ö×Ö½Ú
			**		ÇÒ£¬µÚÒ»¸ö×Ö½Ú8bitÓÐÐ§£¬µÚ¶þ¸ö×Ö½Ú4bitÓÐÐ§
			**		ÎªÁË·½±ã´¦Àí£¬×ª»»Îªå£º
			**		µÚÒ»¸ö×Ö½Ú6bitÓÐÐ§£¬µÚ¶þ¸ö×Ö½Ú6bitÓÐÐ§*/
			pbuffer[Index * 2 + 1] >>= 2 ;
			pbuffer[Index * 2 + 1] |= ( pbuffer[Index * 2] << 6 ) ;
		}
	}

	close(t_File);	

	return (unsigned int)ReadLength ;
}

/*---------------------------------------------------------------------------*/
/*	»ñÈ¡ÏµÍ³IPµØÖ·£¬Ê¹ÓÃsocketÏµÍ³µ÷ÓÃ
*/
int AmrDisplay::GetLocalIp(void)
{
	if (NULL == ipaddr)
		return -1;

    int sock_get_ip;  
    struct   sockaddr_in *sin;  
    struct   ifreq ifr_ip;     
  
    if ((sock_get_ip=socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
         printf("socket create failse...GetLocalIp!\n");  
         return -1;  
    }  
     
    memset(&ifr_ip, 0, sizeof(ifr_ip));     
    strncpy(ifr_ip.ifr_name, "eth0", sizeof(ifr_ip.ifr_name) - 1);     
   
    if( ioctl( sock_get_ip, SIOCGIFADDR, &ifr_ip) < 0 )     
    {     
         return -1;     
    }       
    sin = (struct sockaddr_in *)&ifr_ip.ifr_addr;     
    strcpy(ipaddr,inet_ntoa(sin->sin_addr));         
      
    //fprintf(stderr, "local ip:%s\n",ipaddr);      
    close( sock_get_ip );  
      
    return 0;  
}

/*---------------------------------------------------------------------------*/
/*	ÉèÖÃÏµÍ³IPµØÖ·£¬Ê¹ÓÃsocketÏµÍ³µ÷ÓÃ
*/
int AmrDisplay::SetLocalIp(void)
{
    int sock_set_ip;  
      
    struct sockaddr_in sin_set_ip;  
    struct ifreq ifr_set_ip;  
  
    bzero(&ifr_set_ip,sizeof(ifr_set_ip));  
   
    if( ipaddr == NULL )  
        return -1;  
  
    if ((sock_set_ip=socket(AF_INET, SOCK_STREAM, 0)) == -1)  
    {  
         printf("socket create failse...GetLocalIp!\n");  
         return -1;  
    }  
   
    memset( &sin_set_ip, 0, sizeof(sin_set_ip));  
    strncpy(ifr_set_ip.ifr_name, "eth0", sizeof(ifr_set_ip.ifr_name)-1);     
      
    sin_set_ip.sin_family = AF_INET;  
    sin_set_ip.sin_addr.s_addr = inet_addr(ipaddr);  
    memcpy( &ifr_set_ip.ifr_addr, &sin_set_ip, sizeof(sin_set_ip));  
  
    if( ioctl( sock_set_ip, SIOCSIFADDR, &ifr_set_ip) < 0 )  
    {  
        perror( "Not setup interface\n");  
        return -1;  
    }  
  
    ifr_set_ip.ifr_flags |= IFF_UP |IFF_RUNNING;  
  
    //get the status of the device  
    if( ioctl( sock_set_ip, SIOCSIFFLAGS, &ifr_set_ip ) < 0 )  
    {  
         perror("SIOCSIFFLAGS");  
         return -1;  
    }  
  
    close(sock_set_ip);  

	return 0;
}

/*---------------------------------------------------------------------------*/
/*	ÉèÖÃÏµÍ³Ê±¼ä, fork³öÒ»¸ö½ø³Ì£¬Ö´ÐÐshell³ÌÐòÊµÏÖ£»Ð§ÂÊËäµÍ£¬µ«·½±ã
*/
int AmrDisplay::SetDateTime(void)
{
	std::string strDate(m_date);
	std::string strTime(m_time);
	std::string DateTime;

	if (fork() != 0)
		return 0;

	
	DateTime = std::string("-s ") + strDate + std::string(" ") + strTime;
												//+ std::string("\"");
	std::cout << DateTime << std::endl;

	if (execl("/bin/date", "date", DateTime.c_str(), NULL) < 0)
	{
		fprintf(stderr, "Error execl date %s", DateTime.c_str());
		return -1;
	}

	return 0;
}

int AmrDisplay::GetDateTime(void)
{
    time_t timep;  
    struct tm *p_tm;  
	
    timep = time((time_t *)NULL);  
    p_tm = gmtime(&timep);
    sprintf(m_date, "%04d-%02d-%02d", (p_tm->tm_year + 1900), 
										(p_tm->tm_mon + 1), p_tm->tm_mday);  
    sprintf(m_time, "%02d:%02d:%02d", p_tm->tm_hour, p_tm->tm_min, p_tm->tm_sec);  
}


int AmrDisplay::GetExcDataTime(void)
{
    time_t timep;  
    struct tm *p_tm;  
	
    timep = time((time_t *)NULL);  
    p_tm = gmtime(&timep);
    sprintf(m_ExcCapTime, "%02d\\%02d-%02d:%02d:%02d",
								p_tm->tm_mon,
								p_tm->tm_mday,
								p_tm->tm_hour, 
								p_tm->tm_min, 
								p_tm->tm_sec);  
}


/*---------------------------------------------------------------------------*/
/*	ÉÏ±¨¼¯ÖÐ¿ØÖÆÆ÷Êý¾Ý£¬°´ÕÕÑÝÊ¾°æ±¾ÁÙÊ±¶¨µÄ¸ñÊ½
*/
void AmrDisplay::ReportAmrDate(void)
{
	int len = 0;
	int SendLen = 0;
	char buffer[128] = {0};
	char *ptr = buffer;

/*
	fprintf(stderr, "[%d] [%d] [%d] [%d]\n", 
						AmrData[0],AmrData[1],
						AmrData[2],AmrData[3]);
*/
	AmrData[0] = (AmrData[0] + 1)%100000;
	AmrData[1] = (AmrData[1] + 1)%100000;
	AmrData[2] = (AmrData[2] + 1)%100000;
	AmrData[3] = (AmrData[3] + 1)%100000;

	sprintf(buffer, "<A%05dB%05dC%05dD%05d>",
							AmrData[0],
							AmrData[1],
							AmrData[2],
							AmrData[3]);

	len = 0;
	while ('\0' != *ptr)
	{	
		len++;
		if (' ' == *ptr)
			*ptr = '0';
		ptr++;
	}
	
	SendLen = write(UartFd, buffer, len);
    if (SendLen != len)
	{
    	fprintf(stderr, "write uart failed\n");
    	return;
	}	
	fprintf(stderr, "%s", buffer);
	
	return;
}


/*---------------------------------------------------------------------------*/
/*	ÉÏ±¨½»±ä¿ØÖÆÆ÷Êý¾Ý£¬°´ÕÕÑÝÊ¾°æ±¾ÁÙÊ±¶¨µÄ¸ñÊ½
*/
void AmrDisplay::ReportExcDate(void)
{
	int len = 0;
	int SendLen = 0;
	std::string UartDate;
	char Buffer[215] = { 0 };
	char *ptr = Buffer;
	
	UartDate = std::string("<UA");
	UartDate += std::string(gExcDate.a.volt);
	UartDate += std::string("UB");
	UartDate += std::string(gExcDate.b.volt);
	UartDate += std::string("UC");
	UartDate += std::string(gExcDate.c.volt);

	UartDate += std::string("IA");
	UartDate += std::string(gExcDate.a.curr);
	UartDate += std::string("IB");
	UartDate += std::string(gExcDate.b.curr);
	UartDate += std::string("IC");
	UartDate += std::string(gExcDate.c.curr);

	UartDate += std::string("PA");
	UartDate += std::string(gExcDate.a.power);
	UartDate += std::string("PB");
	UartDate += std::string(gExcDate.b.power);
	UartDate += std::string("PC");
	UartDate += std::string(gExcDate.c.power);

	UartDate += std::string(">");
	strcpy(Buffer, UartDate.c_str());
	ptr = Buffer;

	len = 0;
	while ('\0' != *ptr)
	{	
		len++;
		if (' ' == *ptr)
			*ptr = '0';
		ptr++;
	}

	SendLen = write(UartFd, Buffer, len);
    if (SendLen != len)
	{
    	fprintf(stderr, "write uart failed\n");
    	return;
	}	
	fprintf(stderr, "%s", Buffer, len);
}


/*----------------------------------------------------------------------------*/
/*	ÔËÐÐÕû¸öUI
*/
void AmrDisplay::DisplayRun(void)
{
	int AmrKeypadFd = 0;
	struct input_event {
		struct timeval time;
		unsigned short type;
		unsigned short code;
		int value;
	} Point;
	const char *DevName = "/dev/event0";
	int ConvertCount = 0;
	
	/* ´ò¿ª¼¯¿ØÆ÷°´¼ü£¬¸Ã³ÌÐòÐèÒª¸Ä°´¼üµÄÇý¶¯µÄÖ§³Ö */
	AmrKeypadFd = open(DevName, 0, 0);
	if (AmrKeypadFd < 0) 
	{
		fprintf(stderr, "open %s", DevName);	
		return;
	}

	/* ÏÔÊ¾µÚÒ»ÆÁÊý¾Ý */
	CurDlg->ShowDlg();

	/* ¸ÃÑ­»·£¬¸ºÔð´¦Àí°´¼üÊäÈë */
	while (1)
	{
		read(AmrKeypadFd, &Point, sizeof Point);

		if (Point.type != EV_KEY)
			continue;

		switch (Point.code) 
		{
			case KEY_UP:
				ConvertCount = 0;
				CurDlg->DoBtnUp();
				break;
			case KEY_DOWN:
				ConvertCount = 0;
				CurDlg->DoBtnDown();
				break;
			case KEY_LEFT:
				ConvertCount = 0;
				CurDlg->DoBtnLeft();
				break;
			case KEY_RIGHT:
				ConvertCount = 0;
				CurDlg->DoBtnRight();
				break;
			case KEY_OK:
				ConvertCount = 0;
				CurDlg->DoBtnEnter();
				break;
			case KEY_CANCEL:
				ConvertCount++;
				CurDlg->DoBtnCancel();
				break;
				
		}

		/* Èç¹ûÁ¬Ðø¿ñ°´KEY_CANCEL³¬¹ý30´Î, ÔòÖ÷³ÌÐòÖ÷¶¯ÇÐ»»Ä£Ê½ */
		if (ConvertCount >= 30)
		{
			if (amr_mode == GetMode())
			{
				SetMode(exc_mode);
				CurDlg = &m_ExcDlgWelcome;
				CurDlg->ShowDlg();
			}
			else if (exc_mode == GetMode())
			{
				SetMode(amr_mode);
				CurDlg = &m_DlgWelcome;
				CurDlg->ShowDlg();
			}

			ConvertCount = 0;
		}
		
	}


#if 0	
	while (1)
	{
		char cmd;

		std::cout << "Usage: " << std::endl;
		std::cout << "    w -> UpButton;     s -> DownButton;" << std::endl;
		std::cout << "    a -> LeftButton;   d -> RightButton;" << std::endl;
		std::cout << "    q -> EnterButton;  e -> Exit" << std::endl;
		std::cout << "Input:> ";
		std::cin >> cmd;

		IdleCounter = 0;
		switch (cmd)
		{
			case 'w':
				CurDlg->DoBtnUp();
				break;
				
			case 's':
				CurDlg->DoBtnDown();
				break;
				
			case 'a':
				CurDlg->DoBtnLeft();
				break;
				
			case 'd':
				CurDlg->DoBtnRight();
				break;
				
			case 'q':
				CurDlg->DoBtnEnter();
				break;
				
			case 'e':
				ioctl(disp_fd, AMRDISPLAY_BACKCLEAR, NULL);
				exit(1);
		}
	}
#endif

	return;
}

void AmrDisplay::DsiplaySetWelcome(void)
{
	if (exc_mode == m_Mode)
	{
		CurDlg = &m_ExcDlgWelcome;
	}
	else
		CurDlg = &m_DlgWelcome;
	
	CurDlg->ShowDlg();
}





#if 0
QString GetLocalMac()  
{  
    int sock_mac;  
      
    struct ifreq ifr_mac;  
    char mac_addr[30];     
      
    sock_mac = socket( AF_INET, SOCK_STREAM, 0 );  
    if( sock_mac == -1)  
    {  
        perror("create socket falise...mac/n");  
        return "";  
    }  
      
    memset(&ifr_mac,0,sizeof(ifr_mac));     
    strncpy(ifr_mac.ifr_name, "eth0", sizeof(ifr_mac.ifr_name)-1);     
  
    if( (ioctl( sock_mac, SIOCGIFHWADDR, &ifr_mac)) < 0)  
    {  
        printf("mac ioctl error/n");  
        return "";  
    }  
      
    sprintf(mac_addr,"%02x%02x%02x%02x%02x%02x",  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[0],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[1],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[2],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[3],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[4],  
            (unsigned char)ifr_mac.ifr_hwaddr.sa_data[5]);  
  
    printf("local mac:%s /n",mac_addr);      
      
    close( sock_mac );  
    return QString( mac_addr );  
}  

QString SetLocalNetMask(const char *szNetMask)  
{  
    int sock_netmask;  
    char netmask_addr[32];     
  
    struct ifreq ifr_mask;  
    struct sockaddr_in *sin_net_mask;  
          
    sock_netmask = socket( AF_INET, SOCK_STREAM, 0 );  
    if( sock_netmask == -1)  
    {  
        perror("Not create network socket connect/n");  
        return "";  
    }  
      
    memset(&ifr_mask, 0, sizeof(ifr_mask));     
    strncpy(ifr_mask.ifr_name, "eth0", sizeof(ifr_mask.ifr_name )-1);     
    sin_net_mask = (struct sockaddr_in *)&ifr_mask.ifr_addr;  
    sin_net_mask -> sin_family = AF_INET;  
    inet_pton(AF_INET, szNetMask, &sin_net_mask ->sin_addr);  
  
    if(ioctl(sock_netmask, SIOCSIFNETMASK, &ifr_mask ) < 0)   
    {  
        printf("sock_netmask ioctl error/n");  
        return "";  
    }  
}  

QString GetGateWay()  
{  
    FILE *fp;  
    char buf[512];  
    char cmd[128];  
    char gateway[30];  
    char *tmp;  
  
    strcpy(cmd, "ip route");  
    fp = popen(cmd, "r");  
    if(NULL == fp)  
    {  
        perror("popen error");  
        return "";  
    }  
    while(fgets(buf, sizeof(buf), fp) != NULL)  
    {  
        tmp =buf;  
        while(*tmp && isspace(*tmp))  
            ++ tmp;  
        if(strncmp(tmp, "default", strlen("default")) == 0)  
            break;  
    }  
    sscanf(buf, "%*s%*s%s", gateway);         
    printf("default gateway:%s/n", gateway);  
    pclose(fp);  
      
    return QString(gateway);  
} 

int SetGateWay(const char *szGateWay)  
{  
    int ret = 0;      
    char cmd[128];  
    QString DefGW = GetGateWay();  
  
    const char *strGW = DefGW.latin1();   
      
    strcpy(cmd, "route del default gw ");  
    strcat(cmd, strGW);  
    ret = system(cmd);  
    if(ret < 0)  
    {  
        perror("route error");  
        return -1;  
    }  
    strcpy(cmd, "route add default gw ");  
    strcat(cmd, szGateWay);  
      
    ret = system(cmd);  
    if(ret < 0)  
    {  
        perror("route error");  
        return -1;  
    }  
  
    return ret;  
}  

#endif










