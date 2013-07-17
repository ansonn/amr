/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- ExcDlgPowerTotal.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "ExcDlgPowerTotal.h"


/*----------------------------------------------------------------------------*/


ExcDlgPowerTotal::ExcDlgPowerTotal(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
				, x_pos(0)
				, y_pos(0)
{
	name = "ExcDlgPowerTotal";
	dev_fd = fd;
	InitDlg();
}

ExcDlgPowerTotal::~ExcDlgPowerTotal()
{

}

/* init Dlg */
void ExcDlgPowerTotal::InitDlg(void)
{
	int i = 0;
	//unsigned char str[1] = { 'L' };
	unsigned char buff[32] = {0};

	ClearAll();

	SetMemAera(16, 0, GPS_16X32_8BIT, DISPLAY, false);

	SetRectangle(0, 18, 160, 2, false);
	SetRectangle(0, 142, 160, 2, false);
	SetRectangle(138, 147, 16, 8, false);
	SetRectangle(136, 149, 2, 4, false);
	//DISPLAY_8x16_SR(64, 2, false);


	DISPLAY_16x16_DIANNENGLIANG(55, 25, false);
	DISPLAY_ZHENGXIANGYOUGONG(0, 45, false);
	DISPLAY_ZHENGXIANGWUGONG(0, 63, false);
	DISPLAY_FANXIANGYOUGONG(0, 81, false);
	DISPLAY_FANXIANGWUGONG(0, 99, false);

	DISPLAY_8x16_KWH(120, 45, false);
	DISPLAY_8x16_KVARH(120, 63, false);
	DISPLAY_8x16_KWH(120, 81, false);
	DISPLAY_8x16_KVARH(120, 99, false);
	
	DISPLAY_8x16_000000000210(0, 144, false);
	DisplayTime(120, 2);

	return;
}

void ExcDlgPowerTotal::DisplayTime(int x, int y)
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

void ExcDlgPowerTotal::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(0, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(0, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	LightCount = 0;
	DisplayTime(120, 2);

	DispExcDate();
	
	m_AmrDisplay.CurDlg->ShowDlg();
}

void ExcDlgPowerTotal::DispExcDate()
{
	int x, y;

	DISPLAY_STRING(41, 45, m_AmrDisplay.gExcDate.power_count);
	DISPLAY_STRING(41, 63, m_AmrDisplay.gExcDate.rower_count);	
	DISPLAY_STRING(41, 81, m_AmrDisplay.gExcDate.re_power_count);
	DISPLAY_STRING(41, 99, m_AmrDisplay.gExcDate.re_rower_count);

	DISPLAY_STRING(20, 125, m_AmrDisplay.m_ExcCapTime);	
}

void ExcDlgPowerTotal::DoBtnUp(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerNo;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();
}

void ExcDlgPowerTotal::DoBtnDown(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgTelemetry;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void ExcDlgPowerTotal::DoBtnLeft(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerNo;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void ExcDlgPowerTotal::DoBtnRight(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgTelemetry;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void ExcDlgPowerTotal::DoBtnEnter(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}	
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();
}

void ExcDlgPowerTotal::DoBtnCancel()
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void ExcDlgPowerTotal::DoTimer(void)
{
	m_AmrDisplay.IdleCounter = 0;

/*
	if (y_random != 0)
	{
		SetMemAera(x_random, y_random, ROUND_LOGO16X16_8BIT, CLEAR);
	}
	
	x_random = random()%144;
	y_random = random()%70 + 45;

	SetMemAera(x_random, y_random, ROUND_LOGO16X16_8BIT, DISPLAY);
	
*/

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


	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKCLEAR, NULL);
	}
	else
		LightCount++;

	
	if (0 == m_AmrDisplay.AmrTick%10)
		DispExcDate();
		

	DisplayTime(120, 2);
	m_AmrDisplay.AmrTick++;
	m_AmrDisplay.CurDlg->ShowDlg();
}
