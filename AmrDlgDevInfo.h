/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgDevInfo.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_DEV_INFO_H
#define __AMR_DLG_DEV_INFO_H

#include "AmrDlgBase.h"

class AmrDisplay;
class AmrDlgDevInfo : public AmrDlgBase
{
	public:
		AmrDlgDevInfo(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgDevInfo();

		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoBtnCancel(void);
		virtual void DoTimer(void);

		void InitDlg(void);
		void InitOperation(void);
		
	private:
		bool BackValid;
		AmrDisplay &m_AmrDisplay;
		int x_pos;
		int y_pos;

		bool RoundDisp;
};

















#endif
