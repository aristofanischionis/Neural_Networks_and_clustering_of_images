#include <iostream>
#include <vector>
#include "headers/common.hpp"
#include "headers/handle-input.hpp"
#include "headers/search.hpp"
#include "headers/hashtable.hpp"
using namespace std;

int main(int argc, char **argv) {
    uint32_t number_of_images = 0;
    uint32_t number_of_query_images = 0;
    uint64_t d = 0;
    uint64_t d_original = 0;
    int k = SMALL_K;
	int l = SMALL_L;
    string output_file, query_file_original_space, query_file_new_space;
    ofstream o_file;
    // This give big values for w
    w = 400;
    // calculateW_Component(d, number_of_images, number_of_query_images);
    handleInput(argc, argv, &number_of_images, &d, &d_original, &k, &l, &output_file, &query_file_original_space, &query_file_new_space);
    // open output file
    o_file.open(output_file);
    if (!o_file.is_open()) {
        cerr << "Output file can't be opened" << endl;
        exit(ERROR);
    }
    do {
        readFile(query_file_new_space, QUERY_FILE, &number_of_query_images, &d, k, l);
        readFileOriginalSpace(query_file_original_space, QUERY_FILE, &number_of_query_images, &d_original, k, l);
        // printFiles(number_of_images, number_of_query_images, d_original, d);
        for (uint32_t q_num = 0; q_num < number_of_query_images; q_num++) {
            approximateN_NNs(&o_file, d_original, d, k, l, q_num, number_of_images);
        }
        writeLastMeta(&o_file, number_of_query_images, d_original);
        w = 400;
        // calculateW_Component(d, number_of_images, number_of_query_images);
        o_file.close();
        
        handleReExecution(&number_of_images, &d, &d_original, &k, &l, &output_file, &query_file_original_space, &query_file_new_space);
        // open output file
        o_file.open(output_file);
        if (!o_file.is_open()){
            cerr << "Output file can't be opened" << endl;
            exit(ERROR);
        }
    } while (true);
    o_file.close();
    
    for (uint32_t i = 0; i < number_of_images;i++) {
        delete[] all_images[i];
    }
    delete[] all_images;
    for (uint32_t i = 0; i < number_of_query_images;i++) {
        delete[] query_images[i];
    }
    delete[] query_images;
    for (uint32_t i = 0; i < number_of_images;i++) {
        delete[] all_images_original_space[i];
    }
    delete[] all_images_original_space;
    for (uint32_t i = 0; i < number_of_query_images;i++) {
        delete[] query_images_original_space[i];
    }
    delete[] query_images_original_space;
    deleteHashtable(l, number_of_images);
    return SUCCESS;
}