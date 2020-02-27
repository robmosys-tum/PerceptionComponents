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
#include "ComponentFaceRecognitionCore.hh"

// constructor
ComponentFaceRecognitionCore::ComponentFaceRecognitionCore()
{
	std::cout << "constructor ComponentFaceRecognitionCore\n";

	model = new Facenet(default_graph_path, default_database_path);


}

string ComponentFaceRecognitionCore::recognize(cv::Mat image)
{
	return model->recognize(image);
}
