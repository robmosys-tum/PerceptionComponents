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
#include "RecognitionQueryServiceAnswHandler.hh"
#include "ComponentFaceRecognition.hh"

RecognitionQueryServiceAnswHandler::RecognitionQueryServiceAnswHandler(IQueryServer *server)
:	RecognitionQueryServiceAnswHandlerCore(server)
{
	
}


void RecognitionQueryServiceAnswHandler::handleQuery(const Smart::QueryIdPtr &id, const DomainVision::CommVideoImage& request) 
{
	CommPerception::CommLabel answer;
	
	// implement your query handling logic here and fill in the answer object
	cv::Mat input(cv::Size(request.get_width(), request.get_height()), CV_8UC3, (void*)request.get_data());

	answer.setName(COMP->recognize(input));
	this->server->answer(id, answer);
}
