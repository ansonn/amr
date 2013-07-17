/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgDate.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDlgSysSetting.h"
#include "AmrDisplay.h"


#define SET_MENU_BAKC	34
#define SET_MENU_APL	33

#define IP_SIZE		15
#define DATE_SIZE	10
#define TIME_SIZE	8


DigitalArrStru g_IpOptArr[IP_SIZE] = {
	{11 + 15, 30, ASCII16, '1', true}, {20 + 15, 30, ASCII16, '9', false},
	{29 + 15, 30, ASCII16, '2', false}, {38 + 15, 30, ASCII16, '.', false},

	{47 + 15, 30, ASCII16, '1', false},
	{56 + 15, 30, ASCII16, '6', false}, {65 + 15, 30, ASCII16, '8', false},
	{74 + 15, 30, ASCII16, '.', false},

	{83 + 15, 30, ASCII16, '0', false}, {92 + 15, 30, ASCII16, '0', false},
	{101 + 15, 30, ASCII16, '1', false}, {110 + 15, 30, ASCII16, '.', false},
	{119 + 15, 30, ASCII16, '0', false},
	{128 + 15, 30, ASCII16, '1', false}, {137 + 15, 30, ASCII16, '0', false},
};

DigitalArrStru g_DateOptArr[DATE_SIZE] = {
	{11 + 30, 60, ASCII16, '0', false}, {20 + 30, 60, ASCII16, '0', false},
	{29 + 30, 60, ASCII16, '0', false}, {38 + 30, 60, ASCII16, '0', false},

	{47 + 30, 60, ASCII16, '-', false},
	{56 + 30, 60, ASCII16, '0', false}, {65 + 30, 60, ASCII16, '0', false},
	{74 + 30, 60, ASCII16, '-', false},

	{83 + 30, 60, ASCII16, '0', false}, {92 + 30, 60, ASCII16, '0', false},
};

DigitalArrStru g_TimeOptArr[TIME_SIZE] = {
	{11 + 30, 90, ASCII16, '0', false}, {20 + 30, 90, ASCII16, '0', false},
	{29 + 30, 90, ASCII16, '-', false}, {38 + 30, 90, ASCII16, '0', false},

	{47 + 30, 90, ASCII16, '0', false},
	{56 + 30, 90, ASCII16, '-', false}, {65 + 30, 90, ASCII16, '0', false},
	{74 + 30, 90, ASCII16, '0', false},
};

AmrDlgSysSetting::AmrDlgSysSetting(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
				, MenuIdx(0)
{
	name = "AmrDlgSysSetting";


	InitDlg();
}

AmrDlgSysSetting::~AmrDlgSysSetting()
{
	
}

void AmrDlgSysSetting::InitDlg(void)
{
	ClearAll();

	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);

	DISPLAY_IP(0, 30, false);
	DISPLAY_RIQI(0, 60, false);
	DISPLAY_SHIJIAN(0, 90, false);

	DisplaySetAttr();

	DISPLAY_16x16_TUICHUI(128, 144, false);
	DISPLAY_YINGYIONG(90, 144, false);
}

void AmrDlgSysSetting::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	DISPLAY_16x16_TUICHUI(128, 144, false);
	DISPLAY_YINGYIONG(90, 144, false);

	SyncSysParam();
	DisplaySetAttr();
	MenuIdx = 0;
}

void AmrDlgSysSetting::SyncSysParam(void)
{
	int offset = 0;
	m_AmrDisplay.GetDateTime();
	m_AmrDisplay.GetLocalIp();


	offset = 0;
	for (int i = 0; i < IP_SIZE; i++)
	{
		SetMenuDispVal(i + offset, g_IpOptArr[i].val);	
	}

	offset = IP_SIZE;
	for (int i = 0; i < DATE_SIZE; i++)
	{
		SetMenuDispVal(i + offset, m_AmrDisplay.m_date[i]);	
		
	}

	offset = IP_SIZE + DATE_SIZE;
	for (int i = 0; i < TIME_SIZE; i++)
	{
		SetMenuDispVal(i + offset, m_AmrDisplay.m_time[i]);		
	}
	
	return;
}

void AmrDlgSysSetting::DisplaySetAttr(void)
{
	int i = 0;
	unsigned char buff[32] = {0};
	
	for (i = 0; i < 15; i++)
	{
		if (0 == g_IpOptArr[i].val)
			memset(buff, 0x00, sizeof(buff));
		else
		{
			char *cod = &g_IpOptArr[i].val;
			m_AmrDisplay.ZKDisplayConvert(cod , g_IpOptArr[i].type, buff);
		}
		SetZIFUAera(g_IpOptArr[i].x, g_IpOptArr[i].y, 
								ASCII16, buff, DISPLAY, g_IpOptArr[i].flg);
	}

	for (i = 0; i < 10; i++)
	{
		if (0 == g_DateOptArr[i].val)
			memset(buff, 0x00, sizeof(buff));
		else
		{
			char *cod = &g_DateOptArr[i].val;
			m_AmrDisplay.ZKDisplayConvert(cod , g_DateOptArr[i].type, buff);
		}
		SetZIFUAera(g_DateOptArr[i].x, g_DateOptArr[i].y, 
								ASCII16, buff, DISPLAY, g_DateOptArr[i].flg);
	}

	for (i = 0; i < 8; i++)
	{
		if (0 == g_TimeOptArr[i].val)
			memset(buff, 0x00, sizeof(buff));
		else
		{
			char *cod = &g_TimeOptArr[i].val;
			m_AmrDisplay.ZKDisplayConvert(cod , g_TimeOptArr[i].type, buff);
		}
		SetZIFUAera(g_TimeOptArr[i].x, g_TimeOptArr[i].y, 
								ASCII16, buff, DISPLAY, g_TimeOptArr[i].flg);
	}
}

void AmrDlgSysSetting::DoBtnUp(void)
{
	char val = GetMenuDispVal(MenuIdx);
	val++;

	if (val < '0')
		val = '9';
	else if (val > '9')
		val = '0';

	m_AmrDisplay.IdleCounter = 0;
	SetMenuDispVal(MenuIdx, val);		
}

void AmrDlgSysSetting::DoBtnDown(void)
{
	char val = GetMenuDispVal(MenuIdx);

	
	val--;

	if (val < '0')
		val = '9';
	else if (val > '9')
		val = '0';

	m_AmrDisplay.IdleCounter = 0;
	SetMenuDispVal(MenuIdx, val);	
}

void AmrDlgSysSetting::DoBtnLeft(void)
{
	unsigned char buff[32] = {0};

	m_AmrDisplay.IdleCounter = 0;
	
	switch (MenuIdx)
	{
		case SET_MENU_BAKC:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case SET_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, false);
			break;
		default:
		{
			if (MenuIdx >= 0 && MenuIdx < SET_MENU_APL)
				SetMenuDispFlg(MenuIdx, false);
		}
	}

	MenuIdx--;
	while (1)
	{
		char val = GetMenuDispVal(MenuIdx);
		if (val == '.' || val == '-' || val == 0 || val == ':')
			MenuIdx--;
		else
			break;
	}
	if (MenuIdx < 0)
		MenuIdx = SET_MENU_BAKC;

	switch (MenuIdx)
	{
		case SET_MENU_BAKC:
			DISPLAY_16x16_TUICHUI(128, 144, true);
			break;

		case SET_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, true);
			break;
	}

}

void AmrDlgSysSetting::DoBtnRight(void)
{
	unsigned char buff[32] = {0};

	m_AmrDisplay.IdleCounter = 0;
	
	switch (MenuIdx)
	{
		case SET_MENU_BAKC:
			DISPLAY_16x16_TUICHUI(128, 144, false);
			break;

		case SET_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, false);
			break;
		default:
		{
			if (MenuIdx >= 0 && MenuIdx < SET_MENU_APL)
				SetMenuDispFlg(MenuIdx, false);
		}
	}

	MenuIdx++;
	while (1)
	{
		char val = GetMenuDispVal(MenuIdx);
		//std::cout << val << '.' << '-' << std::endl;
		if (val == '.' || val == '-' || val == 0 || val == ':')
			MenuIdx++;
		else
			break;
	}
	if (MenuIdx > SET_MENU_BAKC)
		MenuIdx = 0;

	switch (MenuIdx)
	{
		case SET_MENU_BAKC:
			DISPLAY_16x16_TUICHUI(128, 144, true);
			break;

		case SET_MENU_APL:
			DISPLAY_YINGYIONG(90, 144, true);
			break;
	}

}

int AmrDlgSysSetting::DoConfig(void)
{
	int flg = 0;
	int j = 0;

	memset(m_AmrDisplay.ipaddr, 0x00, sizeof(m_AmrDisplay.ipaddr));
	for (int i = 0; i < IP_SIZE; i++)
	{
		if ('.' == g_IpOptArr[i].val)
		{
			flg = 0;
			m_AmrDisplay.ipaddr[j++] = g_IpOptArr[i].val;
			continue;
		}

		
		if ('0' == g_IpOptArr[i].val)
		{
			if (flg == 0)
				continue;
			m_AmrDisplay.ipaddr[j++] = g_IpOptArr[i].val;
		}
		else
		{
			m_AmrDisplay.ipaddr[j++] = g_IpOptArr[i].val;
			flg = 1;
		}
	}

	for (int i = 0; i < DATE_SIZE; i++)
	{
		if (0 == g_DateOptArr[i].val)
			break;

		m_AmrDisplay.m_date[i] = g_DateOptArr[i].val;
	}

	for (int i = 0; i < TIME_SIZE; i++)
	{
		if (0 == g_TimeOptArr[i].val)
			break;

		m_AmrDisplay.m_time[i] = g_TimeOptArr[i].val;
	}

	fprintf(stderr, "IP = %s\n", m_AmrDisplay.ipaddr);
	fprintf(stderr, "Date = %s\n", m_AmrDisplay.m_date);
	fprintf(stderr, "TIME = %s\n", m_AmrDisplay.m_time);
	m_AmrDisplay.SetDateTime();
	m_AmrDisplay.SetLocalIp();

	return 0;
}

void AmrDlgSysSetting::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;

	if (m_AmrDisplay.GetMode() == exc_mode)
		m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgMain;
	else
		m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	

}

void AmrDlgSysSetting::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;
	
	if (SET_MENU_BAKC == MenuIdx || SET_MENU_APL == MenuIdx)
	{
		if (MenuIdx == SET_MENU_APL)
		{
			if (DoConfig())
				return;
		}
	
		if (m_AmrDisplay.GetMode() == exc_mode)
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_ExcDlgMain;
		else
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgMain;
		m_AmrDisplay.CurDlg->InitOperation();
		m_AmrDisplay.CurDlg->ShowDlg();
	}
}

bool AmrDlgSysSetting::GetMenuDispFlg(int Index)
{
	DigitalArrStru *p = NULL;
	int idx = 0;
	
	if (Index >= 0 && Index < IP_SIZE)
	{
		p = g_IpOptArr;
		idx = Index;
	}
	else if (Index >= IP_SIZE && Index < DATE_SIZE + IP_SIZE)
	{
		p = g_DateOptArr;
		idx = Index - IP_SIZE;
	}
	else if (Index >= IP_SIZE + DATE_SIZE && Index < SET_MENU_APL)
	{
		p = g_TimeOptArr;
		idx = Index - IP_SIZE - DATE_SIZE;
	}
	else
		idx = -1;

	if (idx != -1)
	{
		return p[idx].flg;
	}

	return false;
}


char AmrDlgSysSetting::GetMenuDispVal(int Index)
{
	DigitalArrStru *p = NULL;
	int idx = 0;
	
	if (Index >= 0 && Index < IP_SIZE)
	{
		p = g_IpOptArr;
		idx = Index;
	}
	else if (Index >= IP_SIZE && Index < DATE_SIZE + IP_SIZE)
	{
		p = g_DateOptArr;
		idx = Index - IP_SIZE;
	}
	else if (Index >= IP_SIZE + DATE_SIZE && Index < SET_MENU_APL)
	{
		p = g_TimeOptArr;
		idx = Index - IP_SIZE - DATE_SIZE;
	}
	else
		idx = -1;

	if (idx != -1)
	{
		return p[idx].val;
	}

	return -1;
}

void AmrDlgSysSetting::SetMenuDispVal(int Index, char val)
{
	DigitalArrStru *p = NULL;
	int idx = 0;

	if (Index >= 0 && Index < IP_SIZE)
	{
		p = g_IpOptArr;
		idx = Index;
	}
	else if (Index >= IP_SIZE && Index < DATE_SIZE + IP_SIZE)
	{
		p = g_DateOptArr;
		idx = Index - IP_SIZE;
	}
	else if (Index >= IP_SIZE + DATE_SIZE && Index < SET_MENU_APL)
	{
		p = g_TimeOptArr;
		idx = Index - IP_SIZE - DATE_SIZE;
	}
	else
	{
		idx = -1;
	}

	if (idx != -1)
	{
		p[idx].val = val;
	}

	return;
}


void AmrDlgSysSetting::SetMenuDispFlg(int Index, bool flag)
{
	DigitalArrStru *p = NULL;
	unsigned char buff[32] = {0};
	char *cod = NULL;
	int idx = 0;
	
	if (Index >= 0 && Index < IP_SIZE)
	{
		p = g_IpOptArr;
		idx = Index;
	}
	else if (Index >= IP_SIZE && Index < DATE_SIZE + IP_SIZE)
	{
		p = g_DateOptArr;
		idx = Index - IP_SIZE;
	}
	else if (Index >= IP_SIZE + DATE_SIZE && Index < SET_MENU_APL)
	{
		p = g_TimeOptArr;
		idx = Index - IP_SIZE - DATE_SIZE;
	}
	else
		idx = -1;

	if (idx != -1)
	{
		p[idx].flg = flag;

		
		if (0 == p[idx].val)
			memset(buff, 0x00, 32);
		else
		{
			cod = &p[idx].val;
			m_AmrDisplay.ZKDisplayConvert(cod , p[idx].type, buff);
		}

		SetZIFUAera(p[idx].x, p[idx].y, 
								ASCII16, buff, DISPLAY, p[idx].flg);	
	}

	return;
}

void AmrDlgSysSetting::DoTimer(void)
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

	
	if (m_AmrDisplay.AmrTick%3 == 0)
	{
		if (MenuIdx >= 0 && MenuIdx < SET_MENU_APL)
		{
			bool flag = GetMenuDispFlg(MenuIdx);
			if (flag)
				flag = false;
			else
				flag = true;

			SetMenuDispFlg(MenuIdx, flag);
		}
	}

	
	m_AmrDisplay.CurDlg->ShowDlg();
	m_AmrDisplay.AmrTick++;
}

