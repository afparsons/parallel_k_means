#ifndef VECTORIZER
#define VECTORIZER

#include <vector>
#include <string>
#include <map>
#include <unordered_set>
#include <iostream>
#include <algorithm>

// tokenizing
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>

// stemming
#include "oleander/stemming/english_stem.h"
#include <sstream>
#include <fstream>
#include <codecvt>

// parallelizing
#include <omp.h>

#include "point.cpp"

class Vectorizer {
    private:
    /* === === OBJECT DATA === === */
        std::vector<std::string> file_paths;
        std::unordered_set<std::wstring> stopwords;
        std::map<std::wstring, int> word_map;
        int total_num_tokens;

    /* === === FUNCTIONS === === */

         /**
         * read_file_to_wstring()
         */
        std::wstring read_file_to_wstring(const char* filename) {
            // std::cout << "Reading: " << filename << "\n";
            std::wifstream wif(filename);
            wif.imbue(std::locale(std::locale(), new std::codecvt_utf8<wchar_t>));
            std::wstringstream wss;
            wss << wif.rdbuf();
            std::wstring contents = wss.str();
            std::transform(contents.begin(), contents.end(), contents.begin(), ::tolower);
            contents.erase(std::remove(contents.begin(), contents.end(), '\n'), contents.end());
            return contents;
        }

        /**
         * tokenize()
         * TODO: improve this
         */
        std::vector<std::wstring> tokenize(std::wstring input_wstring) {
            std::vector<std::wstring> word_tokens;
            // https://theboostcpplibraries.com/boost.tokenizer#ex.tokenizer_05
            typedef boost::tokenizer<boost::char_separator<wchar_t>,
            std::wstring::const_iterator, std::wstring> tokenizer;
            boost::char_separator<wchar_t> sep{L" "};
            tokenizer tok{input_wstring, sep};
            for (const auto &token : tok) {
                word_tokens.push_back(token);
            }
            return word_tokens;
        }
        
        /**
         * stem()
         */
        std::vector<std::wstring> stem(std::vector<std::wstring> word_tokens) {
            std::vector<std::wstring> word_stems;
            stemming::english_stem<> StemEnglish;
            for (std::wstring word : word_tokens) {
                StemEnglish(word);
                auto search = stopwords.find(word);
                if (search == stopwords.end()) {
                    word_stems.push_back(word);
                }
            }
            return word_stems;
        }

        /**
         * load_stopwords()
         */
        int load_stopwords(std::string stopword_filepath) {
            std::wifstream stopwords_file(stopword_filepath);
            std::wstring line;
            while (std::getline(stopwords_file, line))
            {
                std::wistringstream iss(line);
                stopwords.insert(line);
            }
            return 0;
        }

        /**
         * build_global_word_map()
         * ! only works if there are enough threads!
         */
        int build_global_word_map() {
            // #pragma omp declare reduction (merge : std::vector<std::wstring> : omp_out.insert(omp_out.end(), omp_in.begin(), omp_in.end()))
            std::vector<std::wstring> word_vector;
            int i;
            // #pragma omp parallel for reduction(merge: word_vector)
            
            // for each file in filepaths
            for (i = 0; i < file_paths.size(); i++) {

                // extract words from file
                word_vector = stem(tokenize(read_file_to_wstring(file_paths[i].c_str())));

                // create a set of all the words from this local string
                std::unordered_set<std::wstring> local_word_set;

                // add terms to local_word_set
                for (std::wstring word : word_vector) {
                    local_word_set.insert(word);
                }

                // if a term isn't in the global word_map, add it
                // if it is already there, increment its document count value
                for (std::wstring word : local_word_set) {
                    if (word_map.insert(std::pair<std::wstring, int> (word, 1)).second == false) {
                        word_map[word]++;
                    }
                }
            }
            total_num_tokens = word_map.size();
            return 0;
        }

        /**
         * build_local_word_bag()
         */
        std::map<std::wstring, int> build_local_word_bag(std::vector<std::wstring> string_stems) {
            std::map<std::wstring, int> word_bag = word_map;
            // ! reset values to 0
            // TODO: find faster way
            for (auto elem : word_bag) {
                word_bag[elem.first] = 0;
            }
            // print_map(word_bag);
            for (std::wstring stem : string_stems) {                 
                word_bag[stem]++;
            }
            return word_bag;
        }

        /**
         * build_local_tf_vector()
         */
        std::map<std::wstring, double> build_local_tf_vector(std::vector<std::wstring> string_stems) {
            int num_tokens = string_stems.size();
            std::map<std::wstring, int> word_bag = build_local_word_bag(string_stems);
            
            // std::cout << "Word bag:" << "\n";
            // print_map(word_bag);
            // std::cout << "----" << "\n";
            
            std::map<std::wstring, double> tf_vector;
            for (auto word : word_bag) {
                // std::wcout << word.second << "/" << num_tokens << "\n";
                // std::wcout << "TF: " << word.first << " : " << val << "\n";
                tf_vector.insert(std::pair<std::wstring, double>(word.first, double(word.second) / double(num_tokens)));
            }
            return tf_vector;
        }

        /**
         * calculate_idf_value()
         * TODO: remove excess double casts
         */
        double calculate_idf_value(std::wstring word) {
            return double(std::log(double(file_paths.size()) / double(word_map[word])));
        }

        /**
         * build_tf_idf()
         */
        std::map<std::wstring, double> build_tf_idf(std::vector<std::wstring> string_stems) {
            std::map<std::wstring, double> local_tf_vector = build_local_tf_vector(string_stems);
            std::map<std::wstring, double> tf_idf;
            for (auto word : local_tf_vector) {
                double tf_idf_value = word.second * calculate_idf_value(word.first);
                tf_idf.insert(std::pair<std::wstring, double>(word.first, tf_idf_value));
            }
            return tf_idf;
        }

        void print_map(std::map<std::wstring, int> map) {
            for (auto elem : map) {
                std::wcout << "< "<< elem.first << ", " << elem.second << " >\n";
            }
        }

        /**
         * https://stackoverflow.com/a/771463
         */
        template <typename M, typename V> 
        void map_values_to_vector( const  M & m, V & v ) {
            for( typename M::const_iterator it = m.begin(); it != m.end(); ++it ) {
                v.push_back( it->second );
            }
        }

    public:
        /**
         * Constructor.
         */
        Vectorizer(std::vector<std::string> input_file_paths, std::string stopword_filepath) {

            file_paths = input_file_paths;
            load_stopwords(stopword_filepath);
            build_global_word_map();
            std::cout << "Word map size: " << get_word_map_size() << "\n";
        }

        /**
         * go()
         * TODO: better name
         */
        std::vector<Point> go() {
            std::vector<Point> all_points;
            for (int i = 0; i < file_paths.size(); i++) {
                std::vector<std::wstring> word_vector = stem(tokenize(read_file_to_wstring(file_paths[i].c_str())));
                // TODO: better error handling
                if (word_vector.size() > 0 ) {
                    std::vector<double> attribute_values;
                    map_values_to_vector(build_tf_idf(word_vector), attribute_values);
                    all_points.push_back(Point(i, attribute_values));
                }
            }
            return all_points;
        }

        /**
         * 
         */
        void print_word_map() {
            for (auto elem : word_map) {
                std::wcout << "< "<< elem.first << ", " << elem.second << " >\n";
            }
        }

        /**
         * 
         */
        int get_word_map_size() {
            return word_map.size();
        }

};

#endif