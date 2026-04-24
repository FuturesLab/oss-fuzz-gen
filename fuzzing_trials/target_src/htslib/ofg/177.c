#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h> // Include string.h for memcpy

// Assuming the definition of hFILE is available
typedef struct {
    // Add relevant fields here
    char *buffer;
    size_t buffer_size;
} hFILE;

// Mock implementation of hfile_mem_get_buffer_177
char * hfile_mem_get_buffer_177(hFILE *file, size_t *size) {
    if (file == NULL || size == NULL) {
        return NULL;
    }
    *size = file->buffer_size;
    return file->buffer;
}

int LLVMFuzzerTestOneInput_177(const uint8_t *data, size_t size) {
    if (size < sizeof(size_t)) {
        return 0; // Not enough data to proceed
    }

    // Initialize a hFILE object
    hFILE file;
    file.buffer_size = size;
    file.buffer = (char *)malloc(size);
    if (file.buffer == NULL) {
        return 0; // Memory allocation failed
    }

    // Copy data into the buffer
    memcpy(file.buffer, data, size);

    // Initialize a size_t variable
    size_t buffer_size = 0;

    // Call the function-under-test
    char *result = hfile_mem_get_buffer_177(&file, &buffer_size);

    // Check the result to ensure it is not NULL and matches expectations
    if (result != NULL && buffer_size == size) {
        // Perform some operation to ensure the result is used
        // For example, print the first byte if size is greater than 0
        if (buffer_size > 0) {
            printf("First byte: %c\n", result[0]);
        }
    }

    // Clean up
    free(file.buffer);

    return 0;
}
#ifdef INC_MAIN
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    FILE *f;
    uint8_t *data = NULL;
    long size;

    if(argc < 2)
        exit(0);

    f = fopen(argv[1], "rb");
    if(f == NULL)
        exit(0);

    fseek(f, 0, SEEK_END);

    size = ftell(f);
    rewind(f);

    if(size < 2 + 1)
        exit(0);

    data = (uint8_t *)malloc((size_t)size);
    if(data == NULL)
        exit(0);

    if(fread(data, (size_t)size, 1, f) != 1)
        exit(0);

    LLVMFuzzerTestOneInput_177(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
