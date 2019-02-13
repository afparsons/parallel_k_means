/**
 * Sequential K Means
 * Andrew Parsons
 * 
 */

/* === === === INCLUDES === === === === === === */

#include <vector> 

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
         *  ? ? ?
         */
        Point(int id_point, std::vector<double>& attribute_values) {
        //: id_point(id_point), attribute_values(attribute_values), attribute_set_size(attribute_values.size()) 
            
            this->id_point = id_point;
            this->attribute_values = attribute_values;
            this->attribute_set_size = attribute_values.size();
            this->id_cluster = -1;            
        // perhaps implement the 'Rule of Three/Five' for the constructor
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

};