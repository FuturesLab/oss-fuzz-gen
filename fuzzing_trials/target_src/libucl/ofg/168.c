#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <ucl.h>

int LLVMFuzzerTestOneInput_168(const uint8_t *data, size_t size) {
    // Initialize variables
    ucl_object_t *obj;
    const char *key;
    size_t key_len;
    
    // Ensure the size is large enough to extract a key
    if (size < 1) {
        return 0;
    }
    
    // Allocate a new UCL object
    obj = ucl_object_new();

    // Use the first byte of data as the key length, ensuring it's within bounds
    key_len = data[0] % size;
    
    // Ensure there's enough data for the key
    if (key_len + 1 > size) {
        ucl_object_unref(obj);
        return 0;
    }

    // Extract the key from the data
    key = (const char *)(data + 1);

    // Call the function-under-test
    ucl_object_t *result = ucl_object_pop_keyl(obj, key, key_len);

    // Clean up
    if (result != NULL) {
        ucl_object_unref(result);
    }
    ucl_object_unref(obj);

    return 0;
}