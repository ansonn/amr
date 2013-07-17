/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgBase.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_BASE_H
#define __AMR_DLG_BASE_H

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

#include <iostream>
#include "ziku.h"

/* Use 'a' as magic number */
#define AMRDISP_IOC_MAGIC  'a'
/* Please use a different 8-bit number in your code */

/*
 */

// old interface
#define AMRDISP_CMD 				_IO(AMRDISP_IOC_MAGIC,  0)
#define AMRDISP_DAT		    		_IO(AMRDISP_IOC_MAGIC,  1)
#define AMRDISP_RST		    		_IO(AMRDISP_IOC_MAGIC,  2)
#define AMRDISP_INITPIN	    		_IO(AMRDISP_IOC_MAGIC,  3)


#define AMRDISPLAY_CTRL_INIT		_IO(AMRDISP_IOC_MAGIC, 4)
#define AMRDISPLAY_CTRL_CLR			_IO(AMRDISP_IOC_MAGIC, 5)
#define AMRDISPLAY_BACKLIGHT		_IO(AMRDISP_IOC_MAGIC, 6)
#define AMRDISPLAY_BACKCLEAR		_IO(AMRDISP_IOC_MAGIC, 7)



#define DISP_X_MAX	160
#define DISP_Y_MAX	160

/*----------------------------------------------------------------------------*/
/*	演示版本使用的EMI屏，两个字节数据点亮3个点，所以，一行160个点需要108个字节
*/
#define MEM_X_MAX	108
#define MEM_Y_MAX	160

#define DISPLAY		1
#define CLEAR		0


#define WAIT_TO_IDLE_TIME	1000//100s


/*----------------------------------------------------------------------------*/
/*	图片库枚举，用于索引图片库数据
*/
typedef enum {
	LOONGSON_LOGO32X32_8BIT,
	LOONGSON_LOGO16X16_8BIT,
	ROUND_LOGO16X16_8BIT,
	GPS_16X32_8BIT,
	SIGNAL1_16x16_8bit,
	SIGNAL2_16x16_8bit,
	SIGNAL3_16x16_8bit,
	SIGNAL4_16x16_8bit,
	CLEAR_ALL,
	AREA_TYPE_BUTT
} AREA_TYPE_EN;


/*----------------------------------------------------------------------------*/
/*	标示一个字节中有几个bit有效! 底层操作时候使用
*/
typedef enum {
	BIT6_TYPE = 6,
	BIT8_TYPE = 8
} BYTE_TYPE_EN;

/*----------------------------------------------------------------------------*/
/*	使用的字库
*/
enum {
	ASCII12,
	ASCII16,
	CHINESE12,
	CHINESE16
};

/*----------------------------------------------------------------------------*/
/*	该结构描述一个图像数据!
*/
typedef struct {
	int x_len;				//长
	int y_len;				//宽
	BYTE_TYPE_EN b_type;	//类型 8bit && 6bit
	unsigned char *data;	//数据
} AREA_DATA_ARRAY;

/*----------------------------------------------------------------------------*/
/*	该结构用于表示一个显示的字符
*/
typedef struct {
	int x;
	int y;
	int type;
	char val;
	bool flg;
} DigitalArrStru;

/*----------------------------------------------------------------------------*/
/*	所有UI界面的基类
**		所有页面的共同点；内聚到AmrDlgBase中实现
**		页面间的差异，则通过纯虚函数，有各个子类继承接口，并覆盖是实现
*/
class AmrDlgBase {

	public:
		AmrDlgBase(unsigned int fd);
		~AmrDlgBase();

		/* 设置或者清除屏上一点, 仅在缓存上操作 */
		void SetMemDot(int x, int y, int val);

		/* 	在坐标(x,y)处，显示一个事先准备好的图像数据，
			数据由AREA_TYPE_EN指明，turn_over标示色彩翻转
		*/
		void SetMemAera(int x, int y, AREA_TYPE_EN type, 
												int clr_flag, bool turn_over);
		/* 在某点画一个矩形，clr标示清除 */
		void SetRectangle(int x, int y, int x_len, int y_len, bool clr);

		/* 设置字符到坐标(x,y),clr_flag表明清除，turn_over表明色调翻转  */
		void SetZIFUAera(int x, int y, int len, 
						unsigned char *buffer, int clr_flag, bool turn_over);
		/* 把该页面缓存打到EMI屏上 */
		void DisplayMem(void);
		/* 清缓存 */
		void ClearAll(void);


		/* 虚函数，子类差异实现 */
		virtual void ShowDlg(void);
		virtual void DoBtnUp(void) = 0;
		virtual void DoBtnDown(void) = 0;
		virtual void DoBtnLeft(void) = 0;
		virtual void DoBtnRight(void) = 0;
		virtual void DoBtnEnter(void) = 0;
		virtual void DoBtnCancel(void) = 0;
		virtual void DoTimer(void) = 0;
		virtual void InitDlg(void) = 0;
		virtual void InitOperation(void);

		/* 标示一个页面的名字，暂没用 */
		const char *name;	

	private:
		/* 一帧显示的缓存 */
		unsigned char DispMem[MEM_X_MAX][MEM_Y_MAX];
		/* EMI屏设备句柄 */
		unsigned int DispFd;

		

};



#endif

