/**
 * Andrew Parsons
 */

/* === === === INCLUDES === === === === === === === === === */
#include <iostream>             // cout
#include <random>               // Mersenne Twister
#include <vector>               // vector

/* === === === CLASS DEFINITION === === === === === === === === === */
class Attribute_Value_Generator {
    public:
        /**
         * generate_int_array().
         */
        std::vector<double> generate_double_vector(int size_n, int lower_bound, int upper_bound) {
            // create vector
            std::vector<double> attribute_values;

            // fill array with random numbers
            std::random_device rd;
            std::mt19937 engine(rd());
            std::uniform_int_distribution<> uniform_int_distribute(lower_bound, upper_bound);
            for (int i = 0; i < size_n; i++) {
                attribute_values.push_back(uniform_int_distribute(engine));
            }

            return attribute_values;
        }

        void print_double_vector(std::vector<double> vector) {
            for (double element : vector) {
                std::cout << element << ", ";
            }
        }
};