/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgLedCtrl.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_LED_CTRL_H
#define __AMR_DLG_LED_CTRL_H

#include "AmrDlgBase.h"

#define LEDSCTRL_DEV 	"/dev/amrleds"


/*----------------------------------------------------------------------------*/
/*	使用枚举列举出LED
*/
enum {
	RUN_LED_PIN = 0,
	ALM_LED_PIN,
	AMR_MAX_PIN_NR,
};

/*----------------------------------------------------------------------------*/
/*	该结构为LED驱动接口，用于传递参数到底层驱动
*/
struct amr_ledsctrl_param {
	int led_index;
	unsigned short on_time;		// 点亮时间
	unsigned short off_time;	// 熄灭时间
	unsigned int   run_time;	// 总运行时间	
};

/* Use 'A' as magic number */
#define AMR_LED_MAGIC  'A'
/* Please use a different 8-bit number in your code */

/*
 */
#define AMR_LED_RUN 		_IO(AMR_LED_MAGIC,  0)
#define AMR_LED_STOP	    _IO(AMR_LED_MAGIC,  1)
#define AMR_LED_ON 			_IO(AMR_LED_MAGIC,  2)
#define AMR_LED_OFF	    	_IO(AMR_LED_MAGIC,  3)


/*----------------------------------------------------------------------------*/
/*	所有的菜单项枚举；<>
*/
enum {
	LED_MENU_0,
	LED_MENU_1,
	LED_MENU_2,
	LED_MENU_3,
	LED_MENU_4,
	LED_MENU_5,
	LED_MENU_6,
	LED_MENU_7,
	LED_MENU_8,
	LED_MENU_9,
	LED_MENU_10,
	LED_MENU_11,
	LED_MENU_APL,
	LED_MENU_BACK,
	LED_MENU_BUTT
};


class AmrDisplay;

/*----------------------------------------------------------------------------*/
/*	页面类类型保持一致，参见AmrDlgBase类描述
*/
class AmrDlgLedCtrl : public AmrDlgBase
{
	public:
		AmrDlgLedCtrl(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgLedCtrl();

		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoBtnCancel(void);
		virtual void DoTimer(void);

		void InitDlg(void);
		void InitOperation(void);

		void DisplayDigaital(void);
		void RunLed(void);
		
	private:
		AmrDisplay &m_AmrDisplay;
		int x_pos;
		int y_pos;
		int MenuIdx;
		bool RoundDisp;

		int Time_On;
		int Time_Off;
		int Time_all;

		unsigned int amrleds_fd;
};

















#endif
