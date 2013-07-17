/*----------------------------------------------------------------------------*/
/* 	AmrDisplay --- AmrDlgWelcome.h
**
**  ansonn.wang@foxmail.com
**
**
*-----------------------------------------------------------------------------*/

#ifndef _ZIKU_H
#define _ZIKU_H

#define DISPLAY_STRING(a, b, str) do { \
	unsigned char buff[32] = {0};\
	char *ptr = (str);\
	int x = (a); int y = (b);\
	while ('\0' != *ptr)\
	{\
		m_AmrDisplay.ZKDisplayConvert(ptr , ASCII16, buff);\
		SetZIFUAera(x, y, ASCII16, buff, DISPLAY, false);\
		x += 8;\
		ptr++;\
	}\
} while (0)


#define DISPLAY_16x16_JIBENXINXI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"基" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"本" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"信" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"息" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_16x16_RILIXINXI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"日" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"历" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"信" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"息" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_TIAOSHIZHISHIDENG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"调" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"试" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"指" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"示" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"灯" , CHINESE16, buff);\
	SetZIFUAera(x+64, y, CHINESE16, buff, DISPLAY, flg);\
} while(0)

#define DISPLAY_16x16_TUICHUI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"返" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"回" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_8x16_LOONGSON(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"L" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"o" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"o" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"n" , ASCII16, buff);\
	SetZIFUAera(x+24, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"g" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"s" , ASCII16, buff);\
	SetZIFUAera(x+40, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"o" , ASCII16, buff);\
	SetZIFUAera(x+48, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"n" , ASCII16, buff);\
	SetZIFUAera(x+56, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_BEIJINGSHENZHOULONGXIN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"北" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"京" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"神" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"州" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"龙" , CHINESE16, buff);\
	SetZIFUAera(x+64, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"芯" , CHINESE16, buff);\
	SetZIFUAera(x+80, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_DIANLIJIZHONGKONGZHIQI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"力" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"集" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"中" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"控" , CHINESE16, buff);\
	SetZIFUAera(x+64, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"制" , CHINESE16, buff);\
	SetZIFUAera(x+80, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"器" , CHINESE16, buff);\
	SetZIFUAera(x+96, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_XITONGSHEZHI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"系" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"统" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"设" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"置" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_DIANBIAOKONGZHI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"表" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"控" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"制" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_CHULIQILEIXING(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"处" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"理" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"器" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+48, y, ASCII16, buff, DISPLAY, flg);\
\
	m_AmrDisplay.ZKDisplayConvert((char *)"G" , ASCII16, buff);\
	SetZIFUAera(x+56, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"S" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"C" , ASCII16, buff);\
	SetZIFUAera(x+72, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"3" , ASCII16, buff);\
	SetZIFUAera(x+80, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"2" , ASCII16, buff);\
	SetZIFUAera(x+88, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"8" , ASCII16, buff);\
	SetZIFUAera(x+96, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+102, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_IPDIZHI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"地" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"址" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_KEYONGNEICUN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"内" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"存" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"1" , ASCII16, buff);\
	SetZIFUAera(x+40, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"2" , ASCII16, buff);\
	SetZIFUAera(x+48, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"8" , ASCII16, buff);\
	SetZIFUAera(x+56, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"M" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_KEYONGFLASH(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"存" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"储" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"1" , ASCII16, buff);\
	SetZIFUAera(x+40, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"G" , ASCII16, buff);\
	SetZIFUAera(x+48, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_RIQI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"日" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"期" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_SHIJIAN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"时" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"间" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_DIANLIANGSHIJIAN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"点" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"亮" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"时" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"间" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"m" , ASCII16, buff);\
	SetZIFUAera(x+110, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"s" , ASCII16, buff);\
	SetZIFUAera(x+118, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_XIMIESHIJIAN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"熄" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"灭" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"时" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"间" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"m" , ASCII16, buff);\
	SetZIFUAera(x+110, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"s" , ASCII16, buff);\
	SetZIFUAera(x+118, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_CHIXUSHIJIAN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"持" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"续" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"时" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"间" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"s" , ASCII16, buff);\
	SetZIFUAera(x+118, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_YINGYIONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"应" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"用" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_IP(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"I" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"P" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_BIAOYIDIANLIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"表" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"一" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_BIAOERDIANLIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"表" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"二" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_BIAOSANDIANLIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"表" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"三" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_BIAOSIDIANLIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"表" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"四" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_DIZENGJIANGE(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"递" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"增" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"间" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"隔" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_QINGLING(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"清" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"零" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_JIANGEDANWEI(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"(" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"." , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"1" , ASCII16, buff);\
	SetZIFUAera(x+24, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"s" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)")" , ASCII16, buff);\
	SetZIFUAera(x+40, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_DANGQIANDIANLIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"当" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"前" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_DIANLIZHUANBIANXITONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"力" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"专" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"变" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"控" , CHINESE16, buff);\
	SetZIFUAera(x+64, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"制" , CHINESE16, buff);\
	SetZIFUAera(x+80, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"器" , CHINESE16, buff);\
	SetZIFUAera(x+96, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)



#define DISPLAY_8x16_000000000210(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+24, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+40, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+48, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+56, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"2" , ASCII16, buff);\
	SetZIFUAera(x+72, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"1" , ASCII16, buff);\
	SetZIFUAera(x+80, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"0" , ASCII16, buff);\
	SetZIFUAera(x+88, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_SR(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"[" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"S" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"R" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"]" , ASCII16, buff);\
	SetZIFUAera(x+24, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_JIAOCAISHUJU(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"交" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"采" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"数" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"据" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_YOUGONGGONGLV(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"有" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"功" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"功" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"率" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_WUGONGGONGLV(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"无" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"功" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"功" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"率" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_16x16_DIANNENGLIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"电" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"能" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_PA(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"P" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"a" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_PB(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"P" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"b" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_PC(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"P" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"c" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_8x16_RA(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"R" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"a" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_RB(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"R" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"b" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_RC(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"R" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"c" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_8x16_KW(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"k" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"W" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_KVAR(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"k" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"V" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"a" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"r" , ASCII16, buff);\
	SetZIFUAera(x+24, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_KVARH(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"k" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"V" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"a" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"r" , ASCII16, buff);\
	SetZIFUAera(x+24, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"h" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_UA(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"U" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"a" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_IA(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"I" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"a" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_UB(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"U" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"b" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_IB(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"I" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"b" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_8x16_UC(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"U" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"c" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)



#define DISPLAY_8x16_IC(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"I" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"c" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)



#define DISPLAY_8x16_V(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"V" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_A(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"A" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_CAIJISHIJIAN(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"采" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"集" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"时" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"间" , CHINESE16, buff);\
	SetZIFUAera(x+48, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+64, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_ZHENGXIANGYOUGONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"正" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"有" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_ZHENGXIANGWUGONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"正" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"无" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_FANXIANGYOUGONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"反" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"有" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_FANXIANGWUGONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"反" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"无" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+32, y, ASCII16, buff, DISPLAY, flg);\
} while (0)

#define DISPLAY_8x16_KWH(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"k" , ASCII16, buff);\
	SetZIFUAera(x, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"W" , ASCII16, buff);\
	SetZIFUAera(x+8, y, ASCII16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"h" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)


#define DISPLAY_YAOCELIANG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"遥" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"测" , CHINESE16, buff);\
	SetZIFUAera(x+16, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)"量" , CHINESE16, buff);\
	SetZIFUAera(x+32, y, CHINESE16, buff, DISPLAY, flg);\
} while (0)



#define DISPLAY_ZONG(x, y, flg) do {\
	unsigned char buff[32] = {0};\
	m_AmrDisplay.ZKDisplayConvert((char *)"总" , CHINESE16, buff);\
	SetZIFUAera(x, y, CHINESE16, buff, DISPLAY, flg);\
	m_AmrDisplay.ZKDisplayConvert((char *)":" , ASCII16, buff);\
	SetZIFUAera(x+16, y, ASCII16, buff, DISPLAY, flg);\
} while (0)




#endif



