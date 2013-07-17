/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDisplay.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DISPLAY_H
#define __AMR_DISPLAY_H

#include "AmrDlgBase.h"
#include "AmrDlgWelcome.h"
#include "AmrDlgMain.h"
#include "AmrDlgDevInfo.h"
#include "AmrDlgDate.h"
#include "AmrDlgLedCtrl.h"
#include "AmrDlgSysSetting.h"
#include "AmrDlgUartCtrl.h"

#include "ExcDlgWelcome.h"
#include "ExcDlgMain.h"
#include "ExcDlgPowerHave.h"
#include "ExcDlgPowerNo.h"
#include "ExcDlgPowerTotal.h"
#include "ExcDlgTelemetry.h"

#include <iconv.h>
#include <net/if.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <math.h>

/*---------------------------------------------------------------------------*/
/*	两种模式
*/
enum {
	amr_mode,
	exc_mode
};

/*---------------------------------------------------------------------------*/
/*	模拟数据格式
*/
struct power_point{
	int type;
	char volt[8];
	char curr[8];
	char degree[8];
	char power[12];
	char rower[12];
};

/*---------------------------------------------------------------------------*/
/*	模拟数据格式
*/
struct data_frame{
	struct power_point a;
	struct power_point b;
	struct power_point c;
	char active_power[12];
	char reactive_power[12];
	char power_count[12];
	char rower_count[12];
	char re_power_count[12];
	char re_rower_count[12];
};


/*---------------------------------------------------------------------------*/
/*	AmrDisplay类，
*/
class AmrDisplay {

	public:
		AmrDisplay(unsigned int fd);
		~AmrDisplay();
		
		void DisplayRun(void);
		void DsiplaySetWelcome(void);

		/* 集中控制器所有页面，这些类均继承与AmrDlgBase */
		AmrDlgWelcome 	m_DlgWelcome;
		AmrDlgMain		m_AmrDlgMain;
		AmrDlgDevInfo	m_AmrDlgDevInfo;
		AmrDlgDate		m_AmrDlgDate;
		AmrDlgLedCtrl	m_AmrDlgLedCtrl;
		AmrDlgSysSetting	m_AmrDlgSysSetting;
		AmrDlgUartCtrl		m_AmrDlgUartCtrl;

		/* 交变控制器所有页面，这些类均继承与AmrDlgBase */
		ExcDlgWelcome		m_ExcDlgWelcome;
		ExcDlgMain			m_ExcDlgMain;
		ExcDlgPowerHave		m_ExcDlgPowerHave;
		ExcDlgPowerNo		m_ExcDlgPowerNo;
		ExcDlgPowerTotal	m_ExcDlgPowerTotal;
		ExcDlgTelemetry		m_ExcDlgTelemetry;

		/* 当前模式: amr_mode,	exc_mode */
		int m_Mode;
	
		/* 	指向基类的指针，所有UI页面均继承与该基类
		**	依据改基类指针体现多态。
		*/
		AmrDlgBase *CurDlg;
		
		int disp_fd;
		int IdleCounter;
		int ExcDataCapCount;
		int AmrDataCapCount;
		int AmrTick;
		int SignalValue;

		/* 保存系统参数相关 */
		char ipaddr[50];
		char m_date[50];    //2008-05-23
		char m_time[50];	  //01:01:01
		char m_ExcCapTime[50];

		/* 数据相关 */
		const int voltage;
		const int current;
		const double PI;
		double power_count;
		double rower_count;

		
#define FILE_CHINESE_16_NAME  	"/home/HZK16"
#define FILE_CHINESE_12_NAME  	"/home/HZK12"
#define FILE_ASCII_16_NAME   	"/home/ASC16"
#define FILE_ASCII_12_NAME   	"/home/ASC12"

#define VOLT_FLUCT (5)
#define CURR_FLUCT (15)


		/* 从字库文件中读取数据 */
		unsigned int FileReadOffset(unsigned int hfile, unsigned long offset, 
									unsigned char * pbuffer, unsigned int size);

		/* 字库转换为点阵 */
		unsigned int ZKDisplayConvert(char *pdata , 
									  unsigned char font , 
									  unsigned char *pbuffer);
		int GetLocalIp(void);
		int SetLocalIp(void);

		int SetDateTime(void);
		int GetDateTime(void);
		int GetExcDataTime(void);

		void SetExcMode() { m_Mode = exc_mode; CurDlg = &m_ExcDlgWelcome; }
		int GetMode() { return m_Mode; }
		void SetMode(int NMode) { m_Mode = NMode; }

		int GetExcData(struct data_frame *cur);
		int str_align(char *buf, int length);
		int PrintExcData(struct data_frame * cur);
		void ClearExcPowerData() { power_count = 0.0; rower_count = 0.0; }

		void ReportExcDate(void);
		void ReportAmrDate(void);
		unsigned int AmrData[4];

		struct data_frame gExcDate;

};


typedef void *(* IconvOpen)(const char*, const char *);
typedef size_t (* Iconv)(iconv_t, char **, size_t*, char **, size_t*);


#endif

