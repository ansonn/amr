/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- ExcDlgTelemetry.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "ExcDlgTelemetry.h"


/*----------------------------------------------------------------------------*/


ExcDlgTelemetry::ExcDlgTelemetry(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
				, x_pos(0)
				, y_pos(0)
{
	name = "ExcDlgTelemetry";
	dev_fd = fd;
	InitDlg();
}

ExcDlgTelemetry::~ExcDlgTelemetry()
{

}

/* init Dlg */
void ExcDlgTelemetry::InitDlg(void)
{
	int i = 0;
	//unsigned char str[1] = { 'L' };
	unsigned char buff[32] = {0};

	ClearAll();

	SetMemAera(16, 0, GPS_16X32_8BIT, DISPLAY, false);
	DISPLAY_YAOCELIANG(55, 25, false);

	SetRectangle(0, 18, 160, 2, false);
	SetRectangle(0, 142, 160, 2, false);
	SetRectangle(138, 147, 16, 8, false);
	SetRectangle(136, 149, 2, 4, false);
	//DISPLAY_8x16_SR(64, 2, false);

	DISPLAY_8x16_UA(0, 50, false);
	DISPLAY_8x16_V(70, 50, false);
	DISPLAY_8x16_IA(88, 50, false);
	DISPLAY_8x16_A(152, 50, false);
	DISPLAY_8x16_UB(0, 70, false);
	DISPLAY_8x16_V(70, 70, false);
	DISPLAY_8x16_IB(88, 70, false);
	DISPLAY_8x16_A(152, 70, false);
	DISPLAY_8x16_UC(0, 90, false);
	DISPLAY_8x16_V(70, 90, false);
	DISPLAY_8x16_IC(88, 90, false);
	DISPLAY_8x16_A(152, 90, false);

#if 0	// title
	m_AmrDisplay.ZKDisplayConvert((char *)"L" , ASCII12, buff);
	SetZIFUAera(50, 10, ASCII12, buff, DISPLAY, false);
#else
	//DISPLAY_16x16_YOUGONGGONGLV(0, 80, false);
	DISPLAY_8x16_000000000210(0, 144, false);

	//DISPLAY_CAIJISHIJIAN(60, 105, false);
	DisplayTime(120, 2);

#endif
	return;
}

void ExcDlgTelemetry::DisplayTime(int x, int y)
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

void ExcDlgTelemetry::InitOperation(void)
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

void ExcDlgTelemetry::DispExcDate()
{
	int x, y;
	char *ptr = NULL;

	DISPLAY_STRING(25, 50, m_AmrDisplay.gExcDate.a.volt);
	DISPLAY_STRING(113, 50, m_AmrDisplay.gExcDate.a.curr);
	DISPLAY_STRING(25, 70, m_AmrDisplay.gExcDate.b.volt);
	DISPLAY_STRING(113, 70, m_AmrDisplay.gExcDate.b.curr);
	DISPLAY_STRING(25, 90, m_AmrDisplay.gExcDate.c.volt);
	DISPLAY_STRING(113, 90, m_AmrDisplay.gExcDate.c.curr);	

	DISPLAY_STRING(20, 125, m_AmrDisplay.m_ExcCapTime);	
}

void ExcDlgTelemetry::DoBtnUp(void)
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

void ExcDlgTelemetry::DoBtnDown(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerHave;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void ExcDlgTelemetry::DoBtnLeft(void)
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

void ExcDlgTelemetry::DoBtnRight(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgPowerHave;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void ExcDlgTelemetry::DoBtnEnter(void)
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

void ExcDlgTelemetry::DoBtnCancel()
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

void ExcDlgTelemetry::DoTimer(void)
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

