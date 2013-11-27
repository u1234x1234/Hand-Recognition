#include "opencv2/opencv.hpp"
#include <stdio.h>
#include "SVMHandDetector.h"

using namespace std;
using namespace cv;

#include "OpenNIContext.h"
int main(int argc, char** argv)
{

	bool update_bg_model = true;

	BackgroundSubtractorMOG2 bg_model;//(100, 3, 0.3, 5);

	Mat img, fgmask, fgimg;
	OpenNIContext qwe(1, argv);
	HandDetector *handDetector = new SVMHandDetector("palm3.xml");
	VideoCapture cap("1.avi");
	for(;;)
	{
		qwe.update();
		qwe.getImageMap(img);
		//cap >> img;
//		imshow("123",img);
//		imwrite("5.png",img);
//		waitKey(50);
//		continue;
		if( img.empty() )
			break;

		if( fgimg.empty() )
		  fgimg.create(img.size(), img.type());

		//update the model
	//	bg_model(img, fgmask, update_bg_model ? -1 : 0);

		fgimg = Scalar::all(0);
		img.copyTo(fgimg, fgmask);

		Mat bgimg;
	//	bg_model.getBackgroundImage(bgimg);
		int erosion_type = MORPH_RECT;
		int erosion_size = 1;
		Mat element = getStructuringElement( erosion_type,
								   Size( 2*erosion_size + 1, 2*erosion_size+1 ),
							   Point( erosion_size, erosion_size ) );
//		erode( fgimg, fgimg, element, Point(-1, -1), 2 );
//		erode( fgmask, fgmask, element, Point(-1, -1), 2 );

//		dilate( fgimg, fgimg, element, Point(-1, -1), 3 );
//		dilate( fgmask, fgmask, element, Point(-1, -1), 1 );

//		imshow("image", img);
		Mat im;

	//	imshow("denoise", im);

		Mat g;
		//inRange(fgmask, Scalar(1,1,1),Scalar(255,255,255),g);


		//imshow("color", h);
		Rect rect;
		if ( handDetector->separate(img, fgmask, rect) )
		{
//			resize(fgimg,fgimg, Size(256,256));
//			rectangle(fgimg, rect, Scalar(200, 50, 200));
		}
//		imshow("fore", fgmask);
		//imwrite("2.png",g);
		//imshow("or", g|h);

//		imshow("foreground image", fgimg);
//		if(!bgimg.empty())
//		  imshow("mean background image", bgimg );

		char k = (char)waitKey(30);
		if( k == 27 ) break;
		if( k == ' ' )
		{
			update_bg_model = !update_bg_model;
			if(update_bg_model)
				printf("Background update is on\n");
			else
				printf("Background update is off\n");
		}
	}
//	w.release();

	return 0;
}
