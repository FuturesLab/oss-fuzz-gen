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
#include "/src/json-c/json_object.h"
#include "/src/json-c/arraylist.h"

static int compare_json_object(const void *a, const void *b) {
    int intA = json_object_get_int(*(const struct json_object **)a);
    int intB = json_object_get_int(*(const struct json_object **)b);
    return (intA > intB) - (intA < intB);
}

static int compare_int_with_json_object(const void *a, const void *b) {
    int intA = *(const int *)a;
    int intB = json_object_get_int(*(const struct json_object **)b);
    return (intA > intB) - (intA < intB);
}

extern "C" int LLVMFuzzerTestOneInput_9(const uint8_t *Data, size_t Size) {
    // Create a new JSON array
    struct json_object *jsonArray = json_object_new_array();
    if (!jsonArray) return 0;

    // Populate the JSON array with some data from the input
    size_t numElements = Size / sizeof(int);
    for (size_t i = 0; i < numElements; ++i) {
        int value;
        memcpy(&value, Data + i * sizeof(int), sizeof(int));
        json_object_array_add(jsonArray, json_object_new_int(value));
    }

    // Sort the JSON array using a simple comparison function
    json_object_array_sort(jsonArray, compare_json_object);

    // Retrieve the underlying array list
    struct array_list *arrList = json_object_get_array(jsonArray);
    if (arrList) {
        // Sort the array list using the same comparison function
        array_list_sort(arrList, compare_json_object);

        // Perform a binary search on the sorted array list
        if (numElements > 0) {
            int searchValue;
            memcpy(&searchValue, Data, sizeof(int));
            const void *key = &searchValue;
            void *result = array_list_bsearch(&key, arrList, compare_int_with_json_object);
        }
    }

    // Clean up
    json_object_put(jsonArray);

    return 0;
}