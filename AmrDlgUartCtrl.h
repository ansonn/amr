/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgLedCtrl.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_UART_CTRL_H
#define __AMR_DLG_UART_CTRL_H

#include "AmrDlgBase.h"

#define UART_DEV_NAME 	"/dev/ttyS4"

enum {
	UART_MENU_0,
	UART_MENU_1,
	UART_MENU_2,
	UART_MENU_3,
	UART_MENU_BACK,
	UART_MENU_BUTT
};


class AmrDisplay;
class AmrDlgUartCtrl : public AmrDlgBase
{
	public:
		AmrDlgUartCtrl(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgUartCtrl();

		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoTimer(void);
		virtual void DoBtnCancel(void);

		bool MenuClearFlg[4];
		void InitDlg(void);
		void InitOperation(void);
		void UpdateCurrentValue(void);
		
	private:
		AmrDisplay &m_AmrDisplay;
		int x_pos;
		int y_pos;
		int MenuIdx;
		bool RoundDisp;

};

















#endif