/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgMain.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/
#include "AmrDisplay.h"
#include "AmrDlgMain.h"



AmrDlgMain::AmrDlgMain(AmrDisplay &rAmrDisplay, unsigned int fd) 
				: m_AmrDisplay(rAmrDisplay)
				, AmrDlgBase(fd)
{
	name = "AmrDlgMain";

	/* ���캯���У���ʼ����ǰҳ�浽�Դ� */
	InitDlg();
}

AmrDlgMain::~AmrDlgMain()
{

}

void AmrDlgMain::SetTurnOff(int MenuIndex, bool flg)
{
	switch (MenuIndex)
	{
		case MENU_1:
			DISPLAY_16x16_JIBENXINXI(40, 20, flg);
			break;
		case MENU_2:
			DISPLAY_16x16_RILIXINXI(40, 40, flg);
			break;
		case MENU_3:
			DISPLAY_16x16_TIAOSHIZHISHIDENG(40, 60, flg);
			break;
		case MENU_4:
			DISPLAY_16x16_XITONGSHEZHI(40, 80, flg);
			break;
		case MENU_5:
			DISPLAY_16x16_DIANBIAOKONGZHI(40, 100, flg);
			break;
		case MENU_EXIT:
			DISPLAY_16x16_TUICHUI(128, 144, flg);
			break;
	}
}

/* init Dlg */
void AmrDlgMain::InitDlg(void)
{
	ClearAll();

	SetMemAera(0, 0, LOONGSON_LOGO16X16_8BIT, DISPLAY, false);
	SetMemAera(128, 0, GPS_16X32_8BIT, DISPLAY, false);
	
	MenuIndex = MENU_1;
	DISPLAY_16x16_JIBENXINXI(40, 20, true);
	DISPLAY_16x16_RILIXINXI(40, 40, false);
	DISPLAY_16x16_TIAOSHIZHISHIDENG(40, 60, false);
	DISPLAY_16x16_XITONGSHEZHI(40, 80, false);
	DISPLAY_16x16_DIANBIAOKONGZHI(40, 100, false);
	DISPLAY_16x16_TUICHUI(128, 144, false);
	
	//DISPLAY_8x16_LOONGSON(96, 144, false);
	return;
}

/*---------------------------------------------------------------------------*/
/*	�ú��������������л�����ǰ�����ʱ����ã�������һЩ��Ҫ�ĳ�ʼ��
*/
void AmrDlgMain::InitOperation(void)
{
	if (SIGNAL4_16x16_8bit == m_AmrDisplay.SignalValue)
		SetMemAera(144, 0, SIGNAL4_16x16_8bit, DISPLAY, false);
	else
		SetMemAera(144, 0, SIGNAL3_16x16_8bit, DISPLAY, false);

	SetTurnOff(MenuIndex, false);
	MenuIndex = 0;
	SetTurnOff(MenuIndex, true);
}

/*---------------------------------------------------------------------------*/
/*	up������
*/
void AmrDlgMain::DoBtnUp(void)
{
	/* �����IDLE���� */
	m_AmrDisplay.IdleCounter = 0;

	/* ȡ������ǰ�˵��б���Ĳ��촦�� */
	SetTurnOff(MenuIndex, false);

	/* ���������˵��б��� */
	MenuIndex--;
	if (MenuIndex < MENU_1)
		MenuIndex = MENU_EXIT;

	/* ����������Ĳ˵��б��� */
	SetTurnOff(MenuIndex, true);
	/* ��ʾ��ǰҳ�� */
	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgMain::DoBtnDown(void)
{
	m_AmrDisplay.IdleCounter = 0;

	SetTurnOff(MenuIndex, false);

	MenuIndex++;
	if (MenuIndex >= MENU_MAX )
		MenuIndex = MENU_1;

	SetTurnOff(MenuIndex, true);

	m_AmrDisplay.CurDlg->ShowDlg();
}

void AmrDlgMain::DoBtnLeft(void)
{
	m_AmrDisplay.IdleCounter = 0;
	DoBtnUp();
}

void AmrDlgMain::DoBtnRight(void)
{
	m_AmrDisplay.IdleCounter = 0;
	DoBtnDown();
}

/*--------------------------------------------------------------------------*/
/*	ȡ����������ǰ��ҳ���ȡ�����������˵�ҳ���ǹ̶���m_DlgWelcome
*/
void AmrDlgMain::DoBtnCancel(void)
{
	m_AmrDisplay.IdleCounter = 0;

	m_AmrDisplay.CurDlg = &m_AmrDisplay.m_DlgWelcome;
	m_AmrDisplay.CurDlg->InitOperation();
	m_AmrDisplay.CurDlg->ShowDlg();	
}

/*---------------------------------------------------------------------------*/
/*	Enter����
**		���ݵ�ǰ�˵��б�����������л�����Ӧ��ҳ��
*/
void AmrDlgMain::DoBtnEnter(void)
{
	m_AmrDisplay.IdleCounter = 0;

	switch (MenuIndex)
	{
		case MENU_EXIT:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_DlgWelcome;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
		case MENU_1:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgDevInfo;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
		case MENU_2:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgDate;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
		case MENU_3:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgLedCtrl;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();
			break;
		case MENU_4:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgSysSetting;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();	
			break;
		case MENU_5:
			m_AmrDisplay.CurDlg = &m_AmrDisplay.m_AmrDlgUartCtrl;
			m_AmrDisplay.CurDlg->InitOperation();
			m_AmrDisplay.CurDlg->ShowDlg();	
	}
		
}

/*---------------------------------------------------------------------------*/
/*	�����ҳ��Ϊ��ǰҳ��! ��main.cpp�е�AmrTimer�߳��У��ᰴ�չ̶�������ʱ��
**	���øú�����
*/
void AmrDlgMain::DoTimer(void)
{

	/* ���ݹ̶���ʱ����, �л�GPRS���ź�ǿ�ȣ�ģ���ź�ǿ�ȵ�������� */
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
		m_AmrDisplay.CurDlg->ShowDlg();
	}
	

	m_AmrDisplay.AmrTick++;
}


