/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- ExcDlgTelemetry.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef __AMR_DLG_TELEMETRY_EXC_H
#define __AMR_DLG_TELEMETRY_EXC_H

#include "AmrDlgBase.h"

class AmrDisplay;
class ExcDlgTelemetry : public AmrDlgBase
{
	public:
		ExcDlgTelemetry(AmrDisplay &rAmrDisplay, unsigned int fd);
		~ExcDlgTelemetry();

		void InitDlg(void);
		void InitOperation(void);
		void DisplayTime(int x, int y);

		void DispExcDate();

		
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


