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
#include <DomainVision/CommRGBDImage.hh>
#include <CommBasicObjects/CommPosition3d.hh>
#include <CommBasicObjects/CommPose3d.hh>
#include <CommPerception/Box.hh>
//#include <CommPerception/CommInfDetection.hh>
#include <CommPerception/CommObjectProperties.hh>

#include <vector>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/filesystem.hpp>

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
//#include <opencv2/tracking.hpp>
//#include <opencv2/core/ocl.hpp>
//#include "opencv2/core/core.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/features2d/features2d.hpp"
// #include "opencv2/nonfree/features2d.hpp"
// #include "opencv2/nonfree/nonfree.hpp"
#include "opencv2/xfeatures2d/nonfree.hpp"

using namespace boost::filesystem;


struct box_obj {
  cv::Point p1;
  cv::Point p2;
  cv::Point p3;
  cv::Point p4;
};



class CaptureSensor  : public CaptureSensorCore
{
private:
	bool _is_on;
	DomainVision::CommVideoImage rGBImageObject;
	DomainVision::CommDepthImage depthImageObject;
	Smart::StatusCode rGBImageObjectStatus;
	Smart::StatusCode depthImageObjectStatus;

	//Parameters
	std::vector<float> colorcamera_info;

	//Database Values
	std::string db_path;
	bool train_succes;
	std::vector<cv::Mat> db_dscr;
	std::vector<std::string> db_label;
	std::vector<std::vector<cv::KeyPoint>> db_kp;
	std::vector<int> db_width;
	std::vector<int> db_heigth;

	//Detection Information
	std::vector<cv::Mat> detected_imgs;
	std::vector<CommBasicObjects::CommPose3d> detected_pose;
	std::vector<CommPerception::Box> detected_roi;
	std::vector<std::string> detected_label;

	//Features and Matching
	cv::Ptr<cv::Feature2D> detector;
	cv::Ptr<cv::Feature2D> extractor;
	cv::Ptr<cv::DescriptorMatcher> matcher;

	virtual void on_RGBDImagePushServiceIn(const DomainVision::CommRGBDImage &input);

public:
	CaptureSensor(SmartACE::SmartComponent *comp);
	virtual ~CaptureSensor();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();

	//F U N C T I O N S
	bool load_database();
	cv::Mat extract_dscr(cv::Mat image_input, std::vector<cv::KeyPoint> &kp);
	std::vector<int> matching_db(cv::Mat dscr_input, std::vector< std::vector<cv::DMatch> > &matches) ;
	void remove_duplicates(std::vector<box_obj> &objs, std::vector<cv::Rect> &objs_rects);
	void point_to_position(cv::Point point2d, CommBasicObjects::CommPosition3d &point3d);
	CommBasicObjects::CommPose3d point2d_to_pose(cv::Point point_in);


};

#endif