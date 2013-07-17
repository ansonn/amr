#CC=arm-linux-g++
CC=mipsel-linux-g++
target=power

object=main.cpp AmrDisplay.cpp AmrDlgBase.cpp AmrDlgWelcome.cpp AmrDlgMain.cpp AmrDlgLedCtrl.cpp AmrDlgDevInfo.cpp AmrDlgDate.cpp AmrDlgSysSetting.cpp AmrDlgUartCtrl.cpp  ExcDlgWelcome.cpp ExcDlgMain.cpp ExcDlgPowerHave.cpp ExcDlgPowerNo.cpp ExcDlgPowerTotal.cpp ExcDlgTelemetry.cpp

all:power

clean:
	@echo "clean up"
	rm -f *.o $(target)

power:$(object)
	$(CC) $(object) -o $(target) -lpthread -ldl
