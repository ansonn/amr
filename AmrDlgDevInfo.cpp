/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgDevInfo.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "AmrDlgDevInfo.h"



AmrDlgDevInfo::AmrDlgDevInfo(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
				, x_pos(0)
				, y_pos(0)
				, RoundDisp(false)
{
	name = "AmrDlgDevInfo";
	InitDlg();
}



AmrDlgDevInfo::~AmrDlgDevInfo()
{

}

void AmrDlgDevInfo::InitDlg(void)
{
	ClearAll();

	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);

	DISPLAY_CHULIQILEIXING(0, 30, false);
	DISPLAY_IPDIZHI(0, 50, false);
	DISPLAY_KEYONGNEICUN(0, 70, false);
	DISPLAY_KEYONGFLASH(0, 90, false);
	
	BackValid = false;
	DISPLAY_16x16_TUICHUI(128, 144, false);

	x_pos = 0;
	y_pos = 144;
	//SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
}

void AmrDlgDevInfo::InitOperation(void)
{
	char *ipaddr = NULL;
	int x = 40;
	int y = 50;
	unsigned char buff[32] = {0};

	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	BackValid = false;
	DISPLAY_16x16_TUICHUI(128, 144, false);

	m_AmrDisplay.GetLocalIp();

	ipaddr = m_AmrDisplay.ipaddr;
	while ('\0' != *ipaddr)
	{
		m_AmrDisplay.ZKDisplayConvert(ipaddr , ASCII16, buff);
		SetZIFUAera(x, y, ASCII16, buff, DISPLAY, false);
		x += 8;
		ipaddr++;
	}
}
void AmrDlgDevInfo::DoBtnUp(void)
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

void AmrDlgDevInfo::DoBtnDown(void)
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

void AmrDlgDevInfo::DoBtnLeft(void)
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

void AmrDlgDevInfo::DoBtnRight(void)
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

void AmrDlgDevInfo::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (BackValid)
	{
		m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
		m_AmrDisplay.CurDlg->InitOperation();
		m_AmrDisplay.CurDlg->ShowDlg();
	}
}

void AmrDlgDevInfo::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;

	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void AmrDlgDevInfo::DoTimer(void)
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

	if (m_AmrDisplay.AmrTick%10 == 0)
	{	
		if (false == RoundDisp)
		{
			x_pos = random();
			x_pos %= 100;
			SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
			RoundDisp = true;
		}
		else
		{
			RoundDisp = false;
			SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
		}
	}
	
	m_AmrDisplay.CurDlg->ShowDlg();
	m_AmrDisplay.AmrTick++;
}


