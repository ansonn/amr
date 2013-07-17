/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgMain.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "ExcDlgMain.h"



ExcDlgMain::ExcDlgMain(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
{
	name = "AmrDlgMain";
	InitDlg();
}

ExcDlgMain::~ExcDlgMain()
{

}

void ExcDlgMain::SetTurnOff(int MenuIndex, bool flg)
{
	switch (MenuIndex)
	{
		case EXC_MENU_1:
			DISPLAY_16x16_JIAOCAISHUJU(40, 40, flg);
			break;
		case EXC_MENU_2:
			DISPLAY_16x16_XITONGSHEZHI(40, 60, flg);
			break;
	}
}

/* init Dlg */
void ExcDlgMain::InitDlg(void)
{
	ClearAll();

	//SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(16, 0, GPS_16X32_8BIT, DISPLAY, false);
	SetRectangle(0, 18, 160, 2, false);
	SetRectangle(0, 142, 160, 2, false);
	SetRectangle(138, 147, 16, 8, false);
	SetRectangle(136, 149, 2, 4, false);
	//DISPLAY_8x16_SR(64, 2, false);
	
	MenuIndex = EXC_MENU_1;
	DISPLAY_16x16_JIAOCAISHUJU(40, 40, false);
	DISPLAY_16x16_XITONGSHEZHI(40, 60, false);

	DisplayTime(120, 2);
	
	return;
}

void ExcDlgMain::DisplayTime(int x, int y)
{
	m_AmrDisplay.GetDateTime();
	m_AmrDisplay.m_time[5] = '\0';
	unsigned char buff[32] = {0};

	char *time = m_AmrDisplay.m_time;
	while ('\0' != *time)
	{
		m_AmrDisplay.ZKDisplayConvert(time , ASCII16, buff);
		SetZIFUAera(x, y, ASCII16, buff, DISPLAY, false);
		x += 8;
		time++;
	}
}

void ExcDlgMain::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(0, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(0, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	SetTurnOff(MenuIndex, false);
	MenuIndex = 0;
	SetTurnOff(MenuIndex, true);

	DisplayTime(120, 2);
	m_AmrDisplay.CurDlg->ShowDlg();
}

void ExcDlgMain::DoBtnUp(void)
{
	m_AmrDisplay.IdleCounter = 0;

	SetTurnOff(MenuIndex, false);

	MenuIndex--;
	if (MenuIndex < EXC_MENU_1)
		MenuIndex = EXC_MENU_2;

	SetTurnOff(MenuIndex, true);

	m_AmrDisplay.CurDlg->ShowDlg();
}

void ExcDlgMain::DoBtnDown(void)
{
	m_AmrDisplay.IdleCounter = 0;

	SetTurnOff(MenuIndex, false);

	MenuIndex++;
	if (MenuIndex >= EXC_MENU_MAX )
		MenuIndex = EXC_MENU_1;

	SetTurnOff(MenuIndex, true);

	m_AmrDisplay.CurDlg->ShowDlg();
}

void ExcDlgMain::DoBtnLeft(void)
{
	m_AmrDisplay.IdleCounter = 0;

}

void ExcDlgMain::DoBtnRight(void)
{
	m_AmrDisplay.IdleCounter = 0;

}

void ExcDlgMain::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;

	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgWelcome;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}


void ExcDlgMain::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;

	switch (MenuIndex)
	{
		case EXC_MENU_1:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerTotal;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
		case EXC_MENU_2:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgSysSetting;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
	}
		
}

void ExcDlgMain::DoTimer(void)
{
	

	if (0 == m_AmrDisplay.AmrTick%50)
	{
		if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		{
			SetMemAera(0, 0, SIGNAL3_16x16_8bit, DISPLAY, false);
			m_AmrDisplay.SignalValue = SIGNAL3_16x16_8bit;
		}
		else
		{
			SetMemAera(0, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
			m_AmrDisplay.SignalValue = SIGNAL4_16x16_8bit;
		}
	}


	if (m_AmrDisplay.AmrTick%5 == 0)
		DisplayTime(120, 2);
	

	m_AmrDisplay.AmrTick++;
	m_AmrDisplay.CurDlg->ShowDlg();
}


