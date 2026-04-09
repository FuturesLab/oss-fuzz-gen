#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <htslib/hfile.h> // Correct path for hFILE

int LLVMFuzzerTestOneInput_21(const uint8_t *data, size_t size) {
    // Ensure there is enough data to work with
    if (size < sizeof(size_t)) {
        return 0;
    }

    // Initialize hFILE structure
    hFILE *file = (hFILE *)malloc(sizeof(hFILE));
    if (file == NULL) {
        return 0;
    }

    // Initialize size_t variable
    size_t buffer_size = 0;

    // Call the function-under-test
    char *buffer = hfile_mem_get_buffer(file, &buffer_size);

    // Free allocated memory
    free(file);

    return 0;
}