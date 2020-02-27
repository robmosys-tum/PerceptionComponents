//--------------------------------------------------------------------------
// Code generated by the SmartSoft MDSD Toolchain
// The SmartSoft Toolchain has been developed by:
//  
// Service Robotics Research Center
// University of Applied Sciences Ulm
// Prittwitzstr. 10
// 89075 Ulm (Germany)
//
// Information about the SmartSoft MDSD Toolchain is available at:
// www.servicerobotik-ulm.de
//
// This file is generated once. Modify this file to your needs. 
// If you want the toolchain to re-generate this file, please 
// delete it before running the code generator.
//--------------------------------------------------------------------------
#ifndef _CAPTURESENSOR_HH
#define _CAPTURESENSOR_HH

#include "CaptureSensorCore.hh"
#include "DomainVision/CommVideoImage.hh"
#include "CommPerception/CommPoint2d.hh"
#include "CommPerception/CommPoint3d.hh"
#include "CommPerception/CommLabel.hh"

#include <smartIniParameter.hh>

#include <opencv2/objdetect.hpp>
#include <opencv2/imgproc.hpp>

#include <vector>
#include <string>

#include "mtcnn.h"

class CaptureSensor  : public CaptureSensorCore
{
public:
	CaptureSensor(SmartACE::SmartComponent *comp);
	virtual ~CaptureSensor();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();

private:
	//DomainVision::CommVideoImage _input_image;
	DomainVision::CommVideoImage _rgb_input;
	DomainVision::CommRGBDImage _rgbd_input;

	// MTCNN model
	mtcnn* _mtcnn;

	void fromVideo2Mat(const DomainVision::CommVideoImage& input, cv::Mat& rgb_img);
	void fromDepth2Mat(const DomainVision::CommDepthImage& input, cv::Mat& depth_img);
	void fromRGBD2Mat(const DomainVision::CommRGBDImage& input, cv::Mat& rgb_img, cv::Mat& depth_img);
	//void on_RGBImagePushServiceIn(const DomainVision::CommVideoImage &rgb_input);
	void on_RGBDImagePushServiceIn(const DomainVision::CommRGBDImage &input);

	CommBasicObjects::CommPosition3d from2dTo3d(double x, double y, double depth, double fx, double fy, double cx, double cy);

	cv::Mat getMat(const DomainVision::CommVideoImage &input);

};

#endif
