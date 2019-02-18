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
 * === === === kmeans.cpp === === === === === === === === === ===
 * 
 * This class defines a KMeans object.
 * TODO: split into header (.hpp) and implementation (.cpp)
 */

#ifndef KMEANS
#define KMEANS

/* === === === INCLUDES === === === === === === */
#include <iostream>        // cout
#include <vector>          // vectors              
#include <omp.h>           // timing
#include <algorithm>       // std::find
#include <math.h>          // std::sqrt

/* custom classes */
#include "cluster.cpp"

/* === === === CLASS DEFINITION === === === === === === */
class KMeans {
    private:
        // list of clusters
        std::vector<Cluster> list_clusters;

        // number of clusters ('k')
        int k_num_clusters;

        // number of points
        int num_points;

        // maximum number of iterations
        int num_max_iterations;

        // number of attributes
        int num_attributes;

        /**
         * TODO: describe this
         * @param Point point
         * @return: the nearest id_cluster
         */
        int get_nearest_id_cluster(Point point) {

            double sum = 0.0, minimum_distance;
            int nearest_id_cluster;

            // calculate euclidean distance between the first cluster centroid and the point
            for (int i = 0; i < num_attributes; i++) {              
                sum += std::pow(list_clusters[0].get_centroid_attribute_value(i) - point.get_attribute_value_at_index(i), 2.0 );
            }

            minimum_distance = std::sqrt(sum);
            nearest_id_cluster = list_clusters[0].get_id_cluster();

            // ? why does this start at 1
            // ? What is this doing?
            // TODO: better for loop variables
            for (int i = 1; i < k_num_clusters; i++) {
                double distance;
                sum = 0.0;

                // TODO: describe this
                for (int j = 0; j < num_attributes; j++) {
                    sum += std::pow(list_clusters[i].get_centroid_attribute_value(j) - point.get_attribute_value_at_index(j), 2.0 ); 
                }

                distance = std::sqrt(sum);

                // TODO: explain!
                if (distance < minimum_distance) {
                    minimum_distance = distance;
                    nearest_id_cluster = list_clusters[i].get_id_cluster();
                }
            }

            return nearest_id_cluster;
        }


    public:

        KMeans(int k, int iterations){
            k_num_clusters = k;
            num_max_iterations = iterations;
        }

        // ! perhaps change return type
        // TODO: split into multiple functions
        /**
         * cluster()
         * --- does a thing
         * @param:
         */
        void cluster(std::vector<Point>& all_points) {

            num_points = all_points.size();
            num_attributes = all_points[0].get_attribute_set_size();

            // initialize the clusters
            // TODO: KMeans Parallel, re
            // https://www.youtube.com/watch?v=KHu8uNy4pV8
            std::vector<int> list_id_points;

            // TODO: better variable name (not 'i')
            for (int i = 0; i < k_num_clusters; i++) {
             
                while(true) {

                    // generates a point to use
                    // TODO: better variable name (not 'index')
                    int index = rand() % num_points;

                    // if the point isn't in the list
                    if ( std::find(list_id_points.begin(), list_id_points.end(), index) == list_id_points.end()) {

                        // add the point to the list
                        list_id_points.push_back(index);

                        // set root point of cluster
                        all_points[index].set_id_cluster(i);

                        // create cluster of id 'i' with the point @ index
                        Cluster cluster(i, all_points[index]);

                        // add the newly created cluster to the list
                        list_clusters.push_back(cluster);

                        // break the while
                        break;
                    }
                }
            }

            std::cout << "Initialized clusters: " << list_clusters.size() << "\n";

            // for (Cluster c : list_clusters) {
            //     for (Point p : c.get_list_points()) {
            //         std::cout << p.get_id_point() << ", ";
            //     } std::cout << "\n";
            // }

            /* begin clustering */

            int iteration = 1;

            /**
             * This is an enormous while loop.
             * We will likely need to implement a for loop for parallelization!
             * loop until max iterations
             */
            while(true) {
                // std::cout << "Iteration " << iteration << "/" << num_max_iterations << "\n";

                bool complete = true;

                // for each point
                for (int i = 0; i < num_points; i++) {

                    // get its current cluster and find the nearest cluster
                    int current_id_cluster = all_points[i].get_id_cluster();
                    int nearest_id_cluster = get_nearest_id_cluster(all_points[i]);

                    //std::cout << "Point " << i << " current: " << current_id_cluster << " | " << "Point " << i << " nearest: " << nearest_id_cluster << "\n";

                    // if point is not in the nearest cluster, move it
                    if (current_id_cluster != nearest_id_cluster) {

                        // if point is not at the initial dummy cluster
                        if (current_id_cluster != -1) {

                            // then remove it from all clusters it belongs to 
                            for (int j = 0; j < k_num_clusters; j++) {
                                if (list_clusters[j].get_id_cluster() == current_id_cluster) {
                                    list_clusters[j].remove_point_from_cluster(all_points[i].get_id_point());
                                }
                            }
                        }

                        // aditya implementation
                        for (int j = 0; j < k_num_clusters; j++) {
                            if (list_clusters[j].get_id_cluster() == nearest_id_cluster) {
                                list_clusters[j].insert_point_into_cluster(all_points[i]);
                                //std::cout << "i: " << i << ", j: " << j << "\n";
                            }
                        }
                        all_points[i].set_id_cluster(nearest_id_cluster);
                        //std::cout << "Set point " << all_points[i].get_id_point() << " to cluster " << nearest_id_cluster << "\n\n";
                        complete = false;
                    }
                }

                // recalculate the center of each cluster
                for (int i = 0; i < k_num_clusters; i++) {
                    
                    // size of the cluster
                    int num_points_in_cluster = list_clusters[i].get_num_points();

                    //std::cout << "num_points_in_cluster " << i << ": " << num_points_in_cluster << "\n";

                    for (int j = 0; j < num_attributes; j++) {
                        double sum = 0.0;

                        if (num_points_in_cluster > 0) {
                            for (int k = 0; k < num_points_in_cluster; k++) {
                                sum += list_clusters[i].get_point(k).get_attribute_value_at_index(j);
                            }
                            list_clusters[i].set_centroid_attribute_value(j, sum/num_points_in_cluster);
                        }
                    } 
                }

                // if complete or max iterations is hit, break the loop
                if (complete || iteration >= num_max_iterations) {
                    std::cout << "Clustering completed at iteration: " << iteration << "\n";
                    break;
                }

                // otherwise increment iteration
                iteration++;
            } /* end while */

            // ! only enable for small sets
            // print the id_points for each cluster
            for (int i = 0; i < k_num_clusters; i++) {
                std::cout << "Points in cluster " << list_clusters[i].get_id_cluster() << ": ";
                std::cout << list_clusters[i].get_num_points() << "\n";
                for (int j = 0; j < list_clusters[i].get_num_points(); j++) {
                    std::cout << list_clusters[i].get_point(j).get_id_point() << ", ";
                    // std::cout << " < ";
                    // for ( double value : list_clusters[i].get_point(j).get_attribute_values()) {
                    //     std::cout << value << ", ";
                    // }
                    // std::cout << ">" << "\n";

                    // list_clusters[i].get_point(j).print_point();
                }
                std::cout << "\n";
            }
            std::cout << "=============" << "\n";

            // ! only enable for small sets
            // for (int i = 0; i< k_num_clusters; i++) {
            //     std::cout << "Cluster "<< list_clusters[i].get_id_cluster() << " centroid : ";
            //     for (int j = 0; j < num_attributes; j++){
            //         std::cout << list_clusters[i].get_centroid_attribute_value(j) << " ";     //Output to console
            //     }
            //     std::cout << "\n";
            // }
        } /* end cluster() */
}; /* end class */

#endif
