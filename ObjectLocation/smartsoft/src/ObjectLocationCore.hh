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
#ifndef _OBJECTLOCATIONCORE_HH
#define _OBJECTLOCATIONCORE_HH
	
#include "aceSmartSoft.hh"
#include <iostream>

#include <CommBasicObjects/CommPosition3d.hh>

class ObjectLocationCore
{
private:

public:
	std::vector<CommBasicObjects::CommPosition3d> obj_pos_list;

	ObjectLocationCore();
};
	
#endif
