#include "/src/libucl/include/ucl.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include for memcpy

int LLVMFuzzerTestOneInput_225(const uint8_t *data, size_t size) {
    // Initialize two ucl_object_t pointers
    ucl_object_t *array_obj = ucl_object_new_full(UCL_ARRAY, NULL);

    // Ensure the data is non-null and size is reasonable
    if (size > 0) {
        // Create a string from the input data for the search object
        char *input_str = (char *)malloc(size + 1);
        if (input_str == NULL) {
            ucl_object_unref(array_obj);
            return 0;
        }
        memcpy(input_str, data, size);
        input_str[size] = '\0'; // Null-terminate

        // Create a UCL string object from the input string
        ucl_object_t *search_obj = ucl_object_fromstring_common(input_str, size, 0);

        // Add the search object to the array object
        ucl_array_append(array_obj, search_obj);

        // Call the function-under-test
        unsigned int index = ucl_array_index_of(array_obj, search_obj);

        // Free the allocated string
        free(input_str);
    }

    // Clean up
    ucl_object_unref(array_obj);

    return 0;
}