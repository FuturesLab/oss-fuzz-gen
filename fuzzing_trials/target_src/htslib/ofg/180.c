#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h> // Include this header for memcpy

// Function-under-test
void hts_free_180(void *ptr) {
    // Implement a simple free operation
    if (ptr) {
        free(ptr);
    }
}

int LLVMFuzzerTestOneInput_180(const uint8_t *data, size_t size) {
    // Ensure size is greater than 0 to effectively invoke the function under test
    if (size == 0) {
        return 0;
    }

    // Allocate memory to be freed
    void *ptr = malloc(size); // Ensure at least 1 byte is allocated

    // Ensure ptr is not NULL
    if (ptr == NULL) {
        return 0;
    }

    // Copy the fuzz data into the allocated memory
    memcpy(ptr, data, size);

    // Call the function-under-test
    hts_free_180(ptr);

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

    LLVMFuzzerTestOneInput_180(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
