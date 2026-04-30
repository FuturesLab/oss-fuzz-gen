#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

extern "C" {
    // Declare the function under test since the header is not available
    char* icalmemory_strdup(const char *str);
}

extern "C" int LLVMFuzzerTestOneInput_83(const uint8_t *data, size_t size) {
    // Ensure the input data is null-terminated to safely pass as a string
    if (size == 0 || data == NULL) {
        return 0; // Exit if there's no data to process
    }

    // Allocate memory for the input string, ensuring it is null-terminated
    char *input = (char *)malloc(size + 1);
    if (input == NULL) {
        return 0; // Exit if memory allocation fails
    }
    
    memcpy(input, data, size);
    input[size] = '\0'; // Null-terminate the string

    // Check if the input is a valid string before calling the function
    if (strlen(input) > 0) {
        // Call the function-under-test
        char *result = icalmemory_strdup(input);

        // Free the duplicated string if it was successfully created
        if (result != NULL) {
            free(result);
        }
    }

    // Free the allocated input
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

    LLVMFuzzerTestOneInput_83(data + 2, (size_t)(size - 2));

    free(data);
    fclose(f);
    return 0;
}
#endif
