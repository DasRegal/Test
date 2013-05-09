// С точки старта проехать прямо на 1 м, остановиться,
// повернуть налево на 180 градусов, остановиться,
// проехать прямо на 1 м (поворот на 180 градусов
// подобрать опытным путем по времени).

#include "wheel_controll.h"
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{

	WCInit();
	
	// Ехать 1 метр
	WCCommand(FORWARD);
	for (int i = 0; i < 1000; i++) usleep(1000);
	WCCommand(STOP);
	for (int i = 0; i < 2000; i++) usleep(1000);

	// Разворот на 180
	WCCommand(FORWARD);
	WCCommand(LEFT);
	for (int i = 0; i < 1000; i++) usleep(1000);
	WCCommand(STOP);
	WCCommand(CENTER);

	// Ехать 1 метр
	WCCommand(FORWARD);
	for (int i = 0; i < 1000; i++) usleep(1000);
	WCCommand(STOP);
	
	return 0;
}