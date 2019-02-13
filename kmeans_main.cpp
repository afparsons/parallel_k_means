/**
 * Andrew Parsons.
 * Based heavily upon:
 * https://github.com/aditya1601/kmeans-clustering-cpp/blob/master/kmeans.cpp
 * https://github.com/marcoscastro/kmeans/blob/master/kmeans.cpp
 */

#include <iostream>
#include <vector>
#include <omp.h>

#include "attribute_value_generator.cpp"
#include "kmeans.cpp"

int main(int argc, char *argv[])
{
    int num_points, num_attributes, k_num_clusters, iterations;
	sscanf (argv[1], "%d", &num_points);
    sscanf (argv[2], "%d", &num_attributes);
    sscanf (argv[3], "%d", &k_num_clusters);
    sscanf (argv[4], "%d", &iterations);

    Attribute_Value_Generator attribute_value_generator = Attribute_Value_Generator();
    
    std::vector<Point> all_points;
    for (int i = 0; i < num_points; i++) {
        std::vector<double> attribute_values = attribute_value_generator.generate_double_vector(num_attributes, 1, 9);
        Point point(i, attribute_values);
        all_points.push_back(point);
    }

    // for (Point point : all_points) {
    //     std::cout << "Point " << point.get_id_point() << ": < ";
    //     attribute_value_generator.print_double_vector(point.get_attribute_values());
    //     std::cout << "> @ " << point.get_id_cluster() << "\n";
    // }

    KMeans kmeans(k_num_clusters, iterations);
    double duration, start = omp_get_wtime();
    kmeans.cluster(all_points);
    duration = omp_get_wtime() - start;
    std::cout << "Duration: " << duration << "\n";
    return 0;
}
