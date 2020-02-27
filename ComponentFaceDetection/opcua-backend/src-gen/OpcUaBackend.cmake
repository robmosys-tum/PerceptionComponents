CMAKE_MINIMUM_REQUIRED(VERSION 3.5)

FIND_PACKAGE(Open62541Cpp QUIET)
SET(SmartSoft_CD_API_DIR $ENV{SMART_ROOT_ACE}/modules)
FIND_PACKAGE(SeRoNetSDK QUIET)

IF(SeRoNetSDK_FOUND)
	FIND_PACKAGE(CommPerceptionOpcUa PATHS $ENV{SMART_ROOT_ACE}/modules)
	FIND_PACKAGE(DomainVisionOpcUa PATHS $ENV{SMART_ROOT_ACE}/modules)
	SET(CMAKE_CXX_STANDARD 14)
	INCLUDE_DIRECTORIES(${CMAKE_CURRENT_LIST_DIR})
	SET(OPC_UA_BACKEND_SRCS "${CMAKE_CURRENT_LIST_DIR}/ComponentFaceDetectionOpcUaBackendPortFactory.cc")
ENDIF(SeRoNetSDK_FOUND)
