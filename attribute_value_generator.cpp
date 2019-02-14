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
 * This class defines an attribute value generator.
 * The generator's primary function "generate_double_vector" can generate\
 * vectors containing `n` random doubles between the lower and upper bounds.  
 */

/* === === === INCLUDES === === === === === === */
#include <iostream>             // cout
#include <random>               // Mersenne Twister
#include <vector>               // vector

/* === === === CLASS DEFINITION === === === === === === === === === */
class Attribute_Value_Generator {
    public:
        /**
         * generate_int_array()
         * @param int, size_n:                              the number of elements in the vector
         * @param int, lower_bound:                         the lowest possible element value
         * @param int, upper_bound:                         the highest possible element value
         * @return: std::vector<double>, attribute_values:  the vector of random doubles
         */
        std::vector<double> generate_double_vector(int size_n, int lower_bound, int upper_bound) {
            // create vector
            std::vector<double> attribute_values;

            // fill array with random numbers
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_real_distribution<> uniform_real_distribute(lower_bound, upper_bound);
            for (int i = 0; i < size_n; i++) {
                attribute_values.push_back(uniform_real_distribute(engine));
            }

            return attribute_values;
        }

        /**
         * print_double_vector()
         * @param std::vector<double>, vector: vector to print
         * 
         * Prints a comma-delimited vector
         */
        void print_double_vector(std::vector<double> vector) {
            for (double element : vector) {
                std::cout << element << ", ";
            }
        }
};