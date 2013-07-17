/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgDate.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_DATE_H
#define __AMR_DLG_DATE_H

#include "AmrDlgBase.h"

class AmrDisplay;
class AmrDlgDate : public AmrDlgBase
{
	public:
		AmrDlgDate(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgDate();

		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoBtnCancel(void);
		virtual void DoTimer(void);
		
		void InitDlg(void);
		void InitOperation(void);
		void UpdateDateTime(void);
		
	private:
		AmrDisplay &m_AmrDisplay;
		bool BackValid;

};

















#endif

