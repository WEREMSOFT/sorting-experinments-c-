#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>

#define VECTOR_SIZE 1000

using namespace std;

int compare(const int a, const int b) { return a > b; }
int compare_array(const void *a, const void *b) { return *(int *)b - *(int *)a; }


void test_vector() {

        vector<int> intVector(VECTOR_SIZE);

        for(int i = 0; i < VECTOR_SIZE; i++){
            intVector[i] = i;
        }


        auto c_begin = chrono::steady_clock::now();
        int result_a = 0;

        sort(intVector.begin(), intVector.end(), compare);


        auto c_end = chrono::steady_clock::now();
        chrono::duration<double> diff = c_end - c_begin;
        printf("std::sort elapsed time %f\n", diff.count());

    }

void test_array() {

        void* memory = malloc(sizeof(int) * VECTOR_SIZE);

        int* intArray = (int*)memory;

        for(int i = 0; i < VECTOR_SIZE; i++){
            intArray[i] = i;
        }

        auto c_begin = chrono::steady_clock::now();

        qsort(intArray, VECTOR_SIZE, sizeof(int), compare_array);

        auto c_end = chrono::steady_clock::now();
        chrono::duration<double> diff = c_end - c_begin;
        printf("qsort elapsed time.....%f\n", diff.count());

        free(memory);
    }

int main() {

    for(int i = 0; i < 1000; i++){
        test_vector();
        test_array();
        printf("#############\n");
    }


    return 0;
}