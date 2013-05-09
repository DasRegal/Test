// Поставить тележку на расстояние 1м от центра посадочной площадки,
// соориетировав её в направлении ПП, записывая видео, проехать 1 м.

#include "wheel_controll.h"
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{

	WCInit();
	
	// Монтирование флешки
	system("mount /dev/sda /mnt");

	//  Включить камеру на 5 сек.
	system("ffmpeg -f v4l2 -t 5 -s 640x480 -i /dev/video3 /mnt/out.mpg");
	for (int i = 0; i < 1000; i++) usleep(1000);

	// Ехать 1 метр
	WCCommand(FORWARD);
	for (int i = 0; i < 1000; i++) usleep(1000);
	WCCommand(STOP);
	
	// Размонтирование флешки
	system("umount /mnt");

	return 0;
}