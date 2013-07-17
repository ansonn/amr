/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgDate.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_SYS_SETING_H
#define __AMR_DLG_SYS_SETING_H

#include "AmrDlgBase.h"

class AmrDisplay;
class AmrDlgSysSetting : public AmrDlgBase
{
	public:
		AmrDlgSysSetting(AmrDisplay &rAmrDisplay, unsigned int fd);
		~AmrDlgSysSetting();

		virtual void DoBtnUp(void);
		virtual void DoBtnDown(void);
		virtual void DoBtnLeft(void);
		virtual void DoBtnRight(void);
		virtual void DoBtnEnter(void);
		virtual void DoBtnCancel(void);
		virtual void DoTimer(void);
		
		void InitDlg(void);
		void InitOperation(void);
		void DisplaySetAttr(void);
		bool GetMenuDispFlg(int);
		char GetMenuDispVal(int);
		void SetMenuDispFlg(int ,bool);
		void SetMenuDispVal(int, char);

		void SyncSysParam(void);
		int DoConfig(void);
		
	private:
		AmrDisplay &m_AmrDisplay;
		int MenuIdx;
};

















#endif

