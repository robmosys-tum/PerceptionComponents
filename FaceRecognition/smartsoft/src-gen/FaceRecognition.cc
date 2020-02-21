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
#include "FaceRecognition.hh"
#include "smartTimedTaskTrigger.h"
//FIXME: implement logging
//#include "smartGlobalLogger.hh"

// the ace port-factory is used as a default port-mapping
#include "FaceRecognitionAcePortFactory.hh"


// initialize static singleton pointer to zero
FaceRecognition* FaceRecognition::_faceRecognition = 0;

// constructor
FaceRecognition::FaceRecognition()
{
	std::cout << "constructor of FaceRecognition\n";
	
	// set all pointer members to NULL
	recognitionQueryServiceAnsw = NULL;
	recognitionQueryServiceAnswInputTaskTrigger = NULL;
	recognitionQueryServiceAnswHandler = NULL;
	stateChangeHandler = NULL;
	stateSlave = NULL;
	wiringSlave = NULL;
	
	// set default ini parameter values
	connections.component.name = "FaceRecognition";
	connections.component.initialComponentMode = "Neutral";
	connections.component.defaultScheduler = "DEFAULT";
	connections.component.useLogger = false;
	
	connections.recognitionQueryServiceAnsw.serviceName = "RecognitionQueryServiceAnsw";
	connections.recognitionQueryServiceAnsw.roboticMiddleware = "ACE_SmartSoft";
	
	// initialize members of FaceRecognitionROSExtension
	
	// initialize members of PlainOpcUaFaceRecognitionExtension
	
}

void FaceRecognition::addPortFactory(const std::string &name, FaceRecognitionPortFactoryInterface *portFactory)
{
	portFactoryRegistry[name] = portFactory;
}

void FaceRecognition::addExtension(FaceRecognitionExtension *extension)
{
	componentExtensionRegistry[extension->getName()] = extension;
}

SmartACE::SmartComponent* FaceRecognition::getComponentImpl()
{
	return dynamic_cast<FaceRecognitionAcePortFactory*>(portFactoryRegistry["ACE_SmartSoft"])->getComponentImpl();
}

/**
 * Notify the component that setup/initialization is finished.
 * You may call this function from anywhere in the component.
 *
 * Set component's internal lifecycle state automaton (if any) into 
 * Alive mode (from here on the component is ready to provide its services)
 */
void FaceRecognition::setStartupFinished() {
	stateSlave->setWaitState("Alive");
	std::cout << "ComponentDefinition initialization/startup finished." << std::endl;
}




/**
 * First connect ALL client ports contained in this component, then start all services:
 * activate state, push, etc...
 */
Smart::StatusCode FaceRecognition::connectAndStartAllServices() {
	Smart::StatusCode status = Smart::SMART_OK;
	
	return status;
}

/**
 * Start all tasks contained in this component.
 */
void FaceRecognition::startAllTasks() {
}

/**
 * Start all timers contained in this component
 */
void FaceRecognition::startAllTimers() {
}


Smart::TaskTriggerSubject* FaceRecognition::getInputTaskTriggerFromString(const std::string &client)
{
	
	return NULL;
}


void FaceRecognition::init(int argc, char *argv[])
{
	try {
		Smart::StatusCode status;
		
		// load initial parameters from ini-file (if found)
		loadParameter(argc, argv);
		
		
		// initializations of FaceRecognitionROSExtension
		
		// initializations of PlainOpcUaFaceRecognitionExtension
		
		
		// initialize all registered port-factories
		for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
		{
			portFactory->second->initialize(this, argc, argv);
		}
		
		// initialize all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->initialize(this, argc, argv);
		}
		
		FaceRecognitionPortFactoryInterface *acePortFactory = portFactoryRegistry["ACE_SmartSoft"];
		if(acePortFactory == 0) {
			std::cerr << "ERROR: acePortFactory NOT instantiated -> exit(-1)" << std::endl;
			exit(-1);
		}
		
		// this pointer is used for backwards compatibility (deprecated: should be removed as soon as all patterns, including coordination, are moved to port-factory)
		SmartACE::SmartComponent *component = dynamic_cast<FaceRecognitionAcePortFactory*>(acePortFactory)->getComponentImpl();
		
		std::cout << "ComponentDefinition FaceRecognition is named " << connections.component.name << std::endl;
		
		if(connections.component.useLogger == true) {
			//FIXME: use logging
			//Smart::LOGGER->openLogFileInFolder("data/"+connections.component.name);
			//Smart::LOGGER->startLogging();
		}

		// create event-test handlers (if needed)
		
		// create server ports
		// TODO: set minCycleTime from Ini-file
		recognitionQueryServiceAnsw = portFactoryRegistry[connections.recognitionQueryServiceAnsw.roboticMiddleware]->createRecognitionQueryServiceAnsw(connections.recognitionQueryServiceAnsw.serviceName);
		recognitionQueryServiceAnswInputTaskTrigger = new Smart::QueryServerTaskTrigger<DomainVision::CommVideoImage, CommPerception::CommLabel,SmartACE::QueryId>(recognitionQueryServiceAnsw);
		
		// create client ports
		
		// create InputTaskTriggers and UpcallManagers
		
		// create input-handler
		
		// create request-handlers
		recognitionQueryServiceAnswHandler = new RecognitionQueryServiceAnswHandler(recognitionQueryServiceAnsw);
		
		// create state pattern
		stateChangeHandler = new SmartStateChangeHandler();
		stateSlave = new SmartACE::StateSlave(component, stateChangeHandler);
		status = stateSlave->setUpInitialState(connections.component.initialComponentMode);
		if (status != Smart::SMART_OK) std::cerr << status << "; failed setting initial ComponentMode: " << connections.component.initialComponentMode << std::endl;
		// activate state slave
		status = stateSlave->activate();
		if(status != Smart::SMART_OK) std::cerr << "ERROR: activate state" << std::endl;
		
		wiringSlave = new SmartACE::WiringSlave(component);
		// add client port to wiring slave
		
		
		
		
		// link observers with subjects
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std exception" << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}

// run the component
void FaceRecognition::run()
{
	stateSlave->acquire("init");
	// startup all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onStartup();
	}
	
	// startup all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onStartup();
	}
	stateSlave->release("init");
	
	// do not call this handler within the init state (see above) as this handler internally calls setStartupFinished() (this should be fixed in future)
	compHandler.onStartup();
	
	// this call blocks until the component is commanded to shutdown
	stateSlave->acquire("shutdown");
	
	// shutdown all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->onShutdown();
	}
	
	// shutdown all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->onShutdown();
	}
	
	if(connections.component.useLogger == true) {
		//FIXME: use logging
		//Smart::LOGGER->stopLogging();
	}
	
	compHandler.onShutdown();
	
	stateSlave->release("shutdown");
}

// clean-up component's resources
void FaceRecognition::fini()
{
	// unlink all observers
	
	// destroy all task instances

	// destroy all input-handler

	// destroy InputTaskTriggers and UpcallManagers

	// destroy client ports

	// destroy server ports
	delete recognitionQueryServiceAnsw;
	delete recognitionQueryServiceAnswInputTaskTrigger;
	// destroy event-test handlers (if needed)
	
	// destroy request-handlers
	delete recognitionQueryServiceAnswHandler;
	
	delete stateSlave;
	// destroy state-change-handler
	delete stateChangeHandler;
	
	// destroy all master/slave ports
	delete wiringSlave;
	

	// destroy all registered component-extensions
	for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
	{
		extension->second->destroy();
	}

	// destroy all registered port-factories
	for(auto portFactory = portFactoryRegistry.begin(); portFactory != portFactoryRegistry.end(); portFactory++) 
	{
		portFactory->second->destroy();
	}
	
	// destruction of FaceRecognitionROSExtension
	
	// destruction of PlainOpcUaFaceRecognitionExtension
	
}

void FaceRecognition::loadParameter(int argc, char *argv[])
{
	/*
	 Parameters can be specified via command line --filename=<filename> or -f <filename>

	 With this parameter present:
	   - The component will look for the file in the current working directory,
	     a path relative to the current directory or any absolute path
	   - The component will use the default values if the file cannot be found

	 With this parameter absent:
	   - <Name of Component>.ini will be read from current working directory, if found there
	   - $SMART_ROOT/etc/<Name of Component>.ini will be read otherwise
	   - Default values will be used if neither found in working directory or /etc
	 */
	SmartACE::SmartIniParameter parameter;
	std::ifstream parameterfile;
	bool parameterFileFound = false;

	// load parameters
	try
	{
		// if paramfile is given as argument
		if(parameter.tryAddFileFromArgs(argc,argv,"filename", 'f'))
		{
			parameterFileFound = true;
			std::cout << "parameter file is loaded from an argv argument \n";
		} else if(parameter.searchFile("FaceRecognition.ini", parameterfile)) {
			parameterFileFound = true;
			std::cout << "load FaceRecognition.ini parameter file\n";
			parameter.addFile(parameterfile);
		} else {
			std::cout << "WARNING: FaceRecognition.ini parameter file not found! (using default values or command line arguments)\n";
		}
		
		// add command line arguments to allow overwriting of parameters
		// from file
		parameter.addCommandLineArgs(argc,argv,"component");
		
		// initialize the naming service using the command line parameters parsed in the
		// SmartIniParameter class. The naming service parameters are expected to be in
		// the "component" parameter group.
		SmartACE::NAMING::instance()->checkForHelpArg(argc,argv);
		if(parameterFileFound) 
		{
			if(SmartACE::NAMING::instance()->init(parameter.getAllParametersFromGroup("component")) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		} else {
			if(SmartACE::NAMING::instance()->init(argc, argv) != 0) {
				// initialization of naming service failed
				throw std::logic_error( "<NamingService> Service initialization failed!\nPossible causes could be:\n-> Erroneous configuration.\n-> Naming service not reachable.\n" );
			}
		}
			
		// print all known parameters
		// parameter.print();
		
		//--- server port // client port // other parameter ---
		// load parameter
		parameter.getString("component", "name", connections.component.name);
		parameter.getString("component", "initialComponentMode", connections.component.initialComponentMode);
		if(parameter.checkIfParameterExists("component", "defaultScheduler")) {
			parameter.getString("component", "defaultScheduler", connections.component.defaultScheduler);
		}
		if(parameter.checkIfParameterExists("component", "useLogger")) {
			parameter.getBoolean("component", "useLogger", connections.component.useLogger);
		}
		
		
		// load parameters for server RecognitionQueryServiceAnsw
		parameter.getString("RecognitionQueryServiceAnsw", "serviceName", connections.recognitionQueryServiceAnsw.serviceName);
		if(parameter.checkIfParameterExists("RecognitionQueryServiceAnsw", "roboticMiddleware")) {
			parameter.getString("RecognitionQueryServiceAnsw", "roboticMiddleware", connections.recognitionQueryServiceAnsw.roboticMiddleware);
		}
		
		
		// load parameters for FaceRecognitionROSExtension
		
		// load parameters for PlainOpcUaFaceRecognitionExtension
		
		
		// load parameters for all registered component-extensions
		for(auto extension = componentExtensionRegistry.begin(); extension != componentExtensionRegistry.end(); extension++) 
		{
			extension->second->loadParameters(parameter);
		}
		
	
	} catch (const SmartACE::IniParameterError & e) {
		std::cerr << e.what() << std::endl;
	} catch (const std::exception &ex) {
		std::cerr << "Uncaught std::exception: " << ex.what() << std::endl;
	} catch (...) {
		std::cerr << "Uncaught exception" << std::endl;
	}
}