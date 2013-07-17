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
/*	��ʾ�汾ʹ�õ�EMI���������ֽ����ݵ���3���㣬���ԣ�һ��160������Ҫ108���ֽ�
*/
#define MEM_X_MAX	108
#define MEM_Y_MAX	160

#define DISPLAY		1
#define CLEAR		0


#define WAIT_TO_IDLE_TIME	1000//100s


/*----------------------------------------------------------------------------*/
/*	ͼƬ��ö�٣���������ͼƬ������
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
/*	��ʾһ���ֽ����м���bit��Ч! �ײ����ʱ��ʹ��
*/
typedef enum {
	BIT6_TYPE = 6,
	BIT8_TYPE = 8
} BYTE_TYPE_EN;

/*----------------------------------------------------------------------------*/
/*	ʹ�õ��ֿ�
*/
enum {
	ASCII12,
	ASCII16,
	CHINESE12,
	CHINESE16
};

/*----------------------------------------------------------------------------*/
/*	�ýṹ����һ��ͼ������!
*/
typedef struct {
	int x_len;				//��
	int y_len;				//��
	BYTE_TYPE_EN b_type;	//���� 8bit && 6bit
	unsigned char *data;	//����
} AREA_DATA_ARRAY;

/*----------------------------------------------------------------------------*/
/*	�ýṹ���ڱ�ʾһ����ʾ���ַ�
*/
typedef struct {
	int x;
	int y;
	int type;
	char val;
	bool flg;
} DigitalArrStru;

/*----------------------------------------------------------------------------*/
/*	����UI����Ļ���
**		����ҳ��Ĺ�ͬ�㣻�ھ۵�AmrDlgBase��ʵ��
**		ҳ���Ĳ��죬��ͨ�����麯�����и�������̳нӿڣ���������ʵ��
*/
class AmrDlgBase {

	public:
		AmrDlgBase(unsigned int fd);
		~AmrDlgBase();

		/* ���û����������һ��, ���ڻ����ϲ��� */
		void SetMemDot(int x, int y, int val);

		/* 	������(x,y)������ʾһ������׼���õ�ͼ�����ݣ�
			������AREA_TYPE_ENָ����turn_over��ʾɫ�ʷ�ת
		*/
		void SetMemAera(int x, int y, AREA_TYPE_EN type, 
												int clr_flag, bool turn_over);
		/* ��ĳ�㻭һ�����Σ�clr��ʾ��� */
		void SetRectangle(int x, int y, int x_len, int y_len, bool clr);

		/* �����ַ�������(x,y),clr_flag���������turn_over����ɫ����ת  */
		void SetZIFUAera(int x, int y, int len, 
						unsigned char *buffer, int clr_flag, bool turn_over);
		/* �Ѹ�ҳ�滺���EMI���� */
		void DisplayMem(void);
		/* �建�� */
		void ClearAll(void);


		/* �麯�����������ʵ�� */
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

		/* ��ʾһ��ҳ������֣���û�� */
		const char *name;	

	private:
		/* һ֡��ʾ�Ļ��� */
		unsigned char DispMem[MEM_X_MAX][MEM_Y_MAX];
		/* EMI���豸��� */
		unsigned int DispFd;

		

};



#endif

