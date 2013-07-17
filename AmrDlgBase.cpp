/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgBase.cc
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#include "AmrDlgBase.h"


/*---------------------------------------------------------------------------*/
/*	一下为转换好的点阵数据
*/
unsigned char LoongsonLogo32x32_8bit[] = {
	0xFF,0xFF,0xFF,0xFF,0xFF,0xFC,0x00,0x01,0xFF,0xE0,0x00,0x03,0xFF,0x00,0x00,
	0x0F,0xFC,0x00,0x00,0xFF,0xE0,0x00,0x03,0xFF,0x80,0x00,0x1F,0xF1,0x80,0x00,
	0xFF,0xC1,0x80,0x03,0xFE,0x01,0x80,0x1F,0xF0,0x01,0xC0,0xFF,0xC0,0x03,0xE7,
	0xFE,0x00,0x07,0xFF,0xF8,0x00,0x07,0xFF,0xC0,0x00,0x3F,0xFE,0x00,0x00,0xFF,
	0xF8,0x00,0x07,0xFF,0xF8,0x00,0x3F,0xFF,0xFC,0x01,0xFF,0xFF,0xFE,0x07,0xFF,
	0xFF,0xFF,0x3F,0xF8,0xFF,0xFF,0xFF,0xC0,0xFF,0xFF,0xFF,0x01,0xFF,0xFF,0xF8,
	0x03,0xFF,0xFF,0xE0,0x03,0xFF,0xFF,0xE0,0x07,0xFF,0xFF,0xF0,0x0F,0xFF,0xFF,
	0xF0,0x0F,0xFF,0xFF,0xF8,0x1F,0xFF,0xFF,0xFC,0x3F,0xFF,0xFF,0xFC,0x3F,0xFF,
	0xFF,0xFE,0x7F,0xFF,0xFF,0xFF,0xFF,0xFF
};

unsigned char LoongsonLogo16x16_8bit[] = {
	0xFF,0xFF,0x87,0xFF,0x9F,0xF9,0xFF,0x83,0xFE,0x1F,0xF0,0x7D,0x83,0xF1,0x8F,
	0x81,0xBE,0x01,0x98,0x19,0x80,0xF9,0x83,0xF1,0x87,0xE1,0x83,0xC1,0x81,0x81,
	0xFF,0xFF
};

unsigned char Round16x16_8bit[] = {
	0x07,0xE0,0x08,0x10,0x30,0x0C,0x20,0x04,0x40,0x02,0x80,0x01,0x80,0x01,0x80,
	0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x40,0x02,0x20,0x04,0x30,0x0C,0x08,0x10,
	0x07,0xE0
};
unsigned char GPR16x32_8bit[] = {
	0xFF,0xFF,0x80,0x01,0x83,0xF1,0x86,0x1D,0x8C,0x0D,0x98,0x05,0x98,
	0x01,0x98,0x01,0x98,0x01,0x98,0x3D,0x98,0x19,0x8C,0x19,0x86,0x19,0x83,0xF1,
	0x80,0x01,0xFF,0xFF
};

unsigned char Signal4_16x16_8bit[] = {
	0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x66,0x00,0x66,0x00,0x66,0x00,
	0x66,0x06,0x66,0x06,0x66,0x06,0x66,0x06,0x66,0x66,0x66,0x66,0x66,0x66,0x66,
	0x66,0x66 
};
unsigned char Signal3_16x16_8bit[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x06,0x60,0x66,0x60,0x66,0x60,0x66,0x60,
	0x66,0x60 
};
unsigned char Signal2_16x16_8bit[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x06,0x00,0x66,0x00,0x66,0x00,0x66,0x00,
	0x66,0x00 
};

unsigned char Signal1_16x16_8bit[] = {
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x60,0x00,0x60,0x00,
	0x60,0x00 
};

unsigned char ZeroArea[30 * 160] = { 0 };

/*---------------------------------------------------------------------------*/
/*	保存主程序中使用的所有图像，该数组方便通过AREA_TYPE_EN索引
*/
AREA_DATA_ARRAY g_area_array[AREA_TYPE_BUTT] = {
		{32, 32, BIT8_TYPE, LoongsonLogo32x32_8bit},
		{16, 16, BIT8_TYPE, LoongsonLogo16x16_8bit},
		{16, 16, BIT8_TYPE, Round16x16_8bit},
		{16, 16, BIT8_TYPE, GPR16x32_8bit},
		{16, 16, BIT8_TYPE, Signal1_16x16_8bit},
		{16, 16, BIT8_TYPE, Signal2_16x16_8bit},
		{16, 16, BIT8_TYPE, Signal3_16x16_8bit},
		{16, 16, BIT8_TYPE, Signal4_16x16_8bit},
};


/*----------------------------------------------------------------------------*/
AmrDlgBase::AmrDlgBase(unsigned int fd): DispFd(fd)
{
	memset(DispMem, 0x00, sizeof(DispMem));
}

/*----------------------------------------------------------------------------*/
AmrDlgBase::~AmrDlgBase()
{

}

/*---------------------------------------------------------------------------*/
/* 清缓存 
*/
void AmrDlgBase::ClearAll(void)
{
	memset(DispMem, 0x00, sizeof(DispMem));
}

/*----------------------------------------------------------------------------*/
/* 设置或者清除屏上一点, 仅在缓存上操作
*/
void AmrDlgBase::SetMemDot(int x, int y, int val)
{
	int bit0_pos, bit1_pos;
	unsigned char bit0_val = 0;
	unsigned char bit1_val = 0;

	/* 	x,y为160x160屏幕上的坐标，由于2个字节显示三个点
	**	所以，需要把屏幕上的坐标点转换到显存数据上的坐标
	*/
	bit0_pos = (x/3) * 2;
	bit1_pos = (x/3) * 2 + 1;

	/* 	首先大致，划定(x,y)所在的显存位置<缩小到两个字节范围> 
	**	取出当前显示数据
	*/
	bit0_val = DispMem[bit0_pos][y];
	bit1_val = DispMem[bit1_pos][y];

	/* 	进一步计算x位置，在两个字节中的offset
	**	val值决定是清除该点还是置位该点
	*/
	switch (x%3)
	{
		case 0:
			if (val)
			{
				bit0_val |= 0xE0;
				bit1_val |= 0x07;
			}
			else
			{
				bit0_val &= ~0xE0;
				bit1_val &= ~0x07;
			}
			break;
		case 1:
			if (val)
				bit0_val |= 0x1F;
			else
				bit0_val &= ~0x1F;
			break;
		case 2:
			if (val)
				bit1_val |= 0xF8;
			else
				bit1_val &= ~0xF8;
			break;
	}

	/* 更新显存对应的点 */
	DispMem[bit0_pos][y] = bit0_val;
	DispMem[bit1_pos][y] = bit1_val;
}

/*---------------------------------------------------------------------------*/
/*	画一个矩形
*/
void AmrDlgBase::SetRectangle(int x, int y, int x_len, int y_len, bool clr)
{
	int x_end = x + x_len;
	int y_end = y + y_len;

	if (x_end > 160)
		x_end = 160;
	if (y_end > 160)
		y_end = 160;

	for (int i = x; i < x_end; i ++)
	{
		for (int k = y; k < y_end; k++)
		{
			if (clr)
				SetMemDot(i, k, 0);
			else
				SetMemDot(i, k, 1);
		}
			
	}
	return;
}

/*---------------------------------------------------------------------------*/
/* 	在坐标(x,y)处，显示一个事先准备好的图像数据，
	数据由AREA_TYPE_EN指明，turn_over标示色彩翻转
*/
void AmrDlgBase::SetMemAera(int x, int y, AREA_TYPE_EN type, 
											int clr_flag, bool turn_over)
{

	int b_pos = 0;
	int c_pos = 0;
	unsigned char *data = NULL;

	if (type >= AREA_TYPE_BUTT)
	{
		fprintf(stderr, "\nHave No This AREA_TYPE_EN[%d]", type);
		return;
	}

	/* 根据type，映射出数据 */
	if (clr_flag)
		data = g_area_array[type].data;
	else
		data = ZeroArea;
	
	int width = (g_area_array[type].b_type == BIT8_TYPE) ? 7 : 5;
	int x_end = x + g_area_array[type].x_len;
	int y_end = y + g_area_array[type].y_len;

	for (int y_start = y; y_start < y_end; y_start++)
	{
		for (int x_start = x; x_start < x_end; x_start++)
		{
			if (data[c_pos] & (0x01 << (width - b_pos)))
			{
				if (turn_over)
					SetMemDot(x_start, y_start, 0);
				else
					SetMemDot(x_start, y_start, 1);
			}
			else
			{
				if (turn_over)
					SetMemDot(x_start, y_start, 1);
				else
					SetMemDot(x_start, y_start, 0);
			}

			b_pos++;

			if (b_pos > width) 
			{
				b_pos = 0;
				c_pos++;
			}
			
		}
	}


	return;
}

/*---------------------------------------------------------------------------*/
/* 设置字符到坐标(x,y),clr_flag表明清除，turn_over表明色调翻转  
*/
void AmrDlgBase::SetZIFUAera(int x, int y, int type, 
							unsigned char *buffer, int clr_flag, bool turn_over)
{

	int b_pos = 0;
	int c_pos = 0;
	unsigned char *data = NULL;
	
	int width = 0;
	int x_end = 0;
	int y_end = 0;

	/* 根据字符类型和左边，确定长宽 */
	switch (type)
	{
		case ASCII12:
			width = 5;
			x_end = x + 6;
			y_end = y + 12;
			break;
		case ASCII16:
			width = 7;
			x_end = x + 8;
			y_end = y + 16;
			break;
		case CHINESE12:
			width = 5;
			x_end = x + 12;
			y_end = y + 12;
			break;
		case CHINESE16:
			width = 7;
			x_end = x + 16;
			y_end = y + 16;
			break;
		default:
			fprintf(stderr, "SetZIFUAera error input len must 32 || 24\n");
			return;
	}

	if (clr_flag)
		data = buffer;
	else
		data = ZeroArea;	/* 如果clr_flag==false，则使用ZeroArea刷屏 */
	

	for (int y_start = y; y_start < y_end; y_start++)
	{
		for (int x_start = x; x_start < x_end; x_start++)
		{
			if (data[c_pos] & (0x01 << (width - b_pos)))
			{
				if (turn_over)
					SetMemDot(x_start, y_start, 0);
				else
					SetMemDot(x_start, y_start, 1);
			}
			else
			{
				if (turn_over)
					SetMemDot(x_start, y_start, 1);
				else
					SetMemDot(x_start, y_start, 0);
			}
			b_pos++;

			if (b_pos > width) 
			{
				b_pos = 0;
				c_pos++;
			}
			
		}
	}


	return;
}


/*----------------------------------------------------------------------------*/
/* 缓存写到屏上
*/
void AmrDlgBase::DisplayMem(void)
{
	write(DispFd, DispMem, sizeof(DispMem));
	//fprintf(stderr, "ShowDlog -> %s\n", name);
}


/*----------------------------------------------------------------------------*/
/* 显示该平数据，即是把缓存打到EMI屏上
*/
void AmrDlgBase::ShowDlg(void)
{
	DisplayMem();
}

/*----------------------------------------------------------------------------*/
void AmrDlgBase::InitOperation(void)
{
	//nothing
}

