#ifndef HANDDETECTOR_H
#define HANDDETECTOR_H

#include <opencv2/core/core.hpp>

class HandDetector
{
public:
	virtual bool separate( const cv::Mat &srcImage, const cv::Mat &fgImage, cv::Rect &result) = 0;
	virtual ~HandDetector();
};

#endif // HANDDETECTOR_H
