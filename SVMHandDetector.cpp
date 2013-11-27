#include "SVMHandDetector.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

SVMHandDetector::SVMHandDetector( const std::string &classifierFileName )
{
	hog = new HOGDescriptor(
				Size(64,64), //winSize
				Size(16,16), //blocksize
				Size(8,8), //blockStride,
				Size(8,8), //cellSize,
				9,  //nbins,
				0,  //derivAper,
				-1,  //winSigma,
				0,  //histogramNormType,
				0.2,  //L2HysThresh,
				0  //gammal correction,
				//nlevels=64
				);
	svm.load(classifierFileName.c_str());
}
void func(cv::Mat &a, cv::Mat &b)
{
	Mat mask;
	int lo = 35; int up = 35;
	cvtColor( a, b, COLOR_BGR2YCrCb );

	Point seed = Point( a.cols / 2, a.rows/2  );

	int connectivity = 8;
	int flags = connectivity + (255 << 8 ) + FLOODFILL_FIXED_RANGE + FLOODFILL_MASK_ONLY;
	Rect r;
	Mat mask2 = Mat::zeros( b.rows + 2, b.cols + 2, CV_8UC1 );
	floodFill( b, mask2, seed, 255, &r, Scalar( lo, lo, lo ), Scalar( up, up, up), flags );
	mask = mask2( Range( 1, mask2.rows - 1 ), Range( 1, mask2.cols - 1 ) );
	b = mask;
	return;
}
int cnt;
bool SVMHandDetector::separate(const cv::Mat &srcImage, const Mat &fgImage, cv::Rect &boundingBox )
{
	Mat image, im;
	int kk[] = {1, 2, 3, 4, 5, 6, 7, 8};
	Mat q, qq;

	cvtColor(srcImage,q,CV_BGR2GRAY);
//	equalizeHist(q,q);
//	imshow("12", q);
	for (int k = 5; k < 6; k++)
	{
		float kf = (float)kk[k] / 8.0;
		Size newSize = Size(q.size().width * kf, q.size().height * kf);
		//	cout << newSize.width << endl;
		resize(q, image, newSize );
		resize(srcImage, im, newSize );
		cnt++;
		imshow("image", im);
		if (cnt == 10)
		{
			cnt = 0;
		}
		else
		{
			continue;
		}
	//	cvtColor(image,image,CV_BGR2YCrCb);
		//resize(qq, fg, newSize );
		for (int i = 0; i < image.rows - 64; i+=12)
			for (int j = 0; j < image.cols - 64; j+=12)
			{
				Rect r = Rect(j, i, 64, 64);
				Mat asd = image(r);
				Mat g;
				asd.copyTo(g);

				vector<float> d;
				hog->compute(g, d, Size(8,8), Size(0,0));
				Mat ts(d);

				if (svm.predict(ts) == 1)
				{
					boundingBox = r;
					rectangle(im, r, Scalar(150, 100, 255), 2);
					imshow("image",im);
					ostringstream ou;
//					ou << "./grayNeg3/";
//					ou << cnt++;
//					ou << ".png";
//					imwrite(ou.str(), g);
				}
			}
	}
	return false;
}

SVMHandDetector::~SVMHandDetector()
{
	delete hog;
}
