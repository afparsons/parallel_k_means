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
 * === === === kmeans_main.cpp === === === === === === === === === ===
 * 
 * This file holds the main and acts as the program mediator.
 * https://refactoring.guru/design-patterns/mediator
 */

/* === === === INCLUDES === === === === === === */
#include <iostream>
#include <vector>
#include <omp.h>

/* from GitHub */
#include "../include/tinydir.h"

/* custom classes */
#include "attribute_value_generator.cpp"
#include "kmeans.cpp"
#include "vectorizer.cpp"

/* === === === FUNCTIONS === === === === === === */

/**
 * main()
 * @param int, num_points:      the number of points to generate for the dataset
 * @param int, num_attributes:  the number of attributes for each point
 * @param int, k_num_clusters:  the number of clusters to calculate
 * @param int, max_iterations:  the maximum number of clustering iterations 
 * 
 * (1) reads in the parameters and stores them as variables.
 * (2) instantiates a vector generator
 * (3) randomly assigns attributes to each point
 * (4) instantiates a KMeans object
 * (5) runs clustering
 * (6) prints time taken
 */
int main(int argc, char *argv[])
{
    int num_points, num_attributes, k_num_clusters, max_iterations;
    // TODO: replace sscanf with getopt()
	sscanf (argv[1], "%d", &num_points);
    sscanf (argv[2], "%d", &num_attributes);
    sscanf (argv[3], "%d", &k_num_clusters);
    sscanf (argv[4], "%d", &max_iterations);

    // Attribute_Value_Generator attribute_value_generator = Attribute_Value_Generator();
    // std::vector<std::string> corpus = {"apples", "bananas", "cherries", "donuts", "eclair", "froyo"};
    // attribute_value_generator.generate_string_vector(10, corpus);
    // std::cout << "============" << "\n";
    // // attribute_value_generator.reduce_string_to_word_set("Hello, my name is Andrew; I am a student at Kalamazoo College.");
    // std::vector<std::string> myVec = attribute_value_generator.tokenize_string("Test one two three, four five six; seven eight: nine.ten");
    // attribute_value_generator.string_vector_to_set(myVec);

    // std::vector<Point> all_points;
    // // generate double-points and add them to all_points
    // for (int i = 0; i < num_points; i++) {
    //     std::vector<double> attribute_values = attribute_value_generator.generate_double_vector(num_attributes, 1, 9);
    //     Point point(i, attribute_values);
    //     all_points.push_back(point);
    // }

    std::vector<std::string> file_paths;

    // const char * directory_path = "/home/andrew/comp_481/final/parallel_k_means/data/abcnews/headlines/";
    const char * directory_path = "/home/aparsons/Development/comp_481/final/data/abcnews/headlines_subset/";

    tinydir_dir dir;
    tinydir_open_sorted(&dir, directory_path);
    for (int i = 0; i < dir.n_files; i++) {
        tinydir_file file;
        tinydir_readfile_n(&dir, &file, i);
        std::stringstream ss;
        if (!file.is_dir) {
            ss << directory_path << file.name;
            file_paths.push_back(ss.str());
            // std::cout << directory_path << file.name << "\n";
        }
    }
    tinydir_close(&dir);

    Vectorizer vectorizer = Vectorizer(file_paths, "../data/stopwords.txt");
    std::vector<Point> all_points = vectorizer.go();
    // vectorizer.print_word_map();

    // for (Point p : all_points) {
    //     p.print_point();
    // }

    KMeans kmeans(k_num_clusters, max_iterations);
    double duration, start = omp_get_wtime();
    kmeans.cluster(all_points);
    duration = omp_get_wtime() - start;
    std::cout << "Duration: " << duration << "\n";
    return 0;
}


// std::vector<std::string> get_filepaths_in_directory(std::string directory) {
//     auto dir = std::opendir(directory.c_str());
    
// }