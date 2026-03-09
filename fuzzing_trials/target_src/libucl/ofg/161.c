#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_161(const uint8_t *data, size_t size) {
    // Initialize variables
    ucl_object_t *root_obj = NULL;
    const ucl_object_t *result = NULL;
    char *path = NULL;
    char delimiter = '.';

    // Ensure the data size is sufficient to create a valid path string
    if (size < 2) {
        return 0;
    }

    // Allocate memory for the path string
    path = (char *)malloc(size + 1);
    if (path == NULL) {
        return 0;
    }

    // Copy data to path and null-terminate
    memcpy(path, data, size);
    path[size] = '\0';

    // Create a dummy UCL object for testing
    root_obj = ucl_object_typed_new(UCL_OBJECT);
    if (root_obj == NULL) {
        free(path);
        return 0;
    }

    // Call the function-under-test
    result = ucl_object_lookup_path_char(root_obj, path, delimiter);

    // Clean up
    ucl_object_unref(root_obj);
    free(path);

    return 0;
}