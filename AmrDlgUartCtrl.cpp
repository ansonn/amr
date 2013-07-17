/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgLedCtrl.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "AmrDlgUartCtrl.h"

extern int UartFd;


AmrDlgUartCtrl::AmrDlgUartCtrl(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
{
	int ret;

	name = "AmrDlgUartCtrl";
	InitDlg();

	MenuClearFlg[0] = false;
	MenuClearFlg[1] = false;
	MenuClearFlg[2] = false;
	MenuClearFlg[3] = false;

}

AmrDlgUartCtrl::~AmrDlgUartCtrl()
{

}



void AmrDlgUartCtrl::InitDlg(void)
{
	ClearAll();

	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);

	DISPLAY_BIAOYIDIANLIANG(0, 30, false);
	DISPLAY_QINGLING(128, 30, false);
	DISPLAY_BIAOERDIANLIANG(0, 50, false);
	DISPLAY_QINGLING(128, 50, false);
	DISPLAY_BIAOSANDIANLIANG(0, 70, false);
	DISPLAY_QINGLING(128, 70, false);
	DISPLAY_BIAOSIDIANLIANG(0, 90, false);
	DISPLAY_QINGLING(128, 90, false);

	

	//DisplayDigaital();

	DISPLAY_16x16_TUICHUI(128, 144, false);
	//DISPLAY_YINGYIONG(90, 144, false);
	
	x_pos = 0;
	y_pos = 144;
	
	MenuIdx = UART_MENU_0;
}


void AmrDlgUartCtrl::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	DISPLAY_16x16_TUICHUI(128, 144, false);

	switch (MenuIdx)
	{
		case UART_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case UART_MENU_0:	
			DISPLAY_QINGLING(128, 30, false);
			break;
		case UART_MENU_1:
			DISPLAY_QINGLING(128, 50, false);
			break;
		case UART_MENU_2:
			DISPLAY_QINGLING(128, 70, false);
			break;
		case UART_MENU_3:
			DISPLAY_QINGLING(128, 90, false);
			break;
	}

	DISPLAY_QINGLING(128, 30, true);
	MenuIdx = UART_MENU_0;
}



void AmrDlgUartCtrl::DoBtnUp(void)
{
	DoBtnLeft();
}

void AmrDlgUartCtrl::DoBtnDown(void)
{
	m_AmrDisplay.IdleCounter = 0;
	
	DoBtnRight();
}

void AmrDlgUartCtrl::DoBtnLeft(void)
{
	unsigned char buff[32] = {0};

	m_AmrDisplay.IdleCounter = 0;
	
	switch (MenuIdx)
	{
		case UART_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case UART_MENU_0:	
			DISPLAY_QINGLING(128, 30, false);
			break;
		case UART_MENU_1:
			DISPLAY_QINGLING(128, 50, false);
			break;
		case UART_MENU_2:
			DISPLAY_QINGLING(128, 70, false);
			break;
		case UART_MENU_3:
			DISPLAY_QINGLING(128, 90, false);
			break;
	}
	
	MenuIdx--;

	if (MenuIdx < 0)
		MenuIdx = UART_MENU_BACK;

	switch (MenuIdx)
	{
		case UART_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, true);
			break;
		case UART_MENU_0:	
			DISPLAY_QINGLING(128, 30, true);
			break;
		case UART_MENU_1:
			DISPLAY_QINGLING(128, 50, true);
			break;
		case UART_MENU_2:
			DISPLAY_QINGLING(128, 70, true);
			break;
		case UART_MENU_3:
			DISPLAY_QINGLING(128, 90, true);
			break;
	}


}

void AmrDlgUartCtrl::DoBtnRight(void)
{
	unsigned char buff[32] = {0};

	m_AmrDisplay.IdleCounter = 0;
	
	switch (MenuIdx)
	{
		case UART_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case UART_MENU_0:	
			DISPLAY_QINGLING(128, 30, false);
			break;
		case UART_MENU_1:
			DISPLAY_QINGLING(128, 50, false);
			break;
		case UART_MENU_2:
			DISPLAY_QINGLING(128, 70, false);
			break;
		case UART_MENU_3:
			DISPLAY_QINGLING(128, 90, false);
			break;
	}
	
	MenuIdx++;

	if (MenuIdx >= UART_MENU_BUTT)
		MenuIdx = UART_MENU_0;

	switch (MenuIdx)
	{
		case UART_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, true);
			break;
		case UART_MENU_0:	
			DISPLAY_QINGLING(128, 30, true);
			break;
		case UART_MENU_1:
			DISPLAY_QINGLING(128, 50, true);
			break;
		case UART_MENU_2:
			DISPLAY_QINGLING(128, 70, true);
			break;
		case UART_MENU_3:
			DISPLAY_QINGLING(128, 90, true);
			break;
	}

}

void AmrDlgUartCtrl::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;

	switch (MenuIdx)
	{
		case UART_MENU_BACK:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
		case UART_MENU_0:	
			m_AmrDisplay.AmrData[0] = 0;
			break;
		case UART_MENU_1:
			m_AmrDisplay.AmrData[1] = 0;
			break;
		case UART_MENU_2:
			m_AmrDisplay.AmrData[2] = 0;
			break;
		case UART_MENU_3:
			m_AmrDisplay.AmrData[3] = 0;			
			break;
	}
	UpdateCurrentValue();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void AmrDlgUartCtrl::UpdateCurrentValue(void)
{
	char buffer[32];


	memset(buffer, 0x00, sizeof(buffer));
	sprintf(buffer, "%05d", m_AmrDisplay.AmrData[0]);
	DISPLAY_STRING(72, 30, buffer);

	memset(buffer, 0x00, sizeof(buffer));
	sprintf(buffer, "%05d", m_AmrDisplay.AmrData[1]);
	DISPLAY_STRING(72, 50, buffer);

	memset(buffer, 0x00, sizeof(buffer));
	sprintf(buffer, "%05d", m_AmrDisplay.AmrData[2]);
	DISPLAY_STRING(72, 70, buffer);

	memset(buffer, 0x00, sizeof(buffer));
	sprintf(buffer, "%05d", m_AmrDisplay.AmrData[3]);
	DISPLAY_STRING(72, 90, buffer);
}

void AmrDlgUartCtrl::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;
	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}


void AmrDlgUartCtrl::DoTimer(void)
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
			x_pos %= 70;
			SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
			RoundDisp = true;
		}
		else
		{
			RoundDisp = false;
			SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, CLEAR, false);
		}
	}

	if (m_AmrDisplay.AmrTick%3 == 0)
	{
		UpdateCurrentValue();
	}
	
	m_AmrDisplay.CurDlg->ShowDlg();
	m_AmrDisplay.AmrTick++;
}

