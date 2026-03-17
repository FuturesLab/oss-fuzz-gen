#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include string.h for memcpy
#include <gpac/isomedia.h>

int LLVMFuzzerTestOneInput_214(const uint8_t *data, size_t size) {
    GF_ISOFile *file = NULL;
    GF_Err result;

    // Create a temporary buffer to hold the input data
    char *temp_buffer = (char *)malloc(size + 1);
    if (temp_buffer == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    // Copy the input data to the temporary buffer
    memcpy(temp_buffer, data, size);
    temp_buffer[size] = '\0'; // Null-terminate the buffer

    // Open the ISO file from the buffer
    file = gf_isom_open(temp_buffer, GF_ISOM_OPEN_READ, NULL);
    if (file == NULL) {
        free(temp_buffer);
        return 0; // Exit if file opening fails
    }

    // Call the function-under-test
    result = gf_isom_enable_mfra(file);

    // Clean up
    gf_isom_close(file);
    free(temp_buffer);

    return 0;
}