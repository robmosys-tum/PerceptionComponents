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
#include "ObjectQueryServiceAnswHandler.hh"
#include "ObjectDetection.hh"
#include <thread>
#include <chrono>


ObjectQueryServiceAnswHandler::ObjectQueryServiceAnswHandler(Smart::IQueryServerPattern<CommPerception::CommInfDetection, CommPerception::CommObjectRecognitionObjectProperties, SmartACE::QueryId>* server)
:	ObjectQueryServiceAnswHandlerCore(server)
{
	
}

ObjectQueryServiceAnswHandler::~ObjectQueryServiceAnswHandler()
{
	
}

void ObjectQueryServiceAnswHandler::setAnswer(CommPerception::CommPoint2d input)
{
	this->serviceAnswer = input ;
}

void ObjectQueryServiceAnswHandler::handleQuery(const SmartACE::QueryId &id, const CommPerception::CommInfDetection& request) 
{
	CommPerception::CommObjectProperties answer;
	

	COMP->roiObject = request.getRoi();

	if (request.getColor().getName() != CommPerception::Colors::UNDEFINED ){
		COMP->evaluateColorSegmentation = true;
		COMP->colorObject = request.getColor();
	}

	if (request.getShape().getName() == CommPerception::Shapes::SPHERE ||
		request.getShape().getName() == CommPerception::Shapes::CUBE ||
		request.getShape().getName() == CommPerception::Shapes::CYLINDER){
		std::cout<< "[ObjectRecognitionQueryServiceAnsw] Shape"<<std::endl;
		COMP->evaluateShape = true;
		COMP->shapeObject = request.getShape();
	}


	//std::cout<< "[ObjectRecognitionQuery] roi width:"<<request.getRoi().getWidth() <<", height:"<<request.getRoi().getHeight()<<std::endl;

	CommBasicObjects::CommPose3d p_object;
	p_object.set_x(-1);
	p_object.set_y(-1);
	p_object.set_z(-1);


	if (COMP->colorSegmentation_point.getX() > 0 && COMP->colorSegmentation_point.getY() > 0)
		if(COMP->depthImageObjectStatus == Smart::SMART_OK)
			p_object = COMP->get3dPoint (COMP->colorSegmentation_point, COMP->getDepthImage());
		else
			std::cout<< "Depth image not available"<<std::endl;

	if (COMP->shape_pose.get_position().getX() !=-1 && COMP->shape_pose.get_position().getY() !=-1 && COMP->shape_pose.get_position().getZ() !=-1)
		p_object = COMP->shape_pose;

	answer.setPose(p_object);

	
	this->server->answer(id, answer);

}

