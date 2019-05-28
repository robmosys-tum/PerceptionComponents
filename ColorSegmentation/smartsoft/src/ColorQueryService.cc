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
#include "ColorQueryService.hh"
#include "ColorSegmentation.hh"

ColorQueryService::ColorQueryService(Smart::IQueryServerPattern<CommObjectRecognitionObjects::CommColorDetection, CommObjectRecognitionObjects::CommPoint2d, SmartACE::QueryId>* server)
:	ColorQueryServiceCore(server)
{
	
}

ColorQueryService::~ColorQueryService()
{
	
}
CommObjectRecognitionObjects::ROI ColorQueryService::fixROI(CommObjectRecognitionObjects::ROI input, int imagewidth, int imageheight )
{//(a<b?a:b);

	CommObjectRecognitionObjects::ROI roiFixed;
	CommObjectRecognitionObjects::CommPoint2d point;

	point.setX(input.getPoint().getX() < 0 ? 0:input.getPoint().getX());
	point.setY(input.getPoint().getY() < 0 ? 0:input.getPoint().getY());
	roiFixed.setPoint(point);

	int roiWidth = input.getPoint().getX() + input.getWidth() <= imagewidth - 1? \
			input.getWidth() : imagewidth - input.getPoint().getX() - 1;
	int roiHeight = input.getPoint().getY() + input.getHeight() <= imageheight - 1?\
			input.getHeight() : imageheight - input.getPoint().getY() - 1;
	roiFixed.setWidth(roiWidth);
	roiFixed.setHeight(roiHeight);

	std::cout<< "[ColorQueryService-fixROI] image  width:"<< imagewidth <<\
			", height:"<<imageheight<<std::endl;

	std::cout<< "[ColorQueryService-fixROI] oldROI  x:"<<input.getPoint().getX()<<\
			", y:"<<input.getPoint().getY()<<\
			", width:"<<input.getWidth()<<\
			", height:"<<input.getHeight()<<std::endl;

	std::cout<< "[ColorQueryService-fixROI] newROI  x:"<<roiFixed.getPoint().getX()<<\
			", y:"<<roiFixed.getPoint().getY()<<\
			", width:"<<roiFixed.getWidth()<<\
			", height:"<<roiFixed.getHeight()<<std::endl;

	return roiFixed;

}

void ColorQueryService::handleQuery(const SmartACE::QueryId &id, const CommObjectRecognitionObjects::CommColorDetection& request) 
{
	CommObjectRecognitionObjects::CommPoint2d answer;
	answer.setX(-1);
	answer.setY(-1);

	if(COMP->newestImageStatus == Smart::SMART_OK){

		CommObjectRecognitionObjects::ROI roiFixed;
		cv::Mat image = COMP->getMat(COMP->newestImage), subImg;
		cv::imwrite("completeiamge.png", image);

		if(request.getRoi().getWidth() * request.getRoi().getHeight() == 0 ){
			subImg = image;
			std::cout<< "[ColorQueryService] ROI not available "<<std::endl;
		}else{
			std::cout<< "[ColorQueryService] using ROI : "<<request.getRoi().getWidth() <<" - "<<request.getRoi().getHeight() <<std::endl;
			roiFixed = fixROI(request.getRoi(), image.size().width, image.size().height);
			subImg = image(cv::Range(roiFixed.getPoint().getY(), roiFixed.getPoint().getY() + roiFixed.getHeight()),
					cv::Range(roiFixed.getPoint().getX() , roiFixed.getPoint().getX() + roiFixed.getWidth()));   //TODO
			cv::imwrite("subimage.png", subImg);
		}

		//Check color
		CommObjectRecognitionObjects::Color color;
		CommObjectRecognitionObjects::HSVSpace min_range = request.getColor().getMin_range(), max_range = request.getColor().getMax_range();
		if(min_range.getH() == 0 && min_range.getS() == 0 && min_range.getV() == 0 ){
			if(max_range.getH() == 0 && max_range.getS() == 0 && max_range.getV() == 0 ){
				color = COMP->getColor(request.getColor().getName());
				std::cout<< "[ColorQueryService] using default values of color : "<<request.getColor().getName()<<std::endl;
			}
		}
		else
			color = request.getColor();

		cv::Mat mask = COMP->segmentation(subImg, color);
		cv::imwrite("maskimage.png", mask);

		double min, max;
		cv::minMaxLoc(mask, &min, &max);
		if (max > 0)
		{

			cv::Point p_object = COMP->countour(mask);
			if(request.getRoi().getWidth() *request.getRoi().getHeight() != 0 ){
				p_object.x += roiFixed.getPoint().getX() ;
				p_object.y += roiFixed.getPoint().getY() ;
			}

			answer.setX(p_object.x);
			answer.setY(p_object.y);
		}
		else
			std::cout<< "[ColorQueryService] Object not detected "<<std::endl;
	}
	else
		std::cout<< "[ColorQueryService] Failed attempt, no images of the sensor were received"<<std::endl;

	this->server->answer(id, answer);


}
