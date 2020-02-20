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
#ifndef _CAPTURESENSOR_HH
#define _CAPTURESENSOR_HH

#include "CaptureSensorCore.hh"
#include <CommBasicObjects/CommPosition3d.hh>

// PCL
#include <pcl/point_cloud.h>
#include <pcl/PCLPointCloud2.h>
#include <pcl/point_types.h>
#include <pcl/filters/voxel_grid.h>
#include <pcl/filters/passthrough.h>
#include <pcl/filters/extract_indices.h>
#include <pcl/filters/filter_indices.h>
#include <pcl/sample_consensus/sac_model_line.h>
#include <pcl/search/kdtree.h>
#include <pcl/segmentation/sac_segmentation.h>
#include <pcl/segmentation/extract_clusters.h>
#include <pcl/visualization/cloud_viewer.h>
#include <pcl/filters/statistical_outlier_removal.h>

typedef pcl::PointXYZ Point;
typedef pcl::PointCloud<Point> PointCloud;

class CaptureSensor  : public CaptureSensorCore
{
private:
	PointCloud cloud_helper;

	std::vector<CommBasicObjects::CommPosition3d> obj_pos_list;


	// - - - - - Parameters - - - - - - -
	float _crop_width;
	float _crop_depth;
	float _crop_min_z;
	float _crop_max_z;
	float _leaf_size;

	void filter_removeoutliers(PointCloud::Ptr cloud_in, PointCloud::Ptr cloud_out);
	void filter_passthrough(PointCloud cloud_in, PointCloud::Ptr cloud_out);
	void filter_voxel(PointCloud::Ptr  cloud_in, PointCloud::Ptr cloud_out);
	std::vector <PointCloud::Ptr> get_clusters(PointCloud::Ptr  cloud_in);
	void extract_planar(PointCloud::Ptr  cloud_in, PointCloud::Ptr cloud_out);
	CommBasicObjects::CommPosition3d get_pose(PointCloud::Ptr  cloud_in);

public:
	CaptureSensor(SmartACE::SmartComponent *comp);
	virtual ~CaptureSensor();
	
	virtual int on_entry();
	virtual int on_execute();
	virtual int on_exit();
};

#endif
