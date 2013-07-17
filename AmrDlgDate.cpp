/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgDate.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "AmrDlgDate.h"



AmrDlgDate::AmrDlgDate(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
{
	name = "AmrDlgDate";
	InitDlg();
}

AmrDlgDate::~AmrDlgDate()
{

}

void AmrDlgDate::InitDlg(void)
{
	ClearAll();

	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);

	DISPLAY_RIQI(10, 30, false);
	DISPLAY_SHIJIAN(10, 70, false);
	
	BackValid = false;
	DISPLAY_16x16_TUICHUI(128, 144, false);
}

void AmrDlgDate::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	BackValid = false;
	DISPLAY_16x16_TUICHUI(128, 144, false);

	UpdateDateTime();
	
}

void AmrDlgDate::UpdateDateTime(void)
{
	int x,y;
	unsigned char buff[32] = {0};

	m_AmrDisplay.GetDateTime();

	char *date = m_AmrDisplay.m_date;
	x = 50; y = 30;
	while ('\0' != *date)
	{
		m_AmrDisplay.ZKDisplayConvert(date , ASCII16, buff);
		SetZIFUAera(x, y, ASCII16, buff, DISPLAY, false);
		x += 8;
		date++;
	}

	char *time = m_AmrDisplay.m_time;
	x = 50; y = 70;
	while ('\0' != *time)
	{
		m_AmrDisplay.ZKDisplayConvert(time , ASCII16, buff);
		SetZIFUAera(x, y, ASCII16, buff, DISPLAY, false);
		x += 8;
		time++;
	}
}

void AmrDlgDate::DoBtnUp(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (false == BackValid)
	{
		DISPLAY_16x16_TUICHUI(128, 144, true);
		BackValid = true;
	}
	else
	{
		DISPLAY_16x16_TUICHUI(128, 144, false);
		BackValid = false;
	}
	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgDate::DoBtnDown(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (false == BackValid)
	{
		DISPLAY_16x16_TUICHUI(128, 144, true);
		BackValid = true;
	}
	else
	{
		DISPLAY_16x16_TUICHUI(128, 144, false);
		BackValid = false;
	}
	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgDate::DoBtnLeft(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (false == BackValid)
	{
		DISPLAY_16x16_TUICHUI(128, 144, true);
		BackValid = true;
	}
	else
	{
		DISPLAY_16x16_TUICHUI(128, 144, false);
		BackValid = false;
	}
	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgDate::DoBtnRight(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (false == BackValid)
	{
		DISPLAY_16x16_TUICHUI(128, 144, true);
		BackValid = true;
	}
	else
	{
		DISPLAY_16x16_TUICHUI(128, 144, false);
		BackValid = false;
	}
	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgDate::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (BackValid)
	{
		m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
		m_AmrDisplay.CurDlg->InitOperation();
		m_AmrDisplay.CurDlg->ShowDlg();
	}
}

void AmrDlgDate::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;

	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void AmrDlgDate::DoTimer(void)
{
	if (0 == m_AmrDisplay.AmrTick%50)
	{
		if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		{
			SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);
			m_AmrDisplay.SignalValue = SIGNAL3_16x16_8bit;
		}
		else
		{
			SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
			m_AmrDisplay.SignalValue = SIGNAL4_16x16_8bit;
		}
	}
	if (0 == m_AmrDisplay.AmrTick%10)
		UpdateDateTime();

	m_AmrDisplay.CurDlg->ShowDlg();
	m_AmrDisplay.AmrTick++;
}

