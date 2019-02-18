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
#include <iostream>     // cout
#include <random>       // Mersenne Twister
#include <vector>       // vector
#include <map>          // map    
#include <set>          // set    
#include <cstring>       // string, strtok

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

        std::vector<std::string> generate_string_vector(int size_n, std::vector<std::string> corpus) {
            
            std::vector<std::string> string_vector;

            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_real_distribution<> uniform_int_distribute(0, corpus.size());
            for (int i = 0; i < size_n; i++) {
                string_vector.push_back(corpus[uniform_int_distribute(engine)]);
            }
            
            // for (std::string word : string_vector) {
            //     std::cout << word << ", ";
            // }

            return string_vector;
        }

        std::string generate_string(int size_n, std::vector<std::string> corpus) {
            
            std::string final_string;

            // randomly pull from corpus
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_real_distribution<> uniform_int_distribute(0, corpus.size());

            // build string
            for (int i = 0; i < size_n; i++) {
                final_string += corpus[uniform_int_distribute(engine)] + " ";
            }

            return final_string;
        }


        std::vector<std::string> tokenize_string(std::string input_string) {
            char * ptr_token = std::strtok((char*) input_string.c_str(), " .:;?!&()-+=,/\|{}[]''");
            std::vector<std::string> string_vector;

            while (ptr_token != NULL) {
                string_vector.push_back(ptr_token);
                // std::cout << ptr_token << "\n";
                ptr_token = std::strtok(NULL, " .:;?!&()-+=,/\|{}[]''");
            }
            return string_vector;
        }

        std::set<std::string> string_vector_to_set(std::vector<std::string> string_vector) {
            std::set<std::string> word_set;
            for (std::string word : string_vector) {
                word_set.insert(word);
            }
            return word_set;
        }

        std::map<std::string, int> set_to_map(std::set<std::string> word_set) {
            std::map<std::string, int> word_map;
            for (std::string word : word_set) {                
                word_map.insert(std::pair<std::string,int>(word, 0));
            }
            return word_map;
        }

        std::vector<int> string_to_int_vector(std::string input_string) {
            std::vector<std::string> word_vec = tokenize_string(input_string);
            std::set<std::string> word_set = string_vector_to_set(word_vec);
            std::map<std::string, int> word_map = set_to_map(word_set);

            for (std::string word : word_vec) {
                word_map[word]++;
            }

            

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

        /**
         * print_string_vector()
         * @param std::vector<std::string>, vector: vector to print
         * 
         * Prints a comma-delimited vector
         */
        void print_string_vector(std::vector<std::string> vector) {
            for (std::string element : vector) {
                std::cout << element << ", ";
            }
        }
};