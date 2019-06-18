#include <iostream>
#include <ctime>
#include <unistd.h>
#include <stdlib.h>
#include <chrono>
#include <vector>
#include <functional>
#include <algorithm>

#define VECTOR_SIZE 100000

using namespace std;

struct Vector2 {
    int x;
    int y;
};

struct Entity {
    int id;
    unsigned int flags;
    Vector2 position;
    Vector2 lastPosition;
    Entity *parent;
};


int compare(Entity a, Entity b) { return a.id > b.id; }

int compare_array(const void *a, const void *b) {
    return ((Entity*) b)->id - ((Entity*) a)->id;
}

void test_vector() {

    vector<Entity> intVector(VECTOR_SIZE);

    for (int i = 0; i < VECTOR_SIZE; i++) {
        intVector[i].id = i;
    }


    int result_a = 0;

    auto c_begin = chrono::steady_clock::now();

    std::sort(intVector.begin(), intVector.end(), compare);

    auto c_end = chrono::steady_clock::now();
    chrono::duration<double> diff = c_end - c_begin;
    printf("vector elapsed time... %f...%d\n", diff.count(), result_a);
//    for (int i = 0; i < VECTOR_SIZE; i++) {
//        printf("vector: %d\n", intVector[i].id);
//    }
//    printf("----------\n");
}

void test_array() {

    void *memory = malloc(sizeof(Entity) * VECTOR_SIZE);

    Entity *intArray = (Entity *) memory;

    for (int i = 0; i < VECTOR_SIZE; i++) {
        intArray[i].id = i;
    }

    int result_a = 0;

    auto c_begin = chrono::steady_clock::now();

    std::qsort(intArray, VECTOR_SIZE, sizeof(Entity), compare_array);

    auto c_end = chrono::steady_clock::now();
    chrono::duration<double> diff = c_end - c_begin;
    printf("array elapsed time.....%f...%d\n", diff.count(), result_a);
//    for (int i = 0; i < VECTOR_SIZE; i++) {
//        printf("array: %d\n", intArray[i].id);
//    }
//    printf("----------\n");
    free(memory);
}

void test_handler() {
    void *memory = malloc(sizeof(Entity) * VECTOR_SIZE);

    Entity* intArray = (Entity*) memory;

    Entity* handlers[VECTOR_SIZE];

    for (int i = 0; i < VECTOR_SIZE; i++) {
        handlers[i] = &intArray[i];
    }

    int result_a = 0;

    auto c_begin = chrono::steady_clock::now();

    std::qsort(intArray, VECTOR_SIZE, sizeof(Entity), compare_array);

    auto c_end = chrono::steady_clock::now();
    chrono::duration<double> diff = c_end - c_begin;
    printf("handler elapsed time...%f...%d\n", diff.count(), result_a);

//    for (int i = 0; i < VECTOR_SIZE; i++) {
//        printf("handler: %d\n", intArray[i].id);
//    }
//    printf("----------\n");

    free(memory);
}

int main() {

    for (int i = 0; i < 1000; i++) {
        test_vector();
        test_array();
        test_handler();
        printf("#############\n");
    }


    return 0;
}