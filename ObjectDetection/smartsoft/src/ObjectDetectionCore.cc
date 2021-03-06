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
#include "ObjectDetectionCore.hh"
#include <DomainVision/CommRGBDImage.hh>
// constructor
ObjectDetectionCore::ObjectDetectionCore()
{
	std::cout << "constructor ObjectDetectionCore\n";
	evaluateColorSegmentation = false;
	evaluateShape = false;
	colorSegmentation_point.setX(-1).setY(-1);
	CommBasicObjects::CommPosition3d pos;
	shape_pose.set_position(pos.setX(-1).setY(-1).setZ(-1));
}

void ObjectDetectionCore::setVideoImage(DomainVision::CommVideoImage input, Smart::StatusCode status)
{
	rGBImageObject = input;
	rGBImageObjectStatus = status;
}

DomainVision::CommVideoImage ObjectDetectionCore::getVideoImage()
{
	return this->rGBImageObject ;
}

void ObjectDetectionCore::setDepthImage(DomainVision::CommDepthImage input, Smart::StatusCode status)
{
	depthImageObject = input;
	depthImageObjectStatus = status;
}

DomainVision::CommDepthImage ObjectDetectionCore::getDepthImage()
{
	return this->depthImageObject ;
}
cv::Mat ObjectDetectionCore::getImageMat(const DomainVision::CommVideoImage input)
{

	std::cout << "[ColorSegmentationCore] get_Mat\n";
	const unsigned char *color_frame;

	color_frame = input.get_data();

	const int w = input.get_width();
	const int h = input.get_height();

	cv::Mat image(cv::Size(w, h), CV_8UC3, (void*)input.get_data());

	return image;
}
//cv::Mat ObjectDetectionCore::getDepthMat(const DomainVision::CommDepthImage input)
//{
//
//	std::cout << "[ColorSegmentationCore] get_Mat\n";
//	const unsigned char *color_frame;
//
//	color_frame = input.g .get_data();
//
//	const int w = input.get_width();
//	const int h = input.get_height();
//
//	cv::Mat image(cv::Size(w, h), CV_8UC3, (void*)input.get_data());
//
//	return image;
//}

#include <string>

CommBasicObjects::CommPose3d  ObjectDetectionCore::get3dPoint (CommPerception::CommPoint2d input, DomainVision::CommDepthImage depthImage)
{
	CommBasicObjects::CommPose3d point;
	uint16_t* depth_frame = (uint16_t*)depthImage.get_distances();

	 std::cout << "The camera is facing an object " << depth_frame[240*640+320] << " meters away "<<std::endl;


	unsigned int  x = input.getX(), y = input.getY();
	double z_raw = depth_frame[x*depthImage.getWidth()+y]*depthImage.getScale();
////
//	uint16_t f = depthImage.getDataElemAtPos(y*depthImage.getWidth() + x);
////
//	float u = depth_distances[y*depthImage.getWidth() + x];
//	float z_raw = (float)depth_distances[y*depthImage.getWidth() + x];
////	//z_raw = reinterpret_cast<const float>(depthImage.getDataElemAtPos(y*640 + x);
////	//depth camera info
////	/*     |	fx	 0	  cx	0	|
////	 * M = |	0	 fy	  cy	0	|
////	 * 	   |	0	 0	  1		0 	|
////	 * 	   |	0	 0	  0		1 	|
////	 */
//////	arma::mat cameraInfo = depthImage.get_intrinsic();
	float fx = 1;//depth_info->K[0];
	float fy = 1;//depth_info->K[4];
	float cx = 320;// depth_info->K[2];
	float cy = 240;//depth_info->K[5];
////
////	float z_mean = z_raw * 0.001;
////
////
	point.set_x(((input.getX() - cx)/ fx) * z_raw  * 0.001);
	point.set_y(((input.getY() - cy)/ fy) * z_raw * 0.001);
	point.set_z(z_raw);

	std::cout<< "[ObjectDetectionCore-get3dPoint] point 2d x:"<<input.getX() <<", y:"<<input.getY()<<std::endl;
	std::cout<< "[ObjectDetectionCore-get3dPoint] point 3d size: "<<depthImage.getDataSize()<<\
			", width:"<<depthImage.getWidth()<<", height:"<<depthImage.getHeight()<<
			", x:"<<point.get_x()<< \
			", y:"<<point.get_y()<<", z:"<<point.get_z()<<std::endl;

	return point;
}
