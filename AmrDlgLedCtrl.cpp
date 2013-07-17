/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgLedCtrl.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "AmrDlgLedCtrl.h"

/* 仅作为映射使用 */
const char *g_Table[10] = {"0", "1", "2", "3", "4","5", "6", "7", "8", "9"};


/* 该数组表示当前页面中显示配置时间的菜单项状态 */
DigitalArrStru g_DigitalOptArr[12] = {
	{21 + 72, 30, ASCII16, 0, true}, {30 + 72, 30, ASCII16, 0, false},
	{39 + 72, 30, ASCII16, 0, false}, {48 + 72, 30, ASCII16, 0, false},

	{21 + 72, 55, ASCII16, 0, false}, {30 + 72, 55, ASCII16, 0, false},
	{39 + 72, 55, ASCII16, 0, false}, {48 + 72, 55, ASCII16, 0, false},

	{21 + 72, 80, ASCII16, 0, false}, {30 + 72, 80, ASCII16, 0, false},
	{39 + 72, 80, ASCII16, 0, false}, {48 + 72, 80, ASCII16, 0, false},
};

/*---------------------------------------------------------------------------*/
/*	构造函数，初始化页面，并打开LED设备
*/
AmrDlgLedCtrl::AmrDlgLedCtrl(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
{
	name = "AmrDlgLedCtrl";
	InitDlg();

	amrleds_fd = open(LEDSCTRL_DEV, O_RDWR);
	if (amrleds_fd < 0)
	{
		std::cout << "open " << LEDSCTRL_DEV << " failed" << std::endl;
		exit(1);
	}
}

AmrDlgLedCtrl::~AmrDlgLedCtrl()
{

}


/*---------------------------------------------------------------------------*/
/*	运行LED；
**		1、首先从页面配置菜单中提取LED运行的时间参数
**		2、调用底层接口
*/
void AmrDlgLedCtrl::RunLed(void)
{
	int ret = 0;

	Time_On = 0;
	Time_On += g_DigitalOptArr[0].val *1000;
	Time_On += g_DigitalOptArr[1].val *100;
	Time_On += g_DigitalOptArr[2].val *10;
	Time_On += g_DigitalOptArr[3].val;

	Time_Off = 0;
	Time_Off += g_DigitalOptArr[4].val *1000;
	Time_Off += g_DigitalOptArr[5].val *100;
	Time_Off += g_DigitalOptArr[6].val *10;
	Time_Off += g_DigitalOptArr[7].val;	

	Time_all = 0;
	Time_all += g_DigitalOptArr[8].val *1000;
	Time_all += g_DigitalOptArr[9].val *100;
	Time_all += g_DigitalOptArr[10].val *10;
	Time_all += g_DigitalOptArr[11].val;


	std::cout << Time_On << " "
		      << Time_Off << " "
		      << Time_all << " " << std::endl;

	struct amr_ledsctrl_param param;
	param.on_time 	= Time_On;
	param.off_time 	= Time_Off;
	param.run_time 	= Time_all*1000;
	param.led_index = ALM_LED_PIN;

	ioctl(amrleds_fd, AMR_LED_STOP , &param);
	ret = ioctl(amrleds_fd, AMR_LED_RUN , &param);
	if (ret)
	{
		std::cout << "ioctl AMR_LED_RUN Failed!" << std::endl;
	}
}

/*---------------------------------------------------------------------------*/
/*	页面初始化；所有的页面都按照同样的结构设计的
*/
void AmrDlgLedCtrl::InitDlg(void)
{
	ClearAll();

	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);

	DISPLAY_DIANLIANGSHIJIAN(20, 30, false);
	DISPLAY_XIMIESHIJIAN(20, 55, false);
	DISPLAY_CHIXUSHIJIAN(20, 80, false);

	DisplayDigaital();

	DISPLAY_16x16_TUICHUI(128, 144, false);
	DISPLAY_YINGYIONG(90, 144, false);
	
	x_pos = 0;
	y_pos = 144;
	//SetMemAera(x_pos, y_pos, ROUND_LOGO16X16_8BIT, DISPLAY, false);
	MenuIdx = LED_MENU_0;
}

/*---------------------------------------------------------------------------*/
/*	且换到该页面的时候调用该函数，做必要的操作
*/
void AmrDlgLedCtrl::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	DISPLAY_16x16_TUICHUI(128, 144, false);
	DISPLAY_YINGYIONG(90, 144, false);

	MenuIdx = LED_MENU_0;
}

/*---------------------------------------------------------------------------*/
/*	根据g_DigitalOptArr数据，显示时间配置信息
*/
void AmrDlgLedCtrl::DisplayDigaital(void)
{
	int i = 0;
	unsigned char buff[32] = {0};
	
	for (i = 0; i < 12; i++)
	{
		m_AmrDisplay.ZKDisplayConvert((char *)g_Table[g_DigitalOptArr[i].val] , 
												g_DigitalOptArr[i].type, buff);
		SetZIFUAera(g_DigitalOptArr[i].x, g_DigitalOptArr[i].y, 
								ASCII16, buff, DISPLAY, g_DigitalOptArr[i].flg);
	}
}

void AmrDlgLedCtrl::DoBtnUp(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (MenuIdx >= 0 && MenuIdx <= LED_MENU_11)
	{
		g_DigitalOptArr[MenuIdx].val++;
		if (g_DigitalOptArr[MenuIdx].val >= 10)
			g_DigitalOptArr[MenuIdx].val = 0;
	}
}

void AmrDlgLedCtrl::DoBtnDown(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (MenuIdx >= 0 && MenuIdx <= LED_MENU_11)
	{
		g_DigitalOptArr[MenuIdx].val--;
		if (g_DigitalOptArr[MenuIdx].val < 0)
			g_DigitalOptArr[MenuIdx].val = 9;	
	}
}

void AmrDlgLedCtrl::DoBtnLeft(void)
{
	m_AmrDisplay.IdleCounter = 0;

	unsigned char buff[32] = {0};
	switch (MenuIdx)
	{
		case LED_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case LED_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, false);
			break;
		default:
			g_DigitalOptArr[MenuIdx].flg = false;
			m_AmrDisplay.ZKDisplayConvert(
								(char *)g_Table[g_DigitalOptArr[MenuIdx].val] , 
										g_DigitalOptArr[MenuIdx].type, buff);
			SetZIFUAera(g_DigitalOptArr[MenuIdx].x, g_DigitalOptArr[MenuIdx].y, 
								ASCII16, buff, DISPLAY, g_DigitalOptArr[MenuIdx].flg);
			break;
	}
	
	MenuIdx--;

	if (MenuIdx < 0)
		MenuIdx = LED_MENU_BACK;

	switch (MenuIdx)
	{
		case LED_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, true);
			break;

		case LED_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, true);
			break;
		default:
			g_DigitalOptArr[MenuIdx].flg = true;
			m_AmrDisplay.ZKDisplayConvert(
								(char *)g_Table[g_DigitalOptArr[MenuIdx].val] , 
										g_DigitalOptArr[MenuIdx].type, buff);
			SetZIFUAera(g_DigitalOptArr[MenuIdx].x, g_DigitalOptArr[MenuIdx].y, 
								ASCII16, buff, DISPLAY, g_DigitalOptArr[MenuIdx].flg);
			break;
	}


}

void AmrDlgLedCtrl::DoBtnRight(void)
{
	m_AmrDisplay.IdleCounter = 0;

	unsigned char buff[32] = {0};
	switch (MenuIdx)
	{
		case LED_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case LED_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, false);
			break;
		default:
			g_DigitalOptArr[MenuIdx].flg = false;
			m_AmrDisplay.ZKDisplayConvert(
								(char *)g_Table[g_DigitalOptArr[MenuIdx].val] , 
										g_DigitalOptArr[MenuIdx].type, buff);
			SetZIFUAera(g_DigitalOptArr[MenuIdx].x, g_DigitalOptArr[MenuIdx].y, 
								ASCII16, buff, DISPLAY, g_DigitalOptArr[MenuIdx].flg);
			break;
	}
	
	MenuIdx++;

	if (MenuIdx >= LED_MENU_BUTT)
		MenuIdx = LED_MENU_0;

	switch (MenuIdx)
	{
		case LED_MENU_BACK:
			DISPLAY_16x16_TUICHUI(128, 144, true);
			break;

		case LED_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, true);
			break;
		default:
			g_DigitalOptArr[MenuIdx].flg = true;
			m_AmrDisplay.ZKDisplayConvert(
								(char *)g_Table[g_DigitalOptArr[MenuIdx].val] , 
										g_DigitalOptArr[MenuIdx].type, buff);
			SetZIFUAera(g_DigitalOptArr[MenuIdx].x, g_DigitalOptArr[MenuIdx].y, 
								ASCII16, buff, DISPLAY, g_DigitalOptArr[MenuIdx].flg);
			break;
	}

}

void AmrDlgLedCtrl::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;

	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

void AmrDlgLedCtrl::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (LED_MENU_BACK == MenuIdx || LED_MENU_APL == MenuIdx)
	{
		if (MenuIdx == LED_MENU_APL)
		{
			RunLed();
		}
		else
		{
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
		}
	}
}


/*---------------------------------------------------------------------------*/
void AmrDlgLedCtrl::DoTimer(void)
{

	/* 模拟GPRS信号强度变化 */
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

	/* 处理跳变的圆圈 */
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

	/* 处理当前选中的菜单动态特性 */
	if (m_AmrDisplay.AmrTick%3 == 0)
	{
		if (MenuIdx >= 0 && MenuIdx <= LED_MENU_11)
		{
			unsigned char buff[32] = {0};
			if (g_DigitalOptArr[MenuIdx].flg)
				g_DigitalOptArr[MenuIdx].flg = false;
			else
				g_DigitalOptArr[MenuIdx].flg = true;
			
			m_AmrDisplay.ZKDisplayConvert((char *)g_Table[g_DigitalOptArr[MenuIdx].val] , 
												g_DigitalOptArr[MenuIdx].type, buff);
			SetZIFUAera(g_DigitalOptArr[MenuIdx].x, g_DigitalOptArr[MenuIdx].y, 
								ASCII16, buff, DISPLAY, g_DigitalOptArr[MenuIdx].flg);
		}
	}

	/* 以上操作都建立在缓存上，最后调用ShowDlg刷到EMI屏上 */
	m_AmrDisplay.CurDlg->ShowDlg();
	m_AmrDisplay.AmrTick++;
}

