#include <stdint.h>
#include <stdlib.h>
#include <ucl.h>

// Include the UCL library header for UCL_TYPE_MAX
#include <ucl.h>

// Define UCL_TYPE_MAX if not defined
#ifndef UCL_TYPE_MAX
#define UCL_TYPE_MAX UCL_OBJECT // Assuming UCL_OBJECT is the last valid type
#endif

int LLVMFuzzerTestOneInput_185(const uint8_t *data, size_t size) {
    // Ensure we have enough data to create two ucl_object_t pointers
    if (size < 2 * sizeof(ucl_object_t)) {
        return 0;
    }

    // Allocate memory for two ucl_object_t objects
    ucl_object_t *obj1 = (ucl_object_t *)malloc(sizeof(ucl_object_t));
    ucl_object_t *obj2 = (ucl_object_t *)malloc(sizeof(ucl_object_t));

    if (obj1 == NULL || obj2 == NULL) {
        free(obj1);
        free(obj2);
        return 0;
    }

    // Initialize the objects with some data from the input
    // Correct the constant to a valid maximum type value
    obj1->type = (ucl_type_t)(data[0] % UCL_TYPE_MAX);
    obj2->type = (ucl_type_t)(data[1] % UCL_TYPE_MAX);

    // Create pointers to the objects
    const ucl_object_t *obj_ptr1 = obj1;
    const ucl_object_t *obj_ptr2 = obj2;

    // Call the function under test
    int result = ucl_object_compare_qsort(&obj_ptr1, &obj_ptr2);

    // Clean up
    free(obj1);
    free(obj2);

    return 0;
}