#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cstdint>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>
#include "/src/json-c/arraylist.h"

extern "C" int LLVMFuzzerTestOneInput_20(const uint8_t *Data, size_t Size) {
    if (Size < 1) return 0;

    // Initialize a new array list
    struct array_list *al = array_list_new(nullptr);
    if (!al) return 0;

    // Choose an operation based on the first byte of the input
    uint8_t operation = Data[0];
    const uint8_t *inputData = Data + 1;
    size_t inputSize = Size - 1;

    switch (operation % 6) {
        case 0: { // Test array_list_new2
            if (inputSize < sizeof(int)) break;
            int initial_size;
            memcpy(&initial_size, inputData, sizeof(int));
            struct array_list *al2 = array_list_new2(nullptr, initial_size);
            if (al2) {
                array_list_free(al2);
            }
            break;
        }
        case 1: { // Test array_list_insert_idx
            if (inputSize < sizeof(size_t) + sizeof(void*)) break;
            size_t idx;
            void *data;
            memcpy(&idx, inputData, sizeof(size_t));
            memcpy(&data, inputData + sizeof(size_t), sizeof(void*));
            array_list_insert_idx(al, idx, data);
            break;
        }
        case 2: { // Test array_list_add
            if (inputSize < sizeof(void*)) break;
            void *data;
            memcpy(&data, inputData, sizeof(void*));
            array_list_add(al, data);
            break;
        }
        case 3: { // Test array_list_shrink
            if (inputSize < sizeof(size_t)) break;
            size_t empty_slots;
            memcpy(&empty_slots, inputData, sizeof(size_t));
            array_list_shrink(al, empty_slots);
            break;
        }
        case 4: { // Test array_list_free
            array_list_free(al);
            al = nullptr; // Avoid double free
            break;
        }
        case 5: { // Test combining operations
            if (inputSize < sizeof(size_t) + sizeof(void*)) break;
            size_t idx;
            void *data;
            memcpy(&idx, inputData, sizeof(size_t));
            memcpy(&data, inputData + sizeof(size_t), sizeof(void*));
            array_list_insert_idx(al, idx, data);
            array_list_add(al, data);
            array_list_shrink(al, idx);
            break;
        }
    }

    // Clean up
    if (al) {
        array_list_free(al);
    }
    return 0;
}