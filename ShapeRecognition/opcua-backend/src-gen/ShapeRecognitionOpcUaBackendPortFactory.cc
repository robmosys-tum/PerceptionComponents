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
// Please do not modify this file. It will be re-generated
// running the code generator.
//--------------------------------------------------------------------------

#include "ShapeRecognitionOpcUaBackendPortFactory.hh"

// include all potentially required pattern implementations
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/PushClient.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/EventClient.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/QClientOPCUA.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/SendClient.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Client/QueryClient.hpp>

#include <SeRoNetSDK/SeRoNet/OPCUA/Server/PushServer.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Server/EventServer.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Server/SendServer.hpp>
#include <SeRoNetSDK/SeRoNet/OPCUA/Server/QueryServer.hpp>

// include referenced CommunicationObject SeRoNetSDK self description implementations
#include "CommPerceptionOpcUa/CommInfDetectionOpcUa.hh"
#include "CommPerceptionOpcUa/CommObjectPropertiesOpcUa.hh"
#include "DomainVisionOpcUa/Comm3dPointCloudOpcUa.hh"

// create a static instance of the OpcUaBackendPortFactory
static ShapeRecognitionOpcUaBackendPortFactory OpcUaBackendPortFactory;

ShapeRecognitionOpcUaBackendPortFactory::ShapeRecognitionOpcUaBackendPortFactory()
{  
	componentImpl = 0;
	ShapeRecognition::instance()->addPortFactory("OpcUa_SeRoNet", this);
}

ShapeRecognitionOpcUaBackendPortFactory::~ShapeRecognitionOpcUaBackendPortFactory()
{  }

void ShapeRecognitionOpcUaBackendPortFactory::initialize(ShapeRecognition *component, int argc, char* argv[])
{
	componentImpl = new SeRoNet::Utils::Component(component->connections.component.name);
}

int ShapeRecognitionOpcUaBackendPortFactory::onStartup()
{
	if (!component_thread.joinable()) {
    	component_thread = std::thread(&ShapeRecognitionOpcUaBackendPortFactory::task_execution, this);
    	return 0;
    }
	return -1;
}

Smart::IPushClientPattern<DomainVision::Comm3dPointCloud> * ShapeRecognitionOpcUaBackendPortFactory::createPointCloudPushServiceIn()
{
	return new SeRoNet::OPCUA::Client::PushClient<DomainVision::Comm3dPointCloud>(componentImpl);
}


Smart::IQueryServerPattern<CommPerception::CommInfDetection, CommPerception::CommObjectProperties> * ShapeRecognitionOpcUaBackendPortFactory::createObjectQueryServiceAnsw(const std::string &serviceName)
{
	return new SeRoNet::OPCUA::Server::QueryServer<CommPerception::CommInfDetection, CommPerception::CommObjectProperties>(componentImpl, serviceName);
}


int ShapeRecognitionOpcUaBackendPortFactory::task_execution()
{
	componentImpl->run();
	return 0;
}

int ShapeRecognitionOpcUaBackendPortFactory::onShutdown(const std::chrono::steady_clock::duration &timeoutTime)
{
	// stop component-internal infrastructure
	componentImpl->stopRunning();
	// wait on component thread to exit
	if (component_thread.joinable()) {
		// FIXME: don't wait infinetly (use timeoutTime here)
    	component_thread.join();
    }
	return 0;
}

void ShapeRecognitionOpcUaBackendPortFactory::destroy()
{
	// clean-up component's internally used resources
	delete componentImpl;
}
