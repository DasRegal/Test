// Используя левый сонар, установленный под углом 45 градусов влево
// к направлению вперед, проехать вдоль стенки ("зигзагами") до передней
// стены на расстояние 1 м, остановиться, повернуть вправо на ~100 градусов,
// продолжить движение "зигзагами" до задней стенки.

#include "wheel_controll.h"
#include "cd74ac153.h"
#include <unistd.h>
#include "sonar.h"
#include "gpio.h"
#include <stdio.h>

using namespace std;

	#define		SONAR_RIGHT		LINE1		
	#define		SONAR_LEFT		LINE2		
	#define		SONAR_FORW		LINE3
	#define		BORDER_LEFT		400
	#define		BORDER_RIGHT	300
	#define		BORDER_FORWARD	1000

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
}

int main()
{
	int i;
	Init();
	WCCommand(FORWARD);
	//i = ReadSonar(SONAR3);
	while(1)
	{
		i = ReadSonar(SONAR_RIGHT);
		if (i <= BORDER_LEFT && i > BORDER_RIGHT)
		{
			WCCommand(CENTER);
		}
		else
		if (i > BORDER_LEFT)
		{
			WCCommand(RIGHT);
			while (i > BORDER_LEFT)
			{
				i = ReadSonar(SONAR_RIGHT);
			}
			WCCommand(CENTER);
		}
		else
		if (i == BORDER_RIGHT)
		{
			WCCommand(LIGHT);
			while (i == BORDER_RIGHT)
			{
				i = ReadSonar(SONAR_RIGHT);
			}
			WCCommand(CENTER);
		}

		i = ReadSonar(SONAR_FORW);
		if (i <= BORDER_FORWARD)
			break;
//		usleep(500);
	}
	WCCommand(LEFT);
	for (int i = 0; i < 2150; i++) usleep(1000);
	WCCommand(CENTER);
	WCCommand(STOP);

	return 0;
}