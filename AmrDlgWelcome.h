/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgWelcome.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_WELCOME_H
#define __AMR_DLG_WELCOME_H

#include "AmrDlgBase.h"

class AmrDisplay;
class AmrDlgWelcome : public AmrDlgBase
{
	public:
		AmrDlgWelcome(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgWelcome();

		void InitDlg(void);
		void InitOperation(void);
		
		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoBtnCancel(void);
		virtual void DoTimer(void);

	private:
		AmrDisplay &m_AmrDisplay;

		int x_pos;
		int y_pos;

		int dev_fd;
		int LightCount;
};





#endif



