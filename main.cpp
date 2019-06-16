#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <functional>

#define VECTOR_SIZE 100000

using namespace std;

void test_vector() {
        auto c_begin = chrono::steady_clock::now();


        vector<int> intVector(VECTOR_SIZE);


        int result_a = 0;

        for(int i = 0; i < VECTOR_SIZE; i++){
            result_a += intVector[i];
        }

        auto c_end = chrono::steady_clock::now();
        chrono::duration<double> diff = c_end - c_begin;
        printf("elapsed time %f\n", diff.count());
    }

void test_array() {
        auto c_begin = chrono::steady_clock::now();

        int* intArray = (int *)malloc(sizeof(int) * VECTOR_SIZE);

        int result_a = 0;

        for(int i = 0; i < VECTOR_SIZE; i++){
            result_a += intArray[i];
        }



        auto c_end = chrono::steady_clock::now();
        chrono::duration<double> diff = c_end - c_begin;
        printf("elapsed time %f\n", diff.count());

        free(intArray);
    }

int main() {

    for(int i = 0; i < 100; i++){
        test_vector();
        test_array();
        printf("#######################\n");
    }


    return 0;
}