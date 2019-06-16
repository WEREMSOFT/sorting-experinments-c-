#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>


using namespace std;

int compare(const int a, const int b) { return a > b; }
int compare_array(const void *a, const void *b) { return *(int *)b - *(int *)a; }


int main() {
    const int VECTOR_SIZE = 10000000;

    {

        vector<int> intVector(VECTOR_SIZE);

        for(int i = 0; i < VECTOR_SIZE; i++){
            intVector[i] = i;
        }


        auto c_begin = std::chrono::steady_clock::now();
        int result_a = 0;

        sort(intVector.begin(), intVector.end(), compare);


        auto c_end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = c_end - c_begin;
        printf("elapsed time %f\n", diff.count());

    }

    {

        void* memory = malloc(sizeof(int) * VECTOR_SIZE);

        int* intArray = (int*)memory;

        for(int i = 0; i < VECTOR_SIZE; i++){
            intArray[i] = i;
        }

        auto c_begin = std::chrono::steady_clock::now();

        qsort(intArray, VECTOR_SIZE, sizeof(int), compare_array);

        auto c_end = std::chrono::steady_clock::now();
        std::chrono::duration<double> diff = c_end - c_begin;
        printf("elapsed time %f\n", diff.count());

        free(memory);
    }


    return 0;
}