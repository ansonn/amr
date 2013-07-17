/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgMain.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_MAIN_H
#define __AMR_DLG_MAIN_H

#include "AmrDlgBase.h"

enum {
	MENU_1,
	MENU_2,
	MENU_3,
	MENU_4,
	MENU_5,
	MENU_EXIT,
	MENU_MAX
};


class AmrDisplay;
/*----------------------------------------------------------------------------*/
/*	集中控制器主页面的类, 继承于AmrDlgBase
*/
class AmrDlgMain : public AmrDlgBase
{
	public:
		AmrDlgMain(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgMain();

		void InitDlg(void);

		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoBtnCancel(void);
		virtual void DoTimer(void);

		void InitOperation(void);

		void SetTurnOff(int MenuIndex, bool flag);
	private:
		int MenuIndex;
		AmrDisplay &m_AmrDisplay;
};







#endif

