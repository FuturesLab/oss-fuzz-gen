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

static void free_fn(void *data) {
    // Example free function for array_list_new2
    free(data);
}

extern "C" int LLVMFuzzerTestOneInput_35(const uint8_t *Data, size_t Size) {
    if (Size < sizeof(size_t) * 3) {
        return 0;
    }

    // Extract parameters from the input data
    size_t idx1 = reinterpret_cast<const size_t*>(Data)[0];
    size_t idx2 = reinterpret_cast<const size_t*>(Data)[1];
    size_t count = reinterpret_cast<const size_t*>(Data)[2];
    Data += sizeof(size_t) * 3;
    Size -= sizeof(size_t) * 3;

    // Create a dummy array_list
    struct array_list *list = array_list_new2(free_fn, 10);
    if (!list) {
        return 0;
    }

    // Test array_list_put_idx
    void *data = malloc(Size);
    if (data) {
        memcpy(data, Data, Size);

        // Begin mutation: Producer.REPLACE_ARG_MUTATOR - Replaced argument 1 of array_list_put_idx
        array_list_put_idx(list, Size, data);
        // End mutation: Producer.REPLACE_ARG_MUTATOR


    }

    // Test array_list_del_idx
    array_list_del_idx(list, idx2, count);

    // Test array_list_length
    size_t length = array_list_length(list);

    // Test array_list_get_idx
    if (length > 0) {
        void *element = array_list_get_idx(list, idx1 % length);
    }

    // Test array_list_shrink
    array_list_shrink(list, 5);

    // Cleanup
    array_list_free(list);

    return 0;
}