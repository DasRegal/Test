#include "find.h"

double* find (CvCapture* capture)
{
#define POROG 60
	IplImage* frame = cvQueryFrame( capture );
	//	if(!frame) 
	//			return EXIT_FAILURE;	
	IplImage* frameWB = cvCreateImage(cvSize(frame->width,frame->height),8,1);
	IplImage* frameWB2 = cvCreateImage(cvSize(frame->width,frame->height),8,1);
	cvConvertImage(frame,frameWB,0);

	int cx=0;
	int Xmin=frame->width, Xmax=0, Ymin=frame->height, Ymax=0;
	double MX=0, MY=0, DX=0, DY=0, sqDX=0, sqDY=0;
	int XYcount=0;
	std::list<short unsigned int> MXX,MYY;
	
	//gray = cvCreateImage( cvGetSize(frame), 8, 1);
	//cvConvertImage(frame,gray,0);
	/*int hist_size = 256;

	float range_0[]={0,256};

	float* ranges[] = { range_0 };



	CvHistogram *hist;

	IplImage *hist_image = cvCreateImage(cvSize(800,600), 8, 1);

	hist = cvCreateHist(1, &hist_size, CV_HIST_ARRAY, ranges, 1);

	cvCalcHist( &frameWB, hist, 0, NULL );



	int bin_w;

	bin_w = cvRound((double)hist_image->width/hist_size);

	cvSet( hist_image, cvScalarAll(255), 0 );

	for( int i = 0; i < hist_size; i++ )
	{
		cvRectangle (hist_image, cvPoint(i*bin_w, hist_image->height),
			cvPoint ((i+1)*bin_w, hist_image->height -
			cvRound (cvGetReal1D(hist->bins,i))), cvScalar (0), 
			-1,8,0);
		//printf (" %d,     n", i*bin_w   );//(hist_image->height -  cvRound (cvGetReal1D(hist->bins,i))));
	}


	cvNamedWindow( "histogram", 1 );

	cvShowImage( "histogram", hist_image );*/
	for (int y=1; y<frameWB->height-3; y++) //контраст i-того и i+2 пикселей
	{
		uchar *ptr = (uchar*) (
			frameWB->imageData + y * frameWB->widthStep) ;
		for (int x=1; x<frameWB->width; x++)
		{

			uchar *ptr2 = (uchar*) (
				frameWB->imageData + (y+2) * frameWB->widthStep);
			if(abs (ptr[x]- ptr2[x]) >POROG)
			{

				MX+=x; MY+=y+1;
				MXX.push_back(x);
				MYY.push_back(y+1);
				XYcount++;

				((uchar *)(frameWB2->imageData + (y+1)*frameWB2->widthStep))[x]=0; 
			}
		}
	}
	/*for (int y=1; y<frame->height-3; y++) // контраст i-того и i+1 пикселей
	{
	uchar *ptr = (uchar*) (
	frame->imageData + y * frame->widthStep) ;
	for (int x=1; x<frame->width; x++)
	{
	uchar *ptr2 = (uchar*) (
	frame->imageData + (y+1) * frame->widthStep);
	if(abs( (ptr[3*x+1]+ptr[3*x+2]+ptr[3*x+3]) /3- (ptr2[3*x+1]+ptr2[3*x+2]+ptr2[3*x+3])/3 ) >POROG)
	{
	MX+=x; MY+=y+1;
	MXX.push_back(x);
	MYY.push_back(y+1);
	XYcount++;
	/*((uchar *)(frameKK->imageData + (y)*frameKK->widthStep))[3*x+1]=144; 
	((uchar *)(frameKK->imageData + (y)*frameKK->widthStep))[3*x+2]=144; 
	((uchar *)(frameKK->imageData + (y)*frameKK->widthStep))[3*x+3]=0;
	}
	}
	}*/
	////////////////////////////Вертикальный проход///////
	///G///////////////////////////////////////////////////горизонтальный проход
	/*for (int y=1; y<frame->height; y++)//контраст i-того и i+2 пикселей
	{
	uchar *ptr = (uchar*) (
	frame->imageData + y * frame->widthStep) ;
	for (int x=1; x<frame->width-3; x++)
	{
	if(abs( (ptr[3*x+1]+ptr[3*x+2]+ptr[3*x+3]) /3- (ptr[3*(x+2)+1]+ptr[3*(x+2)+2]+ptr[3*(x+2)+3])/3 ) >POROG)
	{
	/*MX+=x+1; MY+=y;
	MXX.push_back(x+1);
	MYY.push_back(y);
	XYcount++;
	((uchar *)(frameKG->imageData + (y)*frameKG->widthStep))[3*(x+1)+1]=3; 
	((uchar *)(frameKG->imageData + (y)*frameKG->widthStep))[3*(x+1)+2]=3; 
	((uchar *)(frameKG->imageData + (y)*frameKG->widthStep))[3*(x+1)+3]=33;/*
	}
	}
	}*/
	/*for (int y=1; y<frame->height; y++)// контраст i-того и i+1 пикселей
	{
	uchar *ptr = (uchar*) (
	frame->imageData + y * frame->widthStep) ;
	for (int x=1; x<frame->width-2; x++)
	{
	if(abs( (ptr[3*x+1]+ptr[3*x+2]+ptr[3*x+3]) /3- (ptr[3*(x+1)+1]+ptr[3*(x+1)+2]+ptr[3*(x+1)+3])/3 ) >POROG)
	{
	MX+=x+1; MY+=y;
	MXX.push_back(x+1);
	MYY.push_back(y);
	XYcount++;
	/*((uchar *)(frameKGS->imageData + (y)*frameKGS->widthStep))[3*(x)+1]=3; 
	((uchar *)(frameKGS->imageData + (y)*frameKGS->widthStep))[3*(x)+2]=3; 
	((uchar *)(frameKGS->imageData + (y)*frameKGS->widthStep))[3*(x)+3]=33;
	}
	}
	}*/
	///G//......
	double xy[3]={0.0};
	if (XYcount!=0 && XYcount>50)
	{
		MX/=XYcount; MY/=XYcount;
		for(std::list<short unsigned int>::iterator i=MXX.begin();i!=MXX.end();i++)
		{
			DX+=abs(*i -MX);
		}
		for(std::list<short unsigned int>::iterator i=MYY.begin();i!=MYY.end();i++)
		{
			DY+=abs(*i -MY);
		}
		DX=abs(DX/XYcount); DY=abs(DY/XYcount);
		//sqDX=sqrt(DX) ; sqDY=sqrt(DY) ;

		int k=2; 
		//xy[0]=Xin+(Xmax-Xmin)/2;
		//xy[1]=Yin+(Ymax-Ymin)/2;
		double fw2 = (double)(frame->width/2);
		xy[0]=MX;
		xy[1]=MY;
		xy[2]=(xy[0]-fw2)/fw2;
		
		for (int y=1; y<frameWB->height-3; y++)
		{
			uchar *ptr = (uchar*) (
				frameWB->imageData + y * frameWB->widthStep) ;
			for (int x=1; x<frameWB->width; x++)
			{

				uchar *ptr2 = (uchar*) (
					frameWB->imageData + (y+2) * frameWB->widthStep); 

				if	(abs (ptr[x]- ptr2[x]) >POROG && (x<(MX+k*DX) )&& (x>(MX-k*DX))&& (y<(MY+k*DY)) && (y>(MY-k*DY)))
				{
					if (x<Xmin)
					{
						Xmin=x;
					}
					if (x>Xmax)
					{
						Xmax=x;
					}
					if (y<Ymin)
					{
						Ymin=y;
					}
					if (y>Ymax)
					{
						Ymax=y;
					}

				}
			}
		}
		if (!(Xmin==frame->width && Xmax==0 && Ymin==frame->height && Ymax==0))
		{
			CvPoint* line = new CvPoint () ;
			line[0].x= Xmin;
			line[0].y= Ymin;
			line[1].x= Xmax;
			line[1].y= Ymin;

			cvLine( frame, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );

			line[0].y= Ymin;
			line[0].x= Xmax;
			line[1].y= Ymax;
			line[1].x= Xmax;
			cvLine( frame, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );

			line[0].y= Ymax;
			line[0].x= Xmax;
			line[1].y= Ymax;
			line[1].x= Xmin;
			cvLine( frame, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );

			line[0].y= Ymax;
			line[0].x= Xmin;
			line[1].y= Ymin;
			line[1].x= Xmin;
			cvLine( frame, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );

			line[0].y= ((Ymax-Ymin))/2+Ymin;
			line[0].x= Xmin+ (Xmax-Xmin)/4;
			line[1].y= ((Ymax-Ymin))/2+Ymin;
			line[1].x= Xmax- (Xmax-Xmin)/4;
			cvLine( frame, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );


			line[0].y= Ymin+ (Ymax-Ymin)/4;
			line[0].x= ((Xmax - Xmin))/2+Xmin;
			line[1].y= Ymax- (Ymax-Ymin)/4;
			line[1].x= ((Xmax - Xmin))/2+Xmin;
			cvLine( frame, line[0], line[1], CV_RGB(255,0,0), 1, CV_AA, 0 );
		}

		const char *windowName = "Window";
		cvNamedWindow(windowName, CV_WINDOW_AUTOSIZE);
		//const char *windowNameWB = "WindowWB";
		//cvNamedWindow(windowNameWB, CV_WINDOW_AUTOSIZE);
		//const char *windowNameWB2 = "WindowWB2";
		//cvNamedWindow(windowNameWB2, CV_WINDOW_AUTOSIZE);
		cvShowImage(windowName, frame);
		//cvShowImage(windowNameWB, frameWB);
		//cvShowImage(windowNameWB2, frameWB);
	}
	else 
	{
		xy[0]=0;
		xy[1]=0;
		xy[2]=0;
	}
	MXX.clear();
	MYY.clear();
	cvReleaseImage ( &frameWB);
	cvReleaseImage ( &frameWB2);
	return xy;
}
