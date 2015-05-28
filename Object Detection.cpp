#include <pcl/io/pcd_io.h>
#include <pcl/point_cloud.h>
#include <pcl/common/transforms.h>
#include <pcl/correspondence.h>
#include <pcl/features/normal_3d_omp.h>
#include <pcl/features/shot_omp.h>
#include <pcl/keypoints/uniform_sampling.h>
#include <pcl/kdtree/kdtree_flann.h>
#include <pcl/kdtree/impl/kdtree_flann.hpp>
#include <pcl/common/eigen.h>

using namespace std;
using namespace pcl;
using namespace pcl::io;

int main (int argc, char** argv)
{
	typedef PointXYZ PointType;
	typedef Normal NormalType;
	typedef ReferenceFrame RFType;
	typedef SHOT352 DescriptorType;

	PointCloud<PointType>::Ptr model_ (new PointCloud<PointType> ());
	PointCloud<PointType>::Ptr model_downsampled_ (new PointCloud<PointType> ());
	PointCloud<PointType>::Ptr scene_ (new PointCloud<PointType> ());
	PointCloud<PointType>::Ptr scene_downsampled_ (new PointCloud<PointType> ());
	PointCloud<NormalType>::Ptr model_normals_ (new PointCloud<NormalType> ());
	PointCloud<NormalType>::Ptr scene_normals_ (new PointCloud<NormalType> ());
	PointCloud<DescriptorType>::Ptr model_descriptors_ (new PointCloud<DescriptorType> ());
	PointCloud<DescriptorType>::Ptr scene_descriptors_ (new PointCloud<DescriptorType> ());
	CorrespondencesPtr model_scene_corrs_ (new Correspondences ());



 //  if (argc < 3)
 // {
  //  cerr << "No test file given. Please download `milk.pcd` and `milk_cartoon_all_small_clorox.pcd` and pass their paths to the test." << endl;
   // return (-1);
  //}

  if (loadPCDFile ("C:/Users/giki/Desktop/milk.pcd", *model_) < 0)
  {
    cerr << "Failed to read test file. Please download `milk.pcd` and pass its path to the test." << endl;
    return (-1);
  }

  if (loadPCDFile ("C:/Users/giki/Desktop/milk_cartoon_all_small_clorox.pcd", *scene_) < 0)
  {
    cerr << "Failed to read test file. Please download `milk_cartoon_all_small_clorox.pcd` and pass its path to the test." << endl;
    return (-1);
  }
//Normals
  NormalEstimationOMP<PointType, NormalType> norm_est;
  norm_est.setKSearch (10);
  norm_est.setInputCloud (model_);
  norm_est.compute (*model_normals_);

  norm_est.setInputCloud (scene_);
  norm_est.compute (*scene_normals_);

  //Downsampling
  PointCloud<int> sampled_indices;
  UniformSampling<PointType> uniform_sampling;
  uniform_sampling.setInputCloud (model_);
  uniform_sampling.setRadiusSearch (0.005);
  uniform_sampling.compute (sampled_indices);
  copyPointCloud (*model_, sampled_indices.points, *model_downsampled_);

  uniform_sampling.setInputCloud (scene_);
  uniform_sampling.setRadiusSearch (0.02);
  uniform_sampling.compute (sampled_indices);
  copyPointCloud (*scene_, sampled_indices.points, *scene_downsampled_);

  //Descriptor
  SHOTEstimationOMP<PointType, NormalType, DescriptorType> descr_est;
  descr_est.setRadiusSearch (0.015);
  descr_est.setInputCloud (model_downsampled_);
  descr_est.setInputNormals (model_normals_);
  descr_est.setSearchSurface (model_);
  descr_est.compute (*model_descriptors_);

  descr_est.setInputCloud (scene_downsampled_);
  descr_est.setInputNormals (scene_normals_);
  descr_est.setSearchSurface (scene_);
  descr_est.compute (*scene_descriptors_);

  //Correspondences with KdTree
  KdTreeFLANN<DescriptorType> match_search;
  match_search.setInputCloud (model_descriptors_);

  for (size_t i = 0; i < scene_descriptors_->size (); ++i)
  {
    if ( pcl_isfinite( scene_descriptors_->at (i).descriptor[0] ) )
    {
      vector<int> neigh_indices (1);
      vector<float> neigh_sqr_dists (1);
      int found_neighs = match_search.nearestKSearch (scene_descriptors_->at(i), 1, neigh_indices, neigh_sqr_dists);
      if(found_neighs == 1 && neigh_sqr_dists[0] < 0.25f)
      {
        Correspondence corr (neigh_indices[0], static_cast<int> (i), neigh_sqr_dists[0]);
        model_scene_corrs_->push_back (corr);
      }
    }
  }

  return 0;
}