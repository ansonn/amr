/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgWelcome.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "AmrDlgWelcome.h"


/*----------------------------------------------------------------------------*/


AmrDlgWelcome::AmrDlgWelcome(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
				, x_pos(0)
				, y_pos(0)
{
	name = "AmrDlgWelcome";
	dev_fd = fd;
	InitDlg();
}

AmrDlgWelcome::~AmrDlgWelcome()
{

}

/* init Dlg */
void AmrDlgWelcome::InitDlg(void)
{
	int i = 0;
	//unsigned char str[1] = { 'L' };
	unsigned char buff[32] = {0};

	ClearAll();

	//logo
	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(10, 40, LOONGSON_LOGO32X32_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);
#if 0	// title
	m_AmrDisplay.ZKDisplayConvert((char *)"L" , ASCII12, buff);
	SetZIFUAera(50, 10, ASCII12, buff, DISPLAY, false);
#else

	DISPLAY_16x16_BEIJINGSHENZHOULONGXIN(50, 40, false);
	//DISPLAY_8x16_LOONGSON(96, 144, false);
	DISPLAY_16x16_DIANLIJIZHONGKONGZHIQI(25, 78, false);

	x_pos = 0;
	y_pos = 144;
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);

#endif
	return;
}

void AmrDlgWelcome::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	LightCount = 0;
}


void AmrDlgWelcome::DoBtnUp(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);
		LightCount = 0;
	}

	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
	y_pos--;
	if (y_pos < 60)
		y_pos = 60;
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
}

void AmrDlgWelcome::DoBtnDown(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
	y_pos++;
	if (y_pos > 144)
		y_pos = 144;
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
}

void AmrDlgWelcome::DoBtnLeft(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
	x_pos--;
	if (x_pos < 0)
		x_pos = 0;
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
}

void AmrDlgWelcome::DoBtnRight(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);
		LightCount = 0;
	}
	
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
	x_pos++;
	if (x_pos > 80)
		x_pos = 80;
	SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);

}

void AmrDlgWelcome::DoBtnEnter(void)
{
	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKLIGHT, NULL);

		LightCount = 0;
	}
	
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgWelcome::DoBtnCancel()
{
	ioctl(dev_fd, AMRDISPLAY_BACKCLEAR, NULL);
	LightCount = 200;
}

void AmrDlgWelcome::DoTimer(void)
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
			SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);
			m_AmrDisplay.SignalValue = SIGNAL3_16x16_8bit;
		}
		else
		{
			SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
			m_AmrDisplay.SignalValue = SIGNAL4_16x16_8bit;
		}
	}


	if (m_AmrDisplay.AmrTick%2)
		SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
	else
	{
		SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
	}


	if (LightCount >= 200)
	{
		ioctl(dev_fd, AMRDISPLAY_BACKCLEAR, NULL);
	}
	else
		LightCount++;

	
	
	m_AmrDisplay.AmrTick++;
	m_AmrDisplay.CurDlg->ShowDlg();
}



