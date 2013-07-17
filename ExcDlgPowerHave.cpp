/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- ExcDlgPowerHave.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "ExcDlgPowerHave.h"


/*----------------------------------------------------------------------------*/


ExcDlgPowerHave::ExcDlgPowerHave(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
				, x_pos(0)
				, y_pos(0)
{
	name = "ExcDlgPowerHave";
	dev_fd = fd;
	InitDlg();
}

ExcDlgPowerHave::~ExcDlgPowerHave()
{

}

/* init Dlg */
void ExcDlgPowerHave::InitDlg(void)
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

	DISPLAY_ZONG(10, 45, false);
	DISPLAY_8x16_PA(10, 65, false);
	DISPLAY_8x16_KW(124, 65, false);
	DISPLAY_8x16_PB(10, 81, false);
	DISPLAY_8x16_KW(124, 81, false);
	DISPLAY_8x16_PC(10, 97, false);
	DISPLAY_8x16_KW(124, 97, false);

#if 0	// title
	m_AmrDisplay.ZKDisplayConvert((char *)"L" , ASCII12, buff);
	SetZIFUAera(50, 10, ASCII12, buff, DISPLAY, false);
#else
	DISPLAY_16x16_YOUGONGGONGLV(50, 25, false);
	DISPLAY_8x16_000000000210(0, 144, false);

	//DISPLAY_CAIJISHIJIAN(60, 105, false);
	DisplayTime(120, 2);

#endif
	return;
}

void ExcDlgPowerHave::DisplayTime(int x, int y)
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

void ExcDlgPowerHave::InitOperation(void)
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

void ExcDlgPowerHave::DispExcDate()
{
	int x, y;
	char *ptr = NULL;

	DISPLAY_STRING(38, 45, m_AmrDisplay.gExcDate.active_power);
	DISPLAY_STRING(38, 65, m_AmrDisplay.gExcDate.a.power);
	DISPLAY_STRING(38, 81, m_AmrDisplay.gExcDate.b.power);
	DISPLAY_STRING(38, 97, m_AmrDisplay.gExcDate.c.power);


	DISPLAY_STRING(20, 125, m_AmrDisplay.m_ExcCapTime);	
}

void ExcDlgPowerHave::DoBtnUp(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerTotal;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();


}

void ExcDlgPowerHave::DoBtnDown(void)
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

void ExcDlgPowerHave::DoBtnLeft(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerTotal;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();

}

void ExcDlgPowerHave::DoBtnRight(void)
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

void ExcDlgPowerHave::DoBtnEnter(void)
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

void ExcDlgPowerHave::DoBtnCancel()
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

void ExcDlgPowerHave::DoTimer(void)
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



