#include "wheel_controll.h"
#include "cd74ac153.h"
#include <unistd.h>
#include "sonar.h"
#include "gpio.h"
#include <stdio.h>

using namespace std;

	#define		SONAR1	LINE1		
	#define		SONAR2	LINE2		
	#define		SONAR3	LINE3

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
	//i = ReadSonar(SONAR3);
	while(1)
	{
		i = ReadSonar(SONAR1);
		printf("Sonar 1 = %d    ", i);

		i = ReadSonar(SONAR2);
		printf("%d    ", i);

		i = ReadSonar(SONAR3);
		printf("%d\n", i);
		//fflush(stdout);
		
		//i = sonar.ReadValue();
		//printf("%d\n", i);
		usleep(500);
	}

//	WCInit();
//	WCCommand(FORWARD);
//	for (int i = 0; i < 1000; i++) usleep(1000);
//	WCCommand(BACK);
//	for (int i = 0; i < 1000; i++) usleep(1000);
//	WCCommand(STOP);
//	for (int i = 0; i < 1000; i++) usleep(1000);
//	WCCommand(LEFT);
//	for (int i = 0; i < 1000; i++) usleep(1000);
//	WCCommand(RIGHT);
//	for (int i = 0; i < 1000; i++) usleep(1000);
//	WCCommand(CENTER);

	return 0;
}