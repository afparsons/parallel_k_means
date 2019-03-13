/**
 * COMP 481: Applied Parallel Algorithms
 * Dr. Sandino Vargas-Perez
 * Final Project - Parallelized K-Means Clustering
 * 14 February 2019
 * Andrew Parsons
 * This program is based heavily upon the following two implementations:
 * https://github.com/aditya1601/kmeans-clustering-cpp/blob/master/kmeans.cpp
 * https://github.com/marcoscastro/kmeans/blob/master/kmeans.cpp
 * Our plan is to extend this program's functionality through parallelization
 * and by integrating plaintext processing functionality.
 * 
 * === === === cluster.cpp === === === === === === === === === ===
 * 
 * This class defines a cluster object.
 * TODO: split into header (.hpp) and implementation (.cpp)
 */

#ifndef CLUSTER
#define CLUSTER

/* === === === INCLUDES === === === === === === */
#include <vector> 

/* custom classes */
#include "point.cpp"

/* === === === CLASS DEFINITION === === === === === === */
class Cluster {
    private:
        // id of the cluster
        int id_cluster;
        
        // list of attribute values of the centroid
        std::vector<double> centroid_attribute_values;

        // list of points belonging to this cluster
        std::vector<Point> list_points;
    
    public:
        /**
         * Constructor.
         * @param int, id_cluster: unique key
         * @param Point, centroid: the centroid point of the cluster
         */
        Cluster(int id_cluster, Point centroid) {

            this->id_cluster = id_cluster;
            // TODO: describe this
            for ( double attribute_value : centroid.get_attribute_values()) {
                this->centroid_attribute_values.push_back(attribute_value);
            }

            this->insert_point_into_cluster(centroid);
        // ? perhaps implement the 'Rule of Three/Five' for the constructor
        }

        // TODO: better return type
        /**
         * desc
         */
        void insert_point_into_cluster(Point point) {
            point.set_id_cluster(id_cluster);
            list_points.push_back(point);
        }

        /**
         * desc
         * ? Should this take param type point?
         * ! this would be better with a map?
         */
        bool remove_point_from_cluster(int id_point) {
            
            for (int i = 0; i < list_points.size(); i++) {
                if (list_points[i].get_id_point() == id_point) {
                    list_points.erase(list_points.begin() + i);
                    // if found and removed, return true
                    return true;
                }
            }
            // if not found in the list, return false
            return false;
        }

        /**
         * get
         */
        int get_id_cluster() {
            return id_cluster;
        } 

        /**
         * get
         */
        std::vector<Point> get_list_points() {
           return list_points; 
        }

        /**
         * get
         */
        Point get_point(int index) {
            return list_points[index];
        }

        /**
         * get
         */
        int get_num_points() {
            return list_points.size();
        }

        /**
         * get
         */
        double get_centroid_attribute_value(int index) {
            return centroid_attribute_values[index];
        }

        /**
         * set
         */
        void set_centroid_attribute_value(int index, double value){
            this->centroid_attribute_values[index] = value;
        }

};

#endif