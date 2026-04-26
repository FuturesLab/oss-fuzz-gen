#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <cstring>

extern "C" {
    // Assuming the functions from icalmemory.h are available in some linked library
    // Declare the function prototype for icalmemory_append_char if it is not included via a header
    void icalmemory_append_char(char **current, char **end, size_t *buf_size, char append_char);
}

extern "C" int LLVMFuzzerTestOneInput_620(const uint8_t *data, size_t size) {
    if (size < 1) {
        return 0; // Ensure there's at least one byte for the char parameter
    }

    // Initialize buffer pointers
    char *current = nullptr;
    char *end = nullptr;

    // Initialize the buffer size
    size_t buf_size = 10; // Arbitrary non-zero size for initial buffer

    // Allocate memory for the buffer
    current = static_cast<char*>(malloc(buf_size));
    if (current == nullptr) {
        return 0; // Allocation failed
    }

    // Set end pointer to the end of the current buffer
    end = current + buf_size;

    // Iterate over the input data and append each byte as a character
    for (size_t i = 0; i < size; ++i) {
        char append_char = static_cast<char>(data[i]);

        // Call the function-under-test
        icalmemory_append_char(&current, &end, &buf_size, append_char);

        // If the buffer has been resized, ensure the end pointer is updated
        if (current >= end) {
            size_t new_size = buf_size * 2;
            char *new_current = static_cast<char*>(realloc(current, new_size));
            if (new_current == nullptr) {
                free(current);
                return 0; // Reallocation failed
            }
            current = new_current;
            end = current + new_size;
            buf_size = new_size;
        }
    }

    // Ensure the buffer is null-terminated if needed
    if (current < end) {
        *current = '\0';
    }

    // Free allocated memory
    free(current);

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

    LLVMFuzzerTestOneInput_620(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
