 // Выполнить п.5, управляя направлением движения по Х центра ПП с изображения.
 // 5. Поставить тележку на расстояние 1м от центра посадочной площадки,
 // соориетировав её в направлении ПП, записывая видео, проехать 1 м.

#include "wheel_controll.h"
#include "find.h"
#include <unistd.h>
#include <stdio.h>

using namespace std;

int main()
{
	CvCapture* capture = 0;	
	capture = cvCreateCameraCapture(3);
	if (!capture)
	{
		return EXIT_FAILURE;
	}

	WCInit();
	while(true) 
	{
		
		double* xy=find(capture);
		
		printf ("x = %.4lf, y = %.4lf, U = %.4lf \n\n", xy[0], xy[1], xy[2]);
	
		if (xy[2] < -0.5)
			WCCommand(LEFT);
		if (xy[2] >= -0.5 && xy[2] <= 0.5)
			WCCommand(CENTER);
		if (xy[2] > 0.5 )
			WCCommand(RIGHT);

		char c = cvWaitKey(33);
		if (c == 27) 
			break;
	}
	cvReleaseCapture( &capture );
	cvDestroyAllWindows();

	return 0;
}