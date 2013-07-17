/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- ExcDlgMain.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __EXC_DLG_MAIN_H
#define __EXC_DLG_MAIN_H

#include "AmrDlgBase.h"

enum {
	EXC_MENU_1,
	EXC_MENU_2,
	EXC_MENU_MAX
};


class AmrDisplay;
class ExcDlgMain : public AmrDlgBase
{
	public:
		ExcDlgMain(AmrDisplay &rAmrDisplay, unsigned int fd);
		~ExcDlgMain();

		void InitDlg(void);
		void DisplayTime(int x, int y);

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
