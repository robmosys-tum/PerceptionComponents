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
#ifndef _RECOGNITIONQUERYSERVICEANSWHANDLER_USER_HH
#define _RECOGNITIONQUERYSERVICEANSWHANDLER_USER_HH
		
#include "RecognitionQueryServiceAnswHandlerCore.hh"

class RecognitionQueryServiceAnswHandler : public RecognitionQueryServiceAnswHandlerCore
{
protected:
public:
	RecognitionQueryServiceAnswHandler(Smart::IQueryServerPattern<DomainVision::CommVideoImage, CommPerception::CommLabel, SmartACE::QueryId>* server);
	virtual ~RecognitionQueryServiceAnswHandler();
	virtual void handleQuery(const SmartACE::QueryId &id, const DomainVision::CommVideoImage& request);
};
#endif