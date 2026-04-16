#include <stdint.h>
#include <stddef.h>
#include "sqlite3.h"
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>  // Include this for malloc and free

int LLVMFuzzerTestOneInput_711(const uint8_t *data, size_t size) {
    // Ensure the input data is not empty
    if (size == 0) {
        return 0;
    }

    // Calculate the number of uint16_t elements needed
    size_t utf16_size = (size / 2) + 1;  // +1 for null-termination

    // Allocate memory for the input string and ensure it is null-terminated
    uint16_t *input = (uint16_t *)malloc(utf16_size * sizeof(uint16_t));
    if (input == NULL) {
        return 0;
    }

    // Copy the input data as UTF-16 and add null-termination
    for (size_t i = 0; i < size / 2; i++) {
        input[i] = ((uint16_t)data[2 * i] | ((uint16_t)data[2 * i + 1] << 8));
    }
    input[utf16_size - 1] = 0;

    // Call the function-under-test
    int result = sqlite3_complete16(input);

    // Free allocated memory
    free(input);

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

    LLVMFuzzerTestOneInput_711(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
