#ifndef OPENNICONTEXT_H
#define OPENNICONTEXT_H

#include <XnOpenNI.h>
#include <XnCodecIDs.h>
#include <XnPropNames.h>
#include <XnCppWrapper.h>
//#include "SceneDrawer.h"
#include <vector>
#include <opencv2/opencv.hpp>

class OpenNIContext
{
public:
	OpenNIContext(int, char**);
	~OpenNIContext();
	void display (void);
	void update();
	void getImageMap(cv::Mat &image);
	void getDepthMap(cv::Mat &depth);
	void getHandsPositions(std::vector<std::pair<std::pair<int, int>, std::pair<int, int> > > &); // vector of users hands, left - first, right - second.
	void getHeadsPositions(std::vector<std::pair<int,int> > &);
private:
//	SceneDrawer *sceneDrawer;
	xn::Context context;
	xn::ScriptNode scriptNode;
	xn::DepthGenerator depthGenerator;
	xn::ImageGenerator imageGenerator;
	xn::UserGenerator userGenerator;
	xn::Player player;
};

#endif // OPENNICONTEXT_H
