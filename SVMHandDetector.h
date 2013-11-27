#ifndef SVMHANDDETECTOR_H
#define SVMHANDDETECTOR_H

#include "HandDetector.h"
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/ml/ml.hpp>

class SVMHandDetector : public HandDetector
{
public:
	SVMHandDetector( const std::string &classifierFileName );
	bool separate( const cv::Mat &srcImage, const cv::Mat &fgImage, cv::Rect &boundingBox);
	~SVMHandDetector();
private:
	cv::HOGDescriptor *hog;
	CvSVM svm;
};

#endif // SVMHANDDETECTOR_H
