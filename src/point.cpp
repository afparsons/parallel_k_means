/**
 * COMP 481: Applied Parallel Algorithms
 * Dr. Sandino Vargas-Perez
 * Final Project - Parallelized K-Means Clustering
 * 14 February 2019
 * Andrew Parsons, Hans Wieland
 * This program is based heavily upon the following two implementations:
 * https://github.com/aditya1601/kmeans-clustering-cpp/blob/master/kmeans.cpp
 * https://github.com/marcoscastro/kmeans/blob/master/kmeans.cpp
 * Our plan is to extend this program's functionality through parallelization
 * and by integrating plaintext processing functionality.
 * 
 * === === === point.cpp === === === === === === === === === ===
 * 
 * This class defines a point object.
 * TODO: split into header (.hpp) and implementation (.cpp)
 */

#ifndef POINT
#define POINT

/* === === === INCLUDES === === === === === === */
#include <vector> 

/* === === === CLASS DEFINITION === === === === === === */
class Point {
    private:
        int id_point;
        int id_cluster;
        int attribute_set_size;
        // ? more advanced implementation: perhaps better as a map?
        std::vector<double> attribute_values;
    
    public:    
        /**
         * Constructor.
         * @param int, id_point:                            unique key
         * @param std::vector<double>, attribute_values:    the list of attribute values for this point
         */
        Point(int id_point, std::vector<double>& attribute_values) {
            // ? is the "this->" syntax necessary ?

            // unique key            
            this->id_point = id_point;

            // the list of attribute values for this point
            this->attribute_values = attribute_values;

            // this is the "dimension" of the problem
            this->attribute_set_size = attribute_values.size();
            
            // points initially do not belong to a cluster
            this->id_cluster = -1;

            // ? perhaps implement the "Rule of Three/Five" for the constructor
        }

        /**
         * get
         */
        int get_id_point() {return id_point;}

        /**
         * get
         */
        int get_id_cluster() {return id_cluster;}

        /**
         * get
         */
        int get_attribute_set_size() {return attribute_set_size;}

        /**
         * get
         */
        std::vector<double> get_attribute_values() {
            return attribute_values;
        }

        /**
         * get
         */
        double get_attribute_value_at_index(int index) {
            return attribute_values[index];
        }

        /**
         * set
         */
        void set_id_cluster(int id_cluster) {
            this->id_cluster = id_cluster;
        }

        /**
         * print
         */
        void print_point() {
            std::cout << "Point ID: " << id_point << "\n";
            std::cout << "Cluster : " << id_cluster << "\n";
            std::cout << "=== Attribute Values ===" << "\n";
            for (double attribute_value : attribute_values) {
                std::cout << attribute_value << "\n";
            }
            std::cout << "========================" << "\n";
        }
};

#endif