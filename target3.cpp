// Проехать до перпендикулярной стенки по переднему сонару,
// пока она не окажется на расстоянии 50см, остановиться,
// повернуть влево на 180 градусов, остановиться, проехать
// вперед до задней стенки на 50 см.

#include "wheel_controll.h"
#include "cd74ac153.h"
#include <unistd.h>
#include "sonar.h"
#include "gpio.h"
#include <stdio.h>

using namespace std;

	#define		SONAR2	LINE2		

	CSonar sonar;

int ReadSonar(ESwLine line)
{
	cd74ac.SwitchLine(line);
	return sonar.ReadValue();
}

void Init()
{
	sonar.Create("ttySAC3");
	cd74ac.Init();
	WCInit();
}

int main()
{
	Init();

	int i;	
	// Ехать до стенки пока не 50 см.
	i = ReadSonar(SONAR2);
	while(i > 500)
	{
		WCCommand(FORWARD);
		i = ReadSonar(SONAR2);
	}
	WCCommand(STOP);
	for (int i = 0; i < 1000; i++) usleep(1000);

	// Разворот на 180
	WCCommand(FORWARD);
	WCCommand(LEFT);
	for (int i = 0; i < 1000; i++) usleep(1000);
	WCCommand(STOP);
	WCCommand(CENTER);

	// Ехать до стенки пока не 50 см.
	i = ReadSonar(SONAR2);
	while(i > 500)
	{
		WCCommand(FORWARD);
		i = ReadSonar(SONAR2);
	}
	WCCommand(STOP);

	return 0;
}